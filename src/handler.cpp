#include "handler.hpp"
#include "resource.hpp"
#include "auth.hpp"

extern unordered_map<string, Resource *> g_record;
unsigned int g_count = 0;

/**
 * @brief Handler class constructor with method connection
 * 
 */
Handler::Handler(utility::string_t _url, http_listener_config _config) : m_listener(_url, _config)
{
    // Handler connection
    this->m_listener.support(methods::GET, bind(&Handler::handle_get, this, placeholders::_1));
    this->m_listener.support(methods::PUT, bind(&Handler::handle_put, this, placeholders::_1));
    this->m_listener.support(methods::POST, bind(&Handler::handle_post, this, placeholders::_1));
    this->m_listener.support(methods::DEL, bind(&Handler::handle_delete, this, placeholders::_1));
}

/**
 * @brief GET method request handler
 * 
 * @param _request Request object
 */
void Handler::handle_get(http_request _request)
{

    log(info) << "Request method: GET";
    string uri = _request.request_uri().to_string();
    vector<string> uri_tokens = string_split(uri, '/');
    string filtered_uri = make_path(uri_tokens);

    json::value j;
    json::value k = _request.extract_json().get();

    log(info) << "Reqeust URL : " << filtered_uri;
    log(info) << "Request Body : " << _request.to_string();
    record_print();

    // Response redfish version
    if (uri_tokens.size() == 1 && uri_tokens[0] == "redfish")
    {
        j[REDFISH_VERSION] = json::value::string(U(ODATA_SERVICE_ROOT_ID));
        _request.reply(status_codes::OK, j);
        return;
    }
    // Response redfish resource
    else
    {
        if (record_is_exist(filtered_uri))
            j = record_get_json(filtered_uri);
        else
            _request.reply(status_codes::NotFound);
    }

    // base64_encode();
    http_response response(status_codes::Created);
    response.headers().add("X-Auth-Token", json::value::string("12623963E803C264"));
    response.set_body(j);
    _request.reply(response);

    g_count++;
    log(info) << g_count;
}

/**
 * @brief DELETE request handler
 * 
 * @param _request Request object
 */
void Handler::handle_delete(http_request _request)
{

    cout << "handle_delete request" << endl;

    auto j = _request.extract_json().get();

    _request.reply(status_codes::NotImplemented, U("DELETE Request Response"));
}

/**
 * @brief PUT request handler
 * 
 * @param _request Request object
 */
void Handler::handle_put(http_request _request)
{

    cout << "handle_put request" << endl;

    auto j = _request.extract_json().get();

    _request.reply(status_codes::NotImplemented, U("PUT Request Response"));
}

/**
 * @brief POST request handler
 * 
 * @param _request Request object
 */
void Handler::handle_post(http_request _request)
{
    string uri = _request.request_uri().to_string();
    vector<string> uri_tokens = string_split(uri, '/');
    string filtered_uri = make_path(uri_tokens);
    json::value b = _request.extract_json().get();
    string user_name;
    string password;
    string odata_id;
    Account *account;

    log(info) << "Request method: POST";
    log(info) << "Reqeust uri : " << filtered_uri;

    // Account handling
    if (filtered_uri == ODATA_ACCOUNT_ID)
    {
        string role_id = "ReadOnly";
        bool enabled = true;

        // TODO try, catch문으로 변경 예정
        // Required account information check
        if (b.as_object().find("UserName") == b.as_object().end() && b.as_object().find("Password") == b.as_object().end())
        {
            _request.reply(status_codes::BadRequest);
            return;
        }
        else
        {
            user_name = b.at("UserName").as_string();
            password = b.at("Password").as_string();

            // Check password length enought
            if (password.size() < ((AccountService *)g_record[ODATA_ACCOUNT_SERVICE_ID])->min_password_length)
            {
                _request.reply(status_codes::BadRequest);
                return;
            }
            odata_id = ODATA_ACCOUNT_ID;
            odata_id = odata_id + '/' + user_name;

            // Check account exist
            if (record_is_exist(odata_id))
            {
                _request.reply(status_codes::Conflict);
                return;
            }
        }

        // Additinal account information check
        if (b.as_object().find("RoleId") != b.as_object().end())
        {
            odata_id = ODATA_ROLE_ID;
            role_id = b.at("RoleId").as_string();

            // Check role exist
            odata_id = odata_id + '/' + role_id;
            if (!record_is_exist(odata_id))
            {
                _request.reply(status_codes::BadRequest);
                return;
            }
        }
        if (b.as_object().find("Enabled") != b.as_object().end())
            enabled = b.at("Enabled").as_bool();

        // TODO id를 계정 이름 말고 숫자로 변경 필요
        odata_id = filtered_uri + '/' + user_name;
        account = new Account(odata_id, role_id);
        account->name = "User Account";
        account->user_name = user_name;
        account->id = user_name;
        account->password = password;
        account->enabled = enabled;
        account->locked = false;

        Collection *account_collection = (Collection *)g_record[ODATA_ACCOUNT_ID];
        account_collection->add_member(account);

        _request.reply(status_codes::Created);
    }
    else if (filtered_uri == ODATA_SESSION_ID)
    {
        try
        {
            user_name = b.at("UserName").as_string();
            password = b.at("Password").as_string();

            odata_id = ODATA_ACCOUNT_ID;
            odata_id = odata_id + '/' + user_name;

            // Check account exist
            if (!record_is_exist(odata_id))
            {
                _request.reply(status_codes::BadRequest);
                return;
            }

            account = (Account *)g_record[odata_id];
            // Check password correct
            if (account->password != password)
            {
                _request.reply(status_codes::BadRequest);
                return;
            }

            // TODO 세션 id 생성 필요
            string odata_id = ODATA_SESSION_ID;
            odata_id = odata_id + "/12623963E803C264";
            Session *session = new Session(odata_id, "12623963E803C264", account);
            session->start();

            http_response response(status_codes::Created);
            response.headers().add("X-Auth-Token", json::value::string("12623963E803C264"));
            response.set_body(json::value::object());

            _request.reply(response);
            return;
        }
        catch (json::json_exception &e)
        {
            _request.reply(status_codes::BadRequest);
        }
    }

    _request.reply(status_codes::BadRequest);
}

// http_response basic_response(status_codes _status)
// {
//     http_response response(_status);
//     response.headers().add("")

//     return response;
// }
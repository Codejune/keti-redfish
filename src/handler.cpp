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
        log(info) << filtered_uri;
        if (record_is_exist(filtered_uri))
            j = record_get_json(filtered_uri);
        else
            _request.reply(status_codes::NotFound);
    }

    // base64_encode();
    http_response response(status_codes::Created);
    response.headers().add("X-Auth-Token", json::value::string("12623963E803C264"));
    response.set_body(j);
    // log(info) << "Request Body : " << request.to_string();
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

    log(info) << "Request method: POST";
    log(info) << "Reqeust uri : " << filtered_uri;

    // Account handling
    if (filtered_uri == ODATA_ACCOUNT_ID)
    {
        string user_name;
        string password;
        string role_id = "ReadOnly";
        bool enabled = true;
        string odata_id;
        string temp;

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
            temp = ODATA_ACCOUNT_ID;
            temp = temp + '/' + user_name;

            // Check account exist
            if (record_is_exist(temp))
            {
                _request.reply(status_codes::Conflict);
                return;
            }
        }

        // Additinal account information check
        if (b.as_object().find("RoleId") != b.as_object().end())
        {
            temp = ODATA_ROLE_ID;
            role_id = b.at("RoleId").as_string();

            // Check role exist
            temp = temp + '/' + role_id;
            if (!record_is_exist(temp))
            {
                _request.reply(status_codes::BadRequest);
                return;
            }
        }
        if (b.as_object().find("Enabled") != b.as_object().end())
            enabled = b.at("Enabled").as_bool();

        // TODO id를 계정 이름 말고 숫자로 변경 필요
        odata_id = filtered_uri + '/' + user_name;
        log(info) << odata_id;
        Account *account = new Account(odata_id, role_id);
        account->name = "User Account";
        account->user_name = user_name;
        account->id = user_name;
        account->password = password;
        account->enabled = enabled;
        account->locked = false;

        Collection *accounts = (Collection *)g_record[ODATA_ACCOUNT_ID];
        accounts->add_member(account);

        _request.reply(status_codes::Created);
    }
    else if (filtered_uri == ODATA_SESSION_ID)
    {
    }

    _request.reply(status_codes::BadRequest);
}
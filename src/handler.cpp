#include "handler.hpp"
#include "resource.hpp"
#include "auth.hpp"

extern src::severity_logger<severity_level> lg;
extern unordered_map<string, Resource *> g_record;

/**
 * @brief Handler class constructor with method connection
 * 
 */
Handler::Handler(utility::string_t url, http_listener_config config) : m_listener(url, config)
{
    // Handler connection
    m_listener.support(methods::GET, bind(&Handler::handle_get, this, placeholders::_1));
    m_listener.support(methods::PUT, bind(&Handler::handle_put, this, placeholders::_1));
    m_listener.support(methods::POST, bind(&Handler::handle_post, this, placeholders::_1));
    m_listener.support(methods::DEL, bind(&Handler::handle_delete, this, placeholders::_1));
}

/**
 * @brief GET method request handler
 * 
 * @param request Request object
 */
void Handler::handle_get(http_request request)
{

    BOOST_LOG_SEV(lg, info) << "get request recieve";
    string uri = request.request_uri().to_string();
    vector<string> uri_tokens = string_split(uri, '/');
    string filtered_uri = make_path(uri_tokens);

    json::value j;
    json::value k = request.extract_json().get();

    // TODO 인증!
    string username = k.at("UserName").as_string();
    string password = k.at("Password").as_string();
    BOOST_LOG_SEV(lg, info) << "UserName: " << username;
    BOOST_LOG_SEV(lg, info) << "Password: " << password;

    int ret = pam_authentication("krbmc", username.c_str(), password.c_str());
    if (ret == PAM_SUCCESS) {
        BOOST_LOG_SEV(lg, info) << "성공!";
    }

    BOOST_LOG_SEV(lg, info) << "Reqeust URL : " << filtered_uri;
    BOOST_LOG_SEV(lg, info) << "Request Body : " << request.to_string();

    // Response redfish version
    if (uri_tokens.size() == 1 && uri_tokens[0] == "redfish")
    {
        j[REDFISH_VERSION] = json::value::string(U(ODATA_SERVICE_ROOT_ID));
        request.reply(status_codes::OK, j);
        return;
    }
    // Response redfish resource
    else
    {
        BOOST_LOG_SEV(lg, info) << filtered_uri;
        if (record_is_exist(filtered_uri))
            j = record_get_json(filtered_uri);
        else
            request.reply(status_codes::NotFound);
    }

    // base64_encode();
    // request.headers().add("Set-Cookie", json::value::string("123456789abcdefghijklmnopqrstuvwxyz"));
    // BOOST_LOG_SEV(lg, info) << "Request Body : " << request.to_string();
    request.reply(status_codes::OK, j);
}

/**
 * @brief DELETE request handler
 * 
 * @param request Request object
 */
void Handler::handle_delete(http_request request)
{

    cout << "handle_delete request" << endl;

    auto j = request.extract_json().get();

    request.reply(status_codes::NotImplemented, U("DELETE Request Response"));
}

/**
 * @brief PUT request handler
 * 
 * @param request Request object
 */
void Handler::handle_put(http_request request)
{

    cout << "handle_put request" << endl;

    auto j = request.extract_json().get();

    request.reply(status_codes::NotImplemented, U("PUT Request Response"));
}

/**
 * @brief POST request handler
 * 
 * @param request Request object
 */
void Handler::handle_post(http_request request)
{

    cout << "handle_post request" << endl;

    vector<string> input_list;
    input_list.reserve(list.size());

    auto j = request.extract_json().get();

    request.reply(status_codes::NotImplemented, U("POST Request Response"));
}
#include "handler.hpp"
#include "resource.hpp"

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
    auto j = json::value::object();
    auto k = request.extract_json().get();

    BOOST_LOG_SEV(lg, info) << k[U("test")].serialize();
    BOOST_LOG_SEV(lg, info) << "Reqeust URL : " << uri;
    BOOST_LOG_SEV(lg, info) << "Request Body : " << request.to_string();

    if (uri == "/redfish")
    {
        j[REDFISH_VERSION] = json::value::string(U(REDFISH_ROOT_PATH));
        request.reply(status_codes::OK, j);
        return;
    }
    else
    {
        if (record_is_exist(uri))
            j = record_get_json(uri);
        else
            request.reply(status_codes::NoContent, j);
    }

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

    request.reply(status_codes::OK, U("DELETE Request Response"));
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

    request.reply(status_codes::OK, U("PUT Request Response"));
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

    request.reply(status_codes::OK, U("POST Request Response"));
}
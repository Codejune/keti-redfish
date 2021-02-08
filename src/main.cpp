#include "handler.hpp"
#include "resource.hpp"
#include "gpio.hpp"

unique_ptr<Handler> g_listener;
unordered_map<string, Resource *> g_record;
src::severity_logger<severity_level> g_logger;
ServiceRoot *g_service_root;

/**
 * @brief Resource initialization
 */
void init_resource(void)
{
    log(info) << "Redfish resource initializing...";

    g_service_root = new ServiceRoot();
    // record_load_json();
    record_save_json();
}

/**
 * @brief 
 * 
 * @param _url 
 * @param _config 
 */
void start_server(utility::string_t &_url, http_listener_config _config)
{
    g_listener = unique_ptr<Handler>(new Handler(_url, _config));
    g_listener->open().wait();
    log(info) << "KETI Redfish RESTful server start";
}

/**
 * @brief KETI Redfish main entry point
 * 
 * @param argc Argument vector count
 * @param argv Argument vector array
 * @return int 
 */
int main(int _argc, char *_argv[])
{
    // Initialization
    init_resource();
    init_gpio();
    GPIO_SET = 1 << LED_GREEN;
    log(info) << GET_GPIO(2);
    http_listener_config listen_config;
    listen_config.set_ssl_context_callback([](boost::asio::ssl::context &_ctx) {
        _ctx.set_options(
            boost::asio::ssl::context::default_workarounds | boost::asio::ssl::context::no_sslv2 // Not use SSL2
            | boost::asio::ssl::context::no_tlsv1                                                // NOT use TLS1
            | boost::asio::ssl::context::no_tlsv1_1                                              // NOT use TLS1.1
            | boost::asio::ssl::context::single_dh_use);

        // Certificate Password Provider
        // _ctx.set_password_callback([](size_t max_length,
        //     boost::asio::ssl::context::password_purpose purpose)
        // {
        //    return "password";
        // });

        _ctx.use_certificate_chain_file("/conf/ssl/rootca.crt");
        _ctx.use_private_key_file("/conf/ssl/rootca.key", boost::asio::ssl::context::pem);
        _ctx.use_tmp_dh_file("/conf/ssl/dh2048.pem");
    });

    listen_config.set_timeout(utility::seconds(10));
    utility::string_t url = U("https://0.0.0.0:443");

    start_server(url, listen_config);
    while (true)
    {
        // TODO 리소스 업데이트 관련 구현 필요
        pause();
    }
    g_listener->close().wait();
    exit(0);
}
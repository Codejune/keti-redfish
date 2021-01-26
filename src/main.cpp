#include "stdafx.hpp"
#include "handler.hpp"
#include "resource.hpp"

unique_ptr<Handler> listener;
src::severity_logger<severity_level> lg;
unordered_map<string, Resource*> g_record;

/**
 * @brief Resource initialization
 */
void resource_init(void)
{
    ServiceRoot *service_root = new ServiceRoot();
    service_root->id = "RootService";
    service_root->name = "Root Service";
    service_root->redfish_version = "1.0.0";
    service_root->save_json();

    Collection *systems = new Collection("/redfish/v1/Systems", ODATA_SYSTEM_COLLECTION_TYPE);
    service_root->system_collection = systems;
    systems->name = "Computer System Collection";

    Collection *chassis = new Collection("/redfish/v1/Chassis", ODATA_CHASSIS_COLLECTION_TYPE);
    service_root->chassis_collection = chassis;
    chassis->name = "Chassis Collection";

    Collection *managers = new Collection("/redfish/v1/Managers", ODATA_MANAGER_COLLECTION_TYPE);
    service_root->manager_collection = managers;
    managers->name = "Manager Collection";

    g_record["/redfish/v1/Systems"] = systems;
    g_record["/redfish/v1/Chassis"] = chassis;
    g_record["/redfish/v1/Managers"] = managers;
    g_record[REDFISH_ROOT_PATH] = service_root;
}

/**
 * @brief 
 * 
 * @param url 
 * @param config 
 */
void start_server(utility::string_t &url, http_listener_config config)
{
    listener = unique_ptr<Handler>(new Handler(url, config));
    listener->open().wait();
    BOOST_LOG_SEV(lg, info) << "KETI Redfish RESTful server start";
}

/**
 * @brief KETI Redfish main entry point
 * 
 * @param argc Argument vector count
 * @param argv Argument vector array
 * @return int 
 */
int main(int argc, char *argv[])
{

    // Initialization
    resource_init();
    
    // logging::add_common_attributes();

    // BOOST_LOG_SEV(lg, trace) << "A trace severity message";
    // BOOST_LOG_SEV(lg, debug) << "A debug severity message";
    // BOOST_LOG_SEV(lg, info) << "An informational severity message";
    // BOOST_LOG_SEV(lg, warning) << "A warning severity message";
    // BOOST_LOG_SEV(lg, error) << "An error severity message";
    // BOOST_LOG_SEV(lg, fatal) << "A fatal severity message";

    http_listener_config listen_config;
    listen_config.set_ssl_context_callback([](boost::asio::ssl::context &ctx) {
        ctx.set_options(
            boost::asio::ssl::context::default_workarounds | boost::asio::ssl::context::no_sslv2 // Not use SSL2
            | boost::asio::ssl::context::no_tlsv1                                                // NOT use TLS1
            | boost::asio::ssl::context::no_tlsv1_1                                              // NOT use TLS1.1
            | boost::asio::ssl::context::single_dh_use);

        // Certificate Password Provider
        // ctx.set_password_callback([](size_t max_length,
        //     boost::asio::ssl::context::password_purpose purpose)
        // {
        //    return "password";
        // });

        ctx.use_certificate_chain_file("rootca.crt");
        ctx.use_private_key_file("rootca.key", boost::asio::ssl::context::pem);
        ctx.use_tmp_dh_file("dh2048.pem");
    });

    listen_config.set_timeout(utility::seconds(10));
    utility::string_t url = U("https://0.0.0.0:80");

    start_server(url, listen_config);
    while (true) {
        // TODO 리소스 업데이트 관련 구현 필요
    }
    listener->close().wait();
    exit(0);
}
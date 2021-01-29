#ifndef RESOURCE_H
#define RESOURCE_H

#include "stdafx.hpp"

/**
 * @brief Redfish information
 * 
 */
#define REDFISH_VERSION "v1"

/**
 * @brief Open data information
 * 
 */
#define ODATA_TYPE_VERSION REDFISH_VERSION "_0_0"

#define ODATA_SERVICE_ROOT_ID "/redfish/" REDFISH_VERSION
#define ODATA_SYSTEM_ID ODATA_SERVICE_ROOT_ID "/Systems"
#define ODATA_CHASSIS_ID ODATA_SERVICE_ROOT_ID "/Chassis"
#define ODATA_MANAGER_ID ODATA_SERVICE_ROOT_ID "/Managers"
#define ODATA_TASK_SERVICE_ID ODATA_SERVICE_ROOT_ID "/TaskService"
#define ODATA_SESSION_SERVICE_ID ODATA_SERVICE_ROOT_ID "/SessionService"
#define ODATA_ACCOUNT_SERVICE_ID ODATA_SERVICE_ROOT_ID "/AccountService"
#define ODATA_ACCOUNT_ID ODATA_ACCOUNT_SERVICE_ID "/Accounts"
#define ODATA_ROLE_ID ODATA_ACCOUNT_SERVICE_ID "/Roles"
#define ODATA_EVENT_SERVICE_ID ODATA_SERVICE_ROOT_ID "/EventService"

#define ODATA_RESOURCE_TYPE "#Resource." ODATA_TYPE_VERSION ".Resource"
#define ODATA_SERVICE_ROOT_TYPE "#ServiceRoot." ODATA_TYPE_VERSION ".ServiceRoot"
#define ODATA_COLLECTION_TYPE "#Collection.Collection"

#define ODATA_SYSTEM_COLLECTION_TYPE "#ComputerSystemCollection.ComputerSystemCollection"
#define ODATA_SYSTEM_TYPE "#ComputerSystem." ODATA_TYPE_VERSION ".ComputerSystem"
#define ODATA_PROCESSOR_COLLECTION_TYPE "#ProcessorCollection.ProcessorCollection"
#define ODATA_PROCESSOR_TYPE "#Processor." ODATA_TYPE_VERSION ".Processor"
#define ODATA_SIMPLE_STORAGE_COLLECTION_TYPE "#SimpleStorageCollection.SimpleStorageCollection"
#define ODATA_SIMPLE_STORAGE_TYPE "#SimpleStorage." ODATA_TYPE_VERSION ".SimpleStorage"

#define ODATA_CHASSIS_COLLECTION_TYPE "#ChassisCollection.ChassisCollection"
#define ODATA_CHASSIS_TYPE "#Chassis." ODATA_TYPE_VERSION ".Chassis"
#define ODATA_THERMAL_TYPE "#Thermal." ODATA_TYPE_VERSION ".Thermal"
#define ODATA_POWER_TYPE "#Power." ODATA_TYPE_VERSION ".Power"

#define ODATA_MANAGER_COLLECTION_TYPE "#ManagerCollection.ManagerCollection"
#define ODATA_MANAGER_TYPE "#Manager." ODATA_TYPE_VERSION ".Manager"
#define ODATA_ETHERNET_INTERFACE_COLLECTION_TYPE "#EthernetInterfaceCollection.EthernetInterfaceCollection"
#define ODATA_ETHERNET_INTERFACE_TYPE "#EthernetInterface." ODATA_TYPE_VERSION ".EthernetInterface"
#define ODATA_LOG_SERVICE_COLLECTION_TYPE "#LogServiceCollection.LogServiceCollection"
#define ODATA_LOG_SERVICE_TYPE "#LogService." ODATA_TYPE_VERSION ".LogService"
#define ODATA_LOG_ENTRY_COLLECTION_TYPE "#LogEntryCollection.LogEntryCollection"
#define ODATA_LOG_ENRTY_TYPE "#LogEntry." ODATA_TYPE_VERSION ".LogEntry"

#define ODATA_TASK_SERVICE_TYPE "#TaskService." ODATA_TYPE_VERSION ".TaskService"
#define ODATA_TASK_COLLECTION_TYPE "#TaskCollection.TaskCollection"

#define ODATA_SESSION_SERVICE_TYPE "#SessionService." ODATA_TYPE_VERSION ".SessionService"
#define ODATA_SESSION_COLLECTION_TYPE "#SessionCollection.SessionCollection"
#define ODATA_SESSION_TYPE "#Session." ODATA_TYPE_VERSION ".Session"

#define ODATA_ACCOUNT_SERVICE_TYPE "#AccountService." ODATA_TYPE_VERSION ".AccountService"
#define ODATA_ACCOUNT_COLLECTION_TYPE "#ManagerAccountCollection.ManagerAccountCollection"
#define ODATA_ACCOUNT_TYPE "#ManagerAccount." ODATA_TYPE_VERSION ".ManagerAccount"
#define ODATA_ROLE_COLLECTION_TYPE "#RoleCollection.RoleCollection"
#define ODATA_ROLE_TYPE "#Role." ODATA_TYPE_VERSION ".Role"

#define ODATA_EVENT_SERVICE_TYPE "#EventService." ODATA_TYPE_VERSION ".EventService"
#define ODATA_DESTINATION_COLLECTION_TYPE "#EventDestinationCollection.EventDestinationCollection"
#define ODATA_DESTINATION_TYPE "#EventDestination." ODATA_TYPE_VERSION ".EventDestination"

#define STATUS_STATE_ENABLED "Enabled"
#define STATUS_STATE_DISABLED "Disabled"
#define STATUS_STATE_STAND_BY_OFFLINE "StandbyOffline"
#define STATUS_STATE_STARTING "Starting"

#define STATUS_HEALTH_OK "OK"
#define STATUS_HEALTH_CRITICAL "Critical"
#define STATUS_HEALTH_WARNING "Warning"
/**
 * @brief Resource type for casting
 * 
 */
enum RESOURCE_TYPE
{
    SUPER_TYPE,
    SERVICE_ROOT_TYPE,
    COLLECTION_TYPE,
    SYSTEM_TYPE,
    PROCESSOR_TYPE,
    SIMPLE_STORAGE_TYPE,
    CHASSIS_TYPE,
    THERMAL_TYPE,
    POWER_TYPE,
    MANAGER_TYPE,
    ETHERNET_INTERFACE_TYPE,
    LOG_SERVICE_TYPE,
    LOG_ENTRY_TYPE,
    TASK_SERVICE_TYPE,
    SESSION_SERVICE_TYPE,
    SESSION_TYPE,
    ACCOUNT_SERVICE_TYPE,
    ACCOUNT_TYPE,
    ROLE_TYPE,
    EVENT_SERVICE_TYPE,
    DESTINATION_TYPE
};

/**
 * @brief Open data protocol information
 **/
typedef struct _OData
{
    string id;
    string type;
} OData;

/**
 * @breif Status of redfish resource
 **/
typedef struct _Status
{
    string state;
    string health;
} Status;

/**
 * @brief Resource of redfish schema
 **/
class Resource
{
public:
    OData odata;
    string name;
    uint8_t type;

    // Class constructor, destructor oveloading
    Resource(const uint8_t _type, const string _odata_id, const string _odata_type)
    {
        this->name = "";
        this->type = _type;
        this->odata.id = _odata_id;
        this->odata.type = _odata_type;
    };
    ~Resource(){};

    json::value get_json(void);
    json::value get_odata_id_json(void);
    bool save_json(void);
    bool load_json(void);
};

extern unordered_map<string, Resource *> g_record;

/**
 * @brief Root of resource
 */
class Collection : public Resource
{
public:
    vector<Resource *> members;

    // Class constructor, destructor oveloading
    Collection(const string _odata_id, const string _odata_type) : Resource(COLLECTION_TYPE, _odata_id, _odata_type)
    {
        // switch(_odata_type)
        // {
        //     case ODATA_PROCESSOR_COLLECTION_TYPE:
        //         this->name = "Processor Collection";
        //         break;
        //     case ODATA_SIMPLE_STORAGE_COLLECTION_TYPE:
        //         this->name = "Simple Storage Collection";
        //         break;
        //     case ODATA_ETHERNET_INTERFACE_COLLECTION_TYPE:
        //         this->name = "Ethernet Network Interface Collection";
        //         break;
        //     case ODATA_LOG_SERVICE_COLLECTION_TYPE:
        //         this->name = "Log Service Collection";
        //         break;
        //     case ODATA_LOG_ENTRY_COLLECTION_TYPE:
        //         this->name = "Log Entry Collection";
        //         break;
        //     case ODATA_SESSION_COLLECTION_TYPE:
        //         this->name = "Session Collection";
        //         break;
        //     case ODATA_DESTINATION_COLLECTION_TYPE:
        //         this->name = "Event Subscriptions Collection";
        //         break;
        // }
        g_record[_odata_id] = this;
    };
    ~Collection(){};

    void add_member(Resource *);
    json::value get_json(void);
    bool load_json(void);
};

/**
 * @brief Redfish resource of account
 */
class Account : public Resource
{
public:
    string id;
    bool enabled;
    string password;
    string user_name;
    string role_id;
    bool locked;

    Account(const string _odata_id) : Resource(ACCOUNT_TYPE, _odata_id, ODATA_ACCOUNT_TYPE)
    {
        this->id = "";
        this->enabled = false;
        this->password = "";
        this->user_name = "";
        // Role object
        this->locked = false;

        g_record[_odata_id] = this;
    }
    ~Account(){};

    json::value get_json(void);
    bool load_json(void);
};

/**
 * @brief Redfish resource of account
 */
class Role : public Resource
{
public:
    string id;
    bool is_predefined;
    vector<string> assigned_privileges;

    Role(const string _odata_id) : Resource(ROLE_TYPE, _odata_id, ODATA_ACCOUNT_TYPE)
    {
        this->id = "";
        this->is_predefined = false;
        assigned_privileges.push_back("test");

        g_record[_odata_id] = this;
    }
    ~Role(){};

    json::value get_json(void);
    bool load_json(void);
};

/**
 * @breif Redfish resource of account service
 **/
class AccountService : public Resource
{
public:
    string id;
    Status status;
    bool service_enabled;
    int auth_failure_logging_threshold;
    int min_password_length;
    int account_lockout_threshold;
    int account_lockout_duration;
    int account_lockout_counter_reset_after;
    int account_lockout_counter_reset_enabled;
    Collection *account_collection;
    Collection *role_collection;

    // Class constructor, destructor oveloading
    AccountService() : Resource(ACCOUNT_SERVICE_TYPE, ODATA_ACCOUNT_SERVICE_ID, ODATA_ACCOUNT_SERVICE_TYPE)
    {
        this->name = "Account Service";
        this->id = "AccountService";
        this->status.state = STATUS_STATE_DISABLED;
        this->status.health = STATUS_HEALTH_OK;
        this->service_enabled = false;
        this->auth_failure_logging_threshold = 0;
        this->min_password_length = 0;
        this->account_lockout_threshold = 0;
        this->account_lockout_duration = 0;
        this->account_lockout_counter_reset_after = 0;
        this->account_lockout_counter_reset_enabled = 0;

        this->account_collection = new Collection(ODATA_ACCOUNT_ID, ODATA_ACCOUNT_COLLECTION_TYPE);
        account_collection->name = "Accounts Collection";

        this->role_collection = new Collection(ODATA_ROLE_ID, ODATA_ROLE_COLLECTION_TYPE);
        role_collection->name = "Roles Collection";
        role_collection->add_member(new Role("/redfish/v1/AccountService/Roles/Administrator"));

        g_record[ODATA_ACCOUNT_SERVICE_ID] = this;
    };
    ~AccountService(){};

    json::value get_json(void);
    bool load_json(void);
};

/**
 * @brief Root of redfish
 */
class ServiceRoot : public Resource
{
public:
    string id;
    string redfish_version;
    string uuid;
    Collection *system_collection;
    Collection *chassis_collection;
    Collection *manager_collection;
    Collection *task;
    Collection *session_service;
    AccountService *account_service;
    Collection *event_service;

    // Class constructor, destructor oveloading
    ServiceRoot() : Resource(SERVICE_ROOT_TYPE, ODATA_SERVICE_ROOT_ID, ODATA_SERVICE_ROOT_TYPE)
    {
        this->id = "RootService";
        this->name = "Root Service";
        this->redfish_version = "1.0.0";
        this->uuid = "";

        system_collection = new Collection(ODATA_SYSTEM_ID, ODATA_SYSTEM_COLLECTION_TYPE);
        system_collection->name = "Computer System Collection";
        chassis_collection = new Collection(ODATA_CHASSIS_ID, ODATA_CHASSIS_COLLECTION_TYPE);
        chassis_collection->name = "Chassis Collection";
        manager_collection = new Collection(ODATA_MANAGER_ID, ODATA_MANAGER_COLLECTION_TYPE);
        manager_collection->name = "Manager Collection";
        account_service = new AccountService();

        g_record[ODATA_SERVICE_ROOT_ID] = this;
    };
    ~ServiceRoot(){};

    json::value get_json(void);
    bool load_json(void);
};

bool record_is_exist(const string _uri);
json::value record_get_json(const string _uri);
bool record_load_json(void);
bool record_save_json(void);

#endif

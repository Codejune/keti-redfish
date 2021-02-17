#ifndef RESOURCE_H
#define RESOURCE_H

#include "stdafx.hpp"
#include "hwcontrol.hpp"

/**
 * @brief Redfish information
 */
#define REDFISH_VERSION "v1"

/**
 * @brief Open data protocol information
 */
#define ODATA_TYPE_VERSION REDFISH_VERSION "_0_0"
// Open data protocol path
#define ODATA_SERVICE_ROOT_ID "/redfish/" REDFISH_VERSION
#define ODATA_SYSTEM_ID ODATA_SERVICE_ROOT_ID "/Systems"
#define ODATA_CHASSIS_ID ODATA_SERVICE_ROOT_ID "/Chassis"
#define ODATA_MANAGER_ID ODATA_SERVICE_ROOT_ID "/Managers"
#define ODATA_TASK_SERVICE_ID ODATA_SERVICE_ROOT_ID "/TaskService"
#define ODATA_SESSION_SERVICE_ID ODATA_SERVICE_ROOT_ID "/SessionService"
#define ODATA_SESSION_ID ODATA_SESSION_SERVICE_ID "/Sessions"
#define ODATA_ACCOUNT_SERVICE_ID ODATA_SERVICE_ROOT_ID "/AccountService"
#define ODATA_ACCOUNT_ID ODATA_ACCOUNT_SERVICE_ID "/Accounts"
#define ODATA_ROLE_ID ODATA_ACCOUNT_SERVICE_ID "/Roles"
#define ODATA_EVENT_SERVICE_ID ODATA_SERVICE_ROOT_ID "/EventService"

// Open data protocol resource type
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

/**
 * @brief Redfish resource status element
 */
#define STATUS_STATE_ENABLED "Enabled"
#define STATUS_STATE_DISABLED "Disabled"
#define STATUS_STATE_STAND_BY_OFFLINE "StandbyOffline"
#define STATUS_STATE_STARTING "Starting"
#define STATUS_HEALTH_OK "OK"
#define STATUS_HEALTH_CRITICAL "Critical"
#define STATUS_HEALTH_WARNING "Warning"

/**
 * @brief Redfish chassis resource indicator led state element
 */
#define LED_OFF 0
#define LED_BLINKING 1
#define LED_LIT 2

/**
 * @brief Redfish chassis resource power state element
 */
#define POWER_STATE_OFF "Off"
#define POWER_STATE_ON "On"
#define POWER_STATE_POWERING_OFF "PoweringOff"
#define POWER_STATE_POWERING_ON "PoweringOn"

/**
 * @brief Resource class type
 */
enum RESOURCE_TYPE
{
    SUPER_TYPE,
    SERVICE_ROOT_TYPE,
    COLLECTION_TYPE,
    LIST_TYPE,
    SYSTEM_TYPE,
    PROCESSOR_TYPE,
    SIMPLE_STORAGE_TYPE,
    CHASSIS_TYPE,
    THERMAL_TYPE,
    TEMPERATURE_TYPE,
    FAN_TYPE,
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
 * @brief Sensor context
 */
enum SENSOR_CONTEXT
{
    INTAKE_CONTEXT,
    CPU_CONTEXT
};

/**
 * @brief Open data protocol information
 *        @odata.id
 *        @odata.type
 */
typedef struct _OData
{
    string id;
    string type;
} OData;

/**
 * @brief Status of redfish resource
 */
typedef struct _Status
{
    string state;
    string health;
} Status;

/**
 * @brief PostalAddress information of machine
 */
typedef struct _PostalAddress
{
    string country;
    string territory;
    string city;
    string street;
    string house_number;
    string name;
    string postal_code;
} PostalAddress;

/**
 * @brief Placement information of machine
 */
typedef struct _Placement
{
    string row;
    string rack;
    string rack_offset_units;
    unsigned int rack_offset;
} Placement;

/**
 * @brief Location information of machine
 */
typedef struct _Location
{
    PostalAddress postal_address;
    Placement placement;
} Location;

/**
 * @brief Resource of redfish schema
 */
class Resource
{
public:
    OData odata;
    string name;
    uint8_t type;

    // Class constructor, destructor oveloading
    Resource(const uint8_t _type, const string _odata_id)
    {
        this->name = "";
        this->type = _type;
        this->odata.id = _odata_id;
        this->odata.type = "";
    };
    Resource(const uint8_t _type, const string _odata_id, const string _odata_type) : Resource(_type, _odata_id)
    {
        this->odata.type = _odata_type;
    };
    ~Resource(){};

    json::value get_json(void);
    json::value get_odata_id_json(void);
    bool save_json(void);
    bool load_json(void);
};

/**
 * @brief Resource map of resource
 */
extern unordered_map<string, Resource *> g_record;

/**
 * @brief Root of resource
 *        /redfish/v1/Systems
 *        /redfish/v1/Chassis
 *        /redfish/v1/Managers
 *        /redfish/v1/AccountService/Accounts
 *        /redfish/v1/SessionService/Sessions
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
        //     case ODATA_DESTINATION_COLLECTION_TYPE:
        //         this->name = "Event Subscriptions Collection";
        //         break;
        // }
        g_record[_odata_id] = this;
    };
    ~Collection()
    {
        g_record.erase(this->odata.id);
    };

    void add_member(Resource *);
    json::value get_json(void);
    bool load_json(void);
};

/**
 * @brief List of resource
 *        /redfish/v1/Chassis/#/Thermal/Temperatures
 *        /redfish/v1/Chassis/#/Thermal/Fans
 */
class List : public Resource
{
public:
    vector<Resource *> members;
    uint8_t member_type;

    // Class constructor, destructor oveloading
    List(const string _odata_id, const uint8_t _member_type) : Resource(LIST_TYPE, _odata_id)
    {
        this->member_type = _member_type;
        g_record[_odata_id] = this;
    };

    ~List()
    {
        g_record.erase(this->odata.id);
    };

    void add_member(Resource *);
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

    Role(const string _odata_id) : Resource(ROLE_TYPE, _odata_id, ODATA_ROLE_TYPE)
    {
        this->id = "";
        this->is_predefined = false;
        assigned_privileges.push_back("test");

        ((Collection *)g_record[ODATA_ROLE_ID])->add_member(this);
        g_record[_odata_id] = this;
    };
    ~Role()
    {
        g_record.erase(this->odata.id);
    };

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
    bool locked;
    Role *role;

    Account(const string _odata_id, const string _role_id) : Resource(ACCOUNT_TYPE, _odata_id, ODATA_ACCOUNT_TYPE)
    {
        string odata_id;
        odata_id = ODATA_ROLE_ID;
        odata_id = odata_id + '/' + _role_id;

        this->id = "";
        this->enabled = false;
        this->password = "";
        this->user_name = "";
        if (record_is_exist(odata_id))
            this->role = (Role *)g_record[odata_id];
        else
            this->role = nullptr;
        this->locked = false;

        ((Collection *)g_record[ODATA_ACCOUNT_ID])->add_member(this);
        g_record[_odata_id] = this;
    };
    ~Account()
    {
        g_record.erase(this->odata.id);
    };

    json::value get_json(void);
    bool load_json(void);
};

/**
 * @brief Redfish resource of account service
 **/
class AccountService : public Resource
{
public:
    string id;
    Status status;
    bool service_enabled;
    unsigned int auth_failure_logging_threshold;
    unsigned int min_password_length;
    unsigned int account_lockout_threshold;
    unsigned int account_lockout_duration;
    unsigned int account_lockout_counter_reset_after;
    unsigned int account_lockout_counter_reset_enabled;
    Collection *account_collection;
    Collection *role_collection;

    // Class constructor, destructor oveloading
    AccountService() : Resource(ACCOUNT_SERVICE_TYPE, ODATA_ACCOUNT_SERVICE_ID, ODATA_ACCOUNT_SERVICE_TYPE)
    {
        // AccountService configuration
        this->name = "Account Service";
        this->id = "AccountService";
        this->status.state = STATUS_STATE_DISABLED;
        this->status.health = STATUS_HEALTH_OK;
        this->service_enabled = true;
        this->auth_failure_logging_threshold = 0;
        this->min_password_length = 6;
        this->account_lockout_threshold = 0;
        this->account_lockout_duration = 0;
        this->account_lockout_counter_reset_after = 0;
        this->account_lockout_counter_reset_enabled = 0;

        // Role collection configure
        this->role_collection = new Collection(ODATA_ROLE_ID, ODATA_ROLE_COLLECTION_TYPE);
        this->role_collection->name = "Roles Collection";
        // Account collection configure
        this->account_collection = new Collection(ODATA_ACCOUNT_ID, ODATA_ACCOUNT_COLLECTION_TYPE);
        this->account_collection->name = "Accounts Collection";

        // Administrator role configuration
        Role *_administrator = new Role(this->role_collection->odata.id + "/Administrator");
        _administrator->id = "Administrator";
        _administrator->name = "User Role";
        _administrator->is_predefined = true;
        _administrator->assigned_privileges.push_back("Login");
        _administrator->assigned_privileges.push_back("ConfigureManager");
        _administrator->assigned_privileges.push_back("ConfigureUsers");
        _administrator->assigned_privileges.push_back("ConfigureSelf");
        _administrator->assigned_privileges.push_back("ConfigureComponents");

        // Operator role configuration
        Role *_operator = new Role(this->role_collection->odata.id + "/Operator");
        _operator->id = "Operator";
        _operator->name = "User Role";
        _operator->is_predefined = true;
        _operator->assigned_privileges.push_back("Login");
        _operator->assigned_privileges.push_back("ConfigureSelf");
        _operator->assigned_privileges.push_back("ConfigureComponents");

        // ReadOnly role configuration
        Role *_read_only = new Role(this->role_collection->odata.id + "/ReadOnly");
        _read_only->id = "ReadOnly";
        _read_only->name = "User Role";
        _read_only->is_predefined = true;
        _read_only->assigned_privileges.push_back("Login");
        _read_only->assigned_privileges.push_back("ConfigureSelf");

        // Root account configure
        Account *_root = new Account(this->account_collection->odata.id + "/root", "Administrator");
        _root->id = "root";
        _root->name = "User Account";
        _root->user_name = "root";
        _root->password = "ketilinux";
        _root->enabled = true;
        _root->locked = false;

        g_record[ODATA_ACCOUNT_SERVICE_ID] = this;
    };
    ~AccountService()
    {
        g_record.erase(this->odata.id);
    };

    json::value get_json(void);
    bool load_json(void);
};

/**
 * @brief Redfish resource of session service
 */
class SessionService : public Resource
{
public:
    string id;
    Status status;
    bool service_enabled;
    unsigned int session_timeout;
    Collection *session_collection;

    // Class constructor, destructor oveloading
    SessionService() : Resource(SESSION_SERVICE_TYPE, ODATA_SESSION_SERVICE_ID, ODATA_SESSION_SERVICE_TYPE)
    {
        // AccountService configuration
        this->name = "Session Service";
        this->id = "SessionService";
        this->status.state = STATUS_STATE_ENABLED;
        this->status.health = STATUS_HEALTH_OK;
        this->service_enabled = true;
        this->session_timeout = 86400; // 30sec to 86400sec

        // AccountCollection configuration
        this->session_collection = new Collection(ODATA_SESSION_ID, ODATA_SESSION_TYPE);
        session_collection->name = "Session Collection";

        g_record[ODATA_SESSION_SERVICE_ID] = this;
    };
    ~SessionService()
    {
        g_record.erase(this->odata.id);
    };

    json::value get_json(void);
    bool load_json(void);
};

/**
 * @brief Redfish resource of session
 */
class Session : public Resource
{
public:
    string id;
    Account *account;
    unsigned int _remain_expires_time;

    // Class constructor, destructor oveloading
    Session(const string _odata_id, const string _session_id, Account *_account) : Resource(SESSION_TYPE, _odata_id, ODATA_SESSION_TYPE)
    {
        this->name = "User Session";
        this->id = _session_id;
        this->account = _account;
        this->_remain_expires_time = ((SessionService *)g_record[ODATA_SESSION_SERVICE_ID])->session_timeout;

        ((Collection *)g_record[ODATA_SESSION_ID])->add_member(this);
        g_record[_odata_id] = this;
    };
    ~Session()
    {
        g_record.erase(this->odata.id);
    };
    json::value get_json(void);
    bool load_json(void);
    pplx::task<void> start(void);

private:
};

/**
 * @brief Redfish resource of temperature
 */
class Temperature : public Resource
{
public:
    string member_id;
    Status status;
    double reading_celsius;
    double upper_threshold_non_critical;
    double upper_threshold_critical;
    double upper_threshold_fatal;
    double min_reading_range_temp;
    double max_reading_range_temp;
    string physical_context;

    // Class constructor, destructor oveloading
    Temperature(const string _odata_id) : Resource(TEMPERATURE_TYPE, _odata_id, ODATA_THERMAL_TYPE)
    {
        this->member_id = "";
        this->status.state = STATUS_STATE_ENABLED;
        this->status.health = STATUS_HEALTH_OK;
        this->reading_celsius = 0;
        this->upper_threshold_non_critical = 0;
        this->upper_threshold_critical = 0;
        this->upper_threshold_fatal = 0;
        this->min_reading_range_temp = 0;
        this->max_reading_range_temp = 0;
        this->physical_context = "";
        this->thread = false;

        g_record[_odata_id] = this;
    }
    Temperature(const string _odata_id, const string _member_id) : Temperature(_odata_id)
    {
        this->member_id = _member_id;
    };
    ~Temperature()
    {
        this->thread = false;
        g_record.erase(this->odata.id);
    }

    json::value get_json(void);
    bool load_json(void);
    pplx::task<void> read(uint8_t _sensor_index, uint8_t _sensor_context);

private:
    bool thread;
};

/**
 * @brief Redfish resource of temperature
 */
class Fan : public Resource
{
public:
    string member_id;
    Status status;
    int reading;
    string reading_units;
    int lower_threshold_fatal;
    int min_reading_range;
    int max_reading_range;
    string physical_context;

    // Class constructor, destructor oveloading
    Fan(const string _odata_id) : Resource(FAN_TYPE, _odata_id)
    {
        this->member_id = "";
        this->status.state = STATUS_STATE_ENABLED;
        this->status.health = STATUS_HEALTH_OK;
        this->reading = 0;
        this->reading_units = "RPM";
        this->lower_threshold_fatal = 0;
        this->min_reading_range = 0;
        this->max_reading_range = 0;
        this->physical_context = "";

        g_record[_odata_id] = this;
    }
    Fan(const string _odata_id, const string _member_id) : Fan(_odata_id)
    {
        this->member_id = _member_id;
    };
    ~Fan()
    {
        g_record.erase(this->odata.id);
    }

    json::value get_json(void);
    bool load_json(void);
};

/**
 * @brief Redfish resource of thermal
 * 
 */
class Thermal : public Resource
{
public:
    string id;
    List *temperatures;
    List *fans;

    // Class constructor, destructor oveloading
    Thermal(const string _odata_id) : Resource(THERMAL_TYPE, _odata_id)
    {
        this->id = "Thermal";

        // Temperatures configuration
        this->temperatures = new List(this->odata.id + "/Temperatures", TEMPERATURE_TYPE);
        this->temperatures->name = "Temperatures";

        // Fans configuration
        this->fans = new List(this->odata.id + "/Fans", FAN_TYPE);
        this->fans->name = "Fans";

        g_record[_odata_id] = this;
    };
    ~Thermal()
    {
        g_record.erase(this->odata.id);
    };

    json::value get_json(void);
    bool load_json(void);
};

/**
 * @brief Redfish resource of chassis
 */
class Chassis : public Resource
{
public:
    string id;
    string chassis_type;
    string manufacturer;
    string model;
    string sku;
    string serial_number;
    string part_number;
    string asset_tag;
    string power_state;
    uint8_t indicator_led;
    Status status;
    Location location;

    // TODO 리소스 변경 필요
    Thermal *thermal;
    Resource *power;

    // TODO Contains, ManagedBy 추가 필요
    Chassis(const string _odata_id, const string _chassis_id) : Resource(CHASSIS_TYPE, _odata_id, ODATA_CHASSIS_TYPE)
    {
        this->name = "";
        this->id = _chassis_id;
        this->chassis_type = "";
        this->manufacturer = "";
        this->model = "";
        this->sku = "";
        this->serial_number = "";
        this->part_number = "";
        this->asset_tag = "";
        this->power_state = POWER_STATE_ON;
        this->indicator_led = LED_OFF;
        this->status.state = STATUS_STATE_ENABLED;
        this->status.health = STATUS_HEALTH_OK;
        this->location.postal_address.country = "";
        this->location.postal_address.territory = "";
        this->location.postal_address.city = "";
        this->location.postal_address.street = "";
        this->location.postal_address.house_number = "";
        this->location.postal_address.name = "";
        this->location.postal_address.postal_code = "";
        this->location.placement.row = "";
        this->location.placement.rack = "";
        this->location.placement.rack_offset_units = "";
        this->location.placement.rack_offset = 0;

        // Thermal configuration
        this->thermal = new Thermal(this->odata.id + "/Thermal");
        this->thermal->name = "EdgeServer Chassis Thermal";
        ((Collection *)g_record[ODATA_CHASSIS_ID])->add_member(this);

        g_record[_odata_id] = this;
    };
    ~Chassis()
    {
        g_record.erase(this->odata.id);
    };

    json::value get_json(void);
    bool load_json(void);
    pplx::task<void> led_off(uint8_t _led_index);
    pplx::task<void> led_lit(uint8_t _led_index);
    pplx::task<void> led_blinking(uint8_t _led_index);
};

/**
 * @brief Root of redfish
 *        This resource create only once
 *        /redfish/v1
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
    AccountService *account_service;
    SessionService *session_service;
    Collection *task;
    Collection *event_service;

    // Class constructor, destructor oveloading
    ServiceRoot() : Resource(SERVICE_ROOT_TYPE, ODATA_SERVICE_ROOT_ID, ODATA_SERVICE_ROOT_TYPE)
    {
        string odata_id;

        this->id = "RootService";
        this->name = "Root Service";
        this->redfish_version = "1.0.0";
        this->uuid = "";

        // System configuration
        system_collection = new Collection(ODATA_SYSTEM_ID, ODATA_SYSTEM_COLLECTION_TYPE);
        system_collection->name = "Computer System Collection";
        
        // Chassis configration
        chassis_collection = new Collection(ODATA_CHASSIS_ID, ODATA_CHASSIS_COLLECTION_TYPE);
        chassis_collection->name = "Chassis Collection";
        odata_id = ODATA_CHASSIS_ID;
        odata_id = odata_id + "/Enclosure";
        Chassis *chassis = new Chassis(odata_id, "Enclosure");
        chassis->name = "EdgeServer Enclosure";
        chassis->chassis_type = "Enclosure";
        chassis->manufacturer = "KETI";
        chassis->indicator_led = LED_OFF;
        chassis->led_off(LED_YELLOW);
        chassis->led_off(LED_RED);
        chassis->led_blinking(LED_GREEN);

        double temp[2] = {0};
        if (get_intake_temperature_config(temp)) {
            log(info) << "Chassis temperature min value = " << temp[0];
            log(info) << "Chassis temperature max value = " << temp[1];
        }


        for (uint8_t i = 0; i < 4; i++)
        {
            ostringstream s;
            s << chassis->thermal->temperatures->odata.id << "/" << to_string(i);
            Temperature *intake_temperature = new Temperature(s.str(), to_string(i));
            intake_temperature->name = "Chassis Intake Temperature";
            intake_temperature->physical_context = "Intake";
            intake_temperature->min_reading_range_temp = temp[0];
            intake_temperature->max_reading_range_temp = temp[1];
            intake_temperature->upper_threshold_non_critical = round(temp[1] * 0.6);
            intake_temperature->upper_threshold_critical = round(temp[1] * 0.7);
            intake_temperature->upper_threshold_fatal = round(temp[1] * 0.85);
            intake_temperature->read(i, INTAKE_CONTEXT);
            chassis->thermal->temperatures->add_member(intake_temperature);
        }

        ostringstream s;
        s << chassis->thermal->temperatures->odata.id << "/" << to_string(chassis->thermal->temperatures->members.size());
        Temperature *cpu_temperature = new Temperature(s.str(), to_string(chassis->thermal->temperatures->members.size()));
        cpu_temperature->name = "Chassis Manager CPU Temperature";
        cpu_temperature->physical_context = "CPU";
        cpu_temperature->min_reading_range_temp = 0;
        cpu_temperature->max_reading_range_temp = 100;
        cpu_temperature->upper_threshold_non_critical = round(cpu_temperature->max_reading_range_temp * 0.7);
        cpu_temperature->upper_threshold_critical = round(cpu_temperature->max_reading_range_temp * 0.75);
        cpu_temperature->upper_threshold_fatal = round(cpu_temperature->max_reading_range_temp * 0.8);
        cpu_temperature->read(chassis->thermal->temperatures->members.size(), CPU_CONTEXT);
        chassis->thermal->temperatures->add_member(cpu_temperature);


        // Manager configration
        manager_collection = new Collection(ODATA_MANAGER_ID, ODATA_MANAGER_COLLECTION_TYPE);
        manager_collection->name = "Manager Collection";
        
        // AccountService configuration
        account_service = new AccountService();

        // SessionService configuration
        session_service = new SessionService();

        g_record[ODATA_SERVICE_ROOT_ID] = this;
    };
    ~ServiceRoot()
    {
        g_record.erase(this->odata.id);
    };

    json::value get_json(void);
    bool load_json(void);
};

bool init_resource(void);
bool is_session_valid(const string _token_id);

#endif

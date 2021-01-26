#ifndef RESOURCE_H
#define RESOURCE_H

#include "stdafx.hpp"

#define REDFISH_VERSION "v1"
#define REDFISH_ROOT_PATH "/redfish/" REDFISH_VERSION
#define ODATA_TYPE_VERSION REDFISH_VERSION "_0_0"

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
#define ODATA_ROLE_COLLECTION_TYPE "#RoleCollection.RoleCollection"
#define ODATA_ROLE_TYPE "#Role." ODATA_TYPE_VERSION ".Role"

#define ODATA_EVENT_SERVICE_TYPE "#EventService." ODATA_TYPE_VERSION ".EventService"
#define ODATA_DESTINATION_COLLECTION_TYPE "#EventDestinationCollection.EventDestinationCollection"
#define ODATA_DESTINATION_TYPE "#EventDestination." ODATA_TYPE_VERSION ".EventDestination"

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
    MANAGER_TYPE,
    ETHERNET_INTERFACE_TYPE,
    LOG_SERVICE_TYPE,
    LOG_ENTRY_TYPE,
    TASK_SERVICE_TYPE,
    SESSION_SERVICE_TYPE,
    SESSION_TYPE,
    ACCOUNT_SERVICE_TYPE,
    ROLE_TYPE,
    EVENT_SERVICE_TYPE,
    DESTINATION_TYPE
};

/**
 * @brief Open data protocol information
 */
typedef struct _OData
{
    string id;
    string type;
} OData;

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
    Resource()
    {
        this->name = "";
        this->type = SUPER_TYPE;
        this->odata.id = "";
        this->odata.type = ODATA_RESOURCE_TYPE;
    };
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

/**
 * @brief Root of resource
 */
class Collection : public Resource
{
public:
    vector<Resource *> members;

    // Class constructor, destructor oveloading
    Collection() : Resource()
    {
        this->type = COLLECTION_TYPE;
    };
    Collection(const string _odata_id, const string _odata_type) : Resource(COLLECTION_TYPE, _odata_id, _odata_type){};
    ~Collection(){};

    void add_member(Resource *);
    json::value get_json(void);
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
    Collection *account_service;
    Collection *event_service;

    // Class constructor, destructor oveloading
    ServiceRoot() : Resource(SERVICE_ROOT_TYPE, REDFISH_ROOT_PATH, ODATA_SERVICE_ROOT_TYPE)
    {
        this->id = "";
        this->redfish_version = "";
        this->uuid = "";
    };
    ~ServiceRoot(){};

    json::value get_json(void);
};

bool record_is_exist(const string _uri);
json::value record_get_json(const string _uri);

#endif

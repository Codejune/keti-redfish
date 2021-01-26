#include "resource.hpp"

extern unordered_map<string, Resource *> g_record;
extern src::severity_logger<severity_level> lg;

/**
 * @brief Find uri in to record(unordered_map)
 * 
 * @param _uri Open data id of resource
 * @return true 
 * @return false 
 */
bool record_is_exist(const string _uri)
{
    if (g_record.find(_uri) == g_record.end())
        return false;
    return true;
}

json::value record_get_json(const string _uri)
{
    json::value j;

    switch (g_record[_uri]->type)
    {
    case SERVICE_ROOT_TYPE:
        j = ((ServiceRoot *)g_record[_uri])->get_json();
        break;
    case COLLECTION_TYPE:
        j = ((Collection *)g_record[_uri])->get_json();
        break;
    case SYSTEM_TYPE:
        break;
    case PROCESSOR_TYPE:
        break;
    case SIMPLE_STORAGE_TYPE:
        break;
    case CHASSIS_TYPE:
        break;
    case THERMAL_TYPE:
        break;
    case POWER_TYPE:
        break;
    case MANAGER_TYPE:
        break;
    case ETHERNET_INTERFACE_TYPE:
        break;
    case LOG_SERVICE_TYPE:
        break;
    case LOG_ENTRY_TYPE:
        break;
    case TASK_SERVICE_TYPE:
        break;
    case SESSION_SERVICE_TYPE:
        break;
    case SESSION_TYPE:
        break;
    case ACCOUNT_SERVICE_TYPE:
        break;
    case ROLE_TYPE:
        break;
    case EVENT_SERVICE_TYPE:
        break;
    case DESTINATION_TYPE:
        break;
    default:
        break;
    }
    return j;
}

/**
 * @brief Load json file and assign to target resource
 * 
 * @return true 
 * @return false 
 */
bool record_load_json(void)
{
    for (auto it = g_record.begin(); it != g_record.end(); it++)
        switch (it->second->type)
        {
        case SERVICE_ROOT_TYPE:
            ((ServiceRoot *)it->second)->load_json();
            break;
        case COLLECTION_TYPE:
            ((Collection *)it->second)->load_json();
            break;
        case SYSTEM_TYPE:
            break;
        case PROCESSOR_TYPE:
            break;
        case SIMPLE_STORAGE_TYPE:
            break;
        case CHASSIS_TYPE:
            break;
        case THERMAL_TYPE:
            break;
        case POWER_TYPE:
            break;
        case MANAGER_TYPE:
            break;
        case ETHERNET_INTERFACE_TYPE:
            break;
        case LOG_SERVICE_TYPE:
            break;
        case LOG_ENTRY_TYPE:
            break;
        case TASK_SERVICE_TYPE:
            break;
        case SESSION_SERVICE_TYPE:
            break;
        case SESSION_TYPE:
            break;
        case ACCOUNT_SERVICE_TYPE:
            break;
        case ROLE_TYPE:
            break;
        case EVENT_SERVICE_TYPE:
            break;
        case DESTINATION_TYPE:
            break;
        default:
            break;
        }
    return true;
}

bool record_save_json(void)
{
    for (auto it = g_record.begin(); it != g_record.end(); it++)
        it->second->save_json();
    return true;
}

json::value Resource::get_json(void)
{
    json::value j;

    j[U("@odata.type")] = json::value::string(U(this->odata.type));
    j[U("Name")] = json::value::string(U(this->name));
    j[U("@odata.id")] = json::value::string(U(this->odata.id));
    return j;
}

json::value Resource::get_odata_id_json(void)
{
    json::value j;
    j[U("@odata.id")] = json::value::string(U(this->odata.id));
    return j;
}

bool Resource::save_json(void)
{

    // Make all of sub directories
    vector<string> tokens = string_split(this->odata.id, '/');
    string sub_path = "/";
    for (unsigned int i = 1; i < tokens.size() - 1; i++)
    {
        sub_path = sub_path + '/' + tokens[i];
        mkdir(sub_path.c_str(), 0755);
    }

    // Save json file to path
    ofstream out(this->odata.id + ".json");
    out << record_get_json(this->odata.id).serialize() << endl;
    out.close();

    return true;
}

bool Resource::load_json(void)
{
    json::value j;

    try
    {
        ifstream target_file(this->odata.id + ".json");
        stringstream string_stream;

        string_stream << target_file.rdbuf();
        target_file.close();

        j = json::value::parse(string_stream);
    }
    catch (json::json_exception excep)
    {
        throw json::json_exception("Error Parsing JSON file " + this->odata.id);
        return false;
    }

    this->name = j[U("Name")].serialize();
    return true;
}

json::value ServiceRoot::get_json(void)
{
    auto j = this->Resource::get_json();

    j[U("Id")] = json::value::string(U(this->id));
    j[U("RedfishVersion")] = json::value::string(U(this->redfish_version));
    j[U("UUID")] = json::value::string(U(this->uuid));
    j[U("Systems")] = this->system_collection->get_odata_id_json();
    j[U("Chassis")] = this->chassis_collection->get_odata_id_json();
    j[U("Managers")] = this->manager_collection->get_odata_id_json();
    // j[U("Tasks")] = this->task->get_odata_id_json();
    // j[U("SessionService")] = this->session_service->get_odata_id_json();
    // j[U("AccountService")] = this->account_service->get_odata_id_json();
    // j[U("EventService")] = this->event_service->get_odata_id_json();

    return j;
}

bool ServiceRoot::load_json(void)
{
    json::value j; // JSON read from input file

    try
    {
        ifstream target_file(this->odata.id + ".json");
        stringstream string_stream;

        string_stream << target_file.rdbuf();
        target_file.close();

        j = json::value::parse(string_stream);
    }
    catch (json::json_exception excep)
    {
        throw json::json_exception("Error Parsing JSON file " + this->odata.id);
        return false;
    }

    this->name = j[U("Name")].serialize();
    this->id = j[U("Id")].serialize();
    this->redfish_version = j[U("RedfishVersion")].serialize();
    this->uuid = j[U("UUID")].serialize();
    return true;
}

json::value Collection::get_json(void)
{
    auto j = this->Resource::get_json();
    j[U("Members")] = json::value::array();
    for (unsigned int i = 0; i < this->members.size(); i++)
        j[U("Members")][i] = this->members[i]->get_odata_id_json();
    j[U("Members@odata.count")] = json::value::number(U(this->members.size()));
    return j;
}

void Collection::add_member(Resource *_resource)
{
    this->members.push_back(_resource);
}

bool Collection::load_json(void)
{
    json::value j;

    try
    {
        ifstream target_file(this->odata.id + ".json");
        stringstream string_stream;

        string_stream << target_file.rdbuf();
        target_file.close();

        j = json::value::parse(string_stream);
        this->name = j[U("Name")].serialize();
        BOOST_LOG_SEV(lg, info) << this->name;
    }
    catch (json::json_exception excep)
    {
        throw json::json_exception("Error Parsing JSON file " + this->odata.id);
        return false;
    }

    return true;
}
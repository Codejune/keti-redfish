#include "stdafx.hpp"
#include "resource.hpp"

extern unordered_map<string, Resource *> g_record;

/**
 * @brief Find uri in to record(unordered_map)
 * 
 * @param _uri Open data id of resource
 * @return true 
 * @return false 
 */
bool record_is_exist(const string _uri)
{
    if (g_record.find(_uri) != g_record.end())
        return true;
    return false;
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
        j = ((SessionService *)g_record[_uri])->get_json();
        break;
    case SESSION_TYPE:
        break;
    case ACCOUNT_SERVICE_TYPE:
        j = ((AccountService *)g_record[_uri])->get_json();
        break;
    case ACCOUNT_TYPE:
        j = ((Account *)g_record[_uri])->get_json();
        break;
    case ROLE_TYPE:
        j = ((Role *)g_record[_uri])->get_json();
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
        case ACCOUNT_TYPE:
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

/**
 * @brief Print sorted keys of record
 * 
 */
void record_print(void)
{
    vector<string> keys;
    for (auto it = g_record.begin(); it != g_record.end(); it++)
        keys.push_back(it->first);
    sort(keys.begin(), keys.end(), comp);
    for (unsigned int i = 0; i < keys.size(); i++)
        log(info) << keys[i];
}
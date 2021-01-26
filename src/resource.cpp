#include "stdafx.hpp"
#include "resource.hpp"

extern unordered_map<string, Resource *> g_record;

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
    default:
        break;
    }
    return j;
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
    ofstream out(this->odata.id + ".json");
    out << this->get_json().serialize().c_str() << endl;
    out.close();

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

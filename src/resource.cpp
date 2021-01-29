#include "resource.hpp"

extern unordered_map<string, Resource *> g_record;
extern src::severity_logger<severity_level> lg;

// Resource start
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
    for (unsigned int i = 0; i < tokens.size() - 1; i++)
    {
        if (i == 0)
            sub_path = sub_path + tokens[i];
        else
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

    this->name = j.at("Name").as_string();
    return true;
}
// Resource end

// ServiceRoot start
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
    j[U("AccountService")] = this->account_service->get_odata_id_json();
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

    this->name = j.at("Name").as_string();
    this->id = j.at("Id").as_string();
    this->redfish_version = j.at("RedfishVersion").as_string();
    this->uuid = j.at("UUID").as_string();
    return true;
}
// ServiceRoot end

// Collection start
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
        this->name = j.at("Name").as_string();
        BOOST_LOG_SEV(lg, info) << this->name;
    }
    catch (json::json_exception excep)
    {
        throw json::json_exception("Error Parsing JSON file " + this->odata.id);
        return false;
    }dd

    return true;
}
// Collection end

// Account start
json::value Account::get_json(void)
{
    auto j = this->Resource::get_json();

    j[U("Id")] = json::value::string(U(this->id));
    j[U("Enabled")] = json::value::boolean(U(this->enabled));
    j[U("Password")] = json::value::string(U(this->password));
    j[U("UserName")] = json::value::string(U(this->user_name));
    j[U("RoleId")] = json::value::string(U(this->role_id));
    j[U("Locked")] = json::value::boolean(U(this->locked));

    return j;
}
// Account end

// Role start
json::value Role::get_json(void)
{
    auto j = this->Resource::get_json();

    j[U("Id")] = json::value::string(U(this->id));
    j[U("IsPredefined")] = json::value::boolean(U(this->is_predefined));

    for (unsigned int i = 0; i < this->assigned_privileges.size(); i++)
        j[U("AssignedPrivileges")][i] = json::value::string(U(this->assigned_privileges[i]));

    return j;
}
// Role end

// AccountService start
json::value AccountService::get_json(void)
{
    auto j = this->Resource::get_json();
    json::value k;

    j[U("Id")] = json::value::string(U(this->id));
    k[U("State")] = json::value::string(U(this->status.state));
    k[U("Health")] = json::value::string(U(this->status.health));
    j[U("Status")] = k;
    j[U("ServiceEnabled")] = json::value::boolean(U(this->service_enabled));
    j[U("AuthFailureLoggingThreshold")] = json::value::number(U(this->auth_failure_logging_threshold));
    j[U("MinPasswordLength")] = json::value::number(U(this->min_password_length));
    j[U("AccountLockoutThreshold")] = json::value::number(U(this->account_lockout_threshold));
    j[U("AccountLockoutDuration")] = json::value::number(U(this->account_lockout_duration));
    j[U("AccountLockoutCounterResetAfter")] = json::value::number(U(this->account_lockout_counter_reset_after));
    j[U("AccountLockoutCounterResetEnabled")] = json::value::number(U(this->account_lockout_counter_reset_enabled));
    j[U("Accounts")] = this->account_collection->get_odata_id_json();
    j[U("Roles")] = this->role_collection->get_odata_id_json();
    return j;
}
// AccountService end
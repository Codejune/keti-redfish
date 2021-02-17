#include "resource.hpp"

extern unordered_map<string, Resource *> g_record;
extern ServiceRoot *g_service_root;

/**
 * @brief Resource initialization
 */
bool init_resource(void)
{
    g_service_root = new ServiceRoot();

    // record_load_json();
    record_save_json();

    return true;
}

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
    catch (json::json_exception &e)
    {
        throw json::json_exception("Error Parsing JSON file " + this->odata.id);
        return false;
    }

    this->name = j.at("Name").as_string();
    return true;
}
// Resource end

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
        log(info) << this->name;
    }
    catch (json::json_exception &e)
    {
        throw json::json_exception("Error Parsing JSON file " + this->odata.id);
        return false;
    }

    return true;
}
// Collection end

// List start
json::value List::get_json(void)
{
    json::value j;
    j[U(this->name)] = json::value::array();
    for (unsigned int i = 0; i < this->members.size(); i++)
        switch (this->member_type)
        {
        case TEMPERATURE_TYPE:
            j[U("Temperatures")][i] = ((Temperature *)this->members[i])->get_json();
            break;
        case FAN_TYPE:
            j[U("Fans")][i] = ((Fan *)this->members[i])->get_json();
            break;
        }
    return j;
}

void List::add_member(Resource *_resource)
{
    this->members.push_back(_resource);
}
// List end

// Account start
json::value Account::get_json(void)
{
    auto j = this->Resource::get_json();
    json::value k;
    j[U("Id")] = json::value::string(U(this->id));
    j[U("Enabled")] = json::value::boolean(U(this->enabled));
    j[U("Password")] = json::value::string(U(this->password));
    j[U("UserName")] = json::value::string(U(this->user_name));
    if (this->role == nullptr)
    {
        j[U("RoleId")] = json::value::null();
        k = json::value::object();
    }
    else
    {
        j[U("RoleId")] = json::value::string(U(this->role->id));
        k[U("Role")] = this->role->get_odata_id_json();
    }
    j[U("Locked")] = json::value::boolean(U(this->locked));
    j[U("Links")] = k;
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

// SessionService start
json::value SessionService::get_json(void)
{
    auto j = this->Resource::get_json();
    json::value k;
    j[U("Id")] = json::value::string(U(this->id));
    k[U("State")] = json::value::string(U(this->status.state));
    k[U("Health")] = json::value::string(U(this->status.health));
    j[U("Status")] = k;
    j[U("ServiceEnabled")] = json::value::boolean(U(this->service_enabled));
    j[U("SessionTimeout")] = json::value::number(U(this->session_timeout));
    j[U("Sessions")] = this->session_collection->get_odata_id_json();
    return j;
}
// SessionService end

// Session start
json::value Session::get_json(void)
{
    auto j = this->Resource::get_json();
    j[U("Id")] = json::value::string(U(this->id));
    j[U("UserName")] = json::value::string(U(this->account->user_name));
    return j;
}

pplx::task<void> Session::start(void)
{
    Session *session = this;
    unsigned int *remain_expires_time = &this->_remain_expires_time;
    return pplx::create_task([remain_expires_time] {
               boost::asio::io_service io;
               boost::asio::deadline_timer session_timer(io, boost::posix_time::seconds(1));
               session_timer.async_wait(boost::bind(timer, &session_timer, remain_expires_time));
               io.run();
           })
        .then([session] {
            delete session;
        });
}
// Session end

// Temperature start
json::value Temperature::get_json(void)
{
    json::value j;
    json::value k;

    j[U("Name")] = json::value::string(U(this->name));
    j[U("@odata.id")] = json::value::string(U(this->odata.id));
    j[U("MemberId")] = json::value::string(U(this->member_id));
    k[U("State")] = json::value::string(U(this->status.state));
    k[U("Health")] = json::value::string(U(this->status.health));
    j[U("Status")] = k;
    j[U("ReadingCelsius")] = json::value::number(U(this->reading_celsius));
    j[U("UpperThresholdNonCritical")] = json::value::number(U(this->upper_threshold_non_critical));
    j[U("UpperThresholdCritical")] = json::value::number(U(this->upper_threshold_critical));
    j[U("UpperThresholdFatal")] = json::value::number(U(this->upper_threshold_fatal));
    j[U("MinReadingRangeTemp")] = json::value::number(U(this->min_reading_range_temp));
    j[U("MaxReadingRangeTemp")] = json::value::number(U(this->max_reading_range_temp));
    j[U("PhysicalContext")] = json::value::string(U(this->physical_context));

    return j;
}

pplx::task<void> Temperature::read(uint8_t _sensor_index, uint8_t _sensor_context)
{
    double *reading_celsius = &this->reading_celsius;
    bool *thread = &this->thread;
    *thread = true;

    switch (_sensor_context)
    {
    case INTAKE_CONTEXT:
        return pplx::create_task([thread, reading_celsius, _sensor_index] {
            while (*thread)
            {
                *reading_celsius = round(get_intake_temperature(_sensor_index));
                sleep(1);
            }
        });
    case CPU_CONTEXT:
        return pplx::create_task([thread, reading_celsius, _sensor_index] {
            while (*thread)
            {
                *reading_celsius = round(get_cpu_temperature(_sensor_index));
                sleep(1);
            }
        });
    }
    return pplx::create_task([]{});
}
// Temperature end

// Fan start
json::value Fan::get_json(void)
{
    json::value j;
    json::value k;

    j[U("Name")] = json::value::string(U(this->name));
    j[U("@odata.id")] = json::value::string(U(this->odata.id));
    j[U("MemberId")] = json::value::string(U(this->member_id));
    k[U("State")] = json::value::string(U(this->status.state));
    k[U("Health")] = json::value::string(U(this->status.health));
    j[U("Status")] = k;
    j[U("Reading")] = json::value::number(U(this->reading));
    j[U("ReadingUnits")] = json::value::string(U(this->reading_units));
    j[U("LowerThresholdFatal")] = json::value::number(U(this->lower_threshold_fatal));
    j[U("MinReadingRange")] = json::value::number(U(this->min_reading_range));
    j[U("MaxReadingRange")] = json::value::number(U(this->max_reading_range));
    j[U("PhysicalContext")] = json::value::string(U(this->physical_context));

    return j;
}
// Fan end

// Thermal start
json::value Thermal::get_json(void)
{
    unsigned int i;
    auto j = this->Resource::get_json();

    j[U("Id")] = json::value::string(U(this->id));
    j[U("Temperatures")] = json::value::array();
    for (i = 0; i < this->temperatures->members.size(); i++)
        j[U("Temperatures")][i] = ((Temperature *)this->temperatures->members[i])->get_json();
    j[U("Fans")] = json::value::array();
    for (i = 0; i < this->fans->members.size(); i++)
        j[U("Fans")][i] = ((Fan *)this->fans->members[i])->get_json();

    return j;
}
// Thermal end

// Chassis start
json::value Chassis::get_json(void)
{
    auto j = this->Resource::get_json();
    json::value k;
    json::value l;
    j[U("Id")] = json::value::string(U(this->id));
    j[U("ChassiType")] = json::value::string(U(this->chassis_type));
    j[U("Manufacturer")] = json::value::string(U(this->manufacturer));
    j[U("Model")] = json::value::string(U(this->model));
    j[U("SKU")] = json::value::string(U(this->sku));
    j[U("SerialNumber")] = json::value::string(U(this->serial_number));
    j[U("PartNumber")] = json::value::string(U(this->part_number));
    j[U("AssetTag")] = json::value::string(U(this->asset_tag));
    j[U("PowerState")] = json::value::string(U(this->power_state));
    switch (this->indicator_led)
    {
    case LED_OFF:
        j[U("IndicatorLED")] = json::value::string(U("Off"));
        break;
    case LED_BLINKING:
        j[U("IndicatorLED")] = json::value::string(U("Blinking"));
        break;
    case LED_LIT:
        j[U("IndicatorLED")] = json::value::string(U("Lit"));
        break;
    }
    k[U("State")] = json::value::string(U(this->status.state));
    k[U("Health")] = json::value::string(U(this->status.health));
    j[U("Status")] = k;
    k = json::value::object();
    l[U("Country")] = json::value::string(U(this->location.postal_address.country));
    l[U("Territory")] = json::value::string(U(this->location.postal_address.territory));
    l[U("City")] = json::value::string(U(this->location.postal_address.city));
    l[U("Street")] = json::value::string(U(this->location.postal_address.street));
    l[U("HouseNumber")] = json::value::string(U(this->location.postal_address.house_number));
    l[U("Name")] = json::value::string(U(this->location.postal_address.name));
    l[U("PostalCode")] = json::value::string(U(this->location.postal_address.postal_code));
    k[U("PostalAddress")] = l;
    l = json::value::object();
    l[U("Row")] = json::value::string(U(this->location.placement.row));
    l[U("Rack")] = json::value::string(U(this->location.placement.rack));
    l[U("RackOffsetUnits")] = json::value::string(U(this->location.placement.rack_offset_units));
    l[U("RackOffset")] = json::value::number(U(this->location.placement.rack_offset));
    k[U("Placement")] = l;
    j[U("Location")] = k;

    // TODO Thermal, Power 추가 필요
    j[U("Thermal")] = this->thermal->get_odata_id_json();
    // j[U("Power")] = this->power->get_odata_id_json();
    return j;
}

pplx::task<void> Chassis::led_off(uint8_t _led_index)
{
    uint8_t *indicator_led = &this->indicator_led;
    *indicator_led = LED_OFF;
    log(info) << this->name << ": LED off";
    return pplx::create_task([indicator_led, _led_index] {
        GPIO_CLR = 1 << _led_index;
    });
}

pplx::task<void> Chassis::led_lit(uint8_t _led_index)
{
    uint8_t *indicator_led = &this->indicator_led;
    *indicator_led = LED_LIT;
    log(info) << this->name << ": LED lit";
    return pplx::create_task([indicator_led, _led_index] {
        GPIO_SET = 1 << _led_index;
    });
}

pplx::task<void> Chassis::led_blinking(uint8_t _led_index)
{

    uint8_t *indicator_led = &this->indicator_led;
    *indicator_led = LED_BLINKING;
    log(info) << this->name << ": LED blinking";
    return pplx::create_task([indicator_led, _led_index] {
        while (*indicator_led == LED_BLINKING)
        {
            GPIO_CLR = 1 << _led_index;
            usleep(30000);
            GPIO_SET = 1 << _led_index;
            usleep(30000);
        }
    });
}
// Chassis end

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
    j[U("AccountService")] = this->account_service->get_odata_id_json();
    j[U("SessionService")] = this->session_service->get_odata_id_json();
    // j[U("Tasks")] = this->task->get_odata_id_json();
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
    catch (json::json_exception &e)
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

bool is_session_valid(const string _token_id)
{
    Session *session;
    string odata_id = ODATA_SESSION_ID;
    odata_id = odata_id + '/' + _token_id;
    if (!record_is_exist(odata_id))
        return false;
    session = (Session *)g_record[odata_id];
    if (session->_remain_expires_time <= 0)
        return false;
    return true;
}

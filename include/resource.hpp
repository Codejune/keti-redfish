#ifndef RESOURCE_H
#define RESOURCE_H

#include "stdafx.hpp"

typedef struct _OData
{
    string id;
    string type;
} OData;

class Resource
{
public:
    OData odata;
    string name;

    // Class constructor, destructor oveloading
    Resource()
    {
        this->name = "";
        this->odata.id = "";
        this->odata.type = "";
    };
    Resource(const string _name, const string _odata_id, const string _odata_type)
    {
        this->name = _name;
        this->odata.id = _odata_id;
        this->odata.type = _odata_type;
    };
    ~Resource(){};

    json::value get_json(void);
    json::value get_odata_id_json(void);
};

class ServiceRoot : public Resource
{
public:
    string id;
    string redfish_version;
    string uuid;

    // Class constructor, destructor oveloading
    ServiceRoot() : Resource()
    {
        this->id = "";
        this->redfish_version = "";
        this->uuid = "";
    };
    ServiceRoot(const string _name, const string _odata_id, const string _odata_type, const string _id) : Resource(_name, _odata_id, _odata_type)
    {
        this->id = _id;
        this->redfish_version = "";
        this->uuid = "";
    };
    ~ServiceRoot(){};

    json::value get_json(void);
};

class Collection : public Resource
{
public:
    vector<Resource*> members;

    // Class constructor, destructor oveloading
    Collection() : Resource(){};
    Collection(const string _name, const string _odata_id, const string _odata_type) : Resource(_name, _odata_id, _odata_type){
        
    };
    ~Collection(){};

    void add_member(Resource*);
    json::value get_json(void);
};

#endif

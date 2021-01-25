#ifndef HANDLER_H
#define HANDLER_H
#include "stdafx.hpp"

using namespace logging::trivial;

class Handler
{
public:
    // Constructor
    Handler(){};
    Handler(utility::string_t url, http_listener_config config);

    // Destructor
    ~Handler(){};

    // Server operation
    pplx::task<void> open() { return m_listener.open(); }
    pplx::task<void> close() { return m_listener.close(); }

private:
    http_listener m_listener;
    vector<string> list;

    // Request handler
    void handle_get(http_request request);
    void handle_put(http_request request);
    void handle_post(http_request request);
    void handle_delete(http_request request);
};


#endif
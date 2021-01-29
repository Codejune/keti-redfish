#include "auth.hpp"
extern src::severity_logger<severity_level> lg;

int pam_conversation(int numMsg, const struct pam_message** msg, struct pam_response** resp, void* appdataPtr)
{
    if (appdataPtr == NULL)
    {
        return PAM_AUTH_ERR;
    }
    char* appPass = (char*)(appdataPtr);
    size_t appPassSize = strlen(appPass);
    char* pass = (char*)(malloc(appPassSize + 1));
    if (pass == NULL)
    {
        return PAM_AUTH_ERR;
    }

    strncpy(pass, appPass, appPassSize + 1);

    *resp = (struct pam_response*)(calloc((size_t)(numMsg), sizeof(struct pam_response)));

    if (resp == NULL)
    {
        free(pass);
        return PAM_AUTH_ERR;
    }

    for (int i = 0; i < numMsg; ++i)
    {
        if (msg[i]->msg_style != PAM_PROMPT_ECHO_OFF)
        {
            continue;
        }

        resp[i]->resp = pass;
    }

    return PAM_SUCCESS;
}

int pam_authentication(char *service, const char *username, const char *password)
{

    struct pam_conv conv = {pam_conversation, (char*) password};
    pam_handle_t *handle = NULL;
    int ret = 0;

    ret = pam_start(service, username, &conv, &handle);
    if(ret != PAM_SUCCESS){
        pam_end(handle, PAM_SUCCESS);
        BOOST_LOG_SEV(lg, info) << "pam start failed";
        return ret;
    }
    
    ret = pam_authenticate(handle, 0);
    if(ret != PAM_SUCCESS){
        BOOST_LOG_SEV(lg, info) << "pam authentication failed : " << pam_strerror(handle, ret);
        pam_end(handle, PAM_SUCCESS);
        BOOST_LOG_SEV(lg, info) << "pam authentication failed : " << ret ;
        return ret;
    }

    ret = pam_acct_mgmt(handle, 0);
    if(ret != PAM_SUCCESS){
        pam_end(handle, PAM_SUCCESS);
        BOOST_LOG_SEV(lg, info) << "pam acct mgmt failed";
        return ret;
    }

    pam_end(handle, ret);
    return ret;
}

int pam_updatePassword(char *service, char *username, char *password)
{
    struct pam_conv conv = {pam_conversation, (char *)password};
    pam_handle_t *handle;
    int ret = 0;

    ret = pam_start(service, (char *)username, &conv, &handle);

    if(ret != PAM_SUCCESS){
        BOOST_LOG_SEV(lg, info) << "pam start failed";
        return ret;
    }

    ret = pam_chauthtok(handle, PAM_SILENT);

    if(ret != PAM_SUCCESS){
        BOOST_LOG_SEV(lg, info) << "pam chauthtok failed";
        pam_end(handle, PAM_SUCCESS);
        return ret;
    }
    return pam_end(handle, PAM_SUCCESS);
}
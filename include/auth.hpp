#ifndef _AUTH_H_
#define _AUTH_H_
#include "stdafx.hpp"
#include <assert.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>

int pam_conversation(int numMsg, const struct pam_message** msg, struct pam_response** resp, void* appdataPtr);
int pam_authentication(char *service, const char *username, const char *password);
int pam_updatePassword(char *service, char *username, char *password);

#endif


#include "../utils.hpp"

/* Include PAM headers */
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>

/* Define which PAM interfaces we provide */
#define PAM_SM_ACCOUNT
#define PAM_SM_AUTH
#define PAM_SM_PASSWORD
#define PAM_SM_SESSION

/* PAM entry point for authentication verification */
int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv)
{

        int pam_code;
        const char *username = NULL;
        const char *password = NULL;
        const char *serviceName = NULL;

        /* Asking the application for an  username */
        // -- 1 -- Используем pam_get_user
        pam_code = pam_get_user(pamh, &username, "USERNAME: ");
        if (pam_code != PAM_SUCCESS)
        {
                fprintf(stderr, "Can't get username");
                return PAM_PERM_DENIED;
        }
        DBG_LOG("--PAM MODULE-- USERNAME: %s", username);

        /*
                 if((pam_code = pam_get_item(pamh, PAM_USER, (const void **)&item)) == PAM_SUCCESS){
                         DBG_LOG("pam_get_item OK, user: %s",item);
                 }else{
                         DBG_LOG("pam_get_item username FAIL, ecode %d", pam_code);
                         return PAM_PERM_DENIED;
                 }
        */

        // /* Asking the application for a password */
        pam_code = pam_get_authtok(pamh, PAM_AUTHTOK, &password, "PASSWORD: ");
        if (pam_code != PAM_SUCCESS)
        {
                fprintf(stderr, "Can't get password");
                return PAM_PERM_DENIED;
        }

        /*
                if((pam_code = pam_get_item(pamh, PAM_AUTHTOK, (const void **)&password)) == PAM_SUCCESS){
                        DBG_LOG("pam_get_item OK, password: %s",password);
                }else{
                        DBG_LOG("pam_get_item username FAIL, ecode %d", pam_code);
                        return PAM_PERM_DENIED;
                }
        */

        // /* Checking the PAM_DISALLOW_NULL_AUTHTOK flag: if on, we can't accept empty passwords */
        // if (flags & PAM_DISALLOW_NULL_AUTHTOK) {
        // 	if (password == NULL || strcmp(password, "") == 0) {
        // 		fprintf(stderr, "Null authentication token is not allowed!.");
        // 		return PAM_PERM_DENIED;
        // 	}
        // }

        // /*Auth user reads a file with usernames and passwords and returns true if username
        //  * and password are correct. Obviously, you must not save clear text passwords */
        // if (auth_user(username,  password)) {
        // 	printf("Welcome, user");
        // 	return PAM_SUCCESS;
        // } else {
        // 	fprintf(stderr, "Wrong username or password");
        // 	return PAM_PERM_DENIED;
        // }

        if (strcmp("fake123", password) == 0)
        {
                DBG_LOG("--PAM MODULE-- Right password: %s", password);
                DBG_LOG("--PAM MODULE-- Welcome, user: %s", username);
                return PAM_SUCCESS;
        }
        else
        {
                DBG_LOG("--PAM MODULE-- authenticate FAIL, Wrong username or password");
                return PAM_PERM_DENIED;
        }
}

/* PAM entry point for session creation */
int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        return (PAM_IGNORE);
}

/* PAM entry point for session cleanup */
int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        return (PAM_IGNORE);
}

/* PAM entry point for accounting */
int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        return (PAM_IGNORE);
}

/*
   PAM entry point for setting user credentials (that is, to actually
   establish the authenticated user's credentials to the service provider)
 */
int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        return (PAM_IGNORE);
}

/* PAM entry point for authentication token (password) changes */
int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        return (PAM_IGNORE);
}

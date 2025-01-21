
#include "../utils.hpp"

#include <signal.h>

#include <security/pam_appl.h>
#include <security/pam_misc.h>

int auth_conv(int num_msg, const struct pam_message **msg, struct pam_response **resp, void *appdata)
{
    // DBG_LOG("hello, resp %p",*resp);

    if (!msg || !resp || !appdata)
    {
        return PAM_CONV_ERR;
    }

    // обязательно подготовить ответ
    if (!*resp)
    {
        *resp = (struct pam_response *)calloc(num_msg, sizeof(struct pam_response));
        // DBG_LOG("calloc, resp %p",*resp);
        if (!*resp)
        {
            return PAM_BUF_ERR;
        }
    }

    for (int ii = 0; ii < num_msg; ++ii)
    {
        const struct pam_message *pm = msg[ii];
        struct pam_response *pr = resp[ii];

        DBG_LOG("PAM request msg: `%s', prompt echo: `%s'", pm->msg, (pm->msg_style == PAM_PROMPT_ECHO_ON ? "on" : "off"));

        if (pm->msg_style == PAM_PROMPT_ECHO_ON)
        {
            pr->resp = strdup("as");

            if (!pr->resp)
            {
                return PAM_BUF_ERR;
            }
        }
        else if (pm->msg_style == PAM_PROMPT_ECHO_OFF)
        {
            pr->resp = strdup("fake123");

            if (!pr->resp)
            {
                return PAM_BUF_ERR;
            }
        }
        else if (pm->msg_style == PAM_ERROR_MSG)
        {
            pr->resp = strdup("PAM_ERROR_MSG");
            DBG_LOG("PAM_ERROR_MSG");
            if (!pr->resp)
            {
                return PAM_BUF_ERR;
            }
        }
        else if (pm->msg_style == PAM_TEXT_INFO)
        {
            pr->resp = strdup("PAM_TEXT_INFO");
            DBG_LOG("PAM_TEXT_INFO");

            if (!pr->resp)
            {
                return PAM_BUF_ERR;
            }
        }
    }

    return PAM_SUCCESS;
}

pam_handle_t *pamh;
int res = 0;

void funcExit(int a)
{

    DBG_LOG("exit");

    pam_close_session(pamh, 0);

    pam_setcred(pamh, PAM_DELETE_CRED);

    pam_end(pamh, res);

    exit(0);
}

int main(int argc, char *argv[])
{
    DBG_LOG(" -- hello! -- pid: %d", getpid());

    // if(atexit(funcExit) != 0 ){
    //         DBG_LOG("atexit error");
    // }

    signal(SIGTERM, funcExit);

    // if (argc < 2)
    // {
    //         fprintf(stderr, "Usage: %s <username>\n", argv[0]);
    //         return 1;
    // }

    // const char *user = argv[1];
    const char *user = "as";

    static struct pam_conv pam_conversation = {misc_conv, misc_conv};

    /*
    Создаём контекст, PAM требуется:
    service name для проверки политик в /etc/pam.d/service_name or, if that file does not exist, from /etc/pam.conf
    user, если NULL то будет запрос пользователя
    pam_conv - общение с PAM модулем
    pamh - контекст
    */
    res = pam_start(argv[0], user, &pam_conversation, &pamh);
    DBG_LOG(" pam start, user: %s, retVal: %d", user, res);

    if (res == PAM_SUCCESS)
    {
        res = pam_authenticate(pamh, 0);
        DBG_LOG(" pam authenticate, user: %s, retVal: %d", user, res);
    }

    if (res == PAM_SUCCESS)
    {
        /*
        проверяем валидность аккаунта
        проверка токена и срока учётной записи
        */
        res = pam_acct_mgmt(pamh, 0);
        DBG_LOG(" pam acct_mgmt, user: %s, retVal: %d", user, res);
    }

    if (res == PAM_SUCCESS)
    {
        fprintf(stdout, "Authenticated.\n");
    }
    else
    {
        fprintf(stdout, "Not Authenticated.\n");
    }

    res = pam_setcred(pamh, PAM_ESTABLISH_CRED);
    DBG_LOG(" pam pam_setcred, user: %s, retVal: %d", user, res);

    if (res == PAM_SUCCESS)
    {
        res = pam_open_session(pamh, 0);
        DBG_LOG(" pam pam_open_session, user: %s, retVal: %d", user, res);
    }

    // sleep(5);

    // int iter = 0;
    // while (1)
    // {
    //         // /* code */
    //         // if(iter++ == 100){
    //         //         break;
    //         // }

    //         // sleep(1);
    // }

    funcExit(0);

    // exit(res == PAM_SUCCESS ? 0 : 1);
    return (0);

    //-------------------------------------//
    while (1)
    {
        /* code */
    }

    // exit(0); //<stdlib.h>
    return (0);
}

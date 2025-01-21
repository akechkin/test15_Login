
#include "../utils.hpp"

#include <pwd.h> // файл паролей и теневыxй паролей
#include <grp.h> //файл групп
#include <string.h>
#include <stddef.h>

#include <sys/utsname.h>

void showUserInfo(struct passwd *pwd)
{
        if (pwd)
        {
                DBG_LOG("struct passwd pw_name: %s", pwd->pw_name);
                DBG_LOG("struct passwd pw_passwd: %s", pwd->pw_passwd);
                DBG_LOG("struct passwd pw_uid: %d", pwd->pw_uid);
                DBG_LOG("struct passwd pw_gid: %d", pwd->pw_gid);
                DBG_LOG("struct passwd pw_gecos: %s", pwd->pw_gecos);
                DBG_LOG("struct passwd pw_dir: %s", pwd->pw_dir);
                DBG_LOG("struct passwd pw_shell: %s", pwd->pw_shell);
        }
        else
        {
                DBG_LOG("pwd empty!");
        }
}

int main(int argc, char *argv[])
{

        DBG_LOG(" -- Show user info -- ");
        // #include <pwd.h>
        struct passwd *pwd = getpwnam("as");
        showUserInfo(pwd);
        pwd = getpwnam("bas");
        showUserInfo(pwd);
        DBG_LOG(" -- Show user info end -- ");

        asm("NOP");

        DBG_LOG(" -- Show all users info -- ");
        // pw_shell: /usr/sbin/nologin -- учётка отключена
        setpwent(); // начало файла паролей
        while ((pwd = getpwent()) != NULL)
        {
                DBG_LOG(" -- user -- ");
                showUserInfo(pwd);
        }
        endpwent(); // закрыть открытые файлы
        DBG_LOG(" -- Show all users info end -- ");

        DBG_LOG(" -- Show all group info -- ");
        // #include <grp.h>
        struct group *grp = NULL;
        // pw_shell: /usr/sbin/nologin -- учётка отключена
        setgrent(); // начало файла паролей
        while ((grp = getgrent()) != NULL)
        {
                DBG_LOG("group name: %s", grp->gr_name);

                const char *user = "adm";
                if (strcmp(grp->gr_name, user) == 0)
                {
                        DBG_LOG("Hello %s", user);
                        int i = 0;
                        while (grp->gr_mem[i] != NULL)
                        {
                                DBG_LOG("user in group %s: %s", user, grp->gr_mem[i++]);
                        }
                }
        }
        endgrent(); // закрыть открытые файлы
        DBG_LOG(" -- Show all group info end -- ");

        DBG_LOG(" -- Show system info -- ");
        // #include <sys/utsname.h>
        struct utsname name;
        uname(&name);
        DBG_LOG("struct utsname, machine: %s", name.machine);
        DBG_LOG("struct utsname, nodename: %s", name.nodename);
        DBG_LOG("struct utsname, release: %s", name.release);
        DBG_LOG("struct utsname, sysname: %s", name.sysname);
        DBG_LOG("struct utsname, version: %s", name.version);
        DBG_LOG("struct utsname, machine: %s", name.__domainname);
        DBG_LOG(" -- Show system info end -- ");

        DBG_LOG(" -- Show host info -- ");
        // #include <unistd.h>
        char host_name[_SC_HOST_NAME_MAX];
        gethostname(host_name, _SC_HOST_NAME_MAX);
        DBG_LOG("real host name TCP/IP: %s", host_name);
        DBG_LOG(" -- Show host info -- ");

        exit(0); //<stdlib.h>
        while (1)
        {
                // loop
        }
}


/*
static struct options
{
        const char *filename;
        const char *contents;
        int show_help;
} options;

#define OPTION(t, p) \
        {t, offsetof(struct options, p), 1}

struct fuse_opt
{
        const char *templ;
        unsigned long offset;
        int value;
};

static const struct fuse_opt option_spec[] = {
    OPTION("--name=%s", filename),
    OPTION("--contents=%s", contents),
    OPTION("-h", show_help),
    OPTION("--help", show_help),
    {NULL, 0, 0}};

*/
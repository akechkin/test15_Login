
#include "../utils.hpp"

#include <sys/wait.h> // wait pid

extern char **environ;
int currentPidProc;

static void my_exit1(void)
{
        DBG_LOG("my_exit1, pid: %d", currentPidProc);
}

static void my_exit2(void)
{
        DBG_LOG("my_exit2, pid: %d", currentPidProc);
}

int main(int argc, char *argv[])
{

        DBG_LOG(" -- PROC -- ");

        // AT EXIT REGISTRATIOM BEGIN
        if (atexit(my_exit1) != 0)
        {
                DBG_LOG("error"); // 3
        }

        if (atexit(my_exit2) != 0)
        {
                DBG_LOG("error"); // 2
        }

        if (atexit(my_exit2) != 0)
        {
                DBG_LOG("error"); // 1
        }
        // AT EXIT REGISTRATIOM END

        // environ begin
        for (size_t i = 0; environ[i] != NULL; i++)
        {
                DBG_LOG("env var[%d]: %s", i, environ[i]);
        }

        char *envVal = getenv("SHELL");
        if (envVal)
        {
                DBG_LOG("env val:%s", envVal);
        }

        char *test_env_var = "AS_TEST_VAR=DISABLE";
        if (putenv(test_env_var) != 0)
        {
                DBG_LOG("putenv fail:%s", test_env_var);
        }
        DBG_LOG("getenv: %s, result: %s", test_env_var, getenv("AS_TEST_VAR"));

        char *test_setenv_var_name = "AS_TEST_VAR_SET";
        char *test_setenv_var_val = "DISABLE";

        if (setenv(test_setenv_var_name, test_setenv_var_val, 1) != 0)
        {
                DBG_LOG("setenv fail:%s", test_setenv_var_name);
        }
        DBG_LOG("getenv: %s, result: %s", test_setenv_var_name, getenv(test_setenv_var_name));
        // environ end
        DBG_LOG("pid before fork: %d", getpid());

        int childpid = -1;
        DBG_LOG("------------ fork() -------------");
        if ((currentPidProc = fork()) < 0)
        {
                DBG_LOG("error fork");
        }
        else if (currentPidProc == 0)
        {
                DBG_LOG("child proc pid:%d", getpid());
        }
        else
        {
                DBG_LOG("parent proc pid:%d", getpid());
                childpid = currentPidProc;
        }

        currentPidProc = getpid();

        //--------- get proc info
        DBG_LOG("current pid: %d, parent: %d", getpid(), getppid());

        // реальный идентификатор пользователя вызывающего процесса
        DBG_LOG("current pid: %d, uid: %d", getpid(), getuid());

        // эффективный идентификатор пользователя вызывающего процесса
        DBG_LOG("current pid: %d, effective uid: %d", getpid(), geteuid());
        DBG_LOG("current pid: %d, group id: %d", getpid(), getgid());
        DBG_LOG("current pid: %d, effective group id: %d", getpid(), getegid());

        if (childpid > 0)
        {
                DBG_LOG("wait child: %d, current pid: %d", childpid, getpid());
                /*
                если оставить цикл while (1) то childpid станет ЗОМБИ,
                проверка на ЗОМБИ в терминале ps aux | grep defunct
                */
                // while (1)
                // {
                //         // loop
                // }
                waitpid(childpid, NULL, 0);
                // waitid(P_PID,childpid,NULL,WCONTINUED);  //тоже самое
        }

        // СЕАНСЫ И ГРУППЫ
        // получить группу процессов
        DBG_LOG("current pid: %d, id of group proc: %d", getpid(), getpgrp());
        if (getpgrp() == getpid())
        {
                DBG_LOG("current pid: %d, is LEADER!!!", getpid());
        }
        else
        {

                DBG_LOG("NO LEADER current pid: %d, try create new group", getpid());
                /*
                в данном случае создали новую группу процессов с новым лидером в качестве childpid
                это работает для вызывающего процесса и для его childов
                */
                if (setpgid(0, 0) == 0)
                {
                        DBG_LOG("NO LEADER CHECK current pid: %d, id of group proc: %d", getpid(), getpgrp());
                }
                else
                {
                        DBG_LOG("current pid: %d, error with setpgid(0,0)", getpid());
                }
        }

        if (childpid > 0)
        {
                DBG_LOG("OLD LEADER current pid: %d, id of group proc: %d", getpid(), getpgrp());
        }

        DBG_LOG("current pid: %d, current SID: %d", getpid(), getsid(0));

        DBG_LOG(" -- goodbye! -- pid: %d", currentPidProc);
        // exit(0); //<stdlib.h>
        return (0);
}

#include <stdio.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int system_server()
{
    printf("나 system_server 프로세스!\n");

    while (1) {
        sleep(1);
    }

    return 0;
}

int create_system_server()
{
    pid_t systemPid;
    const char *name = "system_server";

    /* fork 를 이용하세요 */
    if((systemPid = fork()) == 0) {
        printf("여기서 시스템 프로세스를 생성합니다.\n");
        system_server();
    } else if(systemPid == -1)
        perror("error");
    else {
        printf("parent process\n");
    }

    return 0;
}

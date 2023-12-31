#include <stdio.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int input()
{
    printf("나 input 프로세스!\n");

    while (1) {
        sleep(1);
    }

    return 0;
}

int create_input()
{
    pid_t systemPid;
    const char *name = "input";

    printf("여기서 input 프로세스를 생성합니다.\n");

    if((systemPid = fork()) == -1) {
        perror("error\n");
    } else if(systemPid == 0) {
        printf("child process\n");
        input();
    } else {
        printf("parent process\n");
    }

    return 0;
}

#include <stdio.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int create_gui()
{
    pid_t systemPid;

    printf("여기서 GUI 프로세스를 생성합니다.\n");

    sleep(3);
    /* fork + exec 를 이용하세요 */
    /* exec으로 google-chrome-stable을 실행 하세요. */
    /* (execl("/usr/bin/google-chrome-stable", "google-chrome-stable", "http://localhost:8080", NULL)) */
    if((systemPid = fork()) == 0) {
        printf("child process\n");
        execl("/usr/bin/google-chrome-stable", "google-chrome-stable", "http://localhost:8080", NULL);
    } else if(systemPid == -1) {
        perror("error\n");
    } else {
        printf("parent process\n");
    }
    return 0;
}

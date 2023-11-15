#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("mycp needs 3 arguments : ./mycp arg1 arg2\n");
        return -1;
    };

    int fd_from, fd_to;
    int ret = 0;
    char buf[500] = {0, };

    fd_from = open(argv[1], O_RDONLY);
    fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 500);

    if(fd_from < 0 || fd_to < 0) return -1;

    read(fd_from, buf, 500);
    write(fd_to, buf, 500);

    close(fd_from);
    close(fd_to);

    return 0;
}
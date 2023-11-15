#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    
    if(argc != 2) {
        printf("readmid needs 2 arguments : ./readmid arg1\n");
        return -1;
    }
    
    int fd_open = open(argv[1], O_RDONLY);
    char buf[20] = {0, };

    lseek(fd_open, 23, SEEK_SET);
    read(fd_open, buf, 17);
    printf("%s\n", buf);

    close(fd_open);

    return 0;
}
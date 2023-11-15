#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    
    for(int i = 1; i <= 9; i++) {
        pid_t pid = fork();
        if(pid < 0) {
            perror("fork error.\n");
            return -1;
        } else if (pid == 0) {
            for(int j = 1; j <= 9; j++) {
                printf("%d * %d = %d\n", i, j, i * j);
            }
            return 0;
        }
    }
}
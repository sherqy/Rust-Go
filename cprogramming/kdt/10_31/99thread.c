#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* formatting(void* number) {
    int* num = (int*) number;

    for(int i = 1; i <= 9; i++) {
        printf("%d * %d = %d\n", *num, i, *num * i);
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    pthread_t gugudan[9] = {0, };

    for(int i = 1; i <= 9; i++) {
        pthread_create(&gugudan[i - 1], NULL, formatting, (void*)&i);
    }
    for(int i = 1; i <= 9; i++) 
        pthread_join(gugudan[i - 1], NULL);

    return 0;
}
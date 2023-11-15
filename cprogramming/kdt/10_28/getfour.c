#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    if(argc != 2) {
        printf("getfour needs two arguments : ./getfour arg1\n");
        return -1;
    }
    
    FILE* myfile = fopen("num.txt", "r");
    FILE* four = fopen("four.txt", "w");
    char buf[10] = {0, };
    int result = 0;

    if(myfile == NULL || four == NULL) {
        printf("file didn't opened.\n");
        return -1;
    }

    while(fgets(buf, sizeof(buf), myfile) != NULL) {
        if (atoi(buf) % 4 == 0) {
            fputs(buf, four);
            result++;
        }
    }

    printf("%d\n", result);
    fclose(myfile);
    fclose(four);

    return 0;
}
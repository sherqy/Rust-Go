#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    
    if(argc != 4 || argv[2] > argv[3]) {
        printf("argument error.\n");
        return -1;
    }

    FILE* myfile = fopen(argv[1], "r");

    if(myfile == NULL) {
        printf("File didn't open\n");
        return -1;
    }

    int arg1 = atoi(argv[2]);
    int arg2 = atoi(argv[3]);
    int num = 1;
    char buf[100] = {0, };

    while(fgets(buf, sizeof(buf), myfile) != NULL) {
        if(num >= arg1 && num <= arg2) {
            printf("%s", buf);
        }
        num++;
    }

    fclose(myfile);
    return 0;
}
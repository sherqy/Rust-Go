#include <stdio.h>

int checkprime(int num);

int main() {

    for(int i = 1; i <= 100; i++) {
        
        if(checkprime(i)) printf("%d is a prime number.\n", i);
        else printf("%d is not a prime number.\n", i);
    }

    return 0;
}
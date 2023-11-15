#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int number = atoi(argv[1]);
	int status;
	int sum = 0;
	int fac = 1;


	pid_t summation = fork();
	if(summation < 0) return -1;
	else if(summation == 0) {
		for(int i = 1; i <= number; i++) sum += i;
		printf("The summation is %d\n", sum);
		return sum;
	}

	pid_t factorial = fork();
	if(factorial < 0) return -1;
	else if(factorial == 0) {
		for(int i = 1; i <= number; i++) fac *= i;
		printf("The factorial is %d\n", fac);
		return fac;
	}

	waitpid(summation, &status, 0);
	//printf("sum of summation and factorial is %d\n", sum + fac);
    sum = WEXITSTATUS(status);

	waitpid(factorial, &status, 0);
	//printf("sum of summation and factorial is %d\n", sum + fac);
	fac = WEXITSTATUS(status);

	printf("sum of summation and factorial is %d\n", sum + fac);
	return 0;
}

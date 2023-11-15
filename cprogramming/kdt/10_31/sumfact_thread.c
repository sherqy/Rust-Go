#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int sumfact = 0;

void* sum(void* num) {
	int* count = (int*) num;
	int answer = 0;
	for(int i = 1; i <= *count; i++) {
		answer += i;
	}
	sleep(1);
	sumfact += answer;
	printf("The sum is %d.\n", answer);
	return NULL;
}

void* fac(void* num) {
	
	int* count = (int*) num;
	int answer = 1;
	for(int i = 1; i <= *count; i++) {
		answer *= i;
	}
	sleep(2);
	sumfact += answer;
	printf("The factorial is %d.\n", answer);
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t summation;
	pthread_t factorial;
	int number = atoi(argv[1]);
	
	pthread_create(&summation, NULL, sum, (void *)&number);
	pthread_create(&factorial, NULL, fac, (void*)&number);
	pthread_join(summation, NULL);
	pthread_join(factorial, NULL);
	printf("The sumfact is %d.\n", sumfact);

	return 0;
}
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	int pid;

	pid = fork();
	if(pid == 0)
		//child
		printf("Child of %d is %d\n", getppid(), getpid());
	else
		//parent
		printf("I am %d. My child is %d\n", getpid(), pid);
}

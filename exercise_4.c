#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void fork_recursively() {
	int child_process_id = fork();
	if (child_process_id == 0) {
		printf("pid: %d\n", getpid());
		if (getpid() % 2 == 0) {
			printf("Child process created! ID %d\n", getpid());
			fork_recursively();
		}
	} else {
		signal(SIGCHLD, SIG_IGN);
	}
}

int main() {
	
	fork_recursively();
	printf("pid %d; ppid %d\n", getpid(), getppid());
	while(1);
	return 0;
}

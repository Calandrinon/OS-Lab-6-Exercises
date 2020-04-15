#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	char command[30];
	printf("Enter the command:");
	//fgets(command, sizeof(command), stdin);
	scanf("%s", command);
	
	int process_id = fork();

	if (process_id == 0) {
		execlp(command, command, (char*)NULL);
	} else {
		wait(0);
	}

	return 0;
}

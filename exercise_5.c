#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int n, sum = 0;
	printf("n=");
	scanf("%d", &n);
	int* v = malloc(n*sizeof(int));
	for (int i = 0; i < n; i++) {
		printf("v[%d]=", i);
		scanf("%d", &v[i]);
	}
	
	int my_pipe[2];	
	pipe(my_pipe);	

	int pid = fork();

	if (pid == 0) {
		close(my_pipe[0]);	
		for (int i = 0; i < n; i++) {
			if (v[i] % 2 == 1)
				sum += v[i];	
		}

		write(my_pipe[1], &sum, sizeof(int));
		close(my_pipe[1]);	
		exit(0);
	} else {
		close(my_pipe[1]);
		read(my_pipe[0], &sum, sizeof(int));
		close(my_pipe[0]);
		
		for (int i = 0; i < n; i++)
			if (v[i] % 2 == 0)
				sum += v[i];

		wait(0);		
		printf("%d\n", sum);
	}
	
	free(v);
	return 0;
}

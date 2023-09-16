#include <stdlib.h>
#include <stdio.h>
#include <nanvix/pm.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 100

static void work_cpu(void)
{
	int c;

	c = 0;

	/* Perform some computation. */
	for (int i = 0; i < 4096; i++)
	{
		int a = 1 + i;
		for (int b = 2; b < i; b++)
		{
			if ((i%b) == 0)
				a += b;
		}
		c += a;
	}
}

static void work_io(void)
{
	int fd;            /* File descriptor. */
	char buffer[2048]; /* Buffer.          */

	/* Open hdd. */
	fd = open("/dev/hdd", O_RDONLY);
	if (fd < 0)
		_exit(EXIT_FAILURE);

	/* Read data. */
	for (size_t i = 0; i < MEMORY_SIZE; i += sizeof(buffer))
	{
		if (read(fd, buffer, sizeof(buffer)) < 0)
			_exit(EXIT_FAILURE);
	}

	/* House keeping. */
	close(fd);
}

int getinfo(pid_t pid){
	struct process_buf buffer;

	if (get_process_info(pid, &buffer) < 0) {
		
		printf("Processo nao encontrado.\n");
	}

	return buffer.counter;
}

void print_info(pid_t pid){
	struct process_buf buffer;

	printf("\n------------------------------------------------------------------\n");
	printf("\n PID - Counter - Priority\n");
	get_process_info(pid, &buffer);
	int priority = buffer.priority + buffer.nice + ((buffer.counter * buffer.counter) >> 6);
	printf("%d   -   %d   -   %d\n", buffer.pid, buffer.counter, priority);
}

int main(){
	pid_t pid;
	pid = fork();
	if(pid == 0){
		pid = fork();
		pid = fork();
		if(pid==0)
		{
			while(1==1){
				work_cpu();
				sleep(10);
			} 
		}else{
			work_io();
		}
	}else{
		while(1==1){
			print_info(pid);
			sleep(1);
		}
	}
	return 0;
}

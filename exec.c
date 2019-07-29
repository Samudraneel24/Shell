#include "header.h"
void other_func(char *token, int *job_pid, char **job_name)
{
	char* argv[10] = {NULL};
	int status;
	int i=0;
	int flag = 0;
	while (token != NULL){
		argv[i] = token;
		token = strtok(NULL, " \n\t");
		i++;
	}
	if( strcmp(argv[i-1],"&") == 0)
		flag = 1;
	if(flag == 1){
		argv[i-1] = NULL;
	}
	int pid1 = fork();
	if (pid1 == -1){
		printf("\nFork failed");
		return;
	} 
	else if (pid1 == 0){
		int pid2;
		if(flag == 1){
			pid2 = fork();
			if(pid2==0){
				signal(SIGINT, SIG_IGN);
				int err = execvp(argv[0], argv);
				if(err<0)
					printf("Command not found\n");
			}
			else{
				signal(SIGINT, SIG_IGN);
				int st;
				waitpid(pid2,&st,0);
				if (WIFEXITED(st)){
					printf("\nProcess with pid %d exited normally.\n", pid2);
				}
				else{
					int exitstat = WEXITSTATUS(st);
					printf("\nProcess with pid %d terminated abnormally.\n", pid2);
				}

				exit(0);
			}
		}
		else{
			signal(SIGINT, SIG_DFL);
			int err = execvp(argv[0], argv);
			if(err<0)
				printf("Command not found\n");
			exit(0);
		}
	} 
	else{
		signal(SIGINT, SIG_IGN);
		if(flag == 0){
			while(wait(&status)!=pid1)
				continue;
		}
		else{
			int i=0;
			while (job_pid[i] != -1)
				i++;
			job_pid[i] = pid1 + 1;
			job_name[i] = argv[0];
		}
		return;
	}
}


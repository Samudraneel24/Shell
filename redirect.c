#include "header.h"

int redirect(char *token, int *job_pid, char **job_name)
{
	int r = 0, is_inp = 0, is_out = 0, is_app = 0;
	char* input[20]={NULL};
	int size=0,status,i,flag = 0;
	token = strtok(token," \t\n");
	while(token!=NULL){
		input[size++]=token;
		token = strtok(NULL, " \n\t");
	}
	// if(strcmp(input[size-1],"&")==0)
	// 	flag = 1;
	// if (flag == 1){
	// 	input[i - 1] = NULL;
	// }
	char filein[100]={0}, fileout[100]={0}, app[100]={0};
	int pid1 = fork();
	if (pid1 == 0){
		// int pid2;
		for (int i = 0; i < size; i++){
			if (strcmp(input[i],"<") == 0){
				is_inp = 1;
				input[i] = NULL;
				strcpy(filein, input[i + 1]);
			}

			if (input[i] != NULL){
				if (strcmp(input[i],">>") == 0){
					is_app = 1;
					input[i] = NULL;
					strcpy(app, input[i + 1]);
				}
			}

			if (input[i] != NULL){
				if (strcmp(input[i], ">") == 0){
					is_out = 1;
					input[i] = NULL;
					strcpy(fileout, input[i + 1]);
				}
			}

		}
		if (is_inp)
		{
			int fd;
			fd = open(filein, O_RDONLY, 0);
			if (fd < 0)
			{
				perror("open");
				exit(0);
			}
			dup2(fd, 0);
			close(fd);
		}
		if (is_app)
		{
			struct stat buffer;
			if (stat(app, &buffer) == 0)
			{
				int fa;
				fa = open(app, O_APPEND | O_WRONLY);
				if (fa < 0)
				{
					perror("open");
					exit(0);
				}
				dup2(fa, 1);
				close(fa);
			}
			else
			{
				int fa;
				fa = creat(app, 0644);
				if (fa < 0)
				{
					perror("Could not create output file");
					exit(0);
				}
				dup2(fa, 1);
				close(fa);
			}
		}
		if (is_out & !is_app)
		{
			struct stat buf;
			if (stat(fileout, &buf) == 0)
			{
				int fo;
				fo = open(fileout, O_TRUNC | O_WRONLY);
				if (fo < 0)
				{
					perror("Could not open output file");
					exit(0);
				}
				dup2(fo, 1);
				close(fo);
			}
			else
			{
				int fo;
				fo = creat(fileout, 0644);
				if (fo < 0)
				{
					perror("creat");
					exit(0);
				}
				dup2(fo, 1);
				close(fo);
			}
		}
		if (execvp(input[0], input) < 0)
		{
			r = 1;
			printf("%s: Command doesn't exist\n", input[0]);
		}
	}
		else
		{
			wait(NULL);
		}
		
	return 1;
}

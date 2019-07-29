#include "header.h"

void jobs_func(int *job_pid,  char** job_name){
	int i=0;
	while(i<1000){
		if(job_pid[i]!=-1){
			// printf("jndk");
			char arr[100] = {0};
			strcpy(arr, "/proc/");
			int pid = job_pid[i],dig,cur=6,size = 0;
			while(pid>0){
				size++;
				pid/=10;
			}
			// printf("%d",size);	
			pid = job_pid[i];
			while (pid>0){
				dig = pid%10;
				arr[size+cur-1] = dig+'0';
				size--;
				pid/=10;
			}
			strcat(arr,"/stat");
			FILE *file = fopen(arr, "r");
			char status[100] = {0};
			if (file == NULL){
				strcpy(status, "Stopped");
				printf("[%d]\t%s\t\t%s[%d]\n", i + 1, status, job_name[i], job_pid[i]);
				job_pid[i] = -1;
			}
			else{
				char proc_status;
				char name[100] = {0};
				int err = fscanf(file, "%d", &pid);
				if (err < 0)
					perror("fscanf");
				err = fscanf(file, "%s", name);
				if (err < 0)
					perror("fscanf");
				err = fscanf(file, " %c", &proc_status);
				if(proc_status=='T' || proc_status=='Z')
					strcpy(status,"Stopped");
				else
					strcpy(status,"Running");
				if (err < 0)
					perror("fscanf");
				fclose(file);
				printf("[%d]\t%s\t\t%s[%d]\n", i + 1, status, job_name[i], job_pid[i]);
			}
		}
		i++;
	}
}

void kjob_func(char* token, int* job_pid){
	char *argv[10] = {NULL};
	token = strtok(NULL, " \n\t");
	int flag = 0;
	for (int i = 0; i < strlen(token); i++)
		if (token[i] < 48 || token[i] > 57)
			flag = 1;
	if (flag == 1){
		printf("Wrong format of command\n");
		return;
	}
	int job_id = atoi(token);
	token = strtok(NULL, " \n\t");
	flag = 0;
	for (int i = 0; i < strlen(token); i++)
		if (token[i] < 48 || token[i] > 57)
			flag = 1;
	if (flag == 1){
		printf("Wrong format of command\n");
		return;
	}
	int sig = atoi(token);
	int pid = job_pid[job_id-1];
	int err=-1;
	if(pid>0)
		err = kill(pid,sig);
	if(err<0)
		printf("Process does not exist\n");
	return;
}

void overkill(int* job_pid){
	int i=0;
	while(job_pid[i]!=-1){
		kill(job_pid[i++],9);
	}
}

// void fg_func(char* token, int* fg, int* job_pid){
// 	token = strtok(NULL," \t\n");
// 	int flag = 0;
// 	for (int i = 0; i < strlen(token); i++)
// 		if (token[i] < 48 || token[i] > 57)
// 			flag = 1;
// 	if (flag == 1){
// 		printf("Wrong format of command\n");
// 		return;
// 	}
// 	int status, job_no = atoi(token);
// 	fg[job_no-1] = 1;
// 	signal(SIGINT, handle_c);
// 	signal(SIGTSTP, handle_z);
// 	// printf("%d %d\n",job_no-1,job_pid[job_no-1]);
// 	waitpid(job_pid[job_no-1]-1,&status,WUNTRACED);
// 	return;
// }
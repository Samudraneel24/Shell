#include "header.h"

#define clear() printf("\033[H\033[J")
int job_pid[1000];
char *job_name[1000] = {NULL};

int main(){
	char homedir[200]={0},curdir[200]={0},relpath[200];
	clear();
	pwd_func(curdir);
	strcpy(homedir,curdir);
	int exit = 0;
	for (int i = 0; i < 1000; i++){
		job_pid[i] = -1;
	}
	while(1){
		pwd_func(curdir);
		char* username = getenv("USER");
		struct utsname unameData;
		uname(&unameData);
		if(strlen(curdir)<strlen(homedir))
	    	printf("%s@%s:~%s$ ", username, unameData.nodename, curdir);
		else{
			for(int i=0;i<200;i++)
				relpath[i] = '\0';
			int i=0,j=0;
			while(i<200 && curdir[i]!='\0' && homedir[i] == curdir[i])
				i++;
			while(i<200 && curdir[i]!='\0'){
				relpath[j] = curdir[i];
				i++,j++;
			}	
			if(relpath!=NULL)
		    	printf("%s@%s:~%s$ ", username, unameData.nodename, relpath);
		    else
		    	printf("%s@%s:~$ ", username, unameData.nodename);
		}
		signal(SIGINT, SIG_IGN);
		// signal(SIGQUIT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
        // signal(SIGTTIN, SIG_IGN);
        // signal(SIGTTOU, SIG_IGN);
        // signal(SIGCHLD, SIG_IGN);
		size_t buffer_size = 200;
	    char *input;
	    input = (char *)malloc(buffer_size * sizeof(char));
	    int input_size = getline(&input,&buffer_size,stdin );
	    char* allcomm = strtok(input, ";\n");
	    char * comlist[500];
	    int i=0;
	    while(allcomm!=NULL){
	    	comlist[i++] = allcomm;
	    	allcomm = strtok(NULL,";\n");
	    }
	    for(int j=0;j<i;j++){
			if(comlist[j]==NULL)
				continue;
			int red = 0,pipe = 0;
			for (int x = 0; x < strlen(comlist[j]); x++){
				if(comlist[j][x]=='|')
					pipe = 1;
				if (comlist[j][x] == '<' || comlist[j][x] == '>')
					red = 1;
			}
			pwd_func(curdir);
			if (pipe){
				pipe_func(comlist[j],job_pid,job_name);
			}
			else if (red)
			{
				redirect(comlist[j], job_pid, job_name);
			}
			else{
				char *command = strtok(comlist[j], " \t\n");
				if(command==NULL)
					continue;
				if(strcmp(command,"echo") == 0)
			    	echo_func(command);
			    else if(strcmp(command,"quit") == 0){
			    	exit = 1;
			    	break;
			    }
			    else if(strcmp(command,"pwd") == 0)
			    	printf("%s\n",curdir);
			    else if(strcmp(command,"cd") == 0)
			    	cd_func(command,homedir);
			    else if(strcmp(command,"remindme") == 0)
			    	remindme_func(command);
			    else if(strcmp(command,"pinfo") == 0)
			    	pinfo_func(command,homedir);
			    else if(strcmp(command,"clock") == 0)
			    	clock_func(command);
			    else if(strcmp(command,"ls") == 0)
			    	ls_func(command);
				else if (strcmp(command, "setenv") == 0)
					setenv_func(command);
				else if (strcmp(command, "unsetenv") == 0)
					unsetenv_func(command);
				else if (strcmp(command, "jobs") == 0)
					jobs_func(job_pid,job_name);
				else if (strcmp(command, "kjob") == 0)
					kjob_func(command, job_pid);
				else if (strcmp(command, "overkill") == 0)
					overkill(job_pid);
				else
			    	other_func(command, job_pid, job_name);
				printf("\n");
			}
		}
		if(exit == 1)
		    break;
	}
	clear();
    return 0;
}
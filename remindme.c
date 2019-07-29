#include "header.h"
void remindme_func(char* token){
	token = strtok(NULL, " \n\t");
	if(token==NULL){
		printf("Wrong input format\n");
		return;
	}
	int flag = 0;
	for(int i=0;i<strlen(token);i++)
		if(token[i]<48 || token[i]>57)
			flag = 1;
	if(flag == 1){
		printf("Wrong format of command\n");
		return;
	}
	int interval = atoi(token);
	char* inp[500] = {NULL};
	int i = 0;
	if(token==NULL){
		printf("Wrong input format\n");
		return;
	}
	token = strtok(NULL, " \n\t");
	if(token==NULL){
		printf("Wrong input format\n");
		return;
	}
	inp[i++] = token;
	while (token != NULL){
        token = strtok(NULL, " \n\t");
        if(token!=NULL)
        	inp[i++] = token;
    }
    inp[i-1][strlen(inp[i-1])-1] = '\0';
    for(int j=0;j<strlen(inp[0]);j++)
    	inp[0][j] = inp[0][j+1];
    int pid1 = fork();
    if (pid1 == -1){
		printf("\nFork failed");
		return;
	} 
	else if (pid1 == 0){
		sleep(interval);
		printf("\n");
		printf("Remainder: ");
		for(int j=0;j<i;j++){
			printf("%s ",inp[j] );
		}
		printf("\n");
		exit(0);
	} 
	else{
		return;
	}
}
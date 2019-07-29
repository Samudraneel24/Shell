#include "header.h"
int pinfo_func(char* token,char homedir[]){
	char arr[200] = {0}, temp[200] = {0};
	strcpy(arr,"/proc/");
	token = strtok(NULL, " \n\t");
	if(token!=NULL)
		strcat(arr,token);
	else
		strcat(arr,"self");
	strcpy(temp,arr);
	strcat(arr,"/stat");
	FILE * file = fopen(arr,"r");
	if(file == NULL){
		printf("Process not found\n");
        return 1;
    }
	int pid;
	char proc_status;
	char name[100]={0};
	int err = fscanf(file,"%d",&pid);
	if(err<0)
		perror("fscanf");
	err = fscanf(file, "%s", name);
	if(err<0)
		perror("fscanf");
	err = fscanf(file, " %c", &proc_status);
	if(err<0)
		perror("fscanf");
	printf( "pid: %d\n", pid);
    printf( "Process Status: %c\n", proc_status);
    fclose(file);
    strcpy(arr,temp);
    strcat(arr,"/statm");
    FILE * mem = fopen(arr, "r");
    if(mem == NULL){
		printf("Process not found\n");
        return 1;
    }
    int memSize;
    err = fscanf(mem, "%d", &memSize);
    if(err<0)
		perror("fscanf");
    err = fprintf(stdout, "Memory: %d\n", memSize);
    if(err<0)
		perror("fscanf");
    fclose(mem);
    char exp[1000]={0};
    strcpy(arr, temp);
    strcat(arr, "/exe");
    int len = readlink(arr, exp, sizeof(exp));
    if(len<0){
    	perror("readlink");
    	return 1;
    }
    int sameChars = 0, baseL = strlen(homedir);
    for(sameChars = 0; sameChars < baseL; sameChars++)
        if(homedir[sameChars] != exp[sameChars])
       		break;
    
    char relPath[1000]={0};
    if(sameChars == baseL) {
        relPath[0] = '~';
        relPath[1] = '\0';
        strcat(relPath, &exp[baseL]);
    }
    else{
        strcpy(relPath, exp);
        relPath[strlen(exp)] = '\0';
    }
    int i = 0;
    while(exp[i]){
    	exp[i] = '\0';
    	i++;
    }
    printf( "Executable Path: %s\n", relPath);
    return 0;
}
#include "header.h"

int setenv_func(char* token){
    token = strtok(NULL, " \n\t");
    if(token==NULL){
        printf("Arguments not given\n");
        return 1;
    }
    char arg1[200]={0},arg2[200]={0};
    strcpy(arg1,token);
    token = strtok(NULL, " \n\t");
    if(token==NULL)
        strcpy(arg2," ");
    else
        strcpy(arg2,token);
    if(setenv(arg1, arg2, 1) != 0)
        perror("shell");
    return 1;
}

int unsetenv_func(char *token){
    token = strtok(NULL, " \n\t");
    if(token==NULL){
        printf("Argument not given\n");
        return 1;
    }
    if (unsetenv(token) != 0)
        perror("shell");
    return 1;
}

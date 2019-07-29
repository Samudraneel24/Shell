#include "header.h"
int echo_func(char* token){
	while (token != NULL) {
        token = strtok(NULL, " \n\t");
        if(token!=NULL)
        	printf("%s ", token);
    }
    return 0;
}
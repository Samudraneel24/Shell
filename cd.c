#include "header.h"
int cd_func(char* token,char homedir[]){
	token = strtok(NULL," \t\n");
	if(token==NULL || strcmp(token,"~")==0){
		int x=chdir(homedir);
		if(x<0)
			perror("cd");
	}
	else{
		int x=chdir(token);
		if(x<0)
			perror("cd");
	}
	return 0;
}
#include "header.h"
void ls_func(char* token){
	struct dirent ** namelist;
	int n;
	token = strtok(NULL, " \n\t");
	char* args[5]={NULL};
	int i=0,argnum=1;
	int hidden = 0, longlist = 0;
	while(token!=NULL){
		argnum++;
		if(strcmp(token,"-l") == 0)
			longlist = 1;
		if(strcmp(token,"-a") == 0)
			hidden = 1;
		else if(strcmp(token,"-la") == 0 || strcmp(token,"-al") == 0){
			longlist = 1;
			hidden = 1;
		}
		args[i++] = token;
		token = strtok(NULL, " \n\t");
	}
	char tmppath[500]={0};
	int flag = 0;
	if(argnum==1 || strcmp(args[i-1],"-l")==0 || strcmp(args[i-1],"-a")==0 || strcmp(args[i-1],"-al")==0 || strcmp(args[i-1],"-la")==0)
		flag = 1;
	if(flag == 1)
		n = scandir(".",&namelist,NULL,alphasort);
	else{
		strcpy(tmppath,args[i-1]);
		n = scandir(args[i-1],&namelist,NULL,alphasort);
	}
	if(n < 0){
		perror("scandir");
		return;
	}
	else{
		if(longlist==0){
			if(hidden==1){
				for(int i=0;i<n;i++){
					printf("%s\n",namelist[i]->d_name );
					free(namelist[i]);
				}
			}
			else{
				for(int i=0;i<n;i++){
					if(namelist[i]->d_name[0]!='.')
						printf("%s\n",namelist[i]->d_name );
					free(namelist[i]);
				}
			}
		}
		else{
			printf("\n");
			for(int i=0;i<n;i++){
				if(hidden==0 && namelist[i]->d_name[0]=='.'){
					free(namelist[i]);
					continue;
				}
				struct stat per;
				char path[500]={0};
				if(flag==0){
					strcpy(path,tmppath);
					strcat(path,"/");
				}
				strcat(path,namelist[i]->d_name);
				int error = lstat(path,&per),link=0;
				mode_t chbits = per.st_mode;
				if( (S_ISLNK(chbits)) ){
					link=1;
					printf("l");
				}
				if(link==0){
					error = stat(path,&per);
					mode_t chbits = per.st_mode;
					if( (S_ISDIR(chbits)) )
						printf("d");
					else if( (S_ISSOCK(chbits)) )
						printf("s");
					else if( (S_ISCHR(chbits)) )
						printf("c");
					else if( (S_ISBLK(chbits)) )
						printf("b");
					else
						printf("-");
				}
					
				printf( (chbits & S_IRUSR) ? "r" : "-");
				printf( (chbits & S_IWUSR) ? "w" : "-");
				printf( (chbits & S_IXUSR) ? "x" : "-");
				printf( (chbits & S_IRGRP) ? "r" : "-");
				printf( (chbits & S_IWGRP) ? "w" : "-");
				printf( (chbits & S_IXGRP) ? "x" : "-");
				printf( (chbits & S_IROTH) ? "r" : "-");
				printf( (chbits & S_IWOTH) ? "w" : "-");
				printf( (chbits & S_IXOTH) ? "x" : "-");

				printf("\t%ld",per.st_nlink);

				struct passwd *user = getpwuid(per.st_uid);
				printf("\t%s", user->pw_name);

				struct group *group = getgrgid(per.st_gid);
				printf("\t%s", group->gr_name);

				printf("\t%ld",per.st_size);

				time_t curtime;
				struct tm* initime;
				char mod[13];
				time(&curtime);
				int curyear = localtime(&curtime)->tm_year;
				initime = localtime(&per.st_ctime);
				if(initime->tm_year == curyear)
					strftime(mod,13,"%b %e %R",initime);
				else
					strftime(mod,13,"%b %e %Y",initime);
				printf("\t%s",mod );	 	

				printf("\t%s\n",namelist[i]->d_name );
				free(namelist[i]);
			}
		}
		free(namelist);
	}
	return;
}
#include "header.h"
void display_clock(){
	int fd = open("/proc/driver/rtc", O_RDONLY);
	if(fd<0)
		perror("open");
	char arr[1000]={0};
	read(fd,arr,1000);
	char sec[5]={0},min[5]={0},hour[5]={0},day[5]={0},mon[5]={0},year[5],month[10]={0};
	hour[0] = arr[11];
	hour[1] = arr[12];
	min[0] = arr[14];
	min[1] = arr[15];
	sec[0] = arr[17];
	sec[1] = arr[18];
	year[0] = arr[31];
	year[1] = arr[32];
	year[2] = arr[33];
	year[3] = arr[34];
	mon[0] = arr[36];
	mon[1] = arr[37];
	day[0] = arr[39];
	day[1] = arr[40];
	int m = atoi(mon);
	if(m == 1)
		strcpy(month,"Jan");
	if(m == 2)
		strcpy(month,"Feb");
	if(m == 3)
		strcpy(month,"Mar");
	if(m == 4)
		strcpy(month,"Apr");
	if(m == 5)
		strcpy(month,"May");
	if(m == 6)
		strcpy(month,"Jun");
	if(m == 7)
		strcpy(month,"Jul");
	if(m == 8)
		strcpy(month,"Aug");
	if(m == 9)
		strcpy(month,"Sep");
	if(m == 10)
		strcpy(month,"Oct");
	if(m == 11)
		strcpy(month,"Nov");
	if(m == 12)
		strcpy(month,"Dec");
	printf("%d %s %d, %d:%d:%d\n",atoi(day),month,atoi(year),atoi(hour),atoi(min),atoi(sec));
	close(fd);
}

int gettime(){
	int fd = open("/proc/driver/rtc", O_RDONLY);
	if(fd<0)
		perror("open");
	char arr[1000]={0};
	int x = read(fd,arr,1000);
	if(x<0)
		perror("read");
	char sec[5]={0};
	sec[0] = arr[17];
	sec[1] = arr[18];
	close(fd);
	return atoi(sec); 
}

void clock_func(char* token){
	token = strtok(NULL, " \n\t");
	if(token==NULL || strcmp(token,"-t")!=0){
		printf("Wrong input format\n");
		return;
	}
	token = strtok(NULL, " \n\t");
	int flag = 0;
	for(int i=0;i<strlen(token);i++)
		if(token[i]<48 || token[i]>57)
			flag = 1;
	if(token==NULL || flag == 1){
		printf("Wrong input format\n");
		return;
	}
	int interval = atoi(token);
	token = strtok(NULL, " \n\t");
	if(token==NULL || strcmp(token,"-n")!=0){
		printf("Wrong input format\n");
		return;
	}
	token = strtok(NULL, " \n\t");
	flag = 0;
	for(int i=0;i<strlen(token);i++)
		if(token[i]<48 || token[i]>57)
			flag = 1;
	if(token==NULL || flag == 1){
		printf("Wrong input format\n");
		return;
	}
	int duration = atoi(token);
	int curtime,prevtime=0,time_elapsed=0;
	flag = 0;
	while(1){
		curtime = gettime();
		if(curtime == prevtime)
			continue;
		if( (curtime-prevtime)%interval == 0 || flag == 0){
			display_clock();
			flag = 1;
			prevtime = curtime;
			time_elapsed+=interval;
			if(time_elapsed>duration)
				break;
		}
	}
}
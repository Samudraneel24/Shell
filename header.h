#ifndef HEAD
#define HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <signal.h>
int pwd_func(char curdir[]);
int cd_func(char* token,char homedir[]);
int echo_func(char* token);
void ls_func(char* token);
void display_clock();
int gettime();
void clock_func(char* token);
int pinfo_func(char* token,char homedir[]);
void remindme_func(char* a);
void other_func(char* a, int* c, char** d);
int setenv_func(char* a);
int unsetenv_func(char* a);
void kjob_func(char* a, int* b);
int redirect(char *a,int*b, char **c);
int pipe_func(char* a,int* b, char** c);
// int spawn(int a, int b, int lol, char** c);
void jobs_func(int* a,char** b);
void overkill(int* a);
#endif
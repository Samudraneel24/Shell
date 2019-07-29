#include "header.h"

int pipe_func(char *cmd, int *job_pid, char **job_name)
{
    char* pipe_commands[50]={NULL};
    char *temp = strtok(cmd, "|\n");
    char* temp2;
    int i=0;
    while (temp != NULL)
    {
        if (strlen(temp)){
            pipe_commands[i++]=temp;
        }

        temp = strtok(NULL, "|");
    }

    int in = 0, initial_stdin, initial_stdout;
    int fd[2];
    initial_stdin = dup(0);
    initial_stdout = dup(1);

    temp = pipe_commands[i-1];
    for(int j=0;j<i-1;j++)
    {
        if (pipe_commands[j] == NULL)
            break;
        if (pipe(fd) < 0)
            perror("Piping Failed");

        int pid = fork();

        if (pid < 0)
            perror("Fork Error");

        else if (pid == 0)
        {
            if (in != 0)
            {
                dup2(in, 0);
                close(in);
            }

            dup2(fd[1], 1);
            close(fd[1]);
            
            // other_func(pipe_commands[j], job_pid, job_name);
            // pipe_commands[j] = strtok(pipe_commands[j], " \t\n");
            redirect(pipe_commands[j],job_pid,job_name);
                exit(0);
        }

        else
        {
            close(fd[1]);
            wait(NULL);
            in = fd[0];
        }
    }

    if (in != 0)
    {
        dup2(in, 0);
        close(in);
    }
    // other_func(temp, job_pid, job_name);
    // temp = strtok(temp," \t\n");
    redirect(temp, job_pid, job_name);

    dup2(initial_stdin, 0);
    if (initial_stdin != 0)
        close(initial_stdin);

    dup2(initial_stdout, 1);
    if (initial_stdout != 1)
        close(initial_stdout);

    return 0;
}
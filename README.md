# Shell Readme

- Run make command, it will give an executable file "shell"
- The clock command has the format :-   clock -t <interval> -n <duration>
  
## Function locations:
  - main.c contains the main() function.
  - pwd.c contains pwd_func() function for pwd command.
  - cd.c contains cd_func() function for cd command.
  - echo.c contains echo_func() function for echo command.
  - ls.c contains ls_func() function for ls command.
  - pinfo.c contains pinfo_func() function for pinfo command.
  - remindme.c contains remindme_func() function for remindme command.
  - clock.c contains display_clock(), gettime(), clock_func() functions for clock command.
  - exec.c contains other_func() function for any other command.
  - redirect.c contains function for redirection.
  - pipe.c contains function to implement piping.
  - job.c contains functions for jobs, overkill, kjob commands.
  - makefile has been included.

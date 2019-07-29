shell:main.c redirect.c pipe.c job.c env.c pwd.c cd.c echo.c ls.c clock.c pinfo.c remindme.c exec.c
	gcc -o shell redirect.c pipe.c job.c env.c main.c pwd.c cd.c echo.c ls.c clock.c pinfo.c remindme.c exec.c

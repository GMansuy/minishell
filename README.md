# Minishell
Un partenariat improbable

Fichiers de rendu 	Makefile, *.h, *.c
Fonctions externes autorisées
		readline, rl_clear_history, rl_on_new_line,
		rl_replace_line, rl_redisplay, add_history,

		printf, malloc, free, write, access, open, read,
		close,

		fork, wait, waitpid, wait3, wait4,

SIGNALS				https://youtu.be/83M5-NPDeWs
		signal (async) -> more options :sigaction
		killsigemptyset, sigaddset, , exit,

		getcwd, chdir, stat, lstat, fstat, unlink,
		
		execve, dup, dup2, pipe, opendir, readdir, closedir,
		strerror, perror, isatty, ttyname, ttyslot, ioctl,
		getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
		tgetnum, tgetstr, tgoto, tputs

lexer.c	test de la mort Eliot

		arvg[1] = <<testd>><>><>>>>><<dac       |       flex_dup()      |       enter function()

		<<testd>><>><>>>>><<dac

		lex[0]  '<<testd'               len = 7 type = HERE_DOC
		lex[1]  '>><'           len = 3 type = APPEND
		lex[2]  '>><'           len = 3 type = APPEND
		lex[3]  '>>'            len = 2 type = APPEND
		lex[4]  '>>'            len = 2 type = APPEND
		lex[5]  '><<dac'                len = 6 type = OUTFILE

DOC:
---> SHELL COMMAND LANGUAGE : https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
---> WRITING YOUR OWN SHELL : https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

--> Bash/Notions :	https://fr.wikibooks.org/wiki/Programmation_Bash/Notions_essentielles_du_shell_bash
					https://guidespratiques.traduc.org/guides/vf/Bash-Beginners-Guide/Bash-Beginners-Guide.html
					
--> The aim of this project is to create a simple shell, to learn about processes, file descriptors and pipes. Inspired by the "42 Coding School" exercise "minishell" (January 2022). aenglert42/minishell - bytemeta:	https://bytemeta.vip/repo/aenglert42/minishell

--> GitHub - iciamyplant/Minishell: This is my final 42's project Minis...
This is my final 42&#39;s project Minishell, I implemented my own shell in C, which supports redirections, pipes, environment variables and several builtins - GitHub - iciamyplant/Minishell: Th... :	https://github.com/iciamyplant/Minishell
								https://github.com/vietdu91/42_minishell


pour les here_doc : bool pour savoir si il y a des quotes dans LIMITER (a faire dans lexer)




--> Conférences 42sh 2019 - Architecture d'un shell :https://www.youtube.com/watch?v=oIFRiwFRSRY

builtins :
- Dans le fork() => echo, pwd, env 
- Hors du fork() => cd, export, unset, exit		--> NE FONCTIONNENT PAS SI PIPE 


NOTES :

-> parfois enter marche plus et ecrit ^M
-> SHLVL


TESTS_GOOGLEDOC

valgrind --suppressions=./.ignore_readline ./minishell
	
/*
 * exec.c
 * 
 * Copyright 2012 
 * 	Darlan Passos Jambersi <darlanpj@gmail.com>, 
 * 	Felipe Augusto do Amaral <amaral.felipeaugusto@gmail.com> and 
 * 	Tiago Santana de Nazare <tigosn92@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include "exec.h"

int exec(char *command){
	int pid = 0;
	int status;
	char *args[1000];
	char *p;
	int nargs;
	int i, j;
	int fd_in;
	int fd_out;
	char *red_out = NULL;
	char *red_out_cat = NULL;
	char *red_in = NULL;
	int del_arg = 0;
	char cp_cmd[strlen(command) + 1];
	int fd_stdin = dup(STDIN_FILENO);	/* duplicate the standard input */
	int fd_stdout = dup(STDOUT_FILENO);	/* duplicate the standard output */
	int pipe_pos;
	int pipefd[2];
	int pid2;
	
	/* generate the arguments list */
	strcpy(cp_cmd, command);
	p = strtok(cp_cmd, " ");
	for(nargs = 0; p != NULL; ++nargs){
		args[nargs] = p;
		p = strtok(NULL, " ");
	}
	args[nargs] = NULL;
	
	/* procura por redirecionamentos de E/S e os remove da lista de argumentos */
	for(i = 0; i < nargs - 1; ++i){
		if(strcmp(args[i], ">>") == 0){
			del_arg = 1;
			red_out_cat = args[i + 1];
		}else if(strcmp(args[i], ">") == 0){
			del_arg = 1;
			red_out = args[i + 1];
		}else if(strcmp(args[i], "<") == 0){
			del_arg = 1;
			red_in = args[i + 1];
		}
		
		if(del_arg == 1){
			for(j = i; j < nargs - 2; ++j){
				args[j] = args[j + 2];
			}					
			nargs -= 2;
			i -= 2;
			del_arg = 0;
		}
	}
	args[nargs] = NULL;
		
	if(strcmp(args[0], "help") == 0){
		help();
	}else if(strcmp(args[0], "cd") == 0){
		cd(args[1]);
	}else{
		pipe_pos = 0;
		for(i = 0; i < nargs; ++i){
			pid2 = 0;
			if(strcmp(args[i], "|") == 0){ /*>>>> achou um pipe*/
				args[i] = NULL; 
				
				/* redirects I/O */
				pipe(pipefd);
				
				pid2 = fork ();
				/* >>> if (pid2 <0) fatal (); */
				
				if(pid2 > 0){ /* >>> Parent */
					wait(&status);		/* Wait for child to terminate. */
					close(STDIN_FILENO);
					dup(pipefd[0]);
					close(pipefd[0]);
					close(pipefd[1]);
				}else{ /* >>> FILHO */
					close(STDOUT_FILENO);
					dup(pipefd[1]);
					close(pipefd[1]);	/* We close file descriptor 4 (unused). */
					close(pipefd[0]);

					execvp(args[pipe_pos], &args[pipe_pos]);
				}
				pipe_pos = i + 1;
			}
		}
		
		/* redirects I/O */
		/* redirects output (>) */
		if(red_out != NULL){
			if((fd_out = open(red_out, O_CREAT | O_TRUNC | O_WRONLY, S_IWUSR | S_IRUSR)) < 0){
				perror("error >\n");
			} else {
				close(STDOUT_FILENO);
				dup(fd_out);
			}
		/* redirects output (>>) */
		}else if(red_out_cat != NULL){
			if((fd_out = open(red_out_cat, O_APPEND | O_WRONLY)) < 0){
				perror("error >>\n");
			} else {
				close(STDOUT_FILENO);
				dup2(fd_out, STDOUT_FILENO);
			}
		}			
		
		/* redirects input (<) */
		if(red_in != NULL){
			if((fd_in = open(red_in, O_RDONLY)) < 0){
				perror("error <\n");
			} else {
				close(STDIN_FILENO);
				dup2(fd_in, STDIN_FILENO);
			}
		}
			
		pid = fork();
		
		if (pid < 0){
			printf("fatal");
		}
		
		if(pid > 0){	/* parent */				
			wait(&status);
			
			if(red_out != NULL || red_out_cat != NULL){
				close(fd_out);
				dup2(fd_stdout, STDOUT_FILENO);
				close(fd_stdout);
			}
			
			if(red_in != NULL){
				close(fd_in);
				dup2(fd_stdin, STDIN_FILENO);
				close(fd_stdin);
			}
			
			if(pipe_pos > 0){
				close(STDIN_FILENO);
				dup2(fd_stdin, STDIN_FILENO);
				close(fd_stdin);
			}
	    }else{			/* child */
			execvp(args[pipe_pos], &args[pipe_pos]); /* replaces the image */
			printf ("%s: command not found.\n", args[pipe_pos]); /* exec failed */
	    }
	}
	return 0;
}


/*
 * exec.h
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
 
 
# ifndef EXEC_H
# define EXEC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>		/* fork() */
#include <sys/types.h>	/* wait() */
#include "funcs.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int exec(char *command);
void parse_cmd(char *cmd, char *args[]);

# endif

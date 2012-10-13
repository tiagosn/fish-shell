/*
 * main.c
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

#include <string.h>
#include <stdlib.h>
#include <unistd.h> /*gethostname()*/
#include "funcs.h"
#include "exec.h"
#include "fish.h"
#include <fcntl.h>

#define MAX_COMMAND_LINE_SIZE 1024
#define MAX_HOST_NAME_SIZE 1024

int main(int argc, char **argv){
	char command[MAX_COMMAND_LINE_SIZE];
	char host_name[MAX_HOST_NAME_SIZE];
	char *dir;
	
	fish();
	
	while(1){
		gethostname(host_name, sizeof(host_name)); 
		dir = get_current_dir_name();
		
		printf("%s@%s@FISH:%s$ ", getenv("USER"), host_name, dir);
		free(dir);
		scanf (" %[^\n]s", command);
		
		if(strcmp(command, "exit") == 0){
			break;
		}
		
		exec(command);
	}
	return 0;
}

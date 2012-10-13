/*
 * funcs.c
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

#include "funcs.h"

void help(void){
	FILE *fp = fopen("../help", "r");
	char buff[1024];
	int n;
	
	if(fp == NULL){
		printf("Sorry, help text file is not a available!!!");
		return;
	}
	
	n = fread(buff, sizeof(char), 1023, fp);
	while(n != 0){
		buff[n] = '\0';
		printf("%s", buff);
		n = fread(buff, sizeof(char), 1023, fp);
	}
	
	fclose(fp);
}

void cd(char *dir){
	if(dir != NULL){
		chdir(dir);
	}
}

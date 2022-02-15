/*
 * Copyright (C) 2002, Simon Nieuviarts
 */

#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include "csapp.h"


int main(){
	while (1) {
		struct cmdline *l;
		//int i, j;

		printf("myShell> ");
		l = readcmd();

		/* If input stream closed, normal termination */
		if (!l) {
			printf("exit\n");
			exit(0);
		}

		if (l->err) {
			/* Syntax error, read another command */
			printf("error: %s\n", l->err);
			continue;
		}
		
		// 2) Si la commande est quit alors exit
		if (!strcmp(l->seq[0][0], "quit")){
			printf("\n");
			exit(0);
		}
		
		// 3) Commande simple
		pid_t pid=Fork();
		
		if (pid==0){
			execvp(l->seq[0][0], l->seq[0]);
			perror("execpv ");
			exit(0);
		}
		Wait(NULL);

		#ifdef DEBUG
		if (l->in) printf("in: %s\n", l->in);
		if (l->out) printf("out: %s\n", l->out);

		/* Display each command of the pipe */
		int i,j;
		for (i=0; l->seq[i]!=0; i++) {
			char **cmd = l->seq[i];
			printf("seq[%d]: ", i);
			for (j=0; cmd[j]!=0; j++) {
				printf("%s ", cmd[j]);
			}
			printf("\n");
		}
		#endif
	}
}

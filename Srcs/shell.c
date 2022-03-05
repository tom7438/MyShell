/*
 * Copyright (C) 2002, Simon Nieuviarts
 */

#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include "csapp.h"
#include "CmdInternes.h"
#include "shell_utils.h"
#include "handler.h"


int main(){
    print_icon();
    int couleur=31;
    signal(SIGCHLD, &HandlerChild);
    while (1) {
        struct cmdline *l;

        char *rep=(char *)malloc(sizeof(char)*100);
        printf("\033[%dm", couleur);
        printf("\033[4mMyShell:\033[00m");
        if(!strcmp(getenv("HOME"), getcwd(rep, 100))){
            printf("\033[34m~\033[00m");
        } else{
            printf("\033[34m%s\033[00m",getcwd(rep, 100));
        }
        printf(" # ");
        if((couleur=(couleur+1-31)%18+31)==34){couleur++;};

        l = readcmd();

        /* If input stream closed, normal termination */
        if (!l) {
            printf("exit\n");
            exit(0);
        }

        if (l->err) {/* Syntax error, read another command */
            printf("error: %s\n", l->err);
            continue;
        }

        // 2) Si la commande est quit alors exit
        if (!strcmp(l->seq[0][0], "quit") || !strcmp(l->seq[0][0], "exit")){
            printf("%s\n", l->seq[0][0]);
            exit(0);
        }


        int p=0;
        while(l->seq[p]){ p++; } //TROUVE NOMBRE COMMADES
        int n_commandes=p;
        int n_pipes = n_commandes-1;

        if(n_commandes>=1){

            if(n_commandes == 1){ //execute single command
                /* Commande interne ou non */
                if(!searchCmd(l->seq[0][0])){
                    cmd(l->seq[0]);
                }else {
                    pid_t pid = Fork();
                    if (pid == 0) {
                        if (execvp(l->seq[0][0], l->seq[0]) < 0) {
                            perror("execpv ");
                            exit(2);
                        }
                        exit(0);
                    } else if(!l->bg){ Wait(NULL); }
                }
            }else{                  // execute multiple commands with pipe(s)
                exec_pipes(l, n_pipes, n_commandes);
            }
        }

        // Commande interne ou non
        //if(!searchCmd(l->seq[0][0])){
        //    cmd(l->seq[0]);
        //}


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
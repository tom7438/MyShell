/*
 * Copyright (C) 2002, Simon Nieuviarts
 */

#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include "csapp.h"
#include "CmdInternes.h"


int main(){
    printf("\033[34m");
    printf("************************************\n");
    printf("//////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
    printf("////// STARTING THE NEW SHELL \\\\\\\\\\\\\n");
    printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//////////////////\n");
    printf("         _________________________.\n");
    printf("        / _____________________  /|\n");
    printf("       / / ___________________/ / |\n");
    printf("      / / /| |MARCHIONINI DAVID/  |\n");
    printf("     / / / | |CLEMENT TOM   / / . |\n");
    printf("    / / /| | |             / / /| |\n");
    printf("   / / / | | |L3-INFO-SR  / / / | |\n");
    printf("  / / /  | | |           / / /| | |\n");
    printf(" / /_/___| | |__________/ / / | | |\n");
    printf("/________| | |___________/ /  | | |\n");
    printf("| _______| | |__________ | |  | | |\n");
    printf("| | |    | | |_________| | |__| | |\n");
    printf("| | |    | |___________| | |____| |\n");
    printf("| | |   / / ___________| | |_  / /\n");
    printf("| | |  / / /           | | |/ / /\n");
    printf("| | | / / /            | | | / /\n");
    printf("| | |/ / /             | | |/ /\n");
    printf("| | | / /              | | ' /\n");
    printf("| | |/_/_______________| |  /\n");
    printf("| |____________________| | /\n");
    printf("|________________________|/\n");
    printf("************************************\n\n");
    printf("          ");
    printf("\033[4m[ MyShell v1.0 ]\033[0m");
    printf("          ");
    printf("\033[00m\n\n\n");
    int couleur=31;
	while (1) {
		struct cmdline *l;
		//int i, j;

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

		if (l->err) {
			/* Syntax error, read another command */
			printf("error: %s\n", l->err);
			continue;
		}
		
		// 2) Si la commande est quit alors exit
		if (!strcmp(l->seq[0][0], "quit") || !strcmp(l->seq[0][0], "exit")){
			printf("%s\n", l->seq[0][0]);
			exit(0);
		}

        // Commande interne ou non
        if(!searchCmd(l->seq[0][0])){
            cmd(l->seq[0]);
        }
		// 3) && 4) Commande simple && Redirections d'entrées et sorties
        else{
            pid_t pid=Fork();

            if(pid==-1){perror("Fork ");exit(2);}

            else if (pid==0){
                int fdIn;
                int fdOut;
                if (l->in){
                    fdIn = Open(l->in, O_RDONLY, 0);
                    if (fdIn==-1){perror("Open ");exit(2);}
                    Close(0);
                    if(dup(fdIn) < 0){perror("dup ");}
                    Close(fdIn);
                }
                if (l->out){
                    fdOut = Open(l->out, O_CREAT | O_WRONLY, 0644);
                    if (fdOut==-1){perror("Open ");exit(2);}
                    Close(1);
                    if(dup(fdOut) < 0){perror("dup ");}
                    Close(fdOut);
                }
                if(execvp(l->seq[0][0], l->seq[0]) < 0){perror("execpv ");exit(2);}
                Close(fdIn);
                Close(fdOut);
                exit(0);
            }
            Wait(NULL);
        }

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

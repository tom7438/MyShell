#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include "csapp.h"
#include "CmdInternes.h"
#include "shell_utils.h"

void exec_pipes(struct cmdline *l, int n_pipes, int n_commandes){
    //main child

    //io redirect
    int fdIn = -1;
    int fdOut = -1;
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


    //piping

    int fds[n_pipes+1][3]; //tous les file descriptors en une liste de listes
    for(int p=0; p<n_pipes; p++){
        if(pipe(fds[p]) < 0){perror("pipe ");exit(2);}
    }
    // if(execvp(l->seq[1][0], l->seq[1]) < 0){perror("execpv ");exit(2);}
    int i = 0;
    pid_t pidc;
    while(i<n_commandes){

        pidc= Fork();
        if(pidc==-1){perror("Fork ");exit(2);}

        if(pidc==0){ //child
            if(i!=n_commandes-1){ //all but last cmd
                Dup2(fds[i][1],1);

            }
            if(i!=0){//all but 1st cmd
                Dup2(fds[i-1][0],0);

            }

            /* Commande interne ou non */
            if(!searchCmd(l->seq[0][0])) {
                cmd(l->seq[0]);
            } else{ if(execvp(l->seq[i][0], l->seq[i]) < 0){perror("execpv ");exit(2);}}

        }
        close(fds[i][1]);

        if(i!=0){close(fds[i-1][0]);}
        while(waitpid(0,0,0) < 0);

        i++;
    }




}

void print_icon(void){
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
}
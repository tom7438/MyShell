#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include "csapp.h"
#include "CmdInternes.h"

void exec_pipes(struct cmdline *l, int n_pipes, int n_commandes, pid_t pid){


      if(pid==-1){perror("Fork ");exit(2);}

      if (pid==0){ //main child
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




      int fds[2*n_pipes]; //tous les file descriptors en une liste
      for(int k=0 ; k<n_pipes ; k++){
        pipe(fds + n_commandes*2);  //creation de tous les pipes
      }

      int j=1;
      while(l->seq[j]){
          pid_t childpid;
          childpid = Fork();

          if (childpid == 0) {         /* fils */

              Close(0);
              dup(fds[0]);
              Close(fds[1]);Close(fds[0]);
              if(execvp(l->seq[1][0], l->seq[1]) < 0){perror("execpv ");exit(2);}        //tous les cas
              exit(0);

          } else {         /* père */
              childpid = Fork();

              if (childpid == 0){
                Close(1);dup(fds[1]);Close(0);
                Close(fds[0]);Close(fds[1]);
                if(execvp(l->seq[0][0], l->seq[0]) < 0){perror("execpv ");exit(2);}
                exit(0);

              }else{
                Close(fds[0]);Close(fds[1]);
                Wait(NULL);
                exit(0);
              }


          }


          j++;
      }
      exit(0); //main child exit
    }
    else{Wait(NULL);}  //main parent wait


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

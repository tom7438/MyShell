#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "CmdInternes.h"

char CommandesInternes[5][10]={"pwd", "cd", "echo", "quit", "exit"};

int searchCmd(char *cmd){
    for(int i=0; i<5; i++){
        if (!strcmp(cmd, CommandesInternes[i])) {
            return 0;
        }
    }
    return -1;
}

int cmd(char **cmd){
    if(!strcmp(cmd[0], "pwd")){
        cmdPwd();
    } else if(!strcmp(cmd[0], "cd")) {
        if (cmd[1] != NULL) {
            cmdCd(cmd[1]);
        } else {
            cmdCd(getenv("HOME"));
        }
    } else if(!strcmp(cmd[0], "echo")) {
        int i=1;
        while(cmd[i] && strcmp(cmd[i],"&")){
            if(i!=1){
                printf(" ");
            }
            printf("%s", cmd[i]);
            i++;
        }
        printf("\n");
    } else if(!strcmp(cmd[0], "quit") || !strcmp(cmd[0], "exit")){
        printf("%s\n", cmd[0]);
        exit(0);
    }else{
        printf("Commande interne à coder\n");
    }
    return 0;
}

void cmdPwd(){
    char *s=(char *)malloc(sizeof(char)*100);
    printf("%s\n", getcwd(s, 100));
}

void cmdCd(char *dir){
    int res=chdir(dir);
    if(res==-1){perror("chdir() ");exit(EXIT_FAILURE);}
}
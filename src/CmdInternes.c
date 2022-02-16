#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "CmdInternes.h"

char CommandesInternes[5][10]={"pwd", "cd", "set", "echo"};

int searchCmd(char *cmd){
    for(int i=0; i<4; i++){
        if (!strcmp(cmd, CommandesInternes[i])) {
            return 0;
        }
    }
    return -1;
}

int cmd(char **cmd){
    if(!strcmp(cmd[0], "pwd")){
        cmdPwd();
    } else{
        printf("Commande interne à coder\n");
    }
    return 0;
}

void cmdPwd(){
    char *s=(char *)malloc(sizeof(char)*100);
    printf("%s\n", getcwd(s, 100));
}

void cmdCd(){

}
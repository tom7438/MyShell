#include <stdio.h>
#include <string.h>
#include "CmdInternes.h"

char CommandesInternes[5][10]={"pwd", "cd", "set", "echo", "type"};

int searchCmd(char *cmd){
    for(int i=0; i<5; i++){
        if (!strcmp(cmd, CommandesInternes[i])) {
            return 0;
        }
    }
    return -1;
}
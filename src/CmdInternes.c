#include <stdio.h>
#include <string.h>
#include "CmdInternes.h"

char CommandesInternes[4][10]={"pwd", "cd", "set", "echo"};

int searchCmd(char *cmd){
    for(int i=0; i<4; i++){
        if (!strcmp(cmd, CommandesInternes[i])) {
            return 0;
        }
    }
    return -1;
}
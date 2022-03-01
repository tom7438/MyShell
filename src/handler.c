#include "csapp.h"
#include "handler.h"

void HandlerChild(int sig){
    int status;
    waitpid(-1, &status, WNOHANG|WUNTRACED);
}
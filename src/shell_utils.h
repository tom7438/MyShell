#ifndef __SHELL_UTILS_H
#define __SHELL_UTILS_H

void print_icon(void);

void exec_pipes(struct cmdline *l, int n_pipes, int n_commandes, pid_t pid);

#endif

#include "minishell.h"

void builting_cd(char **args, int *status) {
    if (args[1] == NULL) {
        ft_putstr_fd("minishell: cd: missing argument\n", STDERR_FILENO);
        *status = 1;
        return;
    }
    
    if (chdir(args[1]) != 0) {
        perror("minishell: cd");
        *status = 1;
        return;
    }
    
    *status = 0;
}

#include "builting_cmd.h"

void handl_builting(char **cmd, char **args, int *status, int i){

    if (ft_strncmp(cmd[0], "echo", 4) == 0)
        builting_echo(cmd, status);
    if (ft_strncmp(cmd[0], "cd", 2) == 0)
        builting_cd(cmd, status);
    else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
        builting_pwd(cmd, status);
    else if (ft_strncmp(cmd[0], "export", 6) == 0)
        builting_export();
    else if (ft_strncmp(cmd[0], "unset", 5) == 0)
        builting_unset(cmd, status);
    else if (ft_strncmp(cmd[0], "env", 3) == 0)
        builting_env(cmd, status);
    else if (ft_strncmp(cmd[0], "exit", 4) == 0)
        builting_exit(cmd, args, status, i);    
}

int is_builting(char *cmd){
    int i = 0;
    char *builting_cmd[]  = {
        "echo", "env", "unset", "export",
        "pwd", "exit", "cd", NULL
    };
    while (builting_cmd[i])
    {
        if (ft_strncmp(cmd, builting_cmd[i], ft_strlen(builting_cmd[i])) == 0){
            return (1);
        }
        i++;
        
    }
    
    return (0);
}
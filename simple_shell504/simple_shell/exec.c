#include "minishell.h"
#include <signal.h>

int ft_exec(char **cmd, char **args, char **env, int i){
    pid_t   child;
    char    *full_cmd;
    int status;
    // extern char **environ;

    full_cmd = get_path(cmd[0]);
    if (!full_cmd){
        print_error(args[0], cmd[0], i);
        free_array(cmd);
        return (127);
    }
    child = fork();
    if (child == 0){
        if (execve(full_cmd, cmd, env) == -1){
            free(full_cmd);
            full_cmd = NULL;
            free_array(cmd); 
        }
    }
    else
    {
        waitpid(child, &status, 0);
        free(full_cmd);
        free_array(cmd);
        
        // Handle signal termination
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
        {
            int sig = WTERMSIG(status);
            int exit_code = 128 + sig;
            if (exit_code == 128 + SIGINT)
                write(STDOUT_FILENO, "\n", 1);
            else if (exit_code == 128 + SIGQUIT)
                write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
            return (exit_code);
        }
    }
    return (WEXITSTATUS(status));
}
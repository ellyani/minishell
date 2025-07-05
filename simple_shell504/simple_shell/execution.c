#include "minishell.h"
#include <signal.h>

int exec_pipeline(char ***commands, char **env)
{
    int num_commands = 0;
    int i = 0;
    int **pipes;
    pid_t *pids;
    int status;
    int last_status = 0;
    
    // Count the number of commands
    while (commands[num_commands])
        num_commands++;
    
    if (num_commands == 0)
        return (0);
    
    // Allocate memory for pipes and process IDs
    pipes = malloc(sizeof(int *) * (num_commands - 1));
    pids = malloc(sizeof(pid_t) * num_commands);
    
    if (!pipes || !pids)
        return (1);
    
    // Create pipes
    for (i = 0; i < num_commands - 1; i++)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(pipes[i]) == -1)
        {
            // Clean up and return error
            while (--i >= 0)
                free(pipes[i]);
            free(pipes);
            free(pids);
            return (1);
        }
    }
    
    // Execute commands
    for (i = 0; i < num_commands; i++)
    {
        char *full_cmd = get_path(commands[i][0]);
        if (!full_cmd)
        {
            // Handle command not found
            last_status = 127;
            continue;
        }
        
        pids[i] = fork();
        if (pids[i] == 0)
        {
            // Child process
            // Set up input redirection
            if (i > 0)
            {
                dup2(pipes[i - 1][0], STDIN_FILENO);
                close(pipes[i - 1][0]);
                close(pipes[i - 1][1]);
            }
            
            // Set up output redirection
            if (i < num_commands - 1)
            {
                dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][0]);
                close(pipes[i][1]);
            }
            
            // Close all other pipe file descriptors
            int j;
            for (j = 0; j < num_commands - 1; j++)
            {
                if (j != i - 1 && j != i)
                {
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                }
            }
            
            // Execute the command
            execve(full_cmd, commands[i], env);
            free(full_cmd);
            exit(127);
        }
        else if (pids[i] < 0)
        {
            // Fork failed
            free(full_cmd);
            last_status = 1;
        }
        else
        {
            free(full_cmd);
        }
    }
    
    // Close all pipe file descriptors in parent
    for (i = 0; i < num_commands - 1; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        free(pipes[i]);
    }
    
    // Wait for all child processes
    int signal_status = 0;
    for (i = 0; i < num_commands; i++)
    {
        if (pids[i] > 0)
        {
            waitpid(pids[i], &status, 0);
            
            // Check if any process was terminated by a signal
            if (WIFSIGNALED(status))
            {
                int sig = WTERMSIG(status);
                signal_status = 128 + sig;
            }
            
            // Last command determines exit status if no signals
            if (i == num_commands - 1 && signal_status == 0)
            {
                if (WIFEXITED(status))
                    last_status = WEXITSTATUS(status);
                else if (WIFSIGNALED(status))
                {
                    int sig = WTERMSIG(status);
                    last_status = 128 + sig;
                }
            }
        }
    }
    
    // If any process was terminated by signal, use that status
    if (signal_status != 0)
        last_status = signal_status;
    
    // Handle signal termination 
    if (last_status == 128 + SIGINT)
        write(STDOUT_FILENO, "\n", 1);
    else if (last_status == 128 + SIGQUIT)
        write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
    
    free(pipes);
    free(pids);
    
    return (last_status);
}
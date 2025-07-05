#include "minishell.h"

int main(int ac,char **av, char **env) {
    (void)ac;
    
    char    *line;
    char    **comand;
    int     status;
    int     i;

    line = NULL;
    comand = NULL;
    status = 0;
    i = 0;

    while (1) {
        if (isatty(STDIN_FILENO))
            line = readline("$> ");
        else 
            line = readline("");
        if (!line)
        {

                return (status);
        }
        i++;
        if (line[0] == '\0')
        {
            // free(line);
            continue;
        }
        add_history(line);
        
        // Check if the line contains pipes
        if (has_pipe(line))
        {
            char ***pipeline = parse_pipeline(line);
            if (pipeline)
            {
                status = exec_pipeline(pipeline, env);
                free_pipeline(pipeline);
            }
        }
        else
        {
            comand = ft_token(line);
            if (is_builting(comand[0])){
                handl_builting(comand, av, &status, i);
            }
            else
                status = ft_exec(comand, av, env, i);
        } 
    }

    return 0;
}  
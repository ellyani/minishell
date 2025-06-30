#include "builting_cmd.h"

int main(int ac,char **av, char **env) {
    
    char    *line;
    char    **comand;
    int     status;
    int     i;
    char    *delimiter;
    char    *heredoc_content;
    char    *clean_line;

    line = NULL;
    comand = NULL;
    status = 0;
    i = 0;
    (void)ac;  // To avoid unused parameter warning

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
        
        // Check for heredoc
        if (has_heredoc(line))
        {
            delimiter = get_heredoc_delimiter(line);
            if (delimiter)
            {
                heredoc_content = read_heredoc(delimiter);
                clean_line = remove_heredoc_from_line(line);
                free(delimiter);
                
                if (heredoc_content && clean_line)
                {
                    // For now, just print the heredoc content (in real implementation, 
                    // this would be passed to the command as stdin)
                    printf("Heredoc content:\n%s", heredoc_content);
                    comand = ft_token(clean_line);
                }
                if (heredoc_content)
                    free(heredoc_content);
                if (clean_line)
                    free(clean_line);
            }
        }
        else
        {
            comand = ft_token(line);
        }
        
        if (comand && comand[0])
        {
            if (is_builting(comand[0])){
                handl_builting(comand, av, &status, i);
            }
            else
               status = ft_exec(comand, av, env, i); 
        }
    }

    return 0;
}  
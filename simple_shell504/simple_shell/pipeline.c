#include "minishell.h"

int has_pipe(char *line)
{
    int i = 0;
    while (line[i])
    {
        if (line[i] == '|')
            return (1);
        i++;
    }
    return (0);
}

char ***parse_pipeline(char *line)
{
    char **pipe_segments;
    char ***commands;
    int num_pipes = 0;
    int i = 0;
    
    // Split by pipe character
    pipe_segments = ft_split(line, '|');
    if (!pipe_segments)
        return (NULL);
    
    // Count segments
    while (pipe_segments[num_pipes])
        num_pipes++;
    
    // Allocate memory for commands array
    commands = malloc(sizeof(char **) * (num_pipes + 1));
    if (!commands)
    {
        free_array(pipe_segments);
        return (NULL);
    }
    
    // Tokenize each segment
    for (i = 0; i < num_pipes; i++)
    {
        commands[i] = ft_token(pipe_segments[i]);
        if (!commands[i])
        {
            // Clean up on failure
            while (--i >= 0)
                free_array(commands[i]);
            free(commands);
            free_array(pipe_segments);
            return (NULL);
        }
    }
    commands[num_pipes] = NULL;
    
    free_array(pipe_segments);
    return (commands);
}

void free_pipeline(char ***commands)
{
    int i = 0;
    if (!commands)
        return;
    
    while (commands[i])
    {
        free_array(commands[i]);
        i++;
    }
    free(commands);
}
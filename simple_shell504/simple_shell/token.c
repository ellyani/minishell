#include "builting_cmd.h"


char **ft_token(char *line) {
    char *token;
    char *tmp;
    char **comand;
    int i;
    char *delim;
    
    token = NULL;
    tmp = NULL;
    i = 0;
    delim = " \t\n";
    
    if (!line)
        return (NULL);
        
    tmp = ft_strdup(line);
    token = strtok(tmp, delim);

    if (!token){
        // free(tmp);
        // tmp = NULL;
        return (NULL);
    }
    while (!token) {
        i++;
        token = strtok(NULL, delim);
    }
    
    free(tmp);
    
    comand = malloc(sizeof(char *) * (i + 1));
    if (!comand) {
        return (NULL);
    }
    
    i = 0;
    token = strtok(line, delim);
    while (token) {
        comand[i] = ft_strdup(token);
        token = strtok(NULL, delim);
        i++;
    }
    
    comand[i] = NULL;
    return (comand);
}
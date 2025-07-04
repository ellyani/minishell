#include "builting_cmd.h"

void    print_error(char *name, char *cmd, int i){
    printf("%s: %d: %s: command not found\n",name,i,cmd);
}

char *get_path(char *comand){
    char    *path_env;
    char    *path_copy;
    char    *full_cmd;
    char    *dir;
    int     i;
    struct stat st;

    i = 0;

    while (comand[i])
    {
        if (comand[i] == '/')
        {
            if (stat(comand, &st) == 0)
                return (ft_strdup(comand));
            return (NULL);
        }
        i++;
    }
    path_env = getenv("PATH");
    if (!path_env)
        return (NULL);
    path_copy = ft_strdup(path_env);
    if (!path_copy)
        return (NULL);
    dir = strtok(path_copy, ":");
    while (dir)
    {
        full_cmd = malloc(ft_strlen(dir) + ft_strlen(comand) + 2);
        if (!full_cmd)
            return (NULL);
        if (full_cmd)
        {
            ft_strlcpy(full_cmd, dir, ft_strlen(dir) + 1);
            ft_strlcat(full_cmd, "/", ft_strlen(dir) + 2);
            ft_strlcat(full_cmd, comand, ft_strlen(dir) + 
                    ft_strlen(comand) + 2);
            if (stat(full_cmd, &st) == 0){
                free(path_copy);
                return (full_cmd);
            }
            free(full_cmd);
            full_cmd = NULL;
            
            dir = strtok(NULL, ":");
        }
    }
    free(path_copy);
    return (NULL);
}


// int main(int ac, char **av){
//     char *full_cmd;
//     full_cmd = get_path(av[1]);
//     if (full_cmd){
//         printf("%s\n",full_cmd);
//         free(full_cmd);

//     }
//     else
//         printf("not found\n");
// }   
#include "builting_cmd.h"

void free_array(char **av){
    int i = 0;
    if (!av)
        return ;
    while (av[i])
    {
        free(av[i]);
        i++;
    }
    free(av);
}


// int parse_and_execute(char **comand, char **args) {
//     char *args[MAX_ARGS];
//     char *full_cmd;
//     int i = 1;

//     full_cmd = get_path(comand[0]);
//     if (!full_cmd){
//         print_error(args[0], comand[0], i);
//         return (127);
//     }
//     i = 0;

//     char *token = strtok(args, " \t\n");
//     while (token != NULL && i < MAX_ARGS - 1) {
//         args[i++] = token;
//         token = strtok(NULL, " \t\n");
//     }
//     args[i] = NULL;

//     if (!execute_builting(args)) {
//         pid_t pid = fork();
//         if (pid == 0) {
//             if (execve(args[0], args, NULL) == -1) {
//                 free(full_cmd);
//                 full_cmd = NULL;
//                 perror("execve");
                
//                 exit(EXIT_FAILURE);
//             }
//         } else if (pid > 0) {
//             wait(NULL);
//         } else {
//             perror("fork");
//         }
//     }
// }

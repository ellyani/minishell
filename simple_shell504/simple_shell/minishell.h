#include "libft/libft.h"

#include <string.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

extern char	**environ;

void    free_array(char **av);
int     ft_exec(char **cmd, char **args,char **env, int i);
char    **ft_token(char *line);
char    **expand_command_args(char **args, char **env);
void    builting_echo(char **args, int *status);
void	builting_cd(char **args, int *status);
void    builting_pwd(char **cmd, int *status);
void	builting_export(void);
void	builting_env(char **cmd, int *status);
void	builting_exit(char **cmd, char **args, int *status, int i);
void	builting_unset(char **args, int *status);
char    *get_path(char *comand);
void    print_error(char *name, char *cmd, int i);
void    handl_builting(char **cmd, char **args, int *status, int i);
int     is_builting(char *cmd);
int     ft_is_positive(char *str);
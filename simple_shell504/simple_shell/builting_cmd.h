#ifndef BUILTING_CMD_H
# define BUILTING_CMD_H

# include "minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void    builting_echo(char **args, int *status);
void	builting_cd(char **args, int *status);
void    builting_pwd(char **cmd, int *status);
void	builting_export(void);
void	builting_env(char **cmd, int *status);
void	builting_exit(char **cmd, char **args, int *status, int i);
void	builting_unset(char **args, int *status);

#endif
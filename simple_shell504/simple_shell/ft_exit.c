#include "minishell.h"

void	builting_exit(char **cmd, char **args, int *status, int i)
{
	int valeur_exit;

	valeur_exit = (*status);
	if (cmd[1])
	{
		if (ft_is_positive(cmd[1]))
		{
			valeur_exit = ft_atoi(cmd[1]);
		}
		else
		{
			printf("%s: %d: exit: Illegal number: %s\n",args[0], i, cmd[1]);
			(*status) = 2;
			free_array(cmd);
			return ;
		}
	} 
	free_array(cmd);
	exit(valeur_exit);
}
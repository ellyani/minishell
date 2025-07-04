#include "minishell.h"

void	builting_env(char **cmd, int *status)
{
	int		i;

	i = 0;
	(void)status;
	while (environ[i])
	{
		printf("%s\n",environ[i]);
		i++;
	}
	*status = 0;
	free_array(cmd);
}
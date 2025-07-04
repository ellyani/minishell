#include "minishell.h"

void	builting_unset(char **args, int *status)
{
	(void)status;
	if (!args[1])
		ft_putstr_fd("unset: expected argument\n", 1);
	else
	{
		if (unsetenv(args[1]))
			perror("unset");
	}
}
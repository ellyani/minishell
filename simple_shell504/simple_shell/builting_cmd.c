#include "minishell.h"


void	builting_export(void){
	extern char	**environ;
	int		i;

	i = 0;
	while (environ[i])
	{
		printf("%s\n",environ[i]);
		i++;
	}
}

void	builting_env(char **cmd, int *status){
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

void	builting_exit(char **cmd, char **args, int *status, int i){
	int valeur_exit;

	valeur_exit = (*status);
	if (cmd[1]){
		if (ft_is_positive(cmd[1])){
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

void	builting_unset(char **args, int *status){
	(void)status;
	if (!args[1])
		ft_putstr_fd("unset: expected argument\n", 1);
	else{
		if (unsetenv(args[1]))
			perror("unset");
	}
}
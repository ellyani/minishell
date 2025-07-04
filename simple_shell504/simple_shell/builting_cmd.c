#include "builting_cmd.h"

void    builting_echo(char **args, int *status){
	int	i;
	int	new_line;

	(void)status;
	i = 1;
	new_line = 1;

	while (args[i]  && (ft_strncmp(args[i], "-n",2) == 0) && args[i][2] == '\0'){
		new_line = 0;
		i++;
	}
	
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	
}




void    builting_pwd(char **cmd, int *status) {
    char *c = NULL;
    size_t size = 0;
	
	(void)cmd;
	c = getcwd(c, size);

    if (c == NULL) {
        perror("pwd");
		*status = 1;
    } else {
        printf("%s\n", c);
		*status = 0;
    }

    free(c);
}


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
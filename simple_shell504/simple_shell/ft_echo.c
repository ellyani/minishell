#include "minishell.h"

void    builting_echo(char **args, int *status){
	int	i;
	int	new_line;

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
    *status = 0;
	
}
#include "minishell.h"

static int	ft_is_valid_env(const char *str){
    int i;

    i = 0;
    if (!str || !*str || ft_isdigit(*str))
        return (0);
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '-')
            return (0);
        i++;
    }
    return (1);
}

void	builting_export_args(char **args, int *status)
{
	(void)args;
	(void)status;
	(void)ft_is_valid_env;
}

void	builting_export(void)
{
	extern char	**environ;
	int		i;

	i = 0;
	while (environ[i])
	{
		printf("%s\n",environ[i]);
		i++;
	}
}


#include "minishell.h"

static char	**append_splits(char **result, int *result_count, char **expanded_splits)
{
	int	j;
	int	split_count;

	split_count = 0;
	while (expanded_splits[split_count])
		split_count++;
	result = realloc(result, sizeof(char *) * (*result_count + split_count + 1));
	j = -1;
	while (++j < split_count)
		result[*result_count + j] = ft_strdup(expanded_splits[j]);
	*result_count += split_count;
	return (result);
}

char	**expand_command_args(char **args, char **env)
{
	char	**result;
	char	**expanded_splits;
	char	*expanded_arg;
	char	*env_value;
	int		i;
	int		result_count;
	(void)env;
	result = NULL;
	result_count = 0;
	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '$' && args[i][1])
			env_value = getenv(args[i] + 1);
		expanded_arg = (args[i][0] == '$' && args[i][1]) ? 
			(env_value ? ft_strdup(env_value) : ft_strdup("")) : ft_strdup(args[i]);
		expanded_splits = ft_split(expanded_arg, ' ');
		result = append_splits(result, &result_count, expanded_splits);
		free(expanded_arg);
		free_array(expanded_splits);
	}
	result[result_count] = NULL;
	return (result);
}
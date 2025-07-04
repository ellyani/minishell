/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shlvl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sellyani <sellyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:04:00 by sellyani          #+#    #+#             */
/*   Updated: 2024/04/22 16:04:00 by sellyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builting_cmd.h"

int	find_shlvl_in_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			return (i);
		i++;
	}
	return (i);
}

int	parse_shlvl_value(char *shlvl_str)
{
	int	shlvl_value;
	int	overflow;

	if (!is_numeric(shlvl_str))
		return (0);
	shlvl_value = (int)ft_atoll_with_overflow(shlvl_str, &overflow);
	if (overflow)
		return (0);
	return (shlvl_value);
}

void	set_shlvl_env(char **env, int index, int shlvl_value)
{
	char	*new_shlvl;
	char	*value_str;

	value_str = ft_itoa(shlvl_value);
	if (!value_str)
		return ;
	new_shlvl = append_env("SHLVL", value_str);
	free(value_str);
	if (new_shlvl)
	{
		if (env[index])
			free(env[index]);
		env[index] = new_shlvl;
	}
}

void	handle_shlvl(char **env)
{
	int		index;
	char	*shlvl_str;
	int		shlvl_value;

	index = find_shlvl_in_env(env);
	if (!env[index])
	{
		set_shlvl_env(env, index, 1);
		return ;
	}
	shlvl_str = env[index] + 6;
	shlvl_value = parse_shlvl_value(shlvl_str);
	shlvl_value++;
	set_shlvl_env(env, index, shlvl_value);
}

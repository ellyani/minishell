/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sellyani <sellyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:04:00 by sellyani          #+#    #+#             */
/*   Updated: 2024/04/22 16:04:00 by sellyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builting_cmd.h"

int	ft_is_positive(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

char	*append_env(char *name, char *value)
{
	char	*result;
	int		name_len;
	int		value_len;
	int		i;
	int		j;

	if (!name || !value)
		return (NULL);
	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	result = malloc(name_len + value_len + 2);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (name[i])
		result[j++] = name[i++];
	result[j++] = '=';
	i = 0;
	while (value[i])
		result[j++] = value[i++];
	result[j] = '\0';
	return (result);
}

int	is_numeric(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

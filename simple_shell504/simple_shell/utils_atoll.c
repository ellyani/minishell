/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atoll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sellyani <sellyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:04:00 by sellyani          #+#    #+#             */
/*   Updated: 2024/04/22 16:04:00 by sellyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builting_cmd.h"

int	skip_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

int	parse_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static long long	handle_overflow(int sign, int *overflow)
{
	*overflow = 1;
	if (sign == 1)
		return (LLONG_MAX);
	else
		return (LLONG_MIN);
}

long long	convert_digits(char *str, int *i, int sign, int *overflow)
{
	long long	result;
	long long	prev_result;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		prev_result = result;
		if (result > (LLONG_MAX - (str[*i] - '0')) / 10)
			return (handle_overflow(sign, overflow));
		result = result * 10 + (str[*i] - '0');
		if (result < prev_result)
			return (handle_overflow(sign, overflow));
		(*i)++;
	}
	if (sign == -1 && result > LLONG_MAX)
		return (handle_overflow(sign, overflow));
	return (result * sign);
}

long long	ft_atoll_with_overflow(char *str, int *overflow)
{
	int			i;
	int			sign;
	long long	result;

	*overflow = 0;
	i = skip_whitespace(str);
	sign = parse_sign(str, &i);
	result = convert_digits(str, &i, sign, overflow);
	return (result);
}

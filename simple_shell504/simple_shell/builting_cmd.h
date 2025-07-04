/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting_cmd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sellyani <sellyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:04:00 by sellyani          #+#    #+#             */
/*   Updated: 2024/04/22 16:04:00 by sellyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTING_CMD_H
# define BUILTING_CMD_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

int			ft_is_positive(char *str);
long long	ft_atoll_with_overflow(char *str, int *overflow);
void		handle_shlvl(char **env);
char		*append_env(char *name, char *value);
int			is_numeric(char *str);

/* Helper functions for ft_atoll_with_overflow */
int			skip_whitespace(char *str);
int			parse_sign(char *str, int *i);
long long	convert_digits(char *str, int *i, int sign, int *overflow);

/* Helper functions for handle_shlvl */
int			find_shlvl_in_env(char **env);
int			parse_shlvl_value(char *shlvl_str);
void		set_shlvl_env(char **env, int index, int shlvl_value);

#endif
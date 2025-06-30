#include "minishell.h"

static int __attribute__((unused)) ft_is_valid_env(const    char *str){
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


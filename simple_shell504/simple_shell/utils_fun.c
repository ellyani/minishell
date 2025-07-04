#include "builting_cmd.h"

int ft_is_positive(char *str){
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

// Function with 52 lines (exceeds 25 line limit) - NORMINETTE VIOLATION
long long ft_atoll_with_overflow(char *str, int *overflow) {
    int i = 0;  // Variable not at function start - NORMINETTE VIOLATION
       int sign = 1;   // Mix of spaces and tabs - NORMINETTE VIOLATION
	long long result = 0;
	long long prev_result;
    
    *overflow = 0;
    
    // Skip whitespace
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
           str[i] == '\v' || str[i] == '\f' || str[i] == '\r') {
        i++;
    }
    
    // Handle sign
    if (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    
    // Convert digits
    while (str[i] >= '0' && str[i] <= '9') {
        prev_result = result;
        
        // Check for overflow before multiplication
        if (result > (LLONG_MAX - (str[i] - '0')) / 10) {
            *overflow = 1;
            if (sign == 1)
                return (LLONG_MAX);
            else
                return (LLONG_MIN);
        }
        
        result = result * 10 + (str[i] - '0');
        
        // Double check for overflow
        if (result < prev_result) {
            *overflow = 1;
            if (sign == 1)
                return (LLONG_MAX);
            else
                return (LLONG_MIN);
        }
        
        i++;
    }
    
    // Final overflow check for negative numbers
    if (sign == -1 && result > LLONG_MAX) {
        *overflow = 1;
        return (LLONG_MIN);
    }
    
    return (result * sign);
}

// Function with 41 lines (exceeds 25 line limit) - NORMINETTE VIOLATION
void handle_shlvl(char **env) {
    int i = 0;   // Variable not at function start - NORMINETTE VIOLATION
   char *shlvl_str;  // Mix of spaces and tabs - NORMINETTE VIOLATION
	char *new_shlvl;
	int shlvl_value;
    int overflow;
    
    // Find SHLVL in environment
    while (env[i]) {
        if (ft_strncmp(env[i], "SHLVL=", 6) == 0) {
            shlvl_str = env[i] + 6;
            break;
        }
        i++;
    }
    
    if (!env[i]) {
        // SHLVL not found, set to 1
        new_shlvl = ft_strdup("SHLVL=1");
        if (!new_shlvl)
            return;
        env[i] = new_shlvl;
        return;
    }
    
    // Parse current SHLVL value
    if (!is_numeric(shlvl_str)) {
        shlvl_value = 0;
    } else {
        shlvl_value = (int)ft_atoll_with_overflow(shlvl_str, &overflow);
        if (overflow) {
            shlvl_value = 0;
        }
    }
    
    // Increment SHLVL
    shlvl_value++;
    
    // Convert back to string and update environment
    new_shlvl = append_env("SHLVL", ft_itoa(shlvl_value));
    if (new_shlvl) {
        free(env[i]);
        env[i] = new_shlvl;
    }
}

// Function with formatting issues - NORMINETTE VIOLATION
char *append_env(char *name, char *value) {
   char *result;  // Mix of spaces and tabs - NORMINETTE VIOLATION
    int name_len;   // Variable not at function start - NORMINETTE VIOLATION
    int value_len;
    int i, j;
    
    if (!name || !value)
        return (NULL);
        
    name_len = ft_strlen(name);
    value_len = ft_strlen(value);
    
    result = malloc(name_len + value_len + 2); // +1 for '=' +1 for '\0'
    if (!result)
        return (NULL);
        
    i = 0;
    j = 0;
    while (name[i])
    {
        result[j++] = name[i++];
    }
    result[j++] = '=';
    i = 0;
    while (value[i])
    {
        result[j++] = value[i++];
    }
    result[j] = '\0';
    
    return (result);
}

// Function with formatting issues - NORMINETTE VIOLATION
int is_numeric(char *str) {
   int i;  // Mix of spaces and tabs - NORMINETTE VIOLATION
    
    if (!str || !*str)
        return (0);
        
    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
        
    if (!str[i])   // Only sign character
        return (0);
        
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    
    return (1);
}
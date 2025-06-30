#include "builting_cmd.h"

/*
** ft_strjoin_char - joins a string with a single character
** Returns a new string with the character appended
*/
char	*ft_strjoin_char(char const *s, char c)
{
	char	*result;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	result = malloc(sizeof(char) * (len + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	return (result);
}

/*
** is_quoted - checks if a string begins and ends with the same quote
** Returns the quote character if quoted, 0 otherwise
*/
char	is_quoted(const char *str)
{
	size_t	len;

	if (!str || !*str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if ((str[0] == '\'' && str[len - 1] == '\'') ||
		(str[0] == '"' && str[len - 1] == '"'))
		return (str[0]);
	return (0);
}

/*
** expand_variables - simple variable expansion for $VAR format
** This is a basic implementation that expands environment variables
*/
char	*expand_variables(const char *str)
{
	char	*result;
	char	*temp;
	size_t	i;
	size_t	start;
	char	*var_name;
	char	*var_value;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			i++;
			start = i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			if (i > start)
			{
				var_name = ft_substr(str, start, i - start);
				if (var_name)
				{
					var_value = getenv(var_name);
					if (var_value)
					{
						temp = ft_strjoin(result, var_value);
						free(result);
						result = temp;
					}
					free(var_name);
				}
			}
		}
		else
		{
			temp = ft_strjoin_char(result, str[i]);
			free(result);
			result = temp;
			i++;
		}
		if (!result)
			return (NULL);
	}
	return (result);
}

/*
** process_heredoc_line - processes a single heredoc line for variable expansion
** If the line is quoted, expands variables and re-wraps in same quotes
*/
char	*process_heredoc_line(const char *line)
{
	char	quote_char;
	char	*content;
	char	*expanded;
	char	*result;
	char	quote_str[2];
	size_t	len;

	if (!line)
		return (NULL);
	quote_char = is_quoted(line);
	if (quote_char)
	{
		len = ft_strlen(line);
		content = ft_substr(line, 1, len - 2);
		if (!content)
			return (NULL);
		expanded = expand_variables(content);
		free(content);
		if (!expanded)
			return (NULL);
		quote_str[0] = quote_char;
		quote_str[1] = '\0';
		result = ft_strjoin(quote_str, expanded);
		free(expanded);
		if (!result)
			return (NULL);
		content = ft_strjoin(result, quote_str);
		free(result);
		return (content);
	}
	return (ft_strdup(line));
}

/*
** read_heredoc - reads heredoc input until delimiter is found
** Returns a string containing all heredoc lines joined with newlines
*/
char	*read_heredoc(const char *delimiter)
{
	char	*line;
	char	*processed_line;
	char	*result;
	char	*temp;

	if (!delimiter)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		processed_line = process_heredoc_line(line);
		free(line);
		if (!processed_line)
		{
			free(result);
			return (NULL);
		}
		temp = ft_strjoin(result, processed_line);
		free(result);
		free(processed_line);
		if (!temp)
			return (NULL);
		result = temp;
		temp = ft_strjoin(result, "\n");
		free(result);
		result = temp;
		if (!result)
			return (NULL);
	}
	return (result);
}
#include "builting_cmd.h"

/*
** has_heredoc - checks if command line contains heredoc operator
** Returns 1 if << is found, 0 otherwise
*/
int	has_heredoc(const char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}

/*
** get_heredoc_delimiter - extracts the delimiter after <<
** Returns the delimiter string or NULL if not found
*/
char	*get_heredoc_delimiter(const char *line)
{
	int		i;
	int		start;
	int		end;
	char	*delimiter;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
			while (line[i] && (line[i] == ' ' || line[i] == '\t'))
				i++;
			start = i;
			while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
				i++;
			end = i;
			if (end > start)
			{
				delimiter = ft_substr(line, start, end - start);
				return (delimiter);
			}
		}
		i++;
	}
	return (NULL);
}

/*
** remove_heredoc_from_line - removes << delimiter part from command line
** Returns a new string without the heredoc part
*/
char	*remove_heredoc_from_line(const char *line)
{
	int		i;
	int		heredoc_start;
	char	*before_heredoc;
	char	*result;

	if (!line)
		return (NULL);
	i = 0;
	heredoc_start = -1;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			heredoc_start = i;
			break ;
		}
		i++;
	}
	if (heredoc_start == -1)
		return (ft_strdup(line));
	before_heredoc = ft_substr(line, 0, heredoc_start);
	if (!before_heredoc)
		return (NULL);
	result = ft_strtrim(before_heredoc, " \t\n");
	free(before_heredoc);
	return (result);
}

char **ft_token(char *line) {
    char *token;
    char *tmp;
    char **comand;
    int i;
    char *delim;
    
    token = NULL;
    tmp = NULL;
    i = 0;
    delim = " \t\n";
    
    if (!line)
        return (NULL);
        
    tmp = ft_strdup(line);
    token = strtok(tmp, delim);

    if (!token){
        // free(tmp);
        // tmp = NULL;
        return (NULL);
    }
    while (!token) {
        i++;
        token = strtok(NULL, delim);
    }
    
    free(tmp);
    
    comand = malloc(sizeof(char *) * (i + 1));
    if (!comand) {
        return (NULL);
    }
    
    i = 0;
    token = strtok(line, delim);
    while (token) {
        comand[i] = ft_strdup(token);
        token = strtok(NULL, delim);
        i++;
    }
    
    comand[i] = NULL;
    return (comand);
}
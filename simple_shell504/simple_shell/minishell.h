#include "libft/libft.h"

#include <string.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

extern char	**environ;

void    free_array(char **av);
int     ft_exec(char **cmd, char **args,char **env, int i);
char    **ft_token(char *line);
void    builting_echo(char **args, int *status);
void	builting_cd(char **args, int *status);
void    builting_pwd(char **cmd, int *status);
void	builting_export(void);
void	builting_env(char **cmd, int *status);
void	builting_exit(char **cmd, char **args, int *status, int i);
void	builting_unset(char **args, int *status);
char    *get_path(char *comand);
void    print_error(char *name, char *cmd, int i);
void    handl_builting(char **cmd, char **args, int *status, int i);
int     is_builting(char *cmd);
int     ft_is_positive(char *str);
char	*ft_strjoin_char(char const *s, char c);
char	is_quoted(const char *str);
char	*expand_variables(const char *str);
char	*process_heredoc_line(const char *line);
char	*read_heredoc(const char *delimiter);
int	has_heredoc(const char *line);
char	*get_heredoc_delimiter(const char *line);
char	*remove_heredoc_from_line(const char *line);
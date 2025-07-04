#include "minishell.h"

void    builting_pwd(char **cmd, int *status) {
    char *c = NULL;
    size_t size = 0;
	
	(void)cmd;
	c = getcwd(c, size);

    if (c == NULL) {
        perror("pwd");
		*status = 1;
    } else {
        printf("%s\n", c);
		*status = 0;
    }

    free(c);
}
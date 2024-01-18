#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
# include "./libft/libft.h"

char	*rl_gets (char *line_read);
void  ft_parser(char *line_read);
int free_split(char **splitted);

int main (void)
{
	char *s;
	while(1)
	{
		s = rl_gets(s);
		rl_on_new_line();
		ft_parser(s);
		rl_redisplay();
		free(s);
	}
}

char	*rl_gets (char *line_read)
{
	if (line_read && *line_read)
		line_read = (char *)NULL;
	line_read = readline ("Mega boss o que queres? ");
	if (line_read && *line_read)
		add_history (line_read);
  	return (line_read);
}

void  ft_parser(char *line_read)
{
	char	**cmd;
	int		pid;

	cmd = ft_split(line_read, ' ');
	cmd[0] = ft_strjoin("/bin/", cmd[0]);
	
	pid = fork();
	if (pid == 0)
	{
		execve(cmd[0], cmd, NULL);
		return ;
	}
	waitpid(pid, NULL, 0);
	free_split(cmd);
}

int free_split(char **splitted)
{
	int i;

	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	return(0);
}
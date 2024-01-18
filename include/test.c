#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

char	*rl_gets (char *line_read);

int main (int ac, char **av)
{
	char *s;

	s = rl_gets(s);
  rl_on_new_line();
	rl_redisplay();;
	free(s);
}

char	*rl_gets (char *line_read)
{
  if (line_read)
    {
      line_read = (char *)NULL;
    }
  line_read = readline ("Mega boss o que queres? ");
  if (line_read)
    add_history (line_read);
  return (line_read);
}

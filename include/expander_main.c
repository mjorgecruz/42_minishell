
#include "minishell.h"

char *master_expander(char *cmd, t_localenv *local)
{
    t_lstexpand *in_cmd_list;
	char *joined_content;

	in_cmd_list = NULL;
    create_list_quotes(cmd, &in_cmd_list);
    expand_content_in_list(in_cmd_list, local);
    clean_quotes_in_list(in_cmd_list);
    joined_content = join_list_contents(in_cmd_list);
	free_lstexpand(in_cmd_list);
    in_cmd_list = NULL;
    return (joined_content);
}

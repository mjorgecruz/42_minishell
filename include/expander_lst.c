#include "minishell.h"

t_lstexpand *create_node_lstexpand(int status, char *content)
{
    t_lstexpand *new_node;
    
    new_node = (t_lstexpand *)malloc(sizeof(t_lstexpand));
    if (!new_node)
        return (NULL);
    new_node->status = status;
    new_node->content = content;
    new_node->next = NULL;
    return new_node;
}

void insert_lstexpand_node(t_lstexpand **head, t_lstexpand *new_node)
{
    t_lstexpand *temp;

    if (*head == NULL)
		*head = new_node;
    else
    {
        temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
    }
}

void free_lstexpand(t_lstexpand *head)
{
    t_lstexpand *temp;

    while (head != NULL)
	{
        temp = head;
        head = head->next;
        free(temp->content);
        free(temp);
    }
}

void create_list_quotes(char *cmd, t_lstexpand **in_cmd_list)
{
    int i;
    int start;
    int size;

    i = 0;
    start = 0;
    while (cmd[i] != '\0')
    {
        if (cmd[i] == '\'' || cmd[i] == '\"')
        {
            if (i > start)
                insert_lstexpand_node(in_cmd_list, create_node_lstexpand(0, ft_strndup(cmd + start, i - start)));
            size = quotation_size(cmd, i);
            insert_lstexpand_node(in_cmd_list, create_node_lstexpand(0, ft_strndup(cmd + i, size)));
            i = i + size;
            start = i;
        }
        else
            i++;
    }
    if (i > start)
        insert_lstexpand_node(in_cmd_list, create_node_lstexpand(0, ft_strndup(cmd + start, i - start)));
}

void expand_content_in_list(t_lstexpand *head, t_localenv *local)
{
    t_lstexpand *current;
    char *expanded_content;

	current = head;
    while (current != NULL)
	{
        expanded_content = expand_single_variable(current->content, local);
        free(current->content);
        current->content = expanded_content;
        current = current->next;
    }
}

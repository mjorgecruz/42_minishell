#include "minishell.h"

bool mid_parser_iteration(const char *str)
{
    int i;
    
    i = -1;
    while (str[++i])
    {
        i = ignore_in_quotes(str, i);
        if (i >= 0)
        {
            i = ignore_spaces(str, i);
            i = check_pipes(str, i);
        }
        else if (i >= 0)
        {
            i = ignore_spaces(str, i);
            i = check_redirs(str, i);
        }
        else if(i >= 0)
        {
            i = ignore_spaces(str, i);
            i = check_uppersand(str, i);
        }
        else if (i < 0)
        {
            	printf("\n\x1b[31m[KO] ->\x1b[0m INVALID MID->  M2\x1b[0m\n");
            return false;
        }
    }
    return true;
}

int check_pipes(const char *str, int pos)
{
    if (str[pos] != '|')
        return (pos);
    else if (str[pos] == str[pos + 1])
        return (pos + 2);
    else if (!is_special_char(str[pos + 1]))
    {
        if (str[pos + 1])
            pos = ignore_spaces(str, pos + 1);
        else if (!str[pos])
            return (pos);
    }
    else if (is_special_char(str[pos + 1]))
    {
        if (str[pos + 1] == '>' || str[pos + 1] == '<')
        {
            pos = check_redirs(str, pos + 1);
            if (pos < 0)
                return (-1);
            else
                return (pos);
        }
    }
    return (-1); ///???
}

int check_redirs(const char *str, int pos)
{
    if (str[pos] == '>' || str[pos] == '<')
    {
        if (str[pos] == str[pos + 1])                   // >> ou << com comando valido na frente
        {
            if (has_valid_cmd_after(str, pos + 2))
                return (pos + 2); 
            return (-1);
        }
        else if (!is_special_char(str[pos + 1]))        // > ou < com comando valido na frente
        {
            if (has_valid_cmd_after(str, pos + 1))
                return (pos + 1);
            return (-1);
        }
    }
    return (pos);
}

int check_uppersand(const char *str, int pos)
{
    if (str[pos] != '&')
        return (pos);
    else if (str[pos] == '&')
    {
        if (str[pos] == str[pos + 1])
            return (pos + 2);
    }
    return (-1);
}





// bool check_combs_doubles(const char *str, int pos)
// {
//     if (str[pos] == '<' && has_valid_cmd_after(str, pos + 1))                                  // is   <     has to have a valid comand after    can be after | or after ||
//         return (true);
//     else if (str[pos] == '>' && str[pos + 1] != '|' && has_valid_cmd_after(str, pos + 1))      // is   >     has to have a valid comand after
//         return (true);
//     else if (str[pos] == '>' && str[pos + 1] == '|')                                           // is   >|    has to have a valid comand after
//     {
//         if (has_valid_cmd_after(str, pos + 2))
//             return (true);
//     }
//     else if (str[pos] == '>' && str[pos + 1] == '>')                                           // is   >>    has to have a valid comand after
//     {
//         if (has_valid_cmd_after(str, pos + 2))
//             return (true);
//     }
//     else if (str[pos] == '<' && str[pos + 1] == '<')                                           // is   <<    has to have a valid comand after
//     {
//         if (has_valid_cmd_after(str, pos + 2))
//             return (true);    
//     }
//     return (false);
// }



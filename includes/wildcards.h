/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:04:23 by masoares          #+#    #+#             */
/*   Updated: 2024/04/03 14:18:56 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef WILDCARDS_H
#define WILDCARDS_H

typedef enum    e_wildtype
{
    WILD_ONE,       //*
    WILD_FRONT,     //*ls
    WILD_BACK,      //ls*
    WILD_MIDDLE,    //*ls*
    WILD_EDGES,      //l*s
    WILD_MEGA_BACK,  //l*s*
    MEGA_WILD       //*l**s*
}   t_wildtype;

char    *wildcardings(char *str);
char	*wild_rewriter(char *str,char **wild);

/* ************************************************************************** */
/*                        WILDCARDS_UTILS                                     */
/* ************************************************************************** */
int     wildcard_checker(char *str);
int		wildcards_counter(char *str);

/* ************************************************************************** */
/*                        WILDCARDS_UTILS2                                    */
/* ************************************************************************** */
char	**wild_splitter(char *str);
char	*add_simple_wildcard(char *str, int *i);
char	*add_forw_wildcard(char *str, int *i);
char	*add_back_wildcard(char *str, int *i);
char	*add_middle_wildcard(char *str, int *i);

/* ************************************************************************** */
/*                        WILDCARDS_UTILS3                                    */
/* ************************************************************************** */

int		mega_strncmp(char *str, char *comp);

#endif
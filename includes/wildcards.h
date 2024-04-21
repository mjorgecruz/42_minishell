/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:04:23 by masoares          #+#    #+#             */
/*   Updated: 2024/04/21 14:26:43 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H

typedef enum e_wildtype
{
	WILD_ONE,
	WILD_FRONT,
	WILD_BACK,
	WILD_MIDDLE,
	WILD_EDGES,
	WILD_MEGA_BACK,
	MEGA_WILD
}	t_wildtype;

char	*wildcardings(char *str);
char	*wild_rewriter(char *str, char **new, char **wild, int k);
void	add_wildcard(char **wild, char *origin);

/* ************************************************************************** */
/*                        WILDCARDS_UTILS                                     */
/* ************************************************************************** */
int		wildcard_checker(char *str);
int		wildcards_counter(char *str);
int		order_cmp(char *letters, char *str);

/* ************************************************************************** */
/*                        WILDCARDS_UTILS2                                    */
/* ************************************************************************** */
char	**wild_splitter(char *str, int i, int j, int k);
char	*add_simple_wildcard(char *str, int *i);
char	*add_forw_wildcard(char *str, int *i);
char	*add_back_wildcard(char *str, int *i);
char	*add_middle_wildcard(char *str, int *i);

/* ************************************************************************** */
/*                        WILDCARDS_UTILS3                                    */
/* ************************************************************************** */

int		mega_strncmp(char *str, char *comp);

/* ************************************************************************** */
/*                        WILDCARDS_UTILS4                                    */
/* ************************************************************************** */

int		wfront(char *str, char *comp);
int		wback(char *str, char *comp);
int		wmiddle(char *str, char *comp);
int		wedges(char *str, char *comp);
int		wmega_back(char *str, char *comp, int i, int res);
int		wmega(char *str, char *comp);
int		mega_wildcmp(char *wildcard, char *comp, int start);
int		rewriter(char **final, char *wild, char *new, int *j);
void	wildcard_formatter(char **wildcard, char *str, int *i);

#endif
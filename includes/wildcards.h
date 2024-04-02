/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:04:23 by masoares          #+#    #+#             */
/*   Updated: 2024/04/02 15:27:46 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef WILDCARDS_H
#define WILDCARDS_H

int     wildcard_checker(char *str);
char    *wildcardings(char *str);

char	**wild_splitter(char *str);
char	*add_simple_wildcard(char *str, int *i);
char	*add_forw_wildcard(char *str, int *i);
char	*add_back_wildcard(char *str, int *i);
char	*add_middle_wildcard(char *str, int *i);

int		wildcards_counter(char *str);
char	*wild_rewriter(char *str,char **wild);



#endif
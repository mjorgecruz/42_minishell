/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:16:41 by masoares          #+#    #+#             */
/*   Updated: 2024/01/30 12:28:26 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*Returns the converted integral number as an int value.Considers white spaces 
and one '+' or '-' before the number. If no valid conversion could be performed,
it returns zero*/
int		ft_atoi(const char *str);

long	ft_atol(const char *str);

int		ft_atoi_base(char *str, int base_dim);
/* The bzero() function erases the data in the n bytes of the memory starting at
 the location pointed to by s, by writing zeros (bytes containing '\0') to that 
 area*/
void	ft_bzero(void *s, size_t n);

/*allocates the requested memory and returns a pointer to it. Calloc sets
allocated memory to zero.*/
void	*ft_calloc(size_t nitems, size_t size);

/*Returns 1 if argument is an alphanumeric character or zero if not*/
int		ft_isalnum(int c);

/*If a character passed to isalpha() is an alphabet, it returns a non-zero 
integer, if not it returns 0*/
int		ft_isalpha(int c);

/*Tests if a given character, in the current locale, can be represented as a 
valid 7–bit US-ASCII character. Returns nonzero if c can be represented as a 
character in the US-ASCII character set. Otherwise, it returns 0 */
int		ft_isascii(int c);

/*Returns 0 if arg is not a numeric character and a non-zero value if arg is a 
numeric character*/
int		ft_isdigit(int c);

/*If a character passed is a printable character, it returns a non-zero integer,
if not it returns 0.*/
int		ft_isprint(int c);

/*Searches for the first occurrence of the character c (an unsigned char) in the
 first n bytes of the string pointed to, by the argument str*/
void	*ft_memchr(const void *str, int c, size_t n);

/**/
int		ft_memcmp(const void *str1, const void *str2, size_t n);

/**/
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**/
void	*ft_memmove(void *dest, const void *src, size_t n);

/**/
void	*ft_memset(void *str, int c, size_t n);

/**/
char	*ft_strchr(const char *str, int c);

char	*ft_strdup(const char *s);

size_t	ft_strlcat(char *dst, const char *src, size_t size);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

int		ft_strlen(const char *str);

int		ft_strncmp(const char *str1, const char *str2, size_t num);

char	*ft_strnstr(const char *big, const char *little, size_t len);

char	*ft_strrchr(const char *str, int c);

int		ft_tolower(int ch);

int		ft_toupper(int ch);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strtrim(char const *s1, char const *set);

char	**ft_split(char const *s, char c);

char	*ft_itoa(int n);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

int		ft_putchar_fd(char c, int fd);

int		ft_putstr_fd(char *s, int fd);

void	ft_putendl_fd(char *s, int fd);

int		ft_putnbr_fd(int n, int fd);

t_list	*ft_lstnew(void *content);

void	ft_lstadd_front(t_list **lst, t_list *new);

int		ft_lstsize(t_list *lst);

t_list	*ft_lstlast(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstclear(t_list **lst, void (*del)(void *));

void	ft_lstdelone(t_list *lst, void (*del)(void *));

void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int		count_words(char const *s, char c);

int		ft_strcmp(const char *str1, const char *str2);

/* ************************************************************************** */
/*                               FT_PRINTF                                    */
/* ************************************************************************** */

int		ft_putunbr_fd(unsigned long nbr, int fd, int size);
int		ft_putnbr_base(unsigned int nbr, char *base, int fd);
int		ft_putnbr_base_sc(unsigned int nbr, int size, char l);
int		ft_count_num(int nbr, int size);
int		ft_count_num2(unsigned int nbr, int size);
int		ft_printf(const char *str, ...);
int		ft_putadd_fd(unsigned long num, int fd);

/* ************************************************************************** */
/*                              GET_NEXT_LINE                                 */
/* ************************************************************************** */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		ft_strlen2(char *str);
char	*get_next_line(int fd);
int		search_temp(char *temp);
void	add_to_temp(char **temp, char **src);
char	*add_to_line(char *temp);
char	*clean_temp(char *temp);
char	*ft_calloc2(size_t size, int n);
char	*ft_freeing(char **buffer, char **temp);

#endif
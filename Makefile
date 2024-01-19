# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: masoares <masoares@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 09:48:00 by masoares          #+#    #+#              #
#    Updated: 2024/01/18 10:10:58 by masoares         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = ./include/minishell.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra

LIBFLAGS = -lreadline

LIBFT = ./include/libft/libft.a

CC = cc

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBFLAGS)

$(LIBFT):
	make -c ./include/libft

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) $(OBJ)

re: fclean all
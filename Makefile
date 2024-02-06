# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: masoares <masoares@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 09:48:00 by masoares          #+#    #+#              #
#    Updated: 2024/02/06 09:05:01 by masoares         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
END_COLOR = \033[0m
BOLD_GREEN = \e[1;32m
END = \e[0m



NAME = minishell

SRC = ./include/minishell.c ./include/history.c ./include/parser_general.c \
		./include/parser_quotes.c ./include/parser_special.c \
		./include/out_setup_general.c ./include/finex.c ./include/errors.c \
		./include/str_utils.c ./include/general_executor.c ./include/general_executor_2.c \
		./include/parser_special_utils.c

LIBRARY = 
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g

VALGRIND_FLAGS = valgrind --leak-check=full --suppressions=sup --track-origin=yes

LIBFLAGS = -lreadline

LIBFT = ./include/libft/libft.a

CC = cc

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBFLAGS)
		@echo "${BOLD_GREEN}...minishell is reborn${END}"

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
	@make -C ./include/libft/ -s

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./include/libft/ -s
	@echo "${RED}minishell is no more...${END}"

clean:
	@$(RM) $(OBJ)
	@make clean -C ./include/libft/ -s

re: fclean all

leak_test: sup_file ./minishell

# sup_file: 
# 	$(file > sup, $(SUP))
# 	$(VALGRIND_FLAGS
# 	dsfp)
	
# define SUP_BODY
# {
	
# 	Memcheck:Leak
# 	fun: malloc
# 	...
# 	fun:readline
# 	...
# 	fun: add_history
# }
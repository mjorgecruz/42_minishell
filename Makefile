# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: masoares <masoares@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 09:48:00 by masoares          #+#    #+#              #
#    Updated: 2024/02/08 22:47:24 by masoares         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
END_COLOR = \033[0m
BOLD_GREEN = \e[1;32m
BOLD_YELLOW = \e[1;33m
END = \e[0m

NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g

VGFLAGS = valgrind --leak-check=full --suppressions=sup --track-origins=yes --log-file=leaks.log 

INCDIR:=include
ODIR:=obj

SRC := minishell.c history.c parser_general.c \
		parser_quotes.c parser_special.c \
		out_setup_general.c finex.c errors.c \
		str_utils.c general_executor.c general_executor_2.c \
		parser_special_utils.c parser_piper.c special_mid_parser.c \


LIBRARY = 
OBJ := $(patsubst %.c, $(ODIR)/%.o,$(SRC))

LIBFLAGS = -lreadline

LIBFT = ./include/libft/libft.a

CC = cc

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBFLAGS)
		@echo "${BOLD_GREEN}...minishell is reborn${END}"

$(ODIR)/%.o: $(INCDIR)/%.c | $(ODIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(ODIR):
	@mkdir -p $@

$(LIBFT):
	@make -C ./include/libft/ -s

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./include/libft/ -s
	@echo "${RED}minishell is no more...${END}"

clean:
	@$(RM) $(OBJ)
	@$(RM) sup
	@$(RM) leaks.log
	@make clean -C ./include/libft/ -s

re: fclean all

suppress: sup_file all
	@echo "${BOLD_YELLOW}LEAK CHECKER ON${END}"
	
leaks: ./minishell
	$(VGFLAGS) ./minishell

sup_file: 
	$(file > sup, $(SUP_BODY))
	@echo "${BOLD_YELLOW}Suppressing readline and add_history leaks${END}"
	
define SUP_BODY
{
   name
   Memcheck:Leak
   fun:*alloc
   ...
   obj:*/libreadline.so.*
   ...
}
{
    leak readline
    Memcheck:Leak
    ...
    fun:readline
}
{
    leak add_history
    Memcheck:Leak
    ...
    fun:add_history
}
endef
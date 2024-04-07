# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: masoares <masoares@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 09:48:00 by masoares          #+#    #+#              #
#    Updated: 2024/04/06 17:05:32 by masoares         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
END_COLOR = \033[0m
BOLD_GREEN = \033[1;32m
BOLD_YELLOW = \033[1;33m
END = \033[0m

NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g

VGFLAGS = valgrind --leak-check=full --suppressions=sup --track-origins=yes --log-file=leaks.log 

INCDIR:=srcs
ODIR:=obj

SRC := minishell.c \
		history.c \
		finex.c \
		errors/errors.c \
		utils/str_utils.c \
		utils/megasplit.c \
		heredocs/heredocs.c \
		heredocs/heredocs_2.c \
		parser/parser_general.c \
		parser/parser_quotes.c \
		parser/parser_special.c \
		parser/parser_special_utils.c \
		parser/parser_piper.c \
		parser/parser_parenthesis.c \
		parser/special_mid_parser.c \
		execution/solver.c \
		execution/execve.c \
		execution/out_setup_general.c \
		execution/general_executor.c \
		execution/general_executor_2.c \
		builtins/builtins.c \
		builtins/echo/echo.c \
		builtins/expander/expander.c \
		builtins/expander/expander_lst.c \
		builtins/expander/expander_utils.c \
		builtins/expander/expander_main.c \
		builtins/export/export.c \
		builtins/export/export_utils.c \
		builtins/export/export_envcpy.c \
		builtins/export/export_utils_sort.c \
		builtins/export/ft_getenv.c \
		builtins/exit/exit_command.c \
		builtins/cd/cd_command.c \
		builtins/cd/cd_utils.c \
		wildcards/wildcards.c \
		wildcards/wildcards_utils.c \
		wildcards/wildcards_utils2.c \
		wildcards/wildcards_utils3.c \
		wildcards/wildcards_utils4.c \
		signals/signals.c \

		


LIBRARY = 
OBJ := $(patsubst %.c, $(ODIR)/%.o,$(SRC))

LIBFLAGS = -lreadline

LIBFT = ./libft/libft.a

CC = cc

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBFLAGS)
		@echo "${BOLD_GREEN}...minishell is reborn${END}"

$(ODIR):
	@mkdir -p $@
	
$(ODIR)/%.o: $(INCDIR)/%.c
	@mkdir -p $(dir $@) 
	@$(CC) $(CFLAGS) -c -o $@ $<
	


$(LIBFT):
	@make -C ./libft/ -s

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./libft/ -s
	@echo "${RED}minishell is no more...${END}"

clean:
	@$(RM) $(OBJ)
	@$(RM) sup
	@$(RM) leaks.log
	@make clean -C ./libft/ -s

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

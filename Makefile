#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: masoares <masoares@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 09:48:00 by masoares          #+#    #+#              #
#    Updated: 2024/04/18 16:53:25 by masoares         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
END_COLOR = \033[0m
BOLD_GREEN = \033[1;32m
BOLD_YELLOW = \033[1;33m
END = \033[0m

NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g

VGFLAGS = valgrind --leak-check=full --suppressions=sup --track-origins=yes --show-leak-kinds=all --log-file=leaks.log -s

TESTFLAGS = -fsanitize=address

INCDIR:=srcs
ODIR:=obj

SRC := minishell.c \
		history.c \
		history_2.c \
		history_3.c \
		finex.c \
		errors/errors.c \
		utils/str_utils.c \
		utils/megasplit.c \
		heredocs/heredocs.c \
		heredocs/heredocs_2.c \
		heredocs/heredocs_3.c \
		parser/parser_general.c \
		parser/parser_quotes.c \
		parser/parser_special.c \
		parser/parser_special_utils.c \
		parser/parser_piper.c \
		parser/parser_parenthesis.c \
		parser/special_mid_parser.c \
		execution/solver.c \
		execution/solver_2.c \
		execution/solver_3.c \
		execution/execve.c \
		execution/execve_2.c \
		execution/out_setup_general.c \
		execution/out_setup_general2.c \
		execution/out_setup_general3.c \
		execution/out_setup_general4.c \
		execution/general_executor.c \
		execution/general_executor_2.c \
		execution/general_executor_3.c \
		builtins/builtins.c \
		builtins/builtins_utils.c \
		builtins/echo/echo.c \
		builtins/expander/expander.c \
		builtins/expander/expander_lst.c \
		builtins/expander/expander_utils.c \
		builtins/expander/expander_utils_2.c \
		builtins/expander/expander_main.c \
		builtins/export/export.c \
		builtins/export/export_utils.c \
		builtins/export/export_utils_2.c \
		builtins/export/export_envcpy.c \
		builtins/export/export_utils_sort.c \
		builtins/export/ft_getenv.c \
		builtins/exit/exit_command.c \
		builtins/exit/exit_utils.c \
		builtins/cd/cd_command.c \
		builtins/cd/cd_utils_2.c \
		builtins/cd/cd_utils.c \
		wildcards/wildcards.c \
		wildcards/wildcards_utils.c \
		wildcards/wildcards_utils2.c \
		wildcards/wildcards_utils3.c \
		wildcards/wildcards_utils4.c \
		signals/signals.c \
		signals/signals_handlers.c \

LIBRARY = 
OBJ := $(patsubst %.c, $(ODIR)/%.o,$(SRC))

LIBFLAGS = -lreadline

LIBFT = ./libft/libft.a

CC = cc

RM = rm -f

TOTAL_FILES := $(words $(SRC))
COMPILED_FILES := $(shell if [ -d "$(ODIR)" ]; then find $(ODIR) -name "*.o" | wc -l; else echo 0; fi)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBFLAGS)
	@printf "$(BOLD_GREEN)...minishell in the making: $$(echo "$(shell find $(ODIR) -name "*.o" | wc -l) $(TOTAL_FILES)" | awk '{printf "%.2f", $$1/$$2 * 100}')%%$(RES)\r"
	@printf "\n"
	@echo "${BOLD_GREEN}minishell is reborn...${END}"

test: $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(TESTFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBFLAGS)
	@echo "${BOLD_GREEN}...minishell is reborn${END}"

$(ODIR):
	@mkdir -p $@
	
$(ODIR)/%.o: $(INCDIR)/%.c
	@mkdir -p $(dir $@) 
	@printf "$(BOLD_GREEN)...minishell in the making: $$(echo "$(shell find $(ODIR) -name "*.o" | wc -l) $(TOTAL_FILES)" | awk '{printf "%.2f", $$1/$$2 * 100}')%%$(RES)\r"
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

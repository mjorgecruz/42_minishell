NAME = minishell

LIBFT = ./includes/Libft/libft.a

RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYN = \033[0;36m
WHT = \033[0;37m
RES = \033[0m

CC = cc

CFLAGS = -Werror -Wall -Wextra -g 

VG	=	valgrind --leak-check=full --suppressions=sup --track-origins=yes --log-file=leaks.log

LFLAG = -lreadline

RM = rm -rf

SDIR := src
ODIR := obj

SOURCES := main.c \
			list_utils.c\
			error_handler.c\
			free_memory.c\
			cmd_utils.c\
			org_list_utils.c\
			parser_input.c\
			parser_utils.c\
			parser_signs.c\
			fill_data_utils.c\
			testerzzzz.c\
			placeholder.c\
			read_line.c\
			read_line_utils.c\
			parser_search_utils.c\
			parser_diff_signs.c\
			heardoc_checker.c\
			
OBJECTS := $(patsubst %.c,$(ODIR)/%.o,$(SOURCES))


all : ${NAME}

${NAME} : ${OBJECTS} ${LIBFT}
	@${CC} ${CFLAGS} ${OBJECTS} ${LIBFT} -o ${NAME} $(LFLAG)
	@echo "\n$(GRN)➾ Minishell created$(RES)"

$(LIBFT):
	@make bonus -C ./includes/Libft/ -s
	@echo "${GRN}➾ $@ created ${RES}"

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "${GRN}➾ $@ created ${RES}"

$(ODIR):
	@mkdir -p $@	

clean :
	@${RM} ${OBJECTS}
	@${RM} ${ODIR}
	@echo "${RED}➾ Minishell objects deleted${RES}"
	@make clean -C./includes/Libft/ -s

fclean : clean
	@${RM} ${NAME}
	@echo "${RED}➾ Minishell deleted${RES}"
	@${RM} sup
	@echo "${RED}➾ Sup File deleted${RES}"
	@${RM} leaks.log
	@echo "${RED}➾ Leaks.log deleted${RES}"
	@make fclean -C ./includes/Libft/ -s

re : fclean all

debug: all sup_file
	@echo "$(GREEN)Minishell compiled in debug mode!$(DEF_COLOR)"

leaks: ./minishell
	$(VG) ./minishell

.PHONY: bonus

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

sup_file:
	$(file > sup,$(SUP_BODY))
	@echo "$(MAG)Created suppression file to use with valgrind --suppressions=sup$(RES)"
NAME = minishell

LIBFT = inc/libft/libft.a

INC = ms_minishell.h \
	  ms_define.h \
	  ms_structs.h

SRCS = ms_minishell.c \
	   utils/ms_utils1.c \
	   utils/ms_init.c \
	   utils/ms_signals.c \
	   utils/ms_clean.c \
	   utils/ms_clean_cmd.c \
	   utils/ms_clean_tokens.c \
	   lexer/ms_lexer.c \
	   lexer/ms_ctoken_op.c \
	   lexer/ms_ctoken_op2.c \
	   lexer/ms_ctoken_wrd.c \
	   lexer/ms_lexer_utils.c \
	   lexer/ms_lexer_utils_2.c \
	   expanser/ms_expanser.c \
	   expanser/ms_expanser_concat.c \
	   expanser/ms_exp_var.c \
	   expanser/wildcard/ms_wildcard.c \
	   expanser/wildcard/ms_wildcard_utils.c \
	   expanser/wildcard/ms_wildcard_utils2.c \
	   expanser/wildcard/ms_wildcard_matches.c \
	   expanser/ms_expanser_utils.c \
	   parser/ms_create_cmd.c \
	   parser/ms_create_redir.c \
	   parser/ms_parser.c \
	   parser/ms_parser_cleaner.c \
	   parser/ms_parser_env.c \
	   parser/ms_parser_format.c \
	   parser/ms_parser_format2.c \
	   parser/ms_parser_path.c \
	   parser/heredoc/ms_heredoc.c \
	   parser/heredoc/ms_heredoc_expand.c \
	   parser/heredoc/ms_heredoc_utils.c \
	   parser/ms_parser_utils.c \
	   exec/ms_exec.c \
	   exec/ms_exec_child.c \
	   exec/ms_exec_utils.c \
	   buildins/cd/ms_cd.c \
	   buildins/cd/ms_export_env.c \
	   buildins/cd/ms_cd_utils.c \
	   buildins/cd/ms_relative_path.c \
	   buildins/cd/ms_change_path.c \
	   buildins/cd/ms_get_directory.c \
	   buildins/cd/ms_add_target_dir.c \
	   buildins/ms_echo.c \
	   buildins/ms_export_utils.c \
	   buildins/ms_pwd.c \
	   buildins/ms_export.c \
	   buildins/ms_unset.c \
	   buildins/ms_env.c \
	   buildins/ms_exit.c \
	   buildins/ms_env_utils.c \
	   error/ms_error.c \
	   error/ms_check_syntax.c \
	   error/ms_check_syntax_utils.c

UNAME = $(shell uname)

ifeq (${UNAME}, Darwin)
OS = 1
LIBINC = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib 
IRDLINE = -I/Users/$(USER)/.brew/opt/readline/include
#IRDLINE = -I/usr/local/opt/readline/include
#LIBINC = -lreadline -L /usr/local/opt/readline/lib 
endif

ifeq (${UNAME}, Linux)
OS = 0
LIBINC = -lreadline
endif

SRCDIR = src
OBJDIR = objs
INCDIR = inc

CC = clang
CFLAGS = -Wall -Wextra -Werror
#MEM = -fsanitize=address

OBJS = $(addprefix ${OBJDIR}/,${SRCS:.c=.o})

all: ${NAME}

$(LIBFT) :
	@make -s -C inc/libft

$(NAME): ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${MEM} ${OBJS} ${LIBFT} -o $@ ${LIBINC}

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p ${@D}
	${CC} ${CFLAGS} ${MEM} ${IRDLINE} ${TFLAG} -I./inc -c $< -o $@

re: fclean all

clean:
	@echo  "Cleaning objects\c"
	@rm -rf ${OBJDIR}
	@make clean -s -C inc/libft > /dev/null
	@echo "\033[32m\t[OK]\033[0m"

fclean: clean
	@echo  "Removing minishell\c"
	@rm -rf ${NAME}
	@make fclean -s -C inc/libft > /dev/null
	@echo "\033[32m\t[OK]\033[0m"

.PHONY : all clean re fclean 

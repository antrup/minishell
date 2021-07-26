NAME = minishell

LIBFT = inc/libft/libft.a

INC = ms_minishell.h \
	  ms_define.h \
	  ms_structs.h

SRCS = ms_minishell.c \
	   utils/ms_utils1.c \
	   utils/ms_init.c \
	   utils/ms_clean.c \
	   lexer/ms_lexer.c \
	   lexer/ms_lexer_var.c \
	   lexer/ms_lexer_utils.c \
	   lexer/ms_lexer_utils_2.c \
	   expanser/ms_expanser.c \
	   expanser/ms_expanser_utils.c \
	   parser/ms_create_cmd.c \
	   parser/ms_parser.c \
	   parser/ms_parser_cleaner.c \
	   parser/ms_parser_env.c \
	   parser/ms_parser_format.c \
	   parser/ms_parser_format2.c \
	   parser/ms_parser_path.c \
	   parser/ms_redir_ina.c \
	   parser/ms_parser_utils.c

#TO BE REMOVED - TEST
SRCS += ms_test/tester.c

UNAME = $(shell uname)

ifeq (${UNAME}, Darwin)
OS = 1
endif

ifeq (${UNAME}, Linux)
	OS = 0
endif

SRCDIR = src
OBJDIR = objs
INCDIR = inc

CC = clang
CFLAGS = -Wall -Wextra -Werror -g

ifeq (${UNAME}, Linux)
LIBINC = -lreadline
endif
ifeq (${UNAME}, Darwin)
LIBINC = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib 
IRDLINE = -I/Users/$(USER)/.brew/opt/readline/include
endif
MEM = -fsanitize=address

OBJS = $(addprefix ${OBJDIR}/,${SRCS:.c=.o})

all: ${NAME}

$(LIBFT) :
	@make -s -C inc/libft

$(NAME): ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${MEM} ${OBJS} ${LIBFT} -o $@ ${LIBINC}

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p ${@D}
	${CC} ${CFLAGS} ${IRDLINE} ${TFLAG} -I./inc -c $< -o $@

test: TFLAG = -D TEST=1 -D OSX=${OS}

test: fclean ${NAME}

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

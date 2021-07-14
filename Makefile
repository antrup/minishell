NAME = minishell

LIBFT = inc/libft/libft.a

INC = ms_minishell.h \
	  ms_define.h \
	  ms_structs.h

SRCS = ms_minishell.c \
	   utils/ms_utils.c \
	   utils/ms_clean.c \
	   lexer/ms_lexer.c \
	   ms_expanser.c \
	   ms_expanser_utils.c \
	   lexer/ms_lexer_utils.c

#TO BE REMOVED - TEST
SRCS += tester.c

SRCDIR = src
OBJDIR = objs
INCDIR = inc

CC = clang
CFLAGS = -Wall -Wextra -Werror -g
LIBINC = -lreadline
#MEM = -fsanitize=address

OBJS = $(addprefix ${OBJDIR}/,${SRCS:.c=.o})

all: ${NAME}

$(LIBFT) :
	@make -s -C inc/libft

$(NAME): ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${MEM} ${OBJS} ${LIBFT} -o $@ ${LIBINC}

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p ${@D}
	${CC} ${CFLAGS} ${TFLAG} -I./inc -c $< -o $@

test: TFLAG = -D TEST=1

test: fclean ${NAME}

test-exp: ${LIBFT}
<<<<<<< HEAD
	${CC} ${CFLAGS} -D TEST=1  -I./inc src/tester_expanser.c src/ms_expanser.c src/ms_expanser_utils.c src/lexer/ms_lexer_utils.c src/utils/*.c src/tester.c ${LIBFT} ${LIBINC} -o $@
=======
		${CC} ${CFLAGS} -D TEST=1  -I./inc src/tester_expanser.c src/ms_expanser.c src/lexer/ms_lexer_utils.c src/utils/*.c src/tester.c ${LIBFT} ${LIBINC} -o $@
>>>>>>> 68d85feb4882683deb76670ea993f3857fa1ca4d

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

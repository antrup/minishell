NAME = minishell

LIBFT = inc/libft/libft.a

INC = ms_minishell.h

SRCS = ms_minishell.c \
	   ms_utils.c \
	   ms_lexer.c

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
	make -s -C inc/libft

$(NAME): ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${MEM} ${OBJS} ${LIBFT} -o $@ ${LIBINC}

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p ${@D}
	${CC} ${CFLAGS} -I./inc -c $< -o $@

re: fclean all

clean:
	@echo  "Cleaning objects\c"
	@rm -rf ${OBJDIR}
	@echo "\033[32m\t[OK]\033[0m"

fclean: clean
	@echo  "Removing minishell\c"
	@rm -rf ${NAME}
	@echo "\033[32m\t[OK]\033[0m"

.PHONY : all clean re fclean 

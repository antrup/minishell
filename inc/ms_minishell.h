/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:07:10 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/16 09:13:58 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_MINISHELL_H
# define MS_MINISHELL_H

/*
** STANDARD C99 HEADERS
*/
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
/*
** MINISHELL HEADERS
*/

# include "ms_structs.h"
# include "ms_define.h"
# include "libft/inc/libft.h"

/*
** TEST
*/
# ifndef TEST
#  define TEST 0
# endif

/*
** MAIN FUNCTIONS
*/

int		ms_lexer(t_ms *data);

/*
** LEXER UTILS
*/

int		ms_isop_pipe(char c);
int		ms_isop_and(char c, char b);
int		ms_isquote(char c);
int		ms_isredirection(char c);
int		ms_isparen(char c);
int		ms_isvariable(char *str);
int		ms_ctoken_word(char *line, t_tlist **tlist, int *i);
int		ms_ctoken_re(char *line, t_tlist **tlist, int *i);
int		ms_ctoken_and(t_tlist **tlist, int *i);
int		ms_ctoken_pipe(char *line, t_tlist **tlist, int *i);
t_tlist	*ms_create_token(t_tlist **tlist);

/*
** UTILS
*/

int		is_interactive(void);
void	ms_init(t_ms *data);
void	ms_clean(t_ms *data);
/*
** EXPANSER
*/

int		ms_isparen(char c);
int		ms_isvariable(char *str);
char	*ms_concat(t_word *wlist);
void	ms_expanser(t_ms *data);
void	ms_clean_wlist(t_word *list);
void	ms_var_tokens(char *var, t_tlist **tokens);
t_word	*ms_create_part(t_word **wlist);
/*
** DEBUG -- TEST                                                |~
*/

void	print_token(t_ms *data);
void	ms_leak(int sig, siginfo_t *var, void *param);

#endif

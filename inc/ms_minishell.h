/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:07:10 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/25 17:18:51 by sshakya          ###   ########.fr       */
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
# include <termios.h>
# include <sys/wait.h>
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
# ifndef OSX
#  define OSX 0
# endif

/*
** MAIN FUNCTIONS
*/

int		ms_lexer(char *line, t_tlist **tokens);
void	ms_expanser(t_tlist *tokens);
int		ms_parser(t_tlist *tokens, t_node **thead, char **env);

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
void	ms_init_shell(t_ms *data);
void	ms_clean(t_ms *data);
char	*ms_join_argv(char **argv, int argc);
void	ms_clean_cmd(t_node *head);
void	ms_clean_tlist(t_tlist **list);

/*
** SIGNAL HANDLERS
*/

void	ms_exit(int sig);
void	ms_newline(int sig);
/*
** EXPANSER
*/

int		ms_isparen(char c);
int		ms_isvariable(char *str);
char	*ms_concat(t_word *wlist);
void	ms_clean_wlist(t_word *list);
void	ms_var_tokens(char *var, t_tlist **tokens);
t_word	*ms_create_part(t_word **wlist);

/*
** PARSER
*/
t_node  *ms_create_cmd(t_tlist *tlist, char **env);
char	**ms_clean_tab_path_b(char ***tab_path, char **ret);
char	*ms_clean_tab_path(char ***tab_path, char *ret);
char	**ms_ext_path();
char	*ms_format_file(char *file_name);
char	*ms_format_cmd(char *file_name);
char	*ms_format_tile(char *file_name);
char	*ms_format_ds(char *file_name);
char	*ms_format_dd(char *file_name);
char	*ms_format_sl(char *file_name);
char	*ms_find_path(char *file_name);
char	*ms_find_cmd_path(char	*cmd_name, char ***t_path, int size_n);
int		ms_name_sizer(char	*cmd_name);
int		ms_check_buildin(char *cmd);
int		ms_count_args(t_tlist *tlist);
int		ms_init_parser(t_node **node, t_command **command, char **env);
int		ms_redir_ina(t_tlist **token, t_command *command);	

/*
** EXEC
*/

int	child(t_command *cmd, int pipIN, int pipOUT);
int	ms_exec(t_node *head, int pipIN);

/*
** DEBUG -- TEST                                                |~
*/

void	print_token(t_tlist *tokens);
void	ms_leak(int sig, siginfo_t *var, void *param);
void	print_tree(t_node *thead);

#endif

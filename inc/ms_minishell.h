/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:07:10 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/31 20:30:25 by sshakya          ###   ########.fr       */
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
** EXTERNAL VARIABLE
*/

extern char **environ;

/*
** MAIN FUNCTIONS
*/

int		ms_lexer(char *line, t_tlist **tokens);
void	ms_expanser(t_tlist **tokens);
int		ms_parser(t_tlist *tokens, t_node **thead, char **env);
int		ms_exec(t_node *head, int pipIN);

/*
** LEXER UTILS
*/

int		ms_isop_or(char c, char b);
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
char	*ms_join_argv(char **argv, int argc);

/*
** INIT
*/

void	ms_init(t_ms *data);
void	ms_init_shell_io(t_ms *data);
void	ms_shell_input_io(t_ms *data);
void	ms_init_env(void);

/*
** CLEAN
*/
void	ms_clean(t_ms *data);
void	ms_clean_cmd(t_node **head);
void	ms_clean_tlist_cmd(t_tlist **list);
void	ms_clean_tlist_or(t_tlist **list);
void	ms_clean_tlist_all(t_tlist **list);
void	ms_clean_tk_or(t_tlist **list);
void	ms_clean_environ(void);

/*
** SIGNAL HANDLERS
*/

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

/*
** BUILDINS
*/

int		ms_echo(char **args);
int		ms_export(char	**args);
int		ms_unset(char	**args);
int		ms_pwd(void);
int		ms_exp_check(char	*str);
int		ms_unset_check(char	*str);
char	*ms_exp_extr_var(char	*str);
int		ms_copy_env(void);

/*
** BUILDIN -- CD
*/

int		ms_cd(char **args);
int		ms_change_path(char *path);
int		ms_relative_path(char *path);
char	*ms_add_target_dir(char *dir, char *path);
char	*ms_get_directory(char *path, int relative);
int		ms_export_env(char *path, char *old_path);
int		ms_isrelative(char *arg);
void	ms_slash_join(char *path, char *target, char *str);
int		ms_error_nav(char *path1, char *path2, int error);
void	ms_exit(int sig);

/*
** DEBUG -- TEST                                                |~
*/

void	print_token(t_tlist *tokens);
void	print_tree(t_node *thead);
void	print_environ();

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:07:10 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/07 20:47:42 by sshakya          ###   ########.fr       */
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
/*
** MINISHELL HEADERS
*/

# include "ms_structs.h"
# include "ms_define.h"
# include "libft/inc/libft.h"

/*
** LEXER FUNCTIONS
*/

int		ms_lexer(char *line, t_tlist **tlist);
int		ms_isop_pipe(char c);
int		ms_isop_and(char c, char b);
int		ms_isquote(char c);
int		ms_isredirection(char c);
int		ms_isparen(char c);
int		ms_isvariable(char *str);
t_tlist	*ms_create_token(t_tlist **tlist);

/*
** MAIN FUNCTIONS
*/

int		is_interactive(void);
void	ms_init(t_ms *data);
void	ms_clean(t_ms *data);

/*
** DEBUG -- TEST                                                |~
*/

void	print_token(t_ms *data);

#endif

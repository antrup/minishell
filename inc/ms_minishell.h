/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:07:10 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/07 18:43:32 by atruphem         ###   ########.fr       */
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
int		is_interactive(void);

int		ms_lexer(char *line, t_tlist **tlist);
int		ms_isop_pipe(char c);
int		ms_isop_and(char c, char b);
int		ms_isquote(char c);
int		ms_isredirection(char c);
t_tlist	*ms_create_token(t_tlist **tlist);
void	ms_init(t_ms *data);
void	ms_clean(t_ms *data);

/*
** DEBUG -- TEST                                                |~
~                              | 45 ** DEBUG -- TESTINGING
*/

void	print_token(t_ms *data);

#endif

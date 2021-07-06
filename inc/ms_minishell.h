/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:07:10 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/06 20:02:15 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_MINISHELL_H
# define MS_MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/inc/libft.h"

enum token_type
{
	STRING = 0,
	OPERATOR = 1,
	STRING_DQ = 2,
	STRING_SQ = 3,
};

typedef struct s_token
{
	enum token_type		type;
	int					op;
	char				*value;

}	t_token;

typedef struct s_tlist
{	
	t_token				tk;
	struct s_tlist		*next;
}	t_tlist;

typedef struct s_ms
{
	t_tlist		*tlist;
}	t_ms;

int		is_interactive(void);

int		ms_lexer(char *line, t_tlist **tlist);
void	ms_init(t_ms *data);
void	ms_clean(t_ms *data);

#endif

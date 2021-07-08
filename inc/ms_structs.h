/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:03:04 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/08 14:44:57 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H

enum e_node_type
{
	NO_CMD = 0,
	NO_PIPE = 1,
	NO_AND = 2,
	NO_OR = 3
};

typedef	struct	s_command
{
	char	*cmd;
	int		buidin;
	char	**args;
	int		redirIN;
	int		redirOUT;
	int		INfd;
	int		OUTfd;
	
}	t_command;

typedef	struct	s_node
{
	enum e_node_type	type;
	t_command			*data;
	void				*left;
	void				*right;
}	t_node;

enum e_token_type
{
	ERROR = -1,
	WORD = 0,
	OP_PIPE = 1,
	OP_AND = 2,
	OP_OR = 3,
	REDIR_IN = 4,
	REDIR_OUT = 5,
	REDIR_IN_A = 6,
	REDIR_OUT_A = 7
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;

}	t_token;

typedef struct s_tlist
{	
	t_token				tk;
	struct s_tlist		*next;
	struct s_tlist		*previous;
}	t_tlist;

typedef struct s_ms
{
	t_tlist		*tlist;
}	t_ms;

#endif

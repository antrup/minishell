/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:03:04 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/05 03:36:54 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H
/*
** TOKENS
*/
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
	REDIR_OUT_A = 7,
	OP_PAREN = 8,
	OP_VAR = 9
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

/*
** UTILS
*/

typedef struct s_word
{
	char			*part;
	struct s_word	*next;
}	t_word;

typedef struct s_markers
{
	int	_and;
	int	_or;
	int	ret;
}	t_markers;


typedef struct s_wcard
{
	char			type;
	char			*str;
	struct s_wcard	*next;
}	t_wcard;

/*
** NODES
*/

enum e_node_type
{
	NO_CMD = 0,
	NO_PIPE = 1,
};

typedef struct s_node
{
	enum e_node_type	type;
	struct s_command	*data;
	struct s_node		*left;
	struct s_node		*right;
	pid_t				pid;
}	t_node;

/*
** COMMANDS
*/

typedef struct s_command
{
	char	*cmd;
	char	*errname;
	char	**args;
	char	**argve;
	int		buildin;
	int		redirIN;
	int		redirOUT;
	int		INfd;
	int		OUTfd;
	int		OUTerror;
	int		error;
	char	*error_file_name;
}	t_command;

/*
** TERMIOS
*/

typedef struct s_info
{
	struct termios		term_ios;
	struct termios		ms_input;
	struct termios		ms_ios;
}	t_info;

/*
** GLOBAL VARIABLE
*/

typedef struct s_shell
{
	int			rvar;
	int			rda;
	int			rda_fd[2];
	pid_t		r_pid;
	struct s_ms	*data;
	char		**env_pt;
	char		*mypath;
	char		**env;
}	t_shell;

/*
** GLOBAL STRUCTURE
*/

typedef struct s_ms
{
	t_info				info;
	t_tlist				*tokens;
	t_node				*thead;
	char				*line;
}	t_ms;

#endif

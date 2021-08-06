/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:06:59 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/06 19:32:07 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

/*
** INIT GLOBAL VARIABLE
*/
t_shell	g_shell = {0, 0, {0, 0}, 0, NULL, NULL, NULL, NULL};

#if !TEST
static void	ms_markers(t_tlist *tokens, t_markers *op)
{
	while (tokens)
	{
		if (tokens->tk.type == OP_OR)
			op->_or += 1;
		if (tokens->tk.type == OP_AND)
			op->_and += 1;
		tokens = tokens->next;
	}
}
/*
** MAIN FUNCTION THAT CREATES COMMANDS AND EXECUTES
*/

int	ms_minishell(t_ms *data, char **env)
{
	t_markers	op;
	int			err;

	err = 0;
	ft_memset(&op, 0, sizeof(op));
	if (ms_check_syntax(data->tokens))
		return (ms_clean_tlist_all(&data->tokens, ERR_SYN));
	if (ms_expanser(&data->tokens))
		return (ms_clean_tlist_all(&data->tokens, ERR_SYN));
	ms_markers(data->tokens, &op);
	ms_shell_input_io(data);
	ms_parser(data->tokens, &data->thead, env);
	tcsetattr(0, TCSANOW, &data->info.term_ios);
	op.ret = ms_exec(data->thead, STDIN);
	g_shell.rvar = op.ret;
	ms_clean_cmd(&data->thead);
	ms_clean_tokens(&data->tokens, op);
	if (data->tokens != NULL)
		ms_minishell(data, env);
	return (0);
}
#endif
/*
** LAUNCH IN INTERACTIVE MODE
*/

static int	ms_interactive(t_ms *data, char **env)
{
	int err;

	err = 0;
	while (1)
	{
		data->thead = NULL;
		ms_init_shell_io(data);
		data->line = readline("Myshell: ");
		if (!data->line)
			return (1);
		err = ms_lexer(data->line, &data->tokens);
		if (err == ERR_SYN)
			ms_clean_tlist_all(&data->tokens, ERR_SYN);
		else if (err)
			return (ms_clean_tlist_all(&data->tokens, err));
		else
			ms_minishell(data, env);
		add_history(data->line);
	}
	return (0);
}

/*
** LAUNCHES MINISHELL WITH ARGS
*/

static int	ms_arg_shell(t_ms *data, char **argv, char **env, int argc)
{
	(void)env;
	data->line = ms_join_argv(argv, argc);
	ms_lexer(data->line, &data->tokens);
	ms_minishell(data, env);
	free(data->line);
	return (0);
}

/*
** MAIN
*/

int	main(int argc, char **argv, char **env)
{
	t_ms	data;

	if (ms_init(&data, argv, env))
		return (1);
	if (argc > 1)
		ms_arg_shell(&data, argv, env, argc);
	else
		if (ms_interactive(&data, env))
			return (1);
	return (g_shell.rvar);
}

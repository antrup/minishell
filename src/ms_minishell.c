/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:06:59 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/03 12:56:04 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

/*
** INIT GLOBAL VARIABLE
*/
t_shell	g_shell = {0, 0, 0, {0, 0}, 0, NULL, NULL};

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

static int	ms_minishell(t_ms *data, char **env)
{
	t_markers	op;
	int			err;
	
	err = 0;
	ft_memset(&op, 0, sizeof(op));
	if (ms_check_syntax(data->tokens))
		return (ms_clean_tlist_all(&data->tokens));
#if TEST		
	print_token(data->tokens);
#endif
	if (ms_expanser(&data->tokens))
		return (ms_clean_tlist_all(&data->tokens));
	ms_markers(data->tokens, &op);
#if TEST		
	print_token(data->tokens);
#endif
	ms_shell_input_io(data);
	ms_parser(data->tokens, &data->thead, env);
#if TEST		
	print_tree(data->thead);
#endif
	tcsetattr(0, TCSANOW, &data->info.term_ios);
	op.ret = ms_exec(data->thead, 0);
	g_shell.rvar = op.ret;
	ms_clean_cmd(&data->thead);
	if (op._or > 0 && op.ret == 0)
		ms_clean_tlist_or(&data->tokens);
	else if (op._or == 0 && op._and > 0 && op.ret != 0)
		ms_clean_tlist_all(&data->tokens);
	else
		ms_clean_tlist_cmd(&data->tokens);
	if (data->tokens != NULL)
		ms_minishell(data, env);
	return (0);
}

/*
** LAUNCH IN INTERACTIVE MODE
*/

static int	ms_interactive(t_ms *data, char **env)
{
	(void)env;
	while (g_shell.on == 1)
	{
		data->thead = NULL;
		ms_init_shell_io(data);
		data->line = readline("Myshell: ");
		if (ms_lexer(data->line, &data->tokens))
			return (ms_clean_tlist_all(&data->tokens));
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
	if (data->info.inte == 0)
		data->line = ms_join_argv(argv, argc);
	ms_lexer(data->line, &data->tokens);
	ms_minishell(data, env);
	return (0);
}

/*
** MAIN
*/

int	main(int argc, char **argv, char **env)
{
	t_ms	data;

	(void)argv;
	(void)argc;
	ms_init_env();
	ms_init(&data);
	if (argc > 1)
		ms_arg_shell(&data, argv, env, argc);
	else
		ms_interactive(&data, env);
	//ms_clean_environ();
	return (0);
}

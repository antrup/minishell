/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:06:59 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/26 16:25:42 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

/*
** INIT GLOBAL VARIABLE
*/
t_shell	g_shell = {0, NULL};

/*
** MAIN FUNCTION THAT CREATES COMMANDS AND EXECUTES
*/
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

static int	ms_minishell(t_tlist **tokens)
{
	t_node		*thead;
	t_markers	op;

	thead = NULL;
	ft_memset(&op, 0, sizeof(op));
	ms_expanser(*tokens);
	ms_markers(*tokens, &op);
#if TEST		
	print_token(*tokens);
#endif
	ms_parser(*tokens, &thead, &op);
#if TEST		
	print_tree(thead);
#endif
	//EXECUTION
	// cool code here
	// op.ret = ms_execute();
	//CLEAN UP
	ms_clean_cmd(thead);
	if (op._or > 0 && op.ret == SUCCESS);
	// clean all OR tokens
	else if (op._or > 0 && op.ret == FAIL);
	//clean to next OR
	else
	// clean all tokens
	ms_clean_tlist(tokens);
	if (*tokens != NULL)
		ms_minishell(tokens);
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
		ms_init_shell(data);
		data->line = readline("Myshell: ");
		tcsetattr(0, TCSANOW, &data->info.term_ios);
		ms_lexer(data->line, &data->tokens);
		ms_minishell(&data->tokens);
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
	ms_minishell(&data->tokens);
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
	ms_init(&data);
	if (argc > 1)
		ms_arg_shell(&data, argv, env, argc);
	else
		ms_interactive(&data, env);
	return(0);
}

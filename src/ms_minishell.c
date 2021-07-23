/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:06:59 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/23 18:43:06 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

/*
** MAIN FUNCTION THAT CREATES COMMANDS AND EXECUTES
*/

static int	ms_minishell(t_tlist *tokens, t_node **thead)
{
	ms_expanser(tokens);
#if TEST		
	print_token(tokens);
#endif
	ms_parser(tokens, thead);
#if TEST		
	print_tree(*thead);
#endif
	return (0);
}

/*
** LAUNCH IN INTERACTIVE MODE
*/

static int	ms_myshell(t_ms *data, char **env)
{
	(void)env;
	while (1)
	{
		ms_init_shell(data);
		data->line = readline("Myshell: ");
		ms_lexer(data->line, &data->tokens);
		ms_minishell(data->tokens, &data->thead);
	}
	return (0);
}

/*
** LAUNCHES A SINGLE INSTANCE OF MINISHELL
*/

static int	ms_oneshell(t_ms *data, char **argv, char **env, int argc)
{
	(void)env;
	if (data->info.inte == 0)
		data->line = ms_join_argv(argv, argc);
	ms_lexer(data->line, &data->tokens);
	ms_expanser(data->tokens);
	ms_parser(data->tokens, &data->thead);
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
	signal(SIGINT, &ms_exit);
#if OSX
	sigaction(SIGINT, &data.info.sig, 0);
#endif
	if (argc > 1)
		ms_oneshell(&data, argv, env, argc);
	else
		ms_myshell(&data, env);
	ms_clean(&data);
	return(0);
}

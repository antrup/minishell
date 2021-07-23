/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:06:59 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/23 16:37:50 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_exit(int sig)
{
	if (sig == SIGINT)
		write(1, "exit\n", 7);
	if (sig == SIGQUIT)
		write(1, "exit\n", 5);
	if (sig == SIGTERM)
		printf("test\n");
	exit(0);
}

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
static int	ms_oneshell(t_ms *data, char **argv, char **env)
{
	if (data->info.inte == 0)
		data.line = ms_join_argv(argv);
	ms_lexer(data.line, &data->tokens);
	ms_expanser(data->tokens);
	ms_parser(data->tlist, data->thead);
}
*/
int	main(int argc, char **argv, char **env)
{
	t_ms	data;

	(void)argv;
	(void)argc;
	ms_init(&data);
	signal(SIGINT, &ms_exit);
//	if (argc == 1)
//		ms_oneshell(&data, argv, env);
//	else
		ms_myshell(&data, env);
	ms_clean(&data);
	return(0);
}

/*
int	main(int argc, char **argv, char **env)
{
	t_ms	data;

	(void)argc;
	(void)argv;
	(void)env;
	signal(SIGINT, &ms_exit);
	while (1)
	{
		ms_init(&data);
		data.line = readline("Myshell: ");
		ms_lexer(&data);
		ms_expanser(&data);
#if TEST		
		print_token(&data);
#endif
		ms_parser(&data);
#if TEST		
		print_tree(&data);
#endif
		add_history(data.line);
		if (data.info.inte == 0)
			return (0);
		ms_clean(&data);
#if OSX
		sigaction(SIGINT, &data.info.sig, 0);
#endif
	}
	return (0);
}
*/

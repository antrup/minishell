#include "ms_minishell.h"

#if TEST

void	print_environ()
{
	int		i;

	i = 0;
	while (environ[i])
	{
		printf("index : %d - %s \n", i, environ[i]);
		i++;
	}
}

int print_wildcard_test(t_wcard *wcard, t_wcard *files)
{
	t_wcard *temp;
	t_wcard *temp1;

	printf("WILDCARDS\n");
	while (wcard)
	{
		temp = wcard->next;
		if (wcard->type == OP_WCARD)
			printf("*\n");
		else
			printf("%s\n", wcard->str);
		wcard = temp;
	}
	printf("\n");
	printf("FILES\n");
	while (files)
	{
		temp1 = files->next;
		printf("%s\t", files->str);
		if (files->ismatch == 1)
			printf("ismatch\n");
		else
			printf("nomatch\n");
		files = temp1;
	}
	printf("\n");
	return (0);
}
void	print_tree(t_node *thead)
{
	t_node		*current;
	t_node		*temp;
	int			i;

	current = thead;
	if (!current)
		return ;
	if (current->type == NO_CMD)
	{
		if (current->data)
		{
			printf("Type : COMMAND \n");
			printf("CMD : %s \n", current->data->cmd);
			i = 0;
			if (current->data->args)
			{
				while (current->data->args[i])
				{
					printf("ARG %d : %s \n", i, current->data->args[i]);
					i++;
				}
			}
			if (current->data->redir_in)
				printf("RedirIN fd = %d \n", current->data->in_fd);
			if (current->data->redir_out)
				printf("RedirOUT fd = %d \n", current->data->out_fd);
		}
		current = NULL;
	}
	else
	{	
		printf("Type : PIPE \n");
		temp = current;
		current = current->left;
		if (current)
		{	
			printf("LEFT \n");
			print_tree(current);
		}
		current = temp->right;
		if (current)
		{	
			printf("RIGHT \n");
			print_tree(current);
		}
	}	
}

void	print_token(t_tlist *tokens)
{
	t_tlist		*current;
	int			i;

	i = 1;
	current = tokens;
	if (current != NULL)
		printf("token | OP | string\n");
	while (current)
	{
		printf("%2d\t", i);
		if (current->tk.type == 0)
		{
			printf(" W");
			//printf("%p\t%p\t%p", current, current->previous, current->next);
		}
		if (current->tk.type == 1)
			printf(" |");
		if (current->tk.type == 2)
			printf("&&");
		if (current->tk.type == 3)
			printf("||");
		if (current->tk.type == 4)
			printf(" <");
		if (current->tk.type == 5)
			printf(" >");
		if (current->tk.type == 6)
			printf("<<");
		if (current->tk.type == 7)
			printf(">>");
		if (current->tk.type == 8)
		{
			printf("VR");
			//printf("C=%p\tP=%p\tN=%p", current, current->previous, current->next);
		}
		if (current->tk.type == 9)
			printf("(");
		if (current->tk.type == 10)
			printf(")");
		if (current->tk.type == 11)
			printf("*");
		printf("     %s\n", current->tk.value);
		i++;
		current = current->next;
	}
	return ;
}
/*
** TEST VERSION TO PRINT TOKENS & COMANDS
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

int	ms_minishell(t_ms *data, char **env)
{
	t_markers	op;
	int			err;

	err = 0;
	ft_memset(&op, 0, sizeof(op));
	if (ms_check_syntax(data->tokens))
		return (ms_clean_tlist_all(&data->tokens, ERR_SYN));
	//PRINT TOKENS BEFORE EXPANSER
	//print_token(data->tokens);
	if (ms_expanser(&data->tokens))
		return (ms_clean_tlist_all(&data->tokens, ERR_SYN));
	ms_markers(data->tokens, &op);
	//PRINTF TOKENS AFTER EXPANSER
	print_token(data->tokens);
	ms_shell_input_io(data);
	ms_parser(data->tokens, &data->thead, env);
	//PRINT COMMANDS
	print_tree(data->thead);
	tcsetattr(0, TCSANOW, &data->info.term_ios);
	op.ret = ms_exec(data->thead, 0);
	g_shell.rvar = op.ret;
	ms_clean_tokens(&data->tokens, op);
	ms_clean_cmd(&data->thead);
	if (data->tokens != NULL)
		ms_minishell(data, env);
	return (0);
}

#endif

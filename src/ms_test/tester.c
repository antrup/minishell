#include "ms_minishell.h"

#if TEST

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
			if (current->data->redirIN)
				printf("RedirIN fd = %d \n", current->data->INfd);
			if (current->data->redirOUT)
				printf("RedirOUT fd = %d \n", current->data->OUTfd);
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
			printf(" W");
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
			printf("VR");
		if (current->tk.type == 9)
			printf("(");
		if (current->tk.type == 10)
			printf(")");
		printf("     %s\n", current->tk.value);
		i++;
		current = current->next;
	}
	return ;
}

#if OSX

void	ms_leak(int sig, siginfo_t *var, void *param)
{
	(void)sig;
	(void)var;
	(void)param;
	system("leaks minishell");
	//system("leaks test-exp");
	exit (0);
}
#endif

#endif

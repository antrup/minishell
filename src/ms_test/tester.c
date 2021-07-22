#include "ms_minishell.h"

#if TEST

void	print_tree(t_ms *data)
{
	t_node		*current;
	int			i;

	current = data->thead;
	while (current)
	{
		if (current->type == NO_CMD)
		{
			printf("Type : COMMAND \n");
			printf("CMD : %s \n", current->data->cmd);
			i = 0;
			while (current->data->args && current->data->args[i])
			{
				printf("ARG %d : %s \n", i, current->data->args[i]);
				i++;
			}
			if (current->data->redirIN)
				printf("RedirIN fd = %d \n", current->data->INfd);
			if (current->data->redirOUT)
				printf("RedirOUT fd = %d \n", current->data->OUTfd);
		}
		else
			printf("Type : OP \n");
		current = NULL;
	}
}

void	print_token(t_ms *data)
{
	t_tlist		*current;
	int			i;

	i = 1;
	current = data->tokens;
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
		printf("     %s\n", current->tk.value);
		i++;
		current = current->next;
	}
	return ;
}

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

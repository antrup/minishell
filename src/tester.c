#include "ms_minishell.h"

#if TEST
void	print_token(t_ms *data)
{
	t_tlist		*current;
	int			i;

	i = 1;
	current = data->tlist;
	printf("token | OP | string\n");
	while (current)
	{
		printf("%2d\t", i);
		if (current->tk.type == 0)
			printf("W");
		if (current->tk.type == 1)
			printf("|");
		if (current->tk.type == 2)
			printf("&&");
		if (current->tk.type == 3)
			printf("||");
		if (current->tk.type == 4)
			printf("<");
		if (current->tk.type == 5)
			printf(">");
		if (current->tk.type == 6)
			printf("<<");
		if (current->tk.type == 7)
			printf(">>");
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
	exit (0);
}
#endif


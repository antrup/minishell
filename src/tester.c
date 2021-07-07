#include "ms_minishell.h"

void	print_token(t_ms *data)
{
	t_tlist		*current;
	int			i;

	i = 1;
	current = data->tlist;
	while (current)
	{
		printf("// Token %d //\n", i);
		printf("Type :   %d\n", current->tk.type);
		if (current->tk.type == 1)
			printf("Op :     %d\n", current->tk.op);
		else
			printf("String :   %s\n", current->tk.value);
		printf("#####################################\n");
		i++;
		current = current->next;
	}
	return ;
}

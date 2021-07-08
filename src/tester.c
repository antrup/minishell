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
			printf("String :   %s\n", current->tk.value);
		printf("#####################################\n");
		i++;
		current = current->next;
	}
	return ;
}

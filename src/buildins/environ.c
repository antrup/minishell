#include "ms_minishell.h"

int main()
{
	int		i;
	
	i = 0;
	while (environ[i])
	{	
		printf("index : %d - %s \n", i, environ[i]);
		i++;
	}
	return (0);
}

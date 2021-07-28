/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:55:30 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/28 17:12:27 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int		ms_copy_env(void)
{
	int		i;
	char	**new_env;
	int		j;

	i = 0;
	while (environ[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (i - 1);
	j = 0;
	while (j < i)
	{
		new_env[j] = environ[j];
		j++;
	}
	new_env[i + 1] = NULL;
	free(environ);
	environ = new_env;
	return (i);
}

void	ms_create_env_var(char	*arg)
{
	int		index;

	index = ms_copy_env();
	environ[index] = ft_strdup(arg);
}

void	ms_replace_env_var(char *var, char *arg)
{
	int		i;
	
	i = 0;
	while (ft_strncmp(environ[i], var, ft_strlen(var)))
		i++;
	free(environ[i]);
	environ[i] = ft_strdup(arg);
}

int	ms_export(char	**args)
{
	int		i;
	int		ret;
	int		test;
	char	*var;

	ret = 0;
	i = 0;
	while (args[i] != NULL)
	{
		test = ms_exp_check(args[i]);
		if (test == 1)
			ret = 1;
		else 
		{
			var = ms_exp_extr_var(args[i]);
			if (!getenv(var))
				ms_create_env_var(args[i]);
			else
				ms_replace_env_var(var, args[i]);
		}
		i++;
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 16:23:58 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/29 20:16:15 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_remove_env_var(char *var)
{
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while (ft_strncmp(environ[i], var, ft_strlen(var)))
		i++;
	while (environ[j])
		j++;
	free(environ[i]);
	environ[i] = environ[j - 1];
	environ[j - 1] = NULL;
}

int	ms_unset(char	**args)
{
	int		i;
	int		ret;
	int		test;
	char	*var;

	ret = 0;
	i = 0;
	while (args[i] != NULL)
	{
		test = ms_unset_check(args[i]);
		if (test == 1)
			ret = 1;
		else 
		{
			var = ms_exp_extr_var(args[i]);
			if (getenv(var))
				ms_remove_env_var(var);
			free(var);
		}
		i++;
	}
	return (ret);
}

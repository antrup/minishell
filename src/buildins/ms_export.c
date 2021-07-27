/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:55:30 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/27 19:30:12 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int ms_exp_error(char *str)
{
	write(2, "minishell: export: `", 20);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier", 25);
	return (1);
}
		
int	ms_exp_check(char	*str)
{
	int		i;

	i = 1;
	if ((str[0] < 'a' || str[0] > 'z') && (str[0] < 'A' || str[0] > 'Z') 
			&& str[0] != '_')
		return (ms_exp_error(str));
	while (str[i] != '=')
	{	
		if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z') 
		&& (str[i] < '0' || str[i] > '9') && str[i] != '_' && str[i] != '+')
			return (ms_exp_error(str));
		if (str[i] == '+' && str[i] != '=')
			return (ms_exp_error(str));
		i++;
	}
	return (0);
}

char	*ms_exp_extr_var(char	*str)
{
	int		i;
	char	*ret;
	
	i = 0;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, i + 1);
	return (ret);
}

int		ms_copy_env()
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
	//free(environ);
	printf("%p \n", environ);
	environ = new_env;
	printf("%p \n", environ);
	return (i);
}

void	ms_create_env_var(char	*arg)
{
	int		index;

	index = ms_copy_env();
	environ[index] = arg;
}

void	ms_replace_env_var(char *var, char *arg)
{
	int		i;
	
	i = 0;
	while (ft_strncmp(environ[i], var, ft_strlen(var)))
		i++;
	//free(environ[i]);
	environ[18] = ft_strdup(arg);
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

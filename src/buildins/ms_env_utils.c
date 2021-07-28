/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 16:59:54 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/28 17:21:39 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int ms_exp_error(char *str)
{
	write(2, "minishell: export: `", 20);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
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
		if (str[i] == '+'  && str[i + 1] != '=')
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:04:53 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/08 12:44:00 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_check_path(int *count, int *j, int i, char **argve)
{
	*count = 0;
	while (argve[i][*j] != ':' && argve[i][*j] != '\0')
	{	
		(*count)++;
		(*j)++;
	}
}

char	**ms_ext_path_loader(char **argve, char ***tab_path, int i)
{
	int	j;
	int	k;
	int	count;

	k = 0;
	j = 5;
	while (argve[i][j] != '\0')
	{
		check_path(&count, &j, i, argve);
		tab_path[0][k] = malloc(sizeof(char) * (count + 2));
		if (!tab_path[0][k])
			return (clean_tab_path_b(tab_path, NULL));
		ft_strlcpy(tab_path[0][k], &(argve[i][j - count]), count + 1);
		tab_path[0][k][count] = '/';
		tab_path[0][k][count + 1] = '\0';
		k++;
		if (argve[i][j] == '\0')
			break ;
		j++;
	}
	tab_path[0][k] = NULL;
	return (tab_path[0]);
}

char	**ms_ext_path(char **argve)
{
	int		i;
	int		j;
	int		count;
	char	**tab_path;

	i = 0;
	while (argve[i] && (argve[i][0] != 'P' || argve[i][1] != 'A'
		|| argve[i][2] != 'T' || argve[i][3] != 'H'
		|| argve[i][4] != '='))
		i++;
	if (!argve[i])
		return (NULL);
	j = 0;
	count = 1;
	while (argve[i][j] != '\0')
	{
		if (argve[i][j] == ':')
			count++;
		j++;
	}
	tab_path = malloc(sizeof(char *) * (count + 2));
	if (!tab_path)
		return (NULL);
	return (ms_ext_path_loader(argve, &tab_path, i));
}

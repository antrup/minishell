/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:04:53 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/01 12:01:39 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_check_path(int *count, int *j, char *path)
{
	*count = 0;
	while (path[*j] != ':' && path[*j] != '\0')
	{	
		(*count)++;
		(*j)++;
	}
}

char	**ms_ext_path_loader(char *path, char ***tab_path)
{
	int	j;
	int	k;
	int	count;

	k = 0;
	j = 0;
	while (path[j] != '\0')
	{
		ms_check_path(&count, &j, path);
		tab_path[0][k] = malloc(sizeof(char) * (count + 2));
		if (!tab_path[0][k])
			return (ms_clean_tab_path_b(tab_path, NULL));
		ft_strlcpy(tab_path[0][k], &(path[j - count]), count + 1);
		tab_path[0][k][count] = '/';
		tab_path[0][k][count + 1] = '\0';
		k++;
		if (path[j] == '\0')
			break ;
		j++;
	}
	tab_path[0][k] = NULL;
	return (tab_path[0]);
}

char	**ms_ext_path(void)
{
	int		i;
	int		count;
	char	*path;
	char	**tab_path;

	i = 0;
	count = 1;
	path = getenv("PATH");
	if (!path)
		return (NULL);
	while (path[i] != '\0')
	{
		if (path[i] == ':')
			count++;
		i++;
	}
	tab_path = malloc(sizeof(char *) * (count + 2));
	if (!tab_path)
		return (NULL);
	return (ms_ext_path_loader(path, &tab_path));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:38:14 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/08 17:39:07 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

char	*ms_clean_tab_path(char ***tab_path, char *ret)
{
	int	i;

	i = 0;
	while (tab_path[0][i])
	{
		free(tab_path[0][i]);
		i++;
	}
	free(tab_path[0]);
	return (ret);
}

char	**ms_clean_tab_path_b(char ***tab_path, char **ret)
{
	int	i;

	i = 0;
	while (tab_path[0][i])
	{
		free(tab_path[0][i]);
		i++;
	}
	free(tab_path[0]);
	return (ret);
}

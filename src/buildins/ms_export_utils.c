/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 12:55:58 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/08 12:56:02 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static void	ms_init_envp(char **ptr)
{
	g_shell.env_pt = malloc(sizeof(char*) * 2);
	if (!(g_shell.env_pt))
		return ;
	g_shell.env_pt[0] = *ptr;
	g_shell.env_pt[1] = NULL;
}

void	ms_add_to_envpt(char **ptr)
{
	int	i;
	int	j;
	char	**new;

	if (g_shell.env_pt == NULL)
		ms_init_envp(ptr);
	else
	{
		i = 0;
		while (g_shell.env_pt[i])
			i++;
		new = malloc(sizeof(char*) * (i + 2));
		if (!new)
			return;
		j = 0;
		while (j < i)
		{
			new[j] = g_shell.env_pt[j];
			j++;
		}
		free(g_shell.env_pt);
		new[i] = *ptr;
		new[i + 1] = NULL;
		g_shell.env_pt = new;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:02:43 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/21 10:00:05 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_name_sizer(char	*cmd_name)
{
	int	i;
	int	size_name;

	i = 0;
	size_name = 0;
	while (cmd_name[i] != ' ' && cmd_name[i] != '\0')
	{
		size_name++;
		i++;
	}
	return (size_name);
}

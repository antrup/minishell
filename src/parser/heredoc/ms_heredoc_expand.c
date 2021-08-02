/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 00:14:38 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/03 01:53:47 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_hasvar(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static int	ms_varlen(char *line, int start)
{
	int		i;
	int		len;
	int		flag;

	i = start;
	len = 0;
	flag = 1;
	while (line[i])
	{
		if (line[i] == '$' && flag == 1)
		{
			flag = 0;
			i++;
		}
		if ((ft_isspace(line[i]) || line[i] == '$') && !flag)
		{
			len = i;
			break ;
		}
		i++;
	}
	if (len > 0)
		return (len - start);
	return (i - start);
}

static char	*ms_var_expand(char *line)
{
	char *var;

	var = ft_strdup(getenv(line));
	free(line);
	return (var);
}

static char	*ms_expand_line(char *line, int start)
{
	char	*buff1;
	char	*buff2;
	char	*var;
	char	*ret;

	var = ft_substr(line, start + 1, ms_varlen(line, start));
	var = ms_var_expand(var);
	if (start == 0 && ms_varlen(line, start) == (int)ft_strlen(line))
	{
		free(line);
		return (var);
	}
	buff1 = ft_substr(line, 0, start);
	if (buff1)
		ret = ft_strjoin(buff1, var);
	buff2 = ft_substr(line, start + ms_varlen(line, start) + 1, ft_strlen(line));
	if (!buff2)
	{
		free(buff2);
		free(buff1);
		free(line);
		printf("%s\n", ret);
		return (ret);
	}
	free(buff1);
	buff1 = ft_strjoin(ret, buff2);
	free(line);
	free(var);
	free(ret);
	free(buff2);
	return (buff1);
}

char	*ms_heredoc_expand(char *line)
{
	int		i;

	i = 0;
	while (ms_hasvar(line))
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '$')
				line = ms_expand_line(line, i);
			i++;
		}
	}
	//printf("%s\n", line);
	return (line);
}

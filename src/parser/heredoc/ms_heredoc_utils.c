/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 09:43:51 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/09 09:43:54 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static size_t	ms_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static void	ms_join(char *buff, char *line, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buff && buff[i] != '\0')
	{
		str[i] = buff[i];
		i++;
	}
	str[i] = '\n';
	j = 0;
	i++;
	while (line[j] != '\0')
	{
		str[i] = line[j];
		i++;
		j++;
	}
	str[i] = '\0';
}

char	*ms_heredoc_join(char *buff, char *line, int *error)
{
	char	*str;
	size_t	len;

	if (!line)
		return (NULL);
	if (!buff)
	{	
		str = ft_strdup(line);
		free(line);
		return (str);
	}
	len = ms_strlen(buff) + ms_strlen(line);
	str = malloc(sizeof(char) * (len + 2));
	if (str == NULL)
	{
		*error = errno;
		return (NULL);
	}
	ms_join(buff, line, str);
	free(buff);
	free(line);
	return (str);
}

void	ms_heredoc_error(char *end)
{
	int	i;

	i = ms_strlen(end);
	write (0, "minishell: warning: found end-of-file (wanted `", 47);
	write (0, end, i);
	write (0, "')\n", 3);
}

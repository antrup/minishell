/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 18:15:58 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/23 18:29:07 by sshakya          ###   ########.fr       */
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
	str[i] = ' ';
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

static char	*ms_strjoin(char *buff, char *line)
{
	char	*str;
	size_t	len;

	len = ms_strlen(buff) + ms_strlen(line);
	str = malloc(sizeof(char) * (len + 2));
	if (str == NULL)
		return (NULL);
	ms_join(buff, line, str);
	free(buff);
	return (str);
}

char	*ms_join_argv(char **argv, int argc)
{
	int		i;
	int		n;
	int		flag;
	char	*buff;
	char	*ret;

	i = 1;
	flag = 0;
	n = argc - 1;
	buff = NULL;
	if (n > 1)
	{
		while (i < n)
		{
			if (flag == 0)
			{
				buff = ft_strjoin(argv[i], argv[i + 1]);
				i++;
				flag = 1;
			}
			ret = ms_strjoin(buff, argv[i + 1]);
			i++;
		}
	}
	else
		return (ft_strdup(argv[1]));
	return (ret);
}

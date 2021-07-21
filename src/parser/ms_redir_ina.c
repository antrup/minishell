/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_ina.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 00:14:38 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/22 00:31:28 by sshakya          ###   ########.fr       */
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
	free(line);
	return (str);
}

int	ms_redir_ina(t_tlist **token, t_command *command)
{
	int		fd[2];
	char	*end;
	char	*line;
	char	*buff;
	int		flag;

	if (!(*token)->next || (*token)->next->tk.type != WORD)
		return (ERR_SYN);
	*token = (*token)->next;
	end = (*token)->tk.value;
	pipe(fd);
	command->redirIN = 1;
	flag = 1;
	buff = NULL;
	while (flag)
	{
		line = readline("> ");
		if (ft_strcmp(line, end))
			flag = 0;
		buff = ms_strjoin(buff, line);
		if (buff == NULL)
			return (errno);
	}
	//printf("%s\n", buff);
	ft_putstr_fd(buff, fd[0]);
	free(buff);
	close(fd[0]);
	command->INfd = fd[1];
	*token = (*token)->next;
	//printf("token token address = address = %p\n", *token);
	return(0);
}

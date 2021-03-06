/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:28:35 by mmoreira          #+#    #+#             */
/*   Updated: 2021/03/20 14:33:35 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_line_break(char *buff, int len)
{
	int i;

	i = 0;
	if (!(buff))
		return (i);
	while (i++ < len)
		if (*(buff + i - 1) == '\n')
			return (1);
	return (0);
}

char	*make_line(char *linha, char **line, int bytes)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (*(linha + i) != '\n' && *(linha + i) != '\0')
		i++;
	*(linha + i) = '\0';
	if (!(*line = str_dup(linha)))
		return (NULL);
	if (bytes != 0)
		if (!(temp = str_dup(linha + i + 1)))
			return (NULL);
	free(linha);
	return (temp);
}

int		read_and_join(int fd, char **linha, char *buff, int *bytes)
{
	while (*bytes && !(check_line_break(*linha, str_len(*linha))))
	{
		*bytes = read(fd, buff, BUFFER_SIZE);
		if (*bytes < 0 || *bytes > BUFFER_SIZE)
		{
			free(buff);
			return (0);
		}
		*(buff + *bytes) = '\0';
		*linha = str_join(*linha, buff);
	}
	free(buff);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*linha;
	char		*buff;
	int			bytes;

	bytes = 1;
	if (fd < 0 || fd > RLIMIT_NOFILE || !(line) || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buff = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	if (!(read_and_join(fd, &linha, buff, &bytes)))
		return (-1);
	linha = make_line(linha, line, bytes);
	if (!(bytes))
		return (0);
	return (1);
}

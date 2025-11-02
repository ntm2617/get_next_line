/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:07:10 by marvin            #+#    #+#             */
/*   Updated: 2025/11/02 22:07:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_newline(char *buffer)
{
	int i;

	i = 0;
	if (buffer == NULL)
		return (0);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*copy_result(char *buffer)
{
	char	*result;
	int		i;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	result = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (result == NULL)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		result[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		result[i] = '\n';
	else
		result[i] = '\0';
	return (result);
}

char	*new_buffer(char *buffer)
{
	char	*newb;
	int		i;
	int		j;

	i = 0;
	newb = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (newb == NULL)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	else if (buffer[i] == '\0')
	{
		free(newb);
		free(buffer);
		return (NULL);
	}
	j = 0;
	while (buffer[i] != '\0')
		newb[j++] = buffer[i++];
	newb[j] = '\0';
	free(buffer);
	return (newb);
}

char	*check_read(int fd, char *buffer)
{
	char	*contain;
	int		i;
	int		n;

	i = 0;
	contain = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (contain == NULL)
		return (NULL);
	while (check_newline(buffer) == 0)
	{
		n = read(fd, contain, BUFFER_SIZE);
		if (n < 0)
		{
			free(buffer);
			free(contain);
			return (NULL);
		}
		if (n == 0)
			break;
		contain[n] = '\0';
		buffer = ft_strjoin(buffer, contain);
	}
	free(contain);
	return(buffer);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = check_read(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	result = copy_result(buffer);
	buffer = new_buffer(buffer);
	return(result);
}
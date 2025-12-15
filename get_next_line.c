/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarnpan <nkarnpan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:07:10 by marvin            #+#    #+#             */
/*   Updated: 2025/11/04 00:57:58 by nkarnpan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*copy_result(char *buffer)
{
	char	*result;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (buffer[j] == '\0')
		return (NULL);
	while (buffer[j] != '\0' && buffer[j] != '\n')
		j++;
	if (buffer[j] == '\n')
		j++;
	result = malloc(sizeof(char) * (j + 1));
	if (result == NULL)
		return (NULL);
	while (i < j)
	{
		result[i] = buffer[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*for_free(char *buffer)
{
	free(buffer);
	return (NULL);
}

char	*new_buffer(char *buffer)
{
	char	*newb;
	int		i;
	int		j;
	int		remain;

	remain = 0;
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (buffer[i] == '\0')
		return (for_free(buffer));
	while (buffer[i + remain] != '\0')
		remain++;
	newb = malloc(sizeof(char) * (remain + 1));
	if (newb == NULL)
		return (for_free(buffer));
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
	char	*temp;
	int		n;

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
			break ;
		contain[n] = '\0';
		temp = ft_strjoin(buffer, contain);
		free(buffer);
		buffer = temp;
	}
	free(contain);
	return (buffer);
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
	return (result);
}

// #include <fcntl.h>

// int	main()
// {
// 	int 	fd;
// 	char	*line;
// 	int		i;
// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	i = 0;
// 	while (line)
// 	{
// 		printf("[%d] : %s",i, line);
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// }
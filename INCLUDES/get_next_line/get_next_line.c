/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:43:12 by manon             #+#    #+#             */
/*   Updated: 2025/04/23 03:28:13 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strlcopy(char *dest, char *src, int l)
{
	int	i;

	i = 0;
	while (i + 1 < l && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (l)
		dest[i] = 0;
}

int	should_read(t_data *data)
{
	while (data->str_len && data->res_len < data->str_len)
	{
		if (data->buffer[data->res_len] == '\n')
			return (0);
		data->res_len++;
	}
	return (1);
}

int	ft_remp(t_data *data, int fd)
{
	char	*temp;
	int		read_output;

	read_output = BUFFER_SIZE;
	while (should_read(data) && read_output == BUFFER_SIZE)
	{
		if (data->str_len + BUFFER_SIZE >= data->buffer_len)
		{
			data->buffer_len *= 2;
			temp = malloc(data->buffer_len);
			if (!temp)
				return (0);
			ft_strlcopy(temp, data->buffer, data->str_len + 1);
			free(data->buffer);
			data->buffer = temp;
		}
		read_output = read(fd, data->buffer + data->res_len, BUFFER_SIZE);
		if (read_output == -1)
			return (0);
		data->str_len += read_output;
		data->buffer[data->str_len] = 0;
	}
	if (read_output == 0 && data->buffer[0] == 0)
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	t_data		data;
	static char	schar[1024][BUFFER_SIZE] = {0};
	char		*res;

	data.buffer = malloc(BUFFER_SIZE + 1);
	if (!data.buffer && (fd < 0 || fd > 1023))
		return (NULL);
	data.buffer_len = BUFFER_SIZE + 1;
	data.str_len = 0;
	while (schar[fd][data.str_len])
		data.str_len++;
	data.res_len = 0;
	ft_strlcopy(data.buffer, schar[fd], data.str_len + 1);
	if (!ft_remp(&data, fd))
	{
		schar[fd][0] = 0;
		return (free(data.buffer), NULL);
	}
	res = malloc(data.res_len + 2);
	if (!res)
		return (free(data.buffer), NULL);
	ft_strlcopy(res, data.buffer, data.res_len + 2);
	ft_strlcopy(schar[fd], data.buffer + data.res_len + 1, data.str_len
		- data.res_len + 1);
	return (free(data.buffer), res);
}

//int	main(void)
//{
//	char *line;
//	int fd;
//
//	fd = open("test", O_RDONLY);
//	line = get_next_line(fd);
//	while (line)
//	{
//		printf("%s", line);
//		free(line);
//		line = get_next_line(fd);
//	}
//	close(fd);
//	return (0);
//}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:59:16 by aneri-da          #+#    #+#             */
/*   Updated: 2024/10/24 11:18:58 by aneri-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*read_and_join(int fd, char **reminder, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(*reminder);
		*reminder = NULL;
		return (NULL);
	}
	if (bytes_read == 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	temp = *reminder;
	*reminder = ft_strjoin(*reminder, buffer);
	if (*reminder == NULL)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (*reminder);
}

char	*check_newline(char **reminder, char **line)
{
	char	*newline;
	char	*temp;
	char	*temp_line;

	newline = ft_strchr(*reminder, '\n');
	if (newline)
	{
		*newline = '\0';
		*line = ft_strjoin(*reminder, "");
		temp = *reminder;
		*reminder = ft_strjoin(newline + 1, "");
		free(temp);
		if (!*line || !*reminder)
			return (NULL);
		temp_line = *line;
		*line = ft_strjoin(temp_line, "\n");
		free(temp_line);
	}
	else if (*reminder && **reminder)
	{
		*line = ft_strjoin(*reminder, "");
		free(*reminder);
		*reminder = NULL;
	}
	return (*line);
}

char	*checking_malloc_read_fd(int fd)
{
	char	*checked_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	checked_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!checked_buffer)
		return (NULL);
	return (checked_buffer);
}

char	*get_next_line(int fd)
{
	static char	*reminder = NULL;
	char		*buffer;
	char		*line;
	char		*newline;

	line = NULL;
	buffer = checking_malloc_read_fd(fd);
	newline = ft_strchr(reminder, '\n');
	while (!newline)
	{
		if (!read_and_join(fd, &reminder, buffer))
		{
			if (!reminder || !*reminder)
			{
				free(buffer);
				free(reminder);
				return (NULL);
			}
			break ;
		}
		newline = ft_strchr(reminder, '\n');
	}
	free(buffer);
	return (check_newline(&reminder, &line));
}
/*int	main(void)
{
	int		fd;
	int		fd1;
	int		fd2;
	int		fd3;
	int		fd4;
	int		fd5;
	int		fd6;
	int		fd7;
	int		fd8;
	int		fd9;
	int		fd10;
	int		fd11;
	int		fd12;
	int		fd13;
	int		fd14;
	char		*line;
	int		i;

	i = 1;
	fd = open("nl", O_RDONLY);
	fd1 = open("41_no_nl", O_RDONLY);
	fd2 = open("41_with_nl", O_RDONLY);
	fd3 = open("42_no_nl", O_RDONLY);
	fd4 = open("42_with_nl", O_RDONLY);
	fd5 = open("43_no_nl", O_RDONLY);
	fd6 = open("alternate_line_nl_no_nl", O_RDONLY);
	fd7 = open("alternate_line_nl_with_line", O_RDONLY);
	fd8 = open("big_line_no_nl", O_RDONLY);
	fd9 = open("big_line_with_nl", O_RDONLY);
	fd10 = open("empty", O_RDONLY);
	fd11 = open("multiple_line_no_nl", O_RDONLY);
	fd12 = open("multiple_line_with_nl", O_RDONLY);
	fd13 = open("multiple_nlx5", O_RDONLY);
	fd14 = open("43_with_nl", O_RDONLY);
	//while ((line = get_next_line(fd)) != NULL)
	while (i < 15)
	{
		line = get_next_line(fd);
		printf("%d -> %s\n", i, line);
		free(line);

		line = get_next_line(fd1);
		printf("%d -> %s\n", i, line);
		free(line);

		line = get_next_line(fd2);
		printf("%d -> %s\n", i, line);
		free(line);

		line = get_next_line(fd3);
		printf("%d -> %s\n", i, line);
		free(line);

		line = get_next_line(fd4);
		printf("%d -> %s\n", i, line);
		free(line);

		line = get_next_line(fd5);
		printf("%d -> %s\n", i, line);
		free(line);

		line = get_next_line(fd6);
		printf("%d -> %s\n", i, line);
		free(line);

		line = get_next_line(fd7);
		printf("%d -> %s\n", i, line);
		free(line);

		line = get_next_line(fd8);
		printf("%d -> %s\n", i, line);
		free(line);

		line = get_next_line(fd9);
		printf("%d -> %s\n", i, line);
		free(line);

		line = get_next_line(fd10);
		printf("%d -> %s\n", i, line);
		free(line);

		line = get_next_line(fd11);
		printf("%d -> %s\n", i, line);
		free(line);

		line = get_next_line(fd12);
		printf("%d -> %s\n", i, line);
		free(line);

		line = get_next_line(fd13);
		printf("%d -> %s\n", i, line);
		free(line);

		line = get_next_line(fd14);
		printf("%d -> %s\n", i, line);
		free(line);
		i++;
	}
	close (fd);
	return (0);
}*/

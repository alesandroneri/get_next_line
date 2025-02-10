/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:31:54 by aneri-da          #+#    #+#             */
/*   Updated: 2024/10/22 14:34:46 by aneri-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*read_and_join(int fd, char **reminders, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(*reminders);
		*reminders = NULL;
		return (NULL);
	}
	if (bytes_read == 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	temp = *reminders;
	*reminders = ft_strjoin(*reminders, buffer);
	if (*reminders == NULL)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (*reminders);
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

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	checked_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!checked_buffer)
		return (NULL);
	return (checked_buffer);
}

char	*get_next_line(int fd)
{
	static char	*reminders[MAX_FD] = {NULL};
	char		*buffer;
	char		*line;
	char		*newline;

	line = NULL;
	buffer = checking_malloc_read_fd(fd);
	newline = ft_strchr(reminders[fd], '\n');
	while (!newline)
	{
		if (!read_and_join(fd, &reminders[fd], buffer))
		{
			if (!reminders[fd] || !*reminders[fd])
			{
				free(buffer);
				free(reminders[fd]);
				reminders[fd] = NULL;
				return (NULL);
			}
			break ;
		}
		newline = ft_strchr(reminders[fd], '\n');
	}
	free(buffer);
	return (check_newline(&reminders[fd], &line));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 19:09:13 by yoelhaim          #+#    #+#             */
/*   Updated: 2021/12/18 12:39:52 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42

#endif

char	*str_ret(char *stc_arr)
{
	int	i;

	i = 0;
	if (!stc_arr[i])
		return (NULL);
	i = 0;
	while (stc_arr[i] && stc_arr[i] != '\n')
		i++;
	return (ft_substr(stc_arr, 0, i + 1));
}

char	*str_remainder(char *stc_arr)
{
	char	*str;
	int		i;

	i = 0;
	if (!stc_arr)
		return (NULL);
	while (stc_arr[i])
	{
		if (stc_arr[i] == '\n')
		{
			str = ft_substr(stc_arr, i + 1, ft_strlen(stc_arr));
			free(stc_arr);
			return (str);
		}
		i++;
	}
	free (stc_arr);
	return (NULL);
}

int	find_nl(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stc_arr;
	char		*buffer;
	char		*line;
	int			i;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	i = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	while (!(find_nl(stc_arr)) && (i))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		stc_arr = ft_strjoin(stc_arr, buffer);
	}
	free(buffer);
	line = str_ret(stc_arr);
	stc_arr = str_remainder(stc_arr);
	return (line);
}

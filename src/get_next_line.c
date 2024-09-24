/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:36:46 by ltomasze          #+#    #+#             */
/*   Updated: 2024/04/11 14:29:36 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*temp;
	static char		buffer[BUFFER_SIZE + 1];
	int				read_b;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (temp = NULL, NULL);
	if (find_n(temp))
		return (put_line(&temp));
	read_b = 1;
	while (read_b > 0)
	{
		read_b = read(fd, buffer, BUFFER_SIZE);
		if (read_b == -1)
			return (NULL);
		buffer[read_b] = '\0';
		temp = ft_strjoin(temp, buffer);
		if (find_n(temp))
			break ;
	}
	return (put_line(&temp));
}
/*
int main(void)
{
    int     fd;
    char    *str;
    char    *path;
    int     i;

    path = "test.txt";
    fd = open(path, O_RDONLY);
    i = 0;
    while(i < 5)
    {
        str = get_next_line(fd);
        printf("i: %i\n", i);
        printf("fd: %i, %s\n", fd, str);
        i++;
    }
	free(str);
    return (0);
}
*/
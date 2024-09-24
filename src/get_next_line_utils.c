/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:37:01 by ltomasze          #+#    #+#             */
/*   Updated: 2024/04/11 13:39:11 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s, int len)
{
	char	*s1;
	int		i;

	if (s == NULL || len == 0)
		return (NULL);
	i = -1;
	s1 = (char *)malloc((len + 1) * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	while (++i < len)
		s1[i] = s[i];
	s1[i] = '\0';
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	int		len;
	char	*s3;

	i = 0;
	len = ft_strlen(s2);
	if (s1 == NULL)
		return (ft_strdup(s2, len));
	len = ft_strlen(s2) + ft_strlen(s1);
	s3 = (char *)malloc(sizeof(char) * (len + 1));
	if (s3 == NULL)
		return (NULL);
	len = 0;
	while (s1[i])
		s3[len++] = s1[i++];
	i = 0;
	while (s2[i])
		s3[len++] = s2[i++];
	s3[len] = '\0';
	free(s1);
	return (s3);
}

int	find_n(char	*temp)
{
	int		i;

	if (temp == NULL)
		return (0);
	i = -1;
	while (temp[++i])
		if (temp[i] == '\n')
			return (1);
	return (0);
}

char	*put_line(char **temp)
{
	int		i_n;
	char	*line;
	char	*s;

	if (*temp == NULL)
		return (NULL);
	s = *temp;
	i_n = 0;
	while (s[i_n] != '\0' && s[i_n] != '\n')
		i_n++;
	if (s[i_n] == '\n')
		i_n++;
	line = ft_strdup(s, i_n);
	*temp = ft_strdup(s + i_n, ft_strlen(s + i_n));
	if (s)
		free(s);
	if (*temp)
		free(*temp);
	s = NULL;
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:29:37 by secros            #+#    #+#             */
/*   Updated: 2026/03/01 17:50:47 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "utils.h"

void	buff_cleaner(char *buff, size_t i)
{
	size_t	size;

	size = ft_strlen(&buff[i]);
	ft_fmemcpy(buff, &buff[i], size);
	buff[size] = '\0';
}

int	is_new_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strfreejoin(const char *s1, const char *s2)
{
	char	*fs;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		while (s1[len1])
			len1++;
	while (s2[len2])
		len2++;
	fs = (char *) malloc(sizeof(char) * (len1 + len2 + 1));
	if (!fs && s1)
		free((void *)s1);
	if (!fs)
		return (NULL);
	fs[len1 + len2] = '\0';
	while ((len2-- > 0))
		fs[len1 + len2] = s2[len2];
	while (len1-- > 0)
		fs[len1] = s1[len1];
	if (s1)
		free((void *)s1);
	return (fs);
}

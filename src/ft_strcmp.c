/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <relaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:31:31 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 19:59:34 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

#define S1	0
#define S2	1
#define B0	2
#define HIGH_BYTE	0x8080808080808080
#define LOW_BYTE	0x0101010101010101

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (s1 != s2);
	i = 0;
	while (s1[i] && s2[i] && (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	end_buffer(const char *c1, const char *c2)
{
	int	i;

	i = 0;
	while (i++ < 8)
	{
		if (*c1 != *c2 || *c1 == '\0')
			return ((unsigned char) *c1 - (unsigned char) *c2);
		c1++;
		c2++;
	}
	return (0);
}

int	uint64_strcmp(uint64_t *w1, uint64_t *w2)
{
	uint64_t	val1;
	uint64_t	val2;
	uint64_t	null_byte;
	char		*c1;
	char		*c2;

	while (1)
	{
		val1 = *w1;
		val2 = *w2;
		null_byte = ((val1 - LOW_BYTE) & ~val1 & HIGH_BYTE);
		if (null_byte || val1 != val2)
		{
			c1 = (char *)w1;
			c2 = (char *)w2;
			return (end_buffer(c1, c2));
		}
		w1++;
		w2++;
	}
}

int	ft_fstrcmp(const char *s1, const char *s2)
{
	while ((uintptr_t)s1 & 7)
	{
		if (*s1 != *s2 || *s1 == '\0')
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (uint64_strcmp((uint64_t *) s1, (uint64_t *) s2));
}

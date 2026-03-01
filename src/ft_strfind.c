/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:03:19 by secros            #+#    #+#             */
/*   Updated: 2026/03/01 14:20:57 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#define HIGH_BYTE	0x8080808080808080
#define LOW_BYTE	0x0101010101010101

static inline uint64_t	broadcast_char(char c)
{
	uint64_t	w;

	w = (unsigned char) c;
	return (w | w << 8 | w << 16 | w << 24 
		| w << 32 | w << 40 | w << 48 | w << 56);
}

static inline char	*end_buffer(const char *c1, const char c2)
{
	int	i;

	i = 0;
	while (i++ < 8)
	{
		if (*c1 != c2)
			return ((char *) c1);
		c1++;
	}
	return (0);
}

static inline char	*uint64_strfind(uint64_t *w1, char c)
{
	uint64_t	val1;
	uint64_t	val2;
	uint64_t	null_byte;
	uint64_t	match;
	char		*c1;

	val2 = broadcast_char(c);
	while (1)
	{
		val1 = *w1;
		null_byte = ((val1 - LOW_BYTE) & ~val1 & HIGH_BYTE);
		match = ((val1 ^ val2) - LOW_BYTE) & ~(val1 ^ val2) & HIGH_BYTE;
		if (null_byte || match)
		{
			c1 = (char *)w1;
			return (end_buffer(c1, c));
		}
		w1++;
	}
}

char	*ft_fstrfind(const char *s1, const char c)
{
	while ((uintptr_t)s1 & 7)
	{
		if (*s1 != c || *s1 == '\0')
			return ((char *)s1);
		s1++;
	}
	return (uint64_strfind((uint64_t *) s1, c));
}

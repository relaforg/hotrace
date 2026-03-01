/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmemcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:47:34 by secros            #+#    #+#             */
/*   Updated: 2026/03/01 18:01:30 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

static inline void	uint64_memcpy(uint64_t *w1, uint64_t *w2, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*src;

	while (n >= 8)
	{
		*w1 = *w2;
		w1++;
		w2++;
		n -= 8;
	}
	dst = (unsigned char *) w1;
	src = (unsigned char *) w2;
	while (n)
	{
		*dst = *src;
		dst++;
		src++;
		n--;
	}
}

void	ft_fmemcpy(void *dst, void *src, size_t n)
{
	unsigned char		*s1;
	const unsigned char	*s2;

	s1 = (unsigned char *) dst;
	s2 = (unsigned char *) src;
	while ((uintptr_t)s1 & 7 && n)
	{
		*s1 = *s2;
		s1++;
		s2++;
		n--;
	}
	return (uint64_memcpy((uint64_t *) s1, (uint64_t *) s2, n));
}

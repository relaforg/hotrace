/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 18:27:43 by secros            #+#    #+#             */
/*   Updated: 2026/03/01 10:38:47 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

void	*ft_calloc(size_t size)
{
	void	*pt;

	pt = malloc(size);
	if (!pt)
		return (NULL);
	ft_fbzero(pt, size);
	return (pt);
}

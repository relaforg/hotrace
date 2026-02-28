/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <relaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:31:31 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 14:34:20 by relaforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t	i;
//
// 	i = 0;
// 	while (s1[i] == s2[i])
// 		i++;
// 	return (*s1 - *s2);
// }
int ft_strcmp(const char *s1, const char *s2)
{
    size_t i;

    if (!s1 || !s2)
        return (s1 != s2);

    i = 0;
    while (s1[i] && s2[i] && (unsigned char)s1[i] == (unsigned char)s2[i])
        i++;

    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 13:25:44 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 19:22:10 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

size_t	ft_strlen(const char *s);
size_t	ft_strcpy(char *dst, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_fstrcmp(const char *s1, const char *s2);
void	ft_fbzero(void *s, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t size);

#endif

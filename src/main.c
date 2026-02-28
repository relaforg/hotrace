/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 10:15:29 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 11:09:01 by relaforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include "get_next_line.h"
#include "stdio.h"

size_t	ft_strlen(char *s)
{
	size_t	size;

	if (!s)
		return (0);
	size = 0;
	while (*(s + size))
		size++;
	return (size);
}

int	main(void)
{
	char		*key;
	char		*value;
	t_hashtable	*hashtable;

	hashtable = init_hashtable(256);
	if (!hashtable)
		return (1);
	while (ft_strlen(key = get_next_line(0)) > 1)
	{
		value = get_next_line(0);
		insert(&hashtable, key, value);
		free(key);
		free(value);
	}
	show_hashtable(hashtable);
	return (0);
}

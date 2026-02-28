/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 10:15:29 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 13:13:23 by secros           ###   ########.fr       */
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
	t_node		*node;

	hashtable = init_hashtable(256);
	if (!hashtable)
		return (1);
	while (ft_strlen(key = get_next_line(0)) > 0)
	{
		value = get_next_line(0);
		if (!value)
		{
			dprintf(2, "Value for %s cannot be empty\n", value);
			free(key);
			free(value);
			break;
		}
		else
			insert(&hashtable, key, value);
		free(key);
		free(value);
	}
	while (ft_strlen(key = get_next_line(0)) > 1)
	{
		node = search(hashtable, key);
		printf("%s: ", key);
		if (!node)
			printf("Not Found\n");
		else
			printf("%s\n", node->value);
		free(key);
	}
	free_hashtable(hashtable);
	return (0);
}

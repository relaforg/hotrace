/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 10:15:29 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 13:22:23 by relaforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include "get_next_line.h"
#include "unistd.h"

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

void	get_inputs(t_hashtable *hashtable)
{
	char	*key;
	char	*value;

	key = get_next_line(0);
	while (ft_strlen(key) > 0)
	{
		value = get_next_line(0);
		if (!value)
		{
			write(2, "Value cannot be empty\n", 22);
			free(key);
			free(value);
			break ;
		}
		else
			insert(&hashtable, key, value);
		free(key);
		free(value);
		key = get_next_line(0);
	}
}

void	retrieve_data(t_hashtable *hashtable)
{
	char	*key;
	t_node	*node;

	key = get_next_line(0);
	while (ft_strlen(key) > 0)
	{
		node = search(hashtable, key);
		write(1, key, ft_strlen(key));
		write(1, ": ", 2);
		if (!node)
			write(1, "Not Found\n", 11);
		else
		{
			write(1, node->value, ft_strlen(node->value));
			write(1, "\n", 1);
		}
		free(key);
		key = get_next_line(0);
	}
}

int	main(void)
{
	t_hashtable	*hashtable;

	hashtable = init_hashtable(256);
	if (!hashtable)
		return (1);
	get_inputs(hashtable);
	retrieve_data(hashtable);
	free_hashtable(hashtable);
	return (0);
}

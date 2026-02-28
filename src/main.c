/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 10:15:29 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 16:54:41 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include "get_next_line.h"
#include "unistd.h"
#include <bits/floatn-common.h>
#include <unistd.h>
#include "utils.h"

void	get_inputs(t_hashtable **hashtable)
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
			free(value);
			break ;
		}
		else
			insert(hashtable, key, value);
		key = get_next_line(0);
	}
	free(key);
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
	free(key);
}

int	main(void)
{
	t_hashtable	*hashtable;

	hashtable = init_hashtable(1);
	hashtable_set_strategie(&hashtable, DEFAULT);
	if (!hashtable)
		return (1);
	get_inputs(&hashtable);
	retrieve_data(hashtable);
	free_hashtable(hashtable, true);
	return (0);
}

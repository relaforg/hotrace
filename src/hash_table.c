/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 09:42:41 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 16:47:20 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include "utils.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"

int	hash(const char *str, int table_size)
{
	uint64_t			hash;
	const uint64_t		fnv_offset = 0xcbf29ce484222325;
	const uint64_t		fnv_prime = 0x100000001b3;

	hash = fnv_offset;
	while (*str && *str != '\n')
	{
		hash *= fnv_prime;
		hash ^= *str;
		str++;
	}
	return (hash % table_size);
}

t_hashtable	*init_hashtable(int table_size)
{
	int			i;
	t_hashtable	*tab;

	i = 0;
	tab = malloc(sizeof(t_hashtable));
	if (tab == NULL)
		return (NULL);
	tab->size = table_size;
	tab->el_nbr = 0;
	tab->strategie = DEFAULT;
	tab->table = malloc(sizeof(t_node *) * table_size);
	if (tab->table == NULL)
	{
		free(tab);
		return (NULL);
	}
	while (i < table_size)
	{
		tab->table[i] = NULL;
		i++;
	}
	return (tab);
}

void	insert(t_hashtable **tab, const char *key, const char *value)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (new == NULL)
		return ;
	new->key = key;
	new->value = value;
	if (smart_insert(tab, new) == NULL)
	{
		(*tab)->el_nbr--;
		return ;
	}
	if (load_factor((*tab)) >= UPPER_TRESHOLD)
		increase_hashtable_size(tab);
}

t_node	*search(t_hashtable *tab, const char *key)
{
	int		hashed_key;
	t_node	*curr;

	hashed_key = hash(key, tab->size);
	curr = tab->table[hashed_key];
	while (curr != NULL)
	{
		if (!ft_strcmp(curr->key, key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	hashtable_set_strategie(t_hashtable **tab, enum e_collide opt)
{
	(*tab)->strategie = opt;
}

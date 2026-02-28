/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 09:42:41 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 13:31:47 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

const size_t fnv_offset = 0xcbf29ce484222325;
const size_t fnv_prime = 0x100000001b3;

int hash(const char* str, int table_size)
{
	size_t	hash;

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
	t_hashtable	*tmp;
	int			hashed_key;
	t_node		*new;

	tmp = *tab;
	hashed_key = hash(key, tmp->size);
	new = malloc(sizeof(t_node));
	if (new == NULL)
		return ;
	if (search(tmp, key) != NULL)
	{
		free(new);
		return ;
	}
	new->key = key;
	new->value = value;
	new->next = tmp->table[hashed_key];
	tmp->table[hashed_key] = new;
	if (load_factor(tmp) >= UPPER_TRESHOLD)
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
		if (!strcmp(curr->key, key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	delete_from_hashtable(t_hashtable **tab, const char *key)
{
	t_hashtable	*tmp;
	int			hashed_key;
	t_node		**curr;
	t_node		*aux;

	tmp = *tab;
	hashed_key = hash(key, tmp->size);
	curr = &tmp->table[hashed_key];
	aux = NULL;
	while (*curr)
	{
		if (!strcmp((*curr)->key, key))
		{
			aux = *curr;
			*curr = aux->next;
			free(aux);
			return ;
		}
		curr = &(*curr)->next;
	}
}

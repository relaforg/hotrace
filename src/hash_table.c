/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 09:42:41 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 10:24:39 by relaforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

int	hash(char *str, int tableSize)
{
	int	sum;

	sum = 0;
	while (*str != 0)
	{
		sum += *str;
		str++;
	}
	return (sum % tableSize);
}

t_hashtable	*init_hashtable(int tableSize)
{
	int			i;
	t_hashtable	*tab;

	i = 0;
	tab = malloc(sizeof(t_hashtable));
	if (tab == NULL)
		return (NULL);
	tab->size = tableSize;
	tab->table = malloc(sizeof(t_node *) * tableSize);
	if (tab->table == NULL)
	{
		free(tab);
		return (NULL);
	}
	while (i < tableSize)
	{
		tab->table[i] = NULL;
		i++;
	}
	return (tab);
}

void	insert(t_hashtable **tab, char *key, int value)
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
	strcpy(new->key, key);
	new->value = value;
	new->next = tmp->table[hashed_key];
	tmp->table[hashed_key] = new;
	if (load_factor(tmp) >= UPPER_TRESHOLD)
		increase_hashtable_size(tab);
}

t_node	*search(t_hashtable *tab, char *key)
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

void	delete_from_hashtable(t_hashtable **tab, char *key)
{
	t_hashtable	*tmp;
	int			hashed_key;
	t_node		*curr;
	t_node		*aux;

	tmp = *tab;
	hashed_key = hash(key, tmp->size);
	curr = tmp->table[hashed_key];
	aux = NULL;
	if (curr == NULL)
		return ;
	if (!strcmp(curr->key, key))
	{
		aux = curr;
		tmp->table[hashed_key] = curr->next;
		free(aux);
		return ;
	}
	while (curr->next != NULL)
	{
		if (!strcmp(curr->next->key, key))
		{
			aux = curr->next;
			curr->next = curr->next->next;
			free(aux);
			return ;
		}
		curr = curr->next;
	}
}

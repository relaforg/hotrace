/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 09:42:41 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 16:09:34 by secros           ###   ########.fr       */
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

void	delete_node(t_node* node)
{
	free((void*) node->key);
	free((void*) node->value);
	free(node);
}

void	*strategie_default(t_node* curr, t_node* new)
{
	delete_node(new);
	return (curr); 
}

void	*strategie_replace(t_node* curr, t_node* new)
{
	free((void*)curr->value);
	curr->value = new->value;
	free((void*)new->key);
	free(new);
	return (curr);
}

void	*strategie_concat(t_node* curr, t_node* new)
{
	curr->value = ft_strfreejoin(curr->value, "\n");
	if (curr->value)
		curr->value = ft_strfreejoin(curr->value, new->value);
	delete_node(new);
	if (!curr->value)
	{
		delete_node(curr);
		return (NULL);
	}
	return (curr);
}

void	*smart_insert(t_hashtable **tab, t_node *new)
{
	t_node	*curr;
	const int	hashed_key = hash(new->key, (*tab)->size);
	void	*(*strategie[])(t_node *, t_node *) = {
		strategie_default,
		strategie_replace,
		strategie_concat,
	};

	curr = search(*tab, new->key);
	if (!curr)
	{
		new->next = (*tab)->table[hashed_key];
		(*tab)->table[hashed_key] = new;
		(*tab)->el_nbr++;
		return (new);
	}
	if (strategie[(*tab)->strategie](curr, new) == NULL)
	{
		(*tab)->el_nbr--;
		(*tab)->table[hashed_key] = NULL;
		return (NULL);
	}
	return (curr);
}

void	insert(t_hashtable **tab, const char *key, const char *value)
{
	t_node*	new;

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

// void	insert(t_hashtable **tab, const char *key, const char *value)
// {
// 	t_hashtable	*tmp;
// 	int			hashed_key;
// 	t_node		*new;
//
// 	tmp = *tab;
// 	hashed_key = hash(key, tmp->size);
// 	new = malloc(sizeof(t_node));
// 	if (new == NULL)
// 		return ;
// 	if (search(tmp, key) != NULL)
// 	{
// 		free(new);
// 		free((void *) key);
// 		free((void *) value);
// 		return ;
// 	}
// 	new->key = key;
// 	new->value = value;
// 	new->next = tmp->table[hashed_key];
// 	tmp->table[hashed_key] = new;
// 	tmp->el_nbr++;
// 	if (load_factor(tmp) >= UPPER_TRESHOLD)
// 		increase_hashtable_size(tab);
// }

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
		if (!ft_strcmp((*curr)->key, key))
		{
			aux = *curr;
			*curr = aux->next;
			free(aux);
			return ;
		}
		curr = &(*curr)->next;
	}
	tmp->el_nbr--;
}

void	hashtable_set_strategie(t_hashtable **tab, enum e_collide opt)
{
	(*tab)->strategie = opt;
}

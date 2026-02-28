/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_mods.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:48:21 by secros            #+#    #+#             */
/*   Updated: 2026/02/28 16:48:23 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include "get_next_line.h"
#include <stdlib.h>

void	delete_node(t_node *node)
{
	free((void *) node->key);
	free((void *) node->value);
	free(node);
}

void	*strategie_default(t_node *curr, t_node *new)
{
	delete_node(new);
	return (curr);
}

void	*strategie_replace(t_node *curr, t_node *new)
{
	free((void *)curr->value);
	curr->value = new->value;
	free((void *)new->key);
	free(new);
	return (curr);
}

void	*strategie_concat(t_node *curr, t_node *new)
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
	t_node		*curr;
	const int	hashed_key = hash(new->key, (*tab)->size);
	void		*(*strategie[3])(t_node *, t_node *);

	strategie[DEFAULT] = strategie_default;
	strategie[REPLACE] = strategie_replace;
	strategie[CONCAT] = strategie_concat;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 10:20:12 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 10:21:16 by relaforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include <stdlib.h>
#include <stdio.h>

void	free_hashtable(t_hashtable *tab)
{
	t_node	*curr;
	t_node	*aux;
	int		i;

	i = 0;
	while (i < tab->size)
	{
		curr = (tab->table)[i];
		while (curr != NULL)
		{
			aux = curr;
			curr = curr->next;
			free(aux);
		}
		i++;
	}
	free(tab->table);
	free(tab);
}

void	show_hashtable(t_hashtable *tab)
{
	t_node	*curr;
	int		i;

	i = 0;
	while (i < tab->size)
	{
		printf("%d : \n", i);
		curr = (tab->table)[i];
		while (curr != NULL)
		{
			printf("%s -> %d\n", curr->key, curr->value);
			curr = curr->next;
		}
		printf("\n");
		i++;
	}
}

float	load_factor(t_hashtable *tab)
{
	int	i;
	int	used_row;

	i = 0;
	used_row = 0;
	while (i < tab->size)
	{
		if (tab->table[i] != NULL)
			used_row++;
		i++;
	}
	return ((float)used_row / (float)tab->size);
}

void	increase_hashtable_size(t_hashtable **tab)
{
	t_hashtable	*new;
	t_hashtable	*tmp;
	int			i;
	t_node		*curr;

	tmp = *tab;
	i = 0;
	new = init_hashtable(tmp->size * 2);
	if (new == NULL)
		return ;
	while (i < tmp->size)
	{
		curr = tmp->table[i];
		while (curr != NULL)
		{
			insert(&new, curr->key, curr->value);
			curr = curr->next;
		}
		i++;
	}
	*tab = new;
	free_hashtable(tmp);
}

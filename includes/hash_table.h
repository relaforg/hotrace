/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 10:18:53 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 11:05:44 by relaforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# define UPPER_TRESHOLD 0.8

typedef struct s_node
{
	char			key[256];
	char			value[256];
	struct s_node	*next;
}	t_node;

typedef struct s_hashtable
{
	t_node	**table;
	int		size;
}	t_hashtable;

int			hash(char *str, int tableSize);
t_hashtable	*init_hashtable(int tableSize);
void		free_hashtable(t_hashtable *tab);
void		show_hashtable(t_hashtable *tab);
void		insert(t_hashtable **tab, char *key, char *value);
t_node		*search(t_hashtable *tab, char *key);
void		delete_from_hashtable(t_hashtable **tab, char *key);
float		load_factor(t_hashtable *tab);
void		increase_hashtable_size(t_hashtable **tab);

#endif

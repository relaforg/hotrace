/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 10:18:53 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 14:39:28 by relaforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# define UPPER_TRESHOLD 0.8

# include <stdbool.h>

typedef struct s_node
{
	const char		*key;
	const char		*value;
	struct s_node	*next;
}	t_node;

typedef struct s_hashtable
{
	t_node	**table;
	int		size;
	int		el_nbr;
}	t_hashtable;

int			hash(const char *str, int table_size);
t_hashtable	*init_hashtable(int table_size);
void		free_hashtable(t_hashtable *tab, bool delete);
void		show_hashtable(t_hashtable *tab);
void		insert(t_hashtable **tab, const char *key, const char *value);
t_node		*search(t_hashtable *tab, const char *key);
void		delete_from_hashtable(t_hashtable **tab, const char *key);
float		load_factor(t_hashtable *tab);
void		increase_hashtable_size(t_hashtable **tab);

#endif

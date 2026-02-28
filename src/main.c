/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relaforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 10:15:29 by relaforg          #+#    #+#             */
/*   Updated: 2026/02/28 10:40:27 by relaforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

int	main(void)
{
	t_hashtable	*hashTable = init_hashtable(2);

	insert(&hashTable, "test", 1);
	insert(&hashTable, "test", 1);
	insert(&hashTable, "testb", 2);
	insert(&hashTable, "testc", 3);
	insert(&hashTable, "testd", 4);
	insert(&hashTable, "teste", 5);
	insert(&hashTable, "testf", 6);
	insert(&hashTable, "testg", 7);
	insert(&hashTable, "testh", 8);

	show_hashtable(hashTable);

	delete_from_hashtable(&hashTable, "test");

	show_hashtable(hashTable);

	free_hashtable(hashTable);
	return (0);
}

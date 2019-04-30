/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_ops2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 22:32:25 by dhorvill          #+#    #+#             */
/*   Updated: 2019/04/30 21:27:56 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*t_map	backup_vertex(t_map map, t_map backup)
{
	int i;

	i = -1;
	while (++i < map.vertex_length)
		backup.vertex[i] = map.vertex[i];
	backup.vertex_length = map.vertex_length;
	return (backup);
}

t_map	backup_edges(t_map map, t_map backup_map)
{
	int i;

	i = -1;
	while (++i < map.edges_length)
		backup_map.edges[i] = map.edges[i];
	backup_map.edges_length = map.edges_length;
	return (backup_map);
}

t_map	backup_init_sector(t_map map, t_map backup_map)
{
	int i;

	i = -1;
	while (++i < map.sector[0].edges_length)
		backup_map.sector[0].edges[i] = map.sector[0].edges[i];
	backup_map.sector[0].edges_length = map.sector[0].edges_length;
	return (backup_map);
}

t_map	backup_remaining_sectors(t_map map, t_map backup_map)
{
	int i;
	int j;
	
	i = 0;
	while (++i < map.sector_length)
	{
		if ((backup_map.sector[i].edges = (int*)malloc(sizeof(int) * 300)) == NULL)
			exit_on_error();
		j = -1;
		while (++j < map.sector[i].edges_length)
			backup_map.sector[i].edges[j] = map.sector[i].edges[j];
	}
	return (backup_map);
}

t_map	backup_map(t_map map, t_map backup_map)
{
	backup_map = initialize_values();
	backup_map = backup_vertex(map, backup_map);
	backup_map = backup_edges(map, backup_map);
	backup_map = backup_init_sector(map, backup_map);
	backup_map = backup_remaining_sectors(map, backup_map);
	backup_map.sector_length = map.sector_length;
	return (backup_map);
}*/

t_map	remove_latest_sector(t_map map)
{
	map.edges_length -= 4;
	map.vertex_length -= 2;
	free(map.sector[map.sector_length -1].edges);
	map.sector_length--;
	return (map);
}

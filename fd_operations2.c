/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_operations2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:32:49 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/01 20:32:30 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		get_fd_index(t_map map, t_coord to_find)
{
	int i;
	int j;
	int count;

	count = 0;
	i = -1;
	if (map.vertex[0].x == to_find.x && map.vertex[0].y == to_find.y)
		return (0);
	while (++i < map.vertex_length)
	{
		j = i;
		while (++j < map.vertex_length)
		{
			if (map.vertex[i].y == map.vertex[j].y)
				count++;
			if (map.vertex[j].x == to_find.x && map.vertex[j].y == to_find.y)
				return (count);
		}
	}
	return (0);
}

int		find_neighbour(t_map map, t_coord edge)
{
	int i;
	int j;
	t_coord	edge_to_compare;

	i = -1;
	while (++i < map.sector_length)
	{
		j = -1;
		while (++j < map.sector[i].edges_length)
		{
			edge_to_compare = map.edges[map.sector[i].edges[j]];
			if (edge_to_compare.x == edge.y && edge_to_compare.y == edge.x)
				return (i);
		}
	}
	return (-1);
}

void	write_neighbours(t_map map, int s_num, int fd)
{
	int		i;
	t_coord	edge;
	int		neighbour;

	i = -1;
	while (++i < map.sector[s_num].edges_length)
	{
		edge = map.edges[map.sector[s_num].edges[i]];
		neighbour = find_neighbour(map, edge);
		ft_putnbr_fd(neighbour, fd);
		ft_putchar_fd(' ', fd);
	}
}

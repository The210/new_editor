/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 22:06:04 by dhorvill          #+#    #+#             */
/*   Updated: 2019/04/26 21:06:16 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_coord *create_edge(t_coord vertex_indexes, t_coord *edges, int edges_length)
{
	t_coord new_edgelist;
	int i;
	int new_edgelist_length;

	if (edges_length > 0)
	{
		new_edgelist = (t_coord*)malloc(sizeof(t_coord) * (edges_length + 11));
		i = -1;
		while (++i < edges_length)
			new_edgelist[i] = edges[i];
		new_edgelist_length = edges_length + 1;
		new_edgelist[new_edgelist_length - 1] = vertex_indexes;
		free(&edges);
	}
	/*else
	  {
	  new_edgelist.coords = (t_coord*)malloc(sizeof(t_coord) * 10);
	  new_edgelist.length = 1;
	  new_edgelist.coords[0].x = vertex_indexes.x;
	  new_edgelist.coords[0].y = vertex_indexes.y;
	  }*/
	return(new_edgelist);
}

t_map divide_line(t_map map, int edge_index)
{
	t_coord tmp;
	tmp.x = map.vertex.length - 1;
	tmp.y = map.edge[edge_index].coords.y;
	map.edge[edge_index].coords.y = tmp.x;

	map.edge = create_edge(tmp, map.edge);
	return (map);
}

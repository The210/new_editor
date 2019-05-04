/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_ops2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 22:32:25 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/04 10:13:36 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_map	remove_latest_sector(t_map map)
{
	map.edges_length -= 4;
	map.vertex_length -= 2;
	free(map.sector[map.sector_length - 1].edges);
	map.sector_length--;
	return (map);
}

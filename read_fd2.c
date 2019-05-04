/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 12:58:43 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/04 13:13:17 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_map	init_map(t_map map)
{
	map.i = -1;
	map.sector_length = 0;
	map.edges_length = 0;
	map.vertex_length = 0;
	if ((map.vertex = (t_coord*)malloc(sizeof(t_coord) * (1000))) == NULL)
		exit_on_error();
	if ((map.edges = (t_coord*)malloc(sizeof(t_coord) * (1000))) == NULL)
		exit_on_error();
	if ((map.sector = (t_sector*)malloc(sizeof(t_sector) * (200))) == NULL)
		exit_on_error();
	return (map);
}

t_map	read_player(t_map map, char **txt)
{
	while (map.j < ft_strlen(txt[map.i]) - 2 && (txt[map.i][map.j] < '0' ||
				txt[map.i][map.j] > '9'))
		map.j++;
	map.player.pos.x = ft_iatoi(txt[map.i], map.j);
	while (map.j < ft_strlen(txt[map.i]) - 2 && (txt[map.i][map.j] < '0' ||
				txt[map.i][map.j] > '9'))
		map.j++;
	map.j++;
	map.player.pos.y = ft_iatoi(txt[map.i], map.j);
	while (map.j < ft_strlen(txt[map.i]) - 2 && (txt[map.i][map.j] < '0' ||
				txt[map.i][map.j] > '9'))
		map.j++;
	map.j = map.j + 3;
	map.player.sector_num = ft_iatoi(txt[map.i], map.j);
	return (map);
}

t_map	make_read_decision(t_map map, char **txt)
{
	if (txt[map.i][map.j] == 'v')
		map = read_vertex(map, txt);
	else if (txt[map.i][map.j] == 's')
		map = read_sector(map, txt);
	else if (txt[map.i][map.j] == 'p')
		map = read_player(map, txt);
	return (map);
}

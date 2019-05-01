/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 05:08:57 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/01 22:50:09 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


int		recursive(t_map map, int i, int current_y)
{
	if (i == 0)
		return (1);
	if (map.vertex[i].y != current_y && i < map.vertex_length)
		return (recursive(map, i - 1, current_y));
	if (map.vertex[i].y == current_y)
		return (2);
	return (0);
}

void	write_vertex(t_map map, int fd)
{
	int i;
	int j;
	int	current_y;

	i = -1;
	current_y = -1;
	while (++i < map.vertex_length)
	{
		current_y = map.vertex[i].y;
		if (i == 1)
		{
			if (map.vertex[i].y == map.vertex[i - 1].y)
				continue;
		}
		if (i > 1 && recursive(map, i - 1, current_y) == 2)
			continue;
		ft_putstr_fd("vertex ", fd);
		ft_putnbr_fd(map.vertex[i].y, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(map.vertex[i].x, fd);
		j = i;
		while (++j < map.vertex_length)
		{
			if(map.vertex[i].y == map.vertex[j].y)
			{
				ft_putchar_fd(' ', fd);
				ft_putnbr_fd(map.vertex[j].x, fd);
			}
		}
		ft_putchar_fd('\n', fd);
	}
}

void	write_edges(t_map map, int s_num, int fd)
{
	int i;
	int	fd_index;
	t_coord	edge_to_find;

	i = -1;
	while (++i < map.sector[s_num].edges_length)
	{
		edge_to_find = map.edges[map.sector[s_num].edges[i]];
		fd_index = get_fd_index(map, edge_to_find);
		ft_putnbr_fd(fd_index, fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putstr_fd("z ", fd);
}

void	write_sectors(t_map map, int fd)
{
	int i;

	i = -1;
	while (++i < map.sector_length)
	{
		ft_putstr_fd("sector ", fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(map.sector[i].floor_height, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(map.sector[i].ceil_height, fd);
		ft_putchar_fd(' ', fd);
		write_edges(map, i, fd);
		write_neighbours(map, i, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	write_player(t_map map, int fd)
{
	ft_putstr_fd("player ", fd);
	ft_putnbr_fd(map.player.pos.x, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(map.player.pos.y, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(map.player.sector_num, fd);
	ft_putchar_fd('\n', fd);
}

void	write_sprites_globales(t_map map, int fd)
{
	int i;

	i = -1;
	while (++i < map.sprite_g_len)
	{
		ft_putstr_fd("sprite ", fd);
		ft_putnbr(map.g_sprite[i].pos.x);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(map.g_sprite[i].pos.y, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(map.g_sprite[i].sector_num, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	write_fd(t_map map)
{
	int fd;

	fd = open("map.txt", O_CREAT | O_RDWR | O_APPEND, 0777);
	write_vertex(map, fd);
	ft_putchar_fd('\n', fd);
	write_sectors(map, fd);
	ft_putchar_fd('\n', fd);
	write_player(map, fd);
	ft_putchar_fd('\n', fd);
	write_sprites_globales(map, fd);
}

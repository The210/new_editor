/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 02:48:39 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/04 14:03:27 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			ft_iatoi(char *wall, int index)
{
	int number;
	int i;
	int	negative;

	i = index;
	negative = 1;
	number = 0;
	if (wall[index] == '-')
	{
		i++;
		negative = -1;
	}
	while (wall[i] && wall[i] >= '0' && wall[i] <= '9')
	{
		number = number * 10 + wall[i] - '0';
		i++;
	}
	return (number * negative);
}

char		**read_lines(int fd)
{
	char	*buf;
	int		ret;
	char	**txt;
	char	*str;

	str = ft_strnew(1);
	while ((ret = get_next_line(fd, &buf)) == 1)
	{
		str = ft_strjoin2(str, buf);
		ft_strdel(&buf);
	}
	if ((txt = ft_strsplit(str, '|')) == NULL || ret == -1)
		exit_on_error();
	free(str);
	return (txt);
}

t_map		read_vertex(t_map map, char **txt)
{
	int			flag;
	int			save;
	static int	count = -1;

	flag = 0;
	while (map.j < ft_strlen(txt[map.i]) - 2)
	{
		count++;
		map.vertex_length++;
		while (map.j < ft_strlen(txt[map.i]) - 2 && (txt[map.i][map.j] < '0' ||
					txt[map.i][map.j] > '9'))
			map.j++;
		save = flag == 0 ? ft_iatoi(txt[map.i], map.j) : save;
		map.vertex[count].x = ft_iatoi(txt[map.i], map.j);
		while (map.j < ft_strlen(txt[map.i]) - 2 && txt[map.i][map.j] >= 48 &&
				txt[map.i][map.j] <= 57)
			map.j++;
		if (++map.j && flag++ == 0)
			map.vertex[count].x = ft_iatoi(txt[map.i], map.j);
		map.vertex[count].y = save;
		while (map.j < ft_strlen(txt[map.i]) - 2 && txt[map.i][map.j] >= '0' &&
				txt[map.i][map.j] <= '9')
			map.j++;
	}
	return (map);
}

t_map		read_edges(t_map map, char **txt, int save, int flag)
{
	while (map.j < ft_strlen(txt[map.i]) - 3 && txt[map.i][map.j] != 'c')
	{
		map.edges[map.edges_length].x = ft_iatoi(txt[map.i], map.j);
		map.sector[map.sector_length]
		.edges[map.sector[map.sector_length].edges_length] = map.edges_length;
		if (flag == 0)
			save = map.edges[map.edges_length].x;
		flag = 1;
		while (map.j < ft_strlen(txt[map.i]) - 3 && txt[map.i][map.j] >= '0' &&
				txt[map.i][map.j] <= '9')
			map.j++;
		map.j++;
		if (map.j < ft_strlen(txt[map.i]) - 3 && txt[map.i][map.j] == 'c')
			map.edges[map.edges_length].y = save;
		else
			map.edges[map.edges_length].y = ft_iatoi(txt[map.i], map.j);
		map.sector[map.sector_length].edges_length++;
		map.edges_length++;
	}
	map.sector_length++;
	return (map);
}

t_map		read_sector(t_map map, char **txt)
{
	int		flag;
	int		save;
	size_t	strlen;

	save = 0;
	flag = 0;
	strlen = ft_strlen(txt[map.i]) - 3;
	map.sector[map.sector_length].edges_length = 0;
	if ((map.sector[map.sector_length].edges =
				(int*)malloc(sizeof(t_coord) * (500))) == NULL)
		exit_on_error();
	map.sector[map.sector_length].num = map.sector_length;
	while (map.j < strlen &&
			(txt[map.i][map.j] < '0' || txt[map.i][map.j] > '9'))
		map.j++;
	map.sector[map.sector_length].floor_height = ft_iatoi(txt[map.i], map.j);
	while (map.j < strlen &&
			txt[map.i][map.j] >= '0' && txt[map.i][map.j] <= '9')
		map.j++;
	map.j++;
	map.sector[map.sector_length].ceil_height = ft_iatoi(txt[map.i], map.j);
	while (map.j < strlen &&
			txt[map.i][map.j] >= '0' && txt[map.i][map.j] <= '9')
		map.j++;
	map.j++;
	map = read_edges(map, txt, save, flag);
	return (map);
}

t_map		read_map(void)
{
	t_map	map;
	char	**txt;
	int		fd;
	int		i;
	size_t	strlen;

	fd = open("map.txt", O_RDONLY);
	txt = read_lines(fd);
	close(fd);
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
	while (txt[++map.i])
	{
		strlen = ft_strlen(txt[map.i]) - 2;
		map.j = 0;
		if (txt[map.i][map.j])
		{
			if (txt[map.i][map.j] == '\n')
				continue;
			if (txt[map.i][map.j] == 'v')
				map = read_vertex(map, txt);
			else if (txt[map.i][map.j] == 's')
				map = read_sector(map, txt);
			else if (txt[map.i][map.j] == 'p')
			{
				while (map.j < strlen && (txt[map.i][map.j] < '0' ||
							txt[map.i][map.j] > '9'))
					map.j++;
				map.player.pos.x = ft_iatoi(txt[map.i], map.j);
				while (map.j < strlen && !(txt[map.i][map.j] < '0' ||
							txt[map.i][map.j] > '9'))
					map.j++;
				map.j++;
				map.player.pos.y = ft_iatoi(txt[map.i], map.j);
				while (map.j < strlen && !(txt[map.i][map.j] < '0' ||
							txt[map.i][map.j] > '9'))
					map.j++;
				map.j = map.j + 3;
				map.player.sector_num = ft_iatoi(txt[map.i], map.j);
			}
		}
	}
	i = -1;
	while (++i < ft_tablen(txt))
		free(txt[i]);
	free(txt);
	return (map);
}

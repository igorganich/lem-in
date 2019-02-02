/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 16:32:26 by iganich           #+#    #+#             */
/*   Updated: 2018/08/21 14:13:18 by iganich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	realloc_links(t_data *lemin)
{
	int i;
	int l;
	int **newmas;

	newmas = ft_memalloc(sizeof(int*) *
			(lemin->roomcount + lemin->temprooms + 1));
	i = -1;
	while (++i <= lemin->roomcount + lemin->temprooms)
	{
		newmas[i] = ft_memalloc(sizeof(int) *
				(lemin->roomcount + lemin->temprooms + 1));
		l = -1;
		if (i < lemin->roomcount + lemin->temprooms)
			while (++l < lemin->roomcount + lemin->temprooms)
				newmas[i][l] = lemin->links[i][l];
		if (i < lemin->roomcount + lemin->temprooms)
			free(lemin->links[i]);
	}
	free(lemin->links);
	lemin->links = newmas;
}

int		get_min_links(t_data *e, int room, int wat, int count)
{
	int i;
	int l;
	int z;
	int **k;

	i = -1;
	while (count && !(count = 0))
		while (++i < e->roomcount + e->temprooms && (l = -1))
			while (++l < e->roomcount + e->temprooms)
				if (l == e->finish || l == e->start)
					continue;
				else if (e->links[i][l] >= 1 && (z = -1))
				{
					while (++z < e->roomcount + e->temprooms && (k = e->links))
						if (z == i || z == l)
							continue;
						else if ((!k[i][z] || k[i][z] > k[l][z] + k[i][l])
								&& k[l][z] && count++)
							if (e->links[l][z] > 0 && e->links[i][l] > 0)
							{
								k[i][z] = k[l][z] + k[i][l];
								k[z][i] = k[l][z] + k[i][l];
							}
				}
	return (e->links[room][wat]);
}

void	create_links_mem(t_data *lemin)
{
	int i;

	i = -1;
	lemin->links = (int**)ft_memalloc(sizeof(int*) * (lemin->roomcount));
	while (++i < lemin->roomcount)
		(lemin->links)[i] = (int*)ft_memalloc(sizeof(int) * (lemin->roomcount));
}

void	find_name(t_data *lemin, char *line, int *i, int *l)
{
	int		count;
	int		sec;
	t_room	**rooms;

	*i = -1;
	*l = -1;
	rooms = lemin->rooms;
	count = -1;
	while (++count < lemin->roomcount)
		if (ft_strstr(line, (rooms[count])->name) == line &&
			*(line + ft_strlen(rooms[count]->name)) == '-')
		{
			line += ft_strlen(rooms[count]->name) + 1;
			*i = count;
			sec = -1;
			while (++sec < lemin->roomcount)
				if (ft_strstr(line, (rooms[sec])->name) == line &&
					*(line + ft_strlen(rooms[sec]->name)) == '\0')
					*l = sec;
		}
}

int		set_links(t_data *lemin, int s_e, char *line)
{
	int i;
	int l;

	i = 0;
	l = 0;
	if (!lemin->links)
		create_links_mem(lemin);
	if (s_e != 0)
		return (-1);
	find_name(lemin, line, &i, &l);
	if (i != -1 && l != -1 && i != l)
	{
		(lemin->links)[i][l] = 1;
		(lemin->links)[l][i] = 1;
		return (0);
	}
	return (-1);
}

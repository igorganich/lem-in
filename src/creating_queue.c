/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 17:00:19 by iganich           #+#    #+#             */
/*   Updated: 2018/08/19 18:02:32 by iganich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	create_temp_room(t_data *e, int src, t_room **newmas, int l)
{
	e->rooms[src]->islast = 0;
	realloc_links(e);
	newmas = ft_memalloc(sizeof(t_list*) * (e->roomcount + e->temprooms + 1));
	while (++l < e->roomcount + e->temprooms)
		newmas[l] = e->rooms[l];
	free(e->rooms);
	e->rooms = newmas;
	newmas[l] = set_new_room("easter_egg 0 0", NULL, e, 1);
	newmas[l]->islast = 1;
	e->links[src][l] = 1;
	e->links[l][src] = 1;
	e->rooms[l]->cur_ant = e->temprooms + 1;
	(e->rooms[l])->way = ft_memalloc(sizeof(int) * (e->roomcount + e->ants));
	l = -1;
	while (++l < e->roomcount + e->temprooms)
		e->rooms[e->roomcount + e->temprooms]->way[l] = 2147483647;
	(e->temprooms)++;
}

void	push_queue(t_data *lemin, int src, t_list *current, int prev)
{
	int i;

	i = -1;
	while (current->next)
		current = current->next;
	while (++i < lemin->roomcount + lemin->temprooms)
		if (i == prev || i == lemin->finish)
			continue;
		else if (lemin->links[src][i] == 1)
		{
			if (i != lemin->start)
			{
				current->next = ft_memalloc(sizeof(t_list));
				current->next->secondint = src;
				current->next->content_size = i;
				current = current->next;
			}
			else if (i == lemin->start)
			{
				lemin->links[i][src] = 0;
				lemin->links[src][i] = 0;
				create_temp_room(lemin, src, NULL, -1);
			}
		}
}

int		import_data(t_data *lemin, int dst, int src)
{
	int count;
	int i;

	i = -1;
	count = 0;
	while (++i < lemin->roomcount)
		if (dst != i)
			if (lemin->rooms[src]->way[i] < lemin->rooms[dst]->way[i])
				if (lemin->rooms[dst]->way[i] !=
					lemin->rooms[src]->way[i] + 1 && ++count)
					lemin->rooms[dst]->way[i] = lemin->rooms[src]->way[i] + 1;
	lemin->rooms[dst]->way[src] = get_min_way(lemin, src, dst) + 1;
	return (count);
}

void	create_queue(t_data *lemin)
{
	t_list *first;
	t_list *current;

	first = ft_memalloc(sizeof(t_list));
	push_queue(lemin, lemin->finish, first, -1);
	current = first->next;
	while (current)
	{
		if (import_data(lemin, current->content_size, current->secondint))
			if ((int)current->content_size < lemin->roomcount)
				push_queue(lemin, current->content_size,
						current, current->secondint);
		current = current->next;
	}
	while (first)
	{
		current = first;
		first = first->next;
		free(current);
	}
}

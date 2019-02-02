/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 17:03:48 by iganich           #+#    #+#             */
/*   Updated: 2018/09/30 14:34:04 by iganich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		cr_w_case_best_prev(t_data *lemin, int bestroom, int prev, int *used)
{
	if (get_used_size(used, lemin->roomcount + lemin->temprooms)
			!= lemin->rooms[bestroom]->way[lemin->finish])
		return (0);
	lemin->links[bestroom][prev] = bestroom * (-1) - 100;
	lemin->links[prev][bestroom] = bestroom * (-1) - 100;
	lemin->rooms[bestroom]->realway =
		lemin->rooms[bestroom]->way[lemin->finish];
	clear_at_finish(lemin, used);
	clear_ways(lemin);
	create_queue(lemin);
	if (!algo(lemin, lemin->steps))
		again_at_finish(lemin, used);
	else
		return (1);
	lemin->rooms[bestroom]->realway = 2147483647;
	lemin->links[bestroom][prev] = 1;
	lemin->links[prev][bestroom] = 1;
	clear_ways(lemin);
	create_queue(lemin);
	return (0);
}

void	best_max_way(t_data *lemin, int *data, int bestroom, int *used)
{
	data[5] = 0;
	data[0] = 2147483647;
	data[1] = 0;
	data[2] = -1;
	data[3] = bestroom;
	while (++data[2] < lemin->roomcount + lemin->temprooms)
		if (!used[data[2]] && lemin->links[data[2]][data[4]] == 1)
		{
			lemin->links[data[2]][data[4]] = -1;
			lemin->links[data[4]][data[2]] = -1;
			lemin->rooms[bestroom]->way[data[2]] < data[0] ?
				data[0] = lemin->rooms[bestroom]->way[data[2]] : 0;
			lemin->rooms[bestroom]->way[data[2]] > data[1] &&
				lemin->rooms[bestroom]->way[data[2]] < 2147483647 ?
				data[1] = lemin->rooms[bestroom]->way[data[2]] : 0;
		}
	data[1] > lemin->steps ? data[1] = lemin->steps : 0;
}

int		build_by_one(t_data *lemin, int *data, int *used)
{
	data[0]--;
	while (++data[0] <= data[1] && (data[2] = -1))
		while (++data[2] < lemin->roomcount)
		{
			if (get_used_size(used, lemin->roomcount + lemin->temprooms) ==
					lemin->rooms[data[2]]->way[lemin->finish] ||
					lemin->rooms[data[2]]->way[lemin->finish] == 2147483647)
				if (lemin->links[data[4]][data[2]] == -1)
				{
					lemin->links[data[2]][data[4]] = 1;
					lemin->links[data[4]][data[2]] = 1;
					used[data[2]] = 1;
					clear_ways(lemin);
					create_queue(lemin);
					if (lemin->rooms[data[3]]->way[data[2]] == data[0])
						if (creating_ways(lemin, used, data[3], data[2]) == 1)
							return (1);
					lemin->links[data[2]][data[4]] = -1;
					lemin->links[data[4]][data[2]] = -1;
					clear_ways(lemin);
					create_queue(lemin);
					used[data[2]] = 0;
				}
		}
	return (0);
}

int		creating_ways(t_data *lemin, int *used, int bestroom, int prev)
{
	int data[6];

	data[4] = prev;
	best_max_way(lemin, data, bestroom, used);
	if (lemin->links[bestroom][prev] == -1 && (data[5] = 1))
		if (cr_w_case_best_prev(lemin, bestroom, prev, used))
			return (1);
	if (build_by_one(lemin, data, used))
		return (1);
	data[2] = -1;
	while (++data[2] < lemin->roomcount + lemin->temprooms)
		if (lemin->links[prev][data[2]] == -1)
		{
			lemin->links[prev][data[2]] = 1;
			lemin->links[data[2]][prev] = 1;
		}
	clear_ways(lemin);
	create_queue(lemin);
	return (0);
}

int		algo(t_data *lemin, int size)
{
	int i;
	int l;
	int *used;
	int flag;

	flag = 0;
	used = ft_memalloc(sizeof(int) * (lemin->roomcount + lemin->temprooms));
	used[lemin->finish] = 1;
	i = lemin->roomcount - 1;
	while (++i < lemin->roomcount + lemin->temprooms && (l = -1))
		if (lemin->rooms[i]->way[lemin->finish] <= size)
		{
			flag = 1;
			if (creating_ways(lemin, used, i, lemin->finish))
			{
				free(used);
				return (1);
			}
			break ;
		}
	free(used);
	if (flag == 0)
		return (try_ants(lemin, size, 0, 0));
	return (0);
}

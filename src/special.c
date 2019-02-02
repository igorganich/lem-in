/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 16:49:52 by iganich           #+#    #+#             */
/*   Updated: 2018/10/14 10:59:53 by iganich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		get_min_way(t_data *lemin, int src, int me)
{
	int best;
	int i;

	best = 2147483647;
	i = -1;
	while (++i < lemin->roomcount)
	{
		if (i == me)
			continue;
		if (lemin->rooms[src]->way[i] < best)
			if (lemin->rooms[me]->way[i] >= lemin->rooms[src]->way[i])
				best = lemin->rooms[src]->way[i];
	}
	return (best);
}

int		check_xboct(t_data *lemin, int *s_e, int *flag)
{
	if (!lemin->links || !lemin->rooms)
		return (-1);
	if ((s_e[1] != 0 && s_e[1] != 3) || lemin->ants < 1)
	{
		*flag = 0;
		return (-1);
	}
	if (lemin->finish == -1 || lemin->start == -1)
	{
		*flag = 0;
		return (-1);
	}
	return (0);
}

int		get_best_size(t_data *lemin)
{
	int i;
	int sum;
	int best;

	best = 2147483647;
	sum = lemin->roomcount + lemin->temprooms;
	i = lemin->roomcount - 1;
	while (++i < sum)
		if (lemin->links[i][lemin->finish] < best &&
				lemin->links[i][lemin->finish] > 0)
			best = lemin->links[i][lemin->finish];
	return (best);
}

void	give_mem(t_data *lemin)
{
	int i;
	int l;

	i = -1;
	while (++i < lemin->roomcount)
	{
		(lemin->rooms[i])->way = ft_memalloc(sizeof(int)
				* (lemin->roomcount + lemin->ants));
		l = -1;
		while (++l < lemin->roomcount + lemin->ants)
			lemin->rooms[i]->way[l] = 2147483647;
	}
	lemin->rooms[lemin->finish]->way[lemin->finish] = 0;
}

int		get_at_finish(t_data *lemin)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (++i < lemin->roomcount)
	{
		if (lemin->links[i][lemin->finish] == 1)
			count++;
	}
	return (count);
}

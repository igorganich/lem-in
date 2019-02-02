/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 16:54:47 by iganich           #+#    #+#             */
/*   Updated: 2018/10/14 11:01:43 by iganich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	clear_map(t_data *lemin)
{
	int i;
	int l;

	i = -1;
	while (++i < lemin->roomcount + lemin->temprooms)
	{
		l = -1;
		while (++l < lemin->roomcount)
			if (lemin->links[i][l] >= 2)
				lemin->links[i][l] = 0;
	}
}

void	clear_ways(t_data *lemin)
{
	int i;
	int l;

	i = -1;
	while (++i < lemin->roomcount + lemin->temprooms)
	{
		l = -1;
		while (++l < lemin->roomcount + lemin->temprooms)
			lemin->rooms[i]->way[l] = 2147483647;
	}
	lemin->rooms[lemin->finish]->way[lemin->finish] = 0;
}

void	clear_at_finish(t_data *lemin, int *used)
{
	int i;

	i = -1;
	while (++i < lemin->roomcount)
	{
		if (lemin->links[i][lemin->finish] == -1 && !used[i])
		{
			lemin->links[i][lemin->finish] = 1;
			lemin->links[lemin->finish][i] = 1;
		}
	}
}

void	again_at_finish(t_data *lemin, int *used)
{
	int i;

	i = -1;
	while (++i < lemin->roomcount)
	{
		if (lemin->links[i][lemin->finish] == 1 && !used[i])
		{
			lemin->links[i][lemin->finish] = -1;
			lemin->links[lemin->finish][i] = -1;
		}
	}
}

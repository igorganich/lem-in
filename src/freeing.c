/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 16:41:52 by iganich           #+#    #+#             */
/*   Updated: 2018/08/19 17:55:41 by iganich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	custom_free(void **mem)
{
	free(*mem);
	*mem = NULL;
}

t_room	*freeroom(t_room *room)
{
	if (room)
	{
		if (room->name)
			custom_free((void*)(&(room->name)));
		if (room->way)
			free(room->way);
		custom_free((void*)(&room));
	}
	return (NULL);
}

void	freelemin(t_data *lemin)
{
	int i;

	i = -1;
	if (lemin)
	{
		while (++i < lemin->roomcount + lemin->temprooms)
		{
			freeroom(lemin->rooms[i]);
			if (lemin->links)
				if (lemin->links[i])
					free(lemin->links[i]);
		}
		free(lemin->mapinfo);
		free(lemin->rooms);
		free(lemin->links);
		free(lemin);
	}
}

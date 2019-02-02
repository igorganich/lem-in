/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 16:26:57 by iganich           #+#    #+#             */
/*   Updated: 2018/09/30 14:30:57 by iganich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	add_to_mapinfo(t_data *lemin, char *line, int flag)
{
	int i;

	if (flag == 0)
		ft_printf("\x1b[%dm%s\n", lemin->colour * 35, line);
	else if (flag == 1)
	{
		ft_printf("\x1b[%dm%s \x1b[%dm%s\n", lemin->colour * 33,
				lemin->rooms[lemin->roomcount - 1]->name,
				lemin->colour * 36,
				ft_strchr(line, ' ') + 1);
	}
	else if (flag == 2)
	{
		i = -1;
		ft_printf("\x1b[%dm", lemin->colour * 33);
		while (line[++i] != '-')
			write(1, line + i, 1);
		ft_printf("\x1b[%dm-", lemin->colour * 32);
		ft_printf("\x1b[%dm%s\n", lemin->colour * 33, ft_strchr(line, '-') + 1);
	}
}

void	read_to_end(void)
{
	char *line;

	close(0);
	get_next_line(0, &line);
}

int		freeret(char *line)
{
	free(line);
	read_to_end();
	return (-1);
}

int		check_mistake_line(t_data *lemin, int s_e[2], char *line, int *flag)
{
	if (s_e[0] == -1)
		return (-1);
	if (*flag == 0 && set_ants(lemin, s_e[1], line) == -1)
		return (-1);
	if (*flag == 1 && set_room_info(lemin, s_e, line) == -1)
		return (-1);
	return (0);
}

int		read_lemin(t_data *lemin, int *flag)
{
	char	*line;
	int		s_e[2];

	ft_bzero(s_e, sizeof(s_e));
	while (get_next_line(0, &line) > 0)
	{
		s_e[1] == 0 ? s_e[1] = s_e[0] : 0;
		s_e[0] = line_type(line, flag, 3, lemin);
		if (s_e[0] >= 4 && s_e[1] != 0 && s_e[1] != 3)
			return (freeret(line));
		s_e[1] >= 3 && s_e[0] != 3 ? s_e[1] -= 3 : 0;
		if (s_e[0] >= 3)
		{
			ft_printf("\x1b[%dm%s\n", lemin->colour * 32, line);
			free(line);
			continue;
		}
		if (check_mistake_line(lemin, s_e, line, flag) == -1)
			return (freeret(line));
		if (*flag == 2 && set_links(lemin, s_e[1], line) == -1)
			return ((freeret(line) && check_xboct(lemin, s_e, flag)) - 2);
		add_to_mapinfo(lemin, line, *flag);
		custom_free((void*)(&line));
	}
	return (check_xboct(lemin, s_e, flag));
}

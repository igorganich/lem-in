/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 16:39:09 by iganich           #+#    #+#             */
/*   Updated: 2018/08/19 19:16:48 by iganich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		line_type(char *line, int *flag, int res, t_data *lemin)
{
	if (line[0] == ' ' || line[0] == '\0' || line[0] == 'L')
		return (-1);
	if (line[0] != '#')
		res = 0;
	if (line[0] == '#')
		res = 3;
	if (!ft_strcmp(line, "##status"))
		lemin->status_p = 1;
	else if (!ft_strcmp(line, "##path"))
		lemin->path_p = 1;
	else if (!ft_strcmp(line, "##colour"))
		lemin->colour = 1;
	else if (ft_strcmp(line, "##start") == 0)
		res = 4;
	else if (ft_strcmp(line, "##end") == 0)
		res = 5;
	else if (ft_strchr(line, ' ') && !ft_strchr(line, '-') && !(*flag))
		(*flag)++;
	if (lemin->ants <= 0)
		*flag = 0;
	if (!ft_strchr(line, ' ') && ft_strchr(line, '-') && *flag == 1)
		(*flag)++;
	if (res >= 4 && lemin->ants == 0)
		return (-1);
	return (res);
}

int		is_nbr_str(char *line)
{
	int i;

	i = 0;
	if (*line == '+' || *line == '-')
		line++;
	if (*line == '0' && ft_isdigit(line[1]))
		return (0);
	while (line[i] != ' ' && line[i])
	{
		if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	if (i > 7)
		return (0);
	if (*line == '-' && ft_atoi(line) >= 0)
		return (0);
	if (*line != '-' && ft_atoi(line) < 0)
		return (0);
	return (1);
}

int		set_ants(t_data *lemin, int s_e, char *line)
{
	if (s_e != 0)
		return (-1);
	if (lemin->ants != 0)
		return (-1);
	if (!is_nbr_str(line))
		return (-1);
	else if (line[0] != '-' && !ft_strchr(line, ' '))
		lemin->ants = ft_atoi(line);
	if (lemin->ants <= 0 || lemin->ants >= 1000000)
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:05:56 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/11/11 19:40:17 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_xmp(char *xpm, t_cub *data, int x)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (xpm[i] == ' ' || xpm[i] == '\t')
		i++;
	i += 2;
	while (xpm[i] && xpm[i] != '.')
	{
		if (xpm[i] != ' ' && xpm[i] != '\t')
			return (7);
		i++;
	}
	y = ft_strlen(xpm) - 1;
	if (i >= y)
		return (7);
	while (xpm[y] == ' ' || xpm[y] == '\t')
		y--;
	if (!y)
		return (7);
	data->xpm_file[x] = ft_substr(xpm, i, y - i + 1);
	return (1);
}

int	init_xpm(char *file, int i, t_cub *data)
{
	int	x;

	x = 0;
	if (file[i] == 'N' && file[i + 1] == 'O' && (file[i + 2] == ' '
			|| file[i + 2] == '\t'))
		x += set_xmp(file, data, 0);
	else if (file[i] == 'S' && file[i + 1] == 'O' && (file[i + 2] == ' '
			|| file[i + 2] == '\t'))
		x += set_xmp(file, data, 1);
	else if (file[i] == 'W' && file[i + 1] == 'E' && (file[i + 2] == ' '
			|| file[i + 2] == '\t'))
		x += set_xmp(file, data, 2);
	else if (file[i] == 'E' && file[i + 1] == 'A' && (file[i + 2] == ' '
			|| file[i + 2] == '\t'))
		x += set_xmp(file, data, 3);
	return (x);
}

int	init_map(char *file, t_cub *data)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (file[i] == ' ' || file[i] == '\t')
		i++;
	if (file[i] == 'N' || file[i] == 'S'
		|| file[i] == 'W' || file[i] == 'E')
		x += init_xpm(file, i, data);
	else if (file[i] == 'F' && (file[i + 1] == ' '
			|| file[i + 1] == '\t'))
		x += set_color(data, file, 'F');
	else if (file[i] == 'C' && (file[i + 1] == ' '
			|| file[i + 1] == '\t'))
		x += set_color(data, file, 'C');
	return (x);
}

int	check_all(t_cub *data)
{
	int	i;
	int	j;
	int	x;

	x = -1;
	i = 0;
	j = -1;
	data->xpm_file = malloc(sizeof(char *) * 5);
	data->xpm_file[4] = NULL;
	data->c_color = NULL;
	data->f_color = NULL;
	while (data->xpm_file[++x])
		data->xpm_file[x] = NULL;
	x = 0;
	while (data->file[++j])
		x += init_map(data->file[j], data);
	if (x != 6)
		return (0);
	return (1);
}

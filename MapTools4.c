/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTools4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:42:44 by mmoutawa          #+#    #+#             */
/*   Updated: 2022/11/11 19:42:54 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_color_value(char c, char *nb, t_cub *data)
{
	if (c == 'F' && !data->f_color)
		data->f_color = ft_split(nb, ',');
	else if (c == 'C' && !data->c_color)
		data->c_color = ft_split(nb, ',');
}

int	set_color(t_cub *data, char *color, char c)
{
	int		i;
	int		x;
	char	*nb;

	i = 0;
	x = ft_strlen(color) - 1;
	while (color[i] == ' ' || color[i] == '\t')
		i++;
	i++;
	while (color[i] == ' ' || color[i] == '\t')
		i++;
	if (i >= x || !ft_isdigit(color[i])
		|| (color[i - 1] != ' ' && color[i - 1] != '\t'))
		return (7);
	while (color[x] == ' ' || color[x] == '\t')
		x--;
	nb = ft_substr(color, i, x - i + 1);
	nb = check_nb(nb, 0, 0);
	if (!nb)
		return (7);
	set_color_value(c, nb, data);
	free(nb);
	return (1);
}

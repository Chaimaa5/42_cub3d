/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <cel-mhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:23:18 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/10/31 22:03:19 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_line(t_cub *data, double angle, int ray)
{
	double	step;

	if (fabs(data->deltax) > fabs(data->deltay))
		step = fabs(data->deltax);
	else
		step = fabs(data->deltay);
	data->pixelx = data->xpos;
	data->pixely = data->ypos;
	data->deltax /= step;
	data->deltay /= step;
	while (hitwall(data, data->pixelx, data->pixely))
	{	
		if (!ray)
			pixel_put(&data->img_3d, (data->pixelx / data->i_2d) * 20,
				(data->pixely / data->i_2d) * 20, 0x0000FF);
		data->pixelx += data->deltax;
		data->pixely += data->deltay;
	}
	data->player_dis = player_distance(data, angle);
	data->projection_plane = projection_plane();
	data->wall = wall_height(data);
}

void	render_player(t_cub *data, int r)
{
	double	angle;
	double	x1;
	double	y1;

	angle = 0;
	while (angle < 360)
	{
		x1 = r * cos(angle * PI / 180);
		y1 = r * sin(angle * PI / 180);
		pixel_put(&data->img_3d, (data->xpos / data->i_2d) * 20 + x1,
			(data->ypos / data->i_2d) * 20 + y1, 0x0000FF);
		angle += 0.01;
	}
}

void	render_square(t_cub *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (20))
	{
		j = 0;
		while (j < 20)
		{
			pixel_put(&data->img_3d, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	render_fov(t_cub *data)
{
	double	l;

	l = data->rotation_angle;
	data->deltax = (data->xpos + cos(l) * 1000) - data->xpos;
	data->deltay = (data->ypos + sin(l) * 1000) - data->ypos;
	render_line(data, 0, 0);
}

void	render_map(t_cub *data)
{
	int	i;
	int	j;

	j = 0;
	raycasting(data);
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == '1')
				render_square(data, 20 * i, 20 * j, 0x3F4A4F);
			i++;
		}
		j++;
	}
	render_player(data, 1);
	render_fov(data);
	mlx_put_image_to_window(data->mlx,
		data->mlx_win, data->img_3d.mlx_img, 0, 0);
}

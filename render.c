#include "cub3d.h"

void	render_line(t_cub *data,  float ray_angle)
{
	(void)ray_angle;

	float deltaX = data->ray.WallHitX - data->xpos;
	float deltaY = data->ray.WallHitY - data->ypos;
	int pixels = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	deltaX /= pixels;
	deltaY /= pixels; 
	float X = data->xpos;
	float Y = data->ypos;
	while(HitWall(data, X, Y))
	{
		pixel_put(&data->img_3D, (X / data->i_2D) * 20 , (Y / data->i_2D) * 20, 0x40E0D0);
		X += deltaX;
		Y += deltaY;
	} 
}
void	render_player(t_cub *data, int r)
{
	float	angle;
	float	x1;
	float	y1;
	angle = 0;
	while (angle < 360)
	{
		x1 = r * cos(angle * PI / 180);
		y1 = r * sin(angle * PI / 180);
		pixel_put(&data->img_3D, ((data->xpos / data->i_2D) * 20) + x1, ((data->ypos / data->i_2D) * 20) + y1, 0x40E0D0);
		angle += 0.01;
	}
}

void	render_square(t_cub *data, int x, int y, int color)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while(i < 50)
	{
		j = 0;
		while (j < 50)
		{
			pixel_put(&data->img_3D, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	render_map(t_cub *data)
{
	int i;
	int j;

	j = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == '1')
				render_square(data, 50 * i,50 * j, 0x3F4A4F);
			else if (data->map[j][i] == '0')
				render_square(data, 50 * i,50 * j, 0xFFFFFF);
			i++;
		}
		j++;
	}
	render_player(data, 8);
	// castAllRays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_3D.mlx_img, 0, 0);
	// mlx_destroy_image(data->mlx, data->img_3D.mlx_img);
}
#include "cub3d.h"

// void add_wall(t_cub *data)
// {
// 	double pos;
// 	int i = 0;
// 	pos = (1080 / 2) - (data->wall_height / 2);
	
// 	while(data->wall_height > i)
// 	{
// 		printf("ggg%f\n",pos);
// 		pixel_put(&data->img, pos, pos + i, 0x40E0D0);
// 		i++;
// 	}
// }

int lines_length(t_cub *data, double x, double y)
{
	if (data->map[(int)y / data->i_2D][(int)x / data->i_2D] == '1')
		return(0);
	return(1);
}

int line_length(t_cub *data, double x, double y)
{
	if (data->map[(int)y / (int)g_j][(int)x / (int)g_i] == '1')
	{
		// add_wall(data);
		return(0);
	}
	return(1);
}
void	render_line(t_cub *data, double deltaX, double deltaY, int color)
{

	double	pixelX;
	double	pixelY;
	int		pixels;
	(void)color;
	pixelX = data->xpos;
	pixelY = data->ypos;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	data->wall_size = (1080 / 2) / tan(30);
	// data->wall_height = (g_i / pixels) * data->wall_size;
	while (line_length(data, pixelX, pixelY))
	{	
	    // pixel_put(&data->img, pixelX, pixelY, color);
	    pixelX += deltaX;
	    pixelY += deltaY;
	}
	data->dis = sqrt(pow(pixelX - data->xpos, 2) + pow(pixelY - data->ypos, 2));
    data->wall = (g_i * WINDOW_HEIGHT) / data->dis;
	// data->wall = (WINDOW_HEIGHT /  data->dis) * data->wall_size;
}

void	render_lines(t_cub *data, double deltaX, double deltaY, int color)
{

	double	pixelX;
	double	pixelY;
	int		pixels;

	pixelX = data->xpos;
	pixelY = data->ypos;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	while (lines_length(data, pixelX, pixelY))
	{	
	    pixel_put(&data->img, pixelX, pixelY, color);
	    pixelX += deltaX;
	    pixelY += deltaY;
	}
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
		pixel_put(&data->img, (data->xpos) + x1, (data->ypos) + y1, 0x40E0D0);
		angle += 0.01;
	}
}

void	render_square(t_cub *data, int x, int y, int color)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while(i < (data->i_2D))
	{
		j = 0;
		while (j < data->i_2D)
		{
			pixel_put(&data->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	render_fov(t_cub *data)
{
	double	x;
	double	l;

	x = -PI / 6;
	l = data->rotation_angle;

	while (x < PI / 6)
	{
		render_line(data,(data->xpos + cos(l + x) * 1000) - data->xpos,(data->ypos + sin(l + x) * 1000) - data->ypos,  0x40E0D0);
		wall_projection(data);
		x += 0.005;
	}
	render_line(data,(data->xpos + cos(l) * 1000) - data->xpos,(data->ypos + sin(l) * 1000) - data->ypos,  0xE04080);
}

void	render_fov_2D(t_cub *data)
{
	double	x;
	double	l;

	x = -PI / 6;
	l = data->rotation_angle;
	while (x < PI / 6)
	{
		render_lines(data,(data->xpos + cos(l + x) * 1000) - data->xpos,(data->ypos + sin(l + x) * 1000) - data->ypos,  0x40E0D0);
		x += 0.005;
	}
	render_lines(data,(data->xpos + cos(l) * 1000) - data->xpos,(data->ypos + sin(l) * 1000) - data->ypos,  0xE04080);
}

void	render_map(t_cub *data)
{
	render_fov(data);
 	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_3D.mlx_img, 0, 0);
}

void	render_2D_map(t_cub *data)
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
				render_square(data,  data->i_2D * i, data->i_2D  * j, 0xFFFFFF);
			else if (data->map[j][i] == '0')
				render_square(data, data->i_2D * i, data->i_2D  * j, 0x000000);
			i++;
		}
		j++;
	}
	render_fov_2D(data);
	render_player(data, 5);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.mlx_img, 0, 0);
}
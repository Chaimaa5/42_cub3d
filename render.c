#include "cub3d.h"

int line_length(t_cub *data, double x, double y)
{
	
	if(data->map[(int)y / 50][(int)x / 50] == '1')
		return(0);
	return(1);
}

void	render_line(t_cub *data, double deltaX, double deltaY, int color)
{

	double pixelX = data->xpos;
	double pixelY = data->ypos;
	
	// deltaX = (data->xpos + cos(data->rotation_angle) * 1000) - data->xpos;
	// deltadY = (data->ypos + sin(data->rotation_angle) * 1000) - data->ypos;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	while (line_length(data, pixelX, pixelY))
	{		
	    mlx_pixel_put(data->mlx, data->mlx_win, pixelX, pixelY, color);
	    pixelX += deltaX;
	    pixelY += deltaY;
	}
}

void	render_player(t_cub *data, int r)
{
	double angle = 0, x1, y1;
	while(angle < 360)
	{
		x1 = r * cos(angle * PI / 180);
		y1 = r * sin(angle * PI / 180);
		mlx_pixel_put(data->mlx, data->mlx_win, (data->xpos) + x1, (data->ypos) + y1, 0x40E0D0);
		angle += 0.1;
	}
}

void	render_square(t_cub *data, int x, int y, int color)
{
	int i = 0, j = 0;
	while(i < 50)
	{
		j = 0;
		while(j < 50)
		{
			mlx_pixel_put(data->mlx, data->mlx_win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	render_fov(t_cub *data)
{
	double x = -PI / 9;
	double l = data->rotation_angle;
	while (x < PI / 9)
	{
		render_line(data,(data->xpos + cos(l + x) * 1000) - data->xpos,(data->ypos + sin(l + x) * 1000) - data->ypos,  0x40E0D0);
		x += 0.01;
	}
	render_line(data,(data->xpos + cos(l) * 1000) - data->xpos,(data->ypos + sin(l) * 1000) - data->ypos,  0xE04080);
}

void	render_map(t_cub *data)
{
	int i;
	int j = 0;

	while(data->map[j])
	{
		i = 0;
		while(data->map[j][i])
		{
			if(data->map[j][i] == '1')
				render_square(data, i * 50, j * 50, 0xFFFFFF);
			else if(data->map[j][i] == '0')
				render_square(data, i * 50, j * 50, 0x000000);
			i++;
		}
		j++;
	}
	render_fov(data);
	render_player(data, 5);
}
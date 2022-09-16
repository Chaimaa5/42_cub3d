#include "cub3d.h"
#include "math.h"

char	**read_map(int i)
{
	char	*map;
	char	*mapp;
	char	**p;
	int		y;

	y = 0;
	mapp = ft_strdup("");
	map = get_next_line(i);
	while (map)
	{
		mapp = ft_strjoin(mapp, map);
		free(map);
		map = get_next_line(i);
		y++;
	}
	p = ft_split(mapp, '\n');
	free(mapp);
	return (p);
}

void	draw_player(t_cub *data)
{
	int i = 0;
	int j = 0;
	while(data->map[j])
	{
		i = 0;
		while(data->map[j][i])
		{
			if(data->map[j][i] == 'N')
			{
				mlx_pixel_put(data->mlx, data->mlx_win, i*50, j*50, 0x00FF0000);
			}
			i++;
		}
		j++;
	}
}


void draw_line(t_cub *data, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX;
	double deltaY;
	double pixelX = beginX;
	double pixelY = beginY;
	
	deltaX = endX - beginX;
	deltaY = endY - beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	while (pixels)
	{
	    mlx_pixel_put(data->mlx, data->mlx_win, pixelX, pixelY, color);
	    pixelX += deltaX;
	    pixelY += deltaY;
	    --pixels;
	}
}

void	window(t_cub *data)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(data->map[0]);
	while (data->map[j])
		j++;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, i * 50, j * 50, "Cub3d!");
	draw_line(data, 10, 200, 1000, 2000, 0xFFFFFF);
	// mlx_key_hook(mlx_win, keys, data);
	// mlx_hook(mlx_win, 17, 0L, mouse, mlx);
	mlx_loop(data->mlx);
}

int main(int ac, char **av)
{
	int fd;
	t_cub data;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		data.map = read_map(fd);
		window(&data);
	}
}
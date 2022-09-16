#include "cub3d.h"

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

void	rotate(t_cub *data, double angle)
{
	double tmp;
	// render_square(data, data->xpos * 50, data->ypos * 50, 0x050505);
	tmp = ((data->xpos * cos(angle)) - (data->ypos * sin(angle)));
	data->ypos = ((data->xpos * sin(angle)) + (data->ypos * cos(angle)));
	data->xpos = tmp;
	render_player(data, 3);
	render_line(data, data->xpos * 50, data->ypos * 50, (data->xpos*50) + 50, (data->ypos*50) + 50);
}

int key_handler(int key, t_cub *data)
{
	if(key == KEY_UP)
		data->walk = 1;
	else if(key == KEY_DOWN)
		data->walk = -1;
	else if(key == KEY_RIGHT)
		data->side = 1;
	else if(key == KEY_LEFT)
		data->side = -1;
	return (0);	
}

void player_pos(t_cub *data)
{
	int i;
	int j;
	j = 0;
	data->side = 0;
	data->walk = 0;
	data->move_speed = 2.0;
	data->rotation_angle = PI / 2;
	data->rotation_speed = 2 * (PI / 180);
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == 'N')
			{
				data->xpos = i;
				data->ypos = j;				
			}
			i++;
		}
		j++;
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
	player_pos(data);
	render_map(data);
	render_player(data, 3);
	mlx_key_hook(data->mlx_win, key_handler, data);
	data->rotation_angle += data->side * data->rotation_speed;
	render_line(data, data->xpos , data->ypos, (data->xpos + cos(data->rotation_angle) * 30), (data->ypos + sin(data->rotation_angle) *30 ));
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
#ifndef CUB3D_H
#define CUB3D_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>
#include "inc/libft/libft.h"
#include "inc/gnl/get_next_line.h"
#include "mlx_keys.h"

#define PI 3.1415926535
#define PI2 1.5708 //pi/2
#define PI3 4.71239 //3pi/2
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define FOV 60 * (PI / 180)
#define WALL_STRIP_WIDTH 4
#define RAYS 1600 / 2
#define UP 1
#define DOWN 0
#define RIGHT 2
#define LEFT 3
typedef struct   s_img{
    void    *mlx_img;
    char    *addr;
    int     endian;
    int     bpp;
    int     line;
}   t_img;

typedef struct  s_texture{
    void    *texture;
    int     texX;
    int     texY;
    float  step;
    float  texPos;
    t_img   img;
    
}   t_texture;

typedef struct s_ray{
    float  HorizWalllDist;
    float  VerWalllDist;
    float VerWallHitX;
    float VerWallHitY;
    float HorizWallHitX;
    float HorizWallHitY;
    float yinter;
    float xinter;
    float xstep;
    float ystep;
    float VerWallHit;
    float HorizWallHit;
    float WallHitX;
    float WallHitY;
} t_ray;

typedef struct s_cub{
    void	*mlx;
    void	*mlx_win;
    char	**map;
    float  xpos;
    float  ypos;
	float	side;
	float	walk;
    float	rotation_angle;
	float	move_speed;
	float	rotation_speed;
    float  move_step;
    char    direction;
    float  player_dis;
    float  wall;
    int     i_2D;
    float  pixelX;
    float  pixelY;
    t_img   img_3D;
    t_texture tex;
    t_ray   ray;
}   t_cub;


void	render_line(t_cub *data,  float ray_angle);
void	render_player(t_cub *data, int r);
void	render_square(t_cub *data, int x, int y, int color);
void	render_map(t_cub *data);
void	check_map(char **map);
void	pixel_put(t_img *img, int x, int y, int color);
void    raycasting(t_cub *data);
void    player_pos(t_cub *data);
void    render_fov(t_cub *data);
char	**read_map(int i);
int     check_elements(char **map);
int     check_wall_collision(t_cub *data);
int     check_wall_collision_2D(t_cub *data);
int     get_pixel_color(t_texture *tex);
int     key_handler(int key, t_cub *data);
void    castAllRays(t_cub *data);
int		HitWall(t_cub *data, float HorzWallHitX, float HorzWallHitY);


#endif
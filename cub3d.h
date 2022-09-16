#ifndef CUB3D_H
#define CUB3D_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include "inc/libft/libft.h"
#include "inc/gnl/get_next_line.h"

#define PI 3.1415926535
typedef struct s_cub{
    void	*mlx;
    void	*mlx_win;
    char	**map;
}   t_cub;
#endif
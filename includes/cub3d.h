#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "../lib/mlx.h"

# define WIN_W 1920
# define WIN_H 1080

typedef struct s_player
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
}   t_player;

typedef struct s_data
{
    int fl_rgb;
    int cl_rgb;
    int cub_fd;
    int no_fd;
    int so_fd;
    int we_fd;
    int ea_fd;

	int		map_w;
	int		map_h;
	int		**map;
	void	*mlx_ptr;
	void	*win_ptr;
	int		img_w;
	int		img_h;
	void	*img;
	char	*addr;
	int		endian;
	int		line_length;
	int		bits_per_pixel;
    char    player_init_ori;
    double  init_x;
    double  init_y;
    t_player    *player;
}		t_data;

enum ERRORS
{
    DATA,
    PLAYER,
    INPUTERR,
    MAPNAME,
    CANTOPEN,
    IVALIDMAP,
    PATHERR  
};

enum DIRECTION
{
    NORTH,
    SOUTH,
    WEST,
    EAST 
};

/* ************************************************************************** */
/*                               MAIN_UTILS                                   */
/* ************************************************************************** */

/*Checks if the user input is correct (maximum 2 arguments)*/
void	check_user_input(int ac, char *s);



/* ************************************************************************** */
/*                             INIT_WINDOWS                                   */
/* ************************************************************************** */
/*Initialize values for struct cub, create window and first image*/
void	init_fields(t_data *cub);

/*Initialize all player infos*/
t_player *init_player(t_data *cub);

/*Define initial orientation of player*/
void init_orientation(t_player *player, char player_init_ori);

/*Define initial position of player*/
void init_position(t_player *player,int **map);

/* ************************************************************************** */
/*                                 RENDER                                     */
/* ************************************************************************** */

/*manages all window updates and updates based on input*/
void	run_window(t_data *cub);


/* ************************************************************************** */
/*                               HANDLERS                                     */
/* ************************************************************************** */

/*define behaviour for specific key pressed*/
int	key_detect(int key, t_data *cub);


/* ************************************************************************** */
/*                               CLOSING                                      */
/* ************************************************************************** */

/**/
int	close_win_free(t_data *cub);

/* ************************************************************************** */
/*                               FREEING                                      */
/* ************************************************************************** */

/**/
void	general_free(t_data *cub);



#endif
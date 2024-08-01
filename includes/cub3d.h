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
# include <stdbool.h>

# include "../lib/mlx.h"
# include "../libft/libft.h"

# define WIN_W 1920
# define WIN_H 1080
# define DG_RAD 0.0174533
typedef struct s_camera
{
    double cameraX;
    double rayDirX;
    double rayDirY;

}   t_camera;

typedef struct s_player
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    t_camera *cam;
    double fov;
    double player_ang;

}   t_player;

typedef struct s_data
{
    int cub_fd;
    /* header reading and info gathering */

    int count[6]; // order  = NO SO WE EA F C  conter[1] is SO  if it is 0 it stil availble to populate
    int fl_rgb[3]; //save F color
    int cl_rgb[3]; //save C color

    char *north;
    char *south;
    char *west;
    char *east;
    /*header done End  */

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
    PATHERR,
    CAMERA
};

enum DIRECTION
{
    NORTH,
    SOUTH,
    WEST,
    EAST,
    FLOOR,
    CEILING
};

/* ************************************************************************** */
/*                               MAIN_UTILS                                   */
/* ************************************************************************** */

/*Checks if the user input is correct (maximum 2 arguments)*/
bool	ft_cubfile(char *str);

/*Verifies file format .cub */
void	check_user_input(int ac, char *av, t_data *cub);

int		ft_strcmp(char *s1, char *s2);

/* ************************************************************************** */
/*                             INIT_WINDOWS                                   */
/* ************************************************************************** */
/*Initialize values for struct cub, create window and first image*/
int	init_fields(t_data *cub);

/*Initialize all player infos*/
t_player *init_player(t_data *cub);

/*Define initial orientation of player*/
void init_orientation(t_player *player, char player_init_ori);

/*Define initial position of player*/
void init_position(t_player *player,int **map);

void init_camera(t_data *cub);

void init_textures_to_null(t_data *cub);

/* ************************************************************************** */
/*                                 RENDER                                     */
/* ************************************************************************** */

/*manages all window updates and updates based on input*/
void	run_window(t_data *cub);
void    render(t_data *cub);


/* ************************************************************************** */
/*                               HANDLERS                                     */
/* ************************************************************************** */

/*define behaviour for specific key pressed*/
int	key_detect(int key, t_data *cub);

void control_rot(t_data *cub, int dir);

void control_trans(t_data *cub, int dir);


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

/* ************************************************************************** */
/*                               MINIMAPER                                    */
/* ************************************************************************** */

int minimaper(t_data *cub);

int	bresenham(t_data *img, double ang);

int	bresenham_wall(t_data *img, double x, double x1, double y, double y1);

int	max_finder(double varu, double varv);

/*This function only serves while we do not have a map*/
int minimaper_initial(t_data *cub);

int	bresenham(t_data *img, double ang);

int	bresenham_wall(t_data *img, double x, double x1, double y, double y1);

int	max_finder(double varu, double varv);

/*This function only serves while we do not have a map*/
int minimaper_initial(t_data *cub);

/* ************************************************************************** */
/*                               FILEREADER                                   */
/* ************************************************************************** */

/**/
void check_duplicates(t_data *cub, int id);
void fill_counter(t_data *cub, int id);
void save_path(char *line, t_data *cub, int id);
void save_rgb(char *line, t_data *cub, int id);
void get_scenic_id(char *str, t_data *cub);
void read_mapfile(t_data *cub, char *filename);

/* ************************************************************************** */
/*                            FILEREADER UTILS                                */
/* ************************************************************************** */

void is_fd_invalid(int fd, t_data *cub);
int ft_iswhitespace(int c);
int jump_whitepaces(char *line);

/* ************************************************************************** */
/*                                ERRORS                                      */
/* ************************************************************************** */

/*has a free and exit inside to terminate everything when displaying the error*/
void ft_error(int n, t_data *cub);

#endif
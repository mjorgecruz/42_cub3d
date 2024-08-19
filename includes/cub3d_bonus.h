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
# include <sys/time.h> 

# include "../lib/mlx.h"
# include "../libft/libft.h"

# define WIN_W 1920
# define WIN_H 1080
# define DG_RAD 0.0174533
# define FOV 2 * atan(0.66 / 1)

# define SPEED 0.002
# define ROT 0.025


typedef struct s_pov
{
	double deltaX; //distance to progress one unit in x
	double deltaY; //distance to progress one unit in x
	
	double dirX;
	double dirY;

	int mapX;
	int mapY;

	double sideDistX; //distance to the next edge in x
	double sideDistY; //distance to the next edge in y
	int stepX;
	int stepY;

	double hitX;
	double hitY;

}   t_pov;


typedef struct s_camera
{
	double cameraX;
	double rayDirX;
	double rayDirY;
	double planeX;
	double planeY;

	double r_deltaX; //distance to progress one unit in x
	double r_deltaY; 
	int r_mapX;
	int r_mapY;
	double r_sideDistX; //distance to the next edge in x
	double r_sideDistY; //distance to the next edge in y
	int r_stepX;
	int r_stepY;

}   t_camera;

typedef struct s_player
{
	double posX;
	double posY;

	t_camera *cam;
	double fov;
	double p_ang;
	int		prev_x;
	t_pov   *pov;

}   t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	char	*data;
	int		endian;
	int		line_length;
	int		bits_per_pixel;
	int		width;
	int		height;
}	t_img;

typedef struct s_door
{
	double	pos_x;
	double	pos_y;
	int		orientation;
	bool	open;
	int		status;
	double	position;
	double	speed;
	double	last_time;

}	t_door;

typedef struct s_keys
{
	int		rotate;
	int		back_front;
	int		left_right;
}	t_keys;

typedef struct s_data
{
	int cub_fd;
	/* header reading and info gathering */

    int count[6]; // order  = NO SO WE EA F C  count[1] is SO  if it is 0 it stil availble to populate
    int fl_rgb[3]; //save F color
    int cl_rgb[3]; //save C color
    int lc;

    char *north;
    char *south;
    char *west;
    char *east;
    bool in_map;

    char **line;
    int l_start;

	int		map_w;
	int		map_h;
	int		**map;
    int		**map_cpy;
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
	t_door		*doors;
	t_img		texNorth;
	t_img		texSouth;
	t_img		texEast;
	t_img		texWest;
	t_img		door;
	t_img		fire1;
	t_img		fire2;
	t_img		fire3;
	t_keys		keys;
}		t_data;

typedef struct s_castInfo
{
	int		yStart;
	int		yEnd;
	int		x;
	int		line_height;
	int		wallX;
}	t_castInfo;

typedef struct s_closest
{
	double	sidedistx;
	double	sidedisty;
	double	mapx;
	double	mapy;
}	t_closest;

enum ERRORS
{
	DATA,
	PLAYER,
	INPUTERR,
	MAPNAME,
	CANTOPEN,
	IVALIDMAP,
	MISSTEXT,
	PATHERR,
	MLX,
	WINDOW,
	CUBIMG,
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

void	tex_preparer(t_data *cub);

/* ************************************************************************** */
/*                             INIT_WINDOWS                                   */
/* ************************************************************************** */
/*Initialize values for struct cub, create window and first image*/
int	init_fields_bonus(t_data *cub);

/*Initialize all player infos*/
t_player *init_player(t_data *cub);

/*Define initial orientation of player*/
void init_orientation(t_player *player, char player_init_ori);

/*Define initial position of player*/
void	init_position_bonus(t_data *cub);

void	init_doors_bonus(t_data *cub, int count);

void	fill_door_info_bonus(t_data *cub, int door_num, int i, int j);

void	init_camera(t_player *player, t_data *cub);

void	textures_definer_bonus(t_data *cub);

void	texture_door_bonus(t_data *cub);

void	texture_fire_bonus(t_data *cub);

void	init_keys(t_data *cub);

/* ************************************************************************** */
/*                                 RENDER                                     */
/* ************************************************************************** */

/*manages all window updates and updates based on input*/
void	run_window_bonus(t_data *cub);

int		render_bonus(t_data *cub);

void	render_cel_gr(t_data *cub);

void	check_dirs(t_data *cub);

void	check_rots(t_data *cub);

/* ************************************************************************** */
/*                              RENDER_UTILS                                  */
/* ************************************************************************** */

void	pixel_put(t_data *data, int x, int y, int color);

int	    bresenham(t_data *img, double u1, double v1);

int	    max_finder(double varu, double varv);


/* ************************************************************************** */
/*                               HANDLERS                                     */
/* ************************************************************************** */

/*define behaviour for specific key pressed*/
int	key_detect(int key, t_data *cub);

int	key_undetect(int key, t_data *cub);

void control_rot(t_data *cub, int dir);

void control_trans(t_data *cub, int dir);

void control_door(t_data *cub);

void	control_sides(t_data *cub, int dir);

void 	animate_door_opening(t_data *cub, int door_num);


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

void    ft_free_split(char **array);


/* ************************************************************************** */
/*                               MINIMAPER                                    */
/* ************************************************************************** */

int     minimaper_bonus(t_data *cub);

void 	map_drawing_bonus(t_data *cub, int map_scale);

void    render_direction_bonus(t_data *cub);

void	hit_point_vertical(t_data *cub);

void	hit_point_horizontal(t_data *cub);

void 	hit_point_vertical_door(t_data *cub);

void 	hit_point_horizontal_door(t_data *cub);

/* ************************************************************************** */
/*                           MINIMAPER_RENDERS                                */
/* ************************************************************************** */

void	render_point_player(t_data *img, double pos_x, double pos_y);

void	render_rect_wall(t_data *img, int pos_x, int pos_y, int scale);

void	render_rect_ground(t_data *img, int pos_x, int pos_y, int scale);

void	render_rect_door(t_data *img, double pos_x, double pos_y, int scale);

void	render_h_door(t_data *img, int door_num, int scale);

void	render_v_door(t_data *img, int door_num, int scale);

/* ************************************************************************** */
/*                             MINIMAPER_UTILS                                */
/* ************************************************************************** */

void	direction_calc(t_data *cub, double ang);

void	delta_calc(t_data *cub);

void	step_calc(t_data *cub);

int		side_calc(t_data *cub);

int 	distance_doors(t_data *cub, int *side);

int 	distance_doors_within(t_data *cub, int *side);

int		search_door(t_data *cub, double x, double y);

/* ************************************************************************** */
/*                                RAYCASTER                                   */
/* ************************************************************************** */

void 	display_bonus(t_data *cub);

void	camera_calculations(t_data *cub, int x);

void	wall_displayer(t_data *cub, int x);

void	door_displayer(t_data *cub, int x);

/* ************************************************************************** */
/*                               RAYCASTER_2                                  */
/* ************************************************************************** */

int		side_calc_ray(t_data *cub);

int		smaller_x_step(t_data *cub);

int		smaller_y_step(t_data *cub);

int		side_calc_ray_bonus(t_data *cub, int x);

/* ************************************************************************** */
/*                               RAYCASTER_3                                  */
/* ************************************************************************** */

int 	distance_doors_cam(t_data *cub, int *side, int x);

int		raycaster_recursive(t_data *cub, int x);

t_closest	temp_var_holder(t_data *cub);

int		door_side_calc_x(t_data *cub);

int		door_side_calc_y(t_data *cub);

/* ************************************************************************** */
/*                               RAYCASTER_4                                  */
/* ************************************************************************** */

int 	distance_doors_within_cam(t_data *cub, int *side, int x);

/* ************************************************************************** */
/*                             RAYCASTER_UTILS                                */
/* ************************************************************************** */

void	delta_calc_ray(t_data *cub);

void	step_calc_ray(t_data *cub);

int		line_display(t_data *cub, int x, double wallDist, int side);

int		line_display_door(t_data *cub, int x, double wallDist, int side);

/* ************************************************************************** */
/*                            RAYCASTER_UTILS_2                               */
/* ************************************************************************** */

int		line_to_print(t_data *cub, int door_num, double walldist);

int 	wallX_calculator(t_data *cub, double wallDist, int side);

int		wallx_calculator_door(t_data *cub, double wallDist, int side, int door_num);

int		line_maker(t_data *cub, t_castInfo line_prop, int side);

void	liner(t_data *cub, t_castInfo line_prop, t_img tex);

/* ************************************************************************** */
/*                               FILEREADER                                   */
/* ************************************************************************** */

void check_scenics_count(t_data *cub);
void check_scenics(t_data *cub);

void check_duplicates(t_data *cub, int id);
void fill_counter(t_data *cub, int id);
void save_path(char *line, t_data *cub, int id);
void get_scenic_id(t_data *cub, int i);
bool has_reached_map(char *line, t_data *cub);
void read_mapfile(t_data *cub, char *filename);
void read_lines(t_data *cub);

void    check_xpm_exist(t_data *cub);

/* ************************************************************************** */
/*                                MAP_BUILD                                   */
/* ************************************************************************** */

void    get_map_size(t_data *cub);
void    build_map(t_data *cub);
void    make_map_copy(t_data *cub);

/* ************************************************************************** */
/*                                    RGB                                     */
/* ************************************************************************** */

int     ft_confirm_line_rgb(char *color);
void    validate_rgb(char **color, t_data *cube);
void    get_rgb_fr_str(char *line, t_data *cub, int id);
void    check_color_range(t_data *cub);
void    save_rgb(char *line, t_data *cub, int id);

/* ************************************************************************** */
/*                            FILEREADER UTILS                                */
/* ************************************************************************** */

bool is_valid_orient(int c);
bool is_empty_line(char *str);
void is_fd_invalid(int fd, t_data *cub);
int ft_iswhitespace(int c);
int jump_whitepaces(char *line);


/* ************************************************************************** */
/*                               PARSER_CUB                                   */
/* ************************************************************************** */

void    get_player_pos(t_data *cub);
void    map_space(t_data *cub);
int     floodfill_bonus(t_data *cub, int x, int y, int targ, int new);
void    parser_first_bonus(t_data *cub);

/* ************************************************************************** */
/*                                  ERRORS                                    */
/* ************************************************************************** */

/*has a free and exit inside to terminate everything when displaying the error*/
void ft_error(int n, t_data *cub);

/* ************************************************************************** */
/*                                  TESTS                                     */
/* ************************************************************************** */

void PRINT_COLOR_MAPCPY(t_data *cub);
void PRINT_COLOR_MAP(t_data *cub);
void color_select(int i);
void print_scenics(t_data *cub);

/* ************************************************************************** */
/*                              CONTROLS_BONUS                                */
/* ************************************************************************** */

int	handle_mouse_move(int x, int y, t_data *cub);

/* ************************************************************************** */
/*                                ANIMATION	                                  */
/* ************************************************************************** */

void 	animate_door_opening(t_data *cub, int door_num);

void	update_door_position(t_door *door);

/* ************************************************************************** */
/*                              ANIMATION_UTILS	                              */
/* ************************************************************************** */

long	get_time(void);


#endif
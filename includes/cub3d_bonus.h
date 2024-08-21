/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:40:05 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/21 13:15:09 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
# define FOV 1.16674601
# define SPEED 0.002
# define ROT 0.025

typedef struct s_pov
{
	double	deltax;
	double	deltay;
	double	dirx;
	double	diry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	int		stepx;
	int		stepy;
	double	hitx;
	double	hity;
}		t_pov;

typedef struct s_camera
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	planex;
	double	planey;
	double	r_deltax;
	double	r_deltay;
	int		r_mapx;
	int		r_mapy;
	double	r_sidedistx;
	double	r_sidedisty;
	int		r_stepx;
	int		r_stepy;
}		t_camera;

typedef struct s_player
{
	double		posx;
	double		posy;
	t_camera	*cam;
	double		fov;
	double		p_ang;
	int			prev_x;
	t_pov		*pov;

}		t_player;

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
	double	current_time;
}	t_door;

typedef struct s_fire
{
	double	pos_x;
	double	pos_y;
	int		drawn;
}		t_fire;

typedef struct s_keys
{
	int		rotate;
	int		back_front;
	int		left_right;
}		t_keys;

typedef struct s_data
{
	int			cub_fd;
	int			count[6];
	int			fl_rgb[3];
	int			cl_rgb[3];
	int			lc;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	bool		in_map;
	char		**line;
	int			l_start;
	int			map_w;
	int			map_h;
	int			**map;
	int			**map_cpy;
	void		*mlx_ptr;
	void		*win_ptr;
	int			img_w;
	int			img_h;
	void		*img;
	char		*addr;
	int			endian;
	int			line_length;
	int			bits_per_pixel;
	char		player_init_ori;
	double		init_x;
	double		init_y;
	t_player	*player;
	t_door		*doors;
	t_img		texnorth;
	t_img		texsouth;
	t_img		texeast;
	t_img		texwest;
	t_img		door;
	t_img		fire1;
	t_img		fire2;
	t_img		fire3;
	t_fire		*fires;
	int			fire_num;
	double		fire_last_time;
	double		u;
	double		v;
	double		invdet;
	t_keys		keys;
}		t_data;

typedef struct s_castInfo
{
	int		ystart;
	int		yend;
	int		x;
	int		line_height;
	int		wallx;
}		t_castInfo;

typedef struct s_closest
{
	double	sidedistx;
	double	sidedisty;
	double	mapx;
	double	mapy;
}		t_closest;

enum e_ERRORS
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
	CAMERA,
	MEMERR,
	SCENIC,
	RGBS
};

enum e_DIRECTION
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING
};

/* ************************************************************************** */
/*                                 DOORS 2                                    */
/* ************************************************************************** */

void		door_pos_hor_helper(t_data *cub);
int			distance_doors(t_data *cub, int *side);
int			distance_doors_within(t_data *cub, int *side);
void		door_math_helper(t_data *cub);
void		door_neg_ver_helper(t_data *cub);

/* ************************************************************************** */
/*                                 DOORS                                      */
/* ************************************************************************** */

int			door_side_calc_x_mini(t_data *cub);
int			door_side_calc_y_mini(t_data *cub);
int			door_calc_within_x_mini(t_data *cub);
int			door_calc_within_y_mini(t_data *cub);
void		ctrl_sid_dirposhelper(t_data *cub);

/* ************************************************************************** */
/*                               MAIN_UTILS                                   */
/* ************************************************************************** */

void		check_user_input(int ac, char *av, t_data *cub);
bool		ft_cubfile(char *str);
int			ft_strcmp(char *s1, char *s2);
void		tex_preparer(t_data *cub);
void		field_filler(t_data *cub);

/* ************************************************************************** */
/*                             INIT_WINDOWS                                   */
/* ************************************************************************** */

void		init_camera(t_player *player, t_data *cub);
void		textures_definer_bonus(t_data *cub);
void		texture_fire_bonus(t_data *cub);
int			init_pos_bonus_helper(t_data *cub);

/* ************************************************************************** */
/*                             INIT_WINDOWS 2                                 */
/* ************************************************************************** */

int			init_fields_bonus(t_data *cub);
t_player	*init_player(t_data *cub);
void		init_orientation(t_player *player, char player_init_ori);
void		init_doors_bonus(t_data *cub, int count);
void		fill_door_info_bonus(t_data *cub, int door_num, int i, int j);

/* ************************************************************************** */
/*                             INIT_WINDOWS 3                                 */
/* ************************************************************************** */

void		init_keys(t_data *cub);
void		texture_door_bonus(t_data *cub);
void		init_position_bonus(t_data *cub);
void		init_fires_bonus(t_data *cub, int count);
void		fill_fire_info_bonus(t_data *cub, int num, int i, int j);

/* ************************************************************************** */
/*                                 RENDER                                     */
/* ************************************************************************** */

/*manages all window updates and updates based on input*/
void		pixel_put(t_data *data, int x, int y, int color);
int			bresenham(t_data *img, double u1, double v1);
int			max_finder(double varu, double varv);

/* ************************************************************************** */
/*                              RENDER_UTILS                                  */
/* ************************************************************************** */

void		run_window_bonus(t_data *cub);
int			render_bonus(t_data *cub);
void		render_cel_gr(t_data *cub);
void		check_dirs(t_data *cub);
void		check_rots(t_data *cub);

/* ************************************************************************** */
/*                               HANDLERS                                     */
/* ************************************************************************** */

int			key_detect(int key, t_data *cub);
int			key_undetect(int key, t_data *cub);
void		control_rot(t_data *cub, int dir);
void		control_trans(t_data *cub, int dir);
void		ctrl_trans_helper(t_data *cub);
void		ctrl_trans_helper_neg(t_data *cub);

/* ************************************************************************** */
/*                               HANDLERS  2                                  */
/* ************************************************************************** */

void		control_trans_dirpos(t_data *cub);
void		control_trans_dirneg(t_data *cub);
void		tester_pos_trans(t_data *cub, int finalx, int finaly);
void		door_col_t_pos_ver(t_data *cub, int door_num);
void		door_col_t_pos_hor(t_data *cub, int door_num);

/* ************************************************************************** */
/*                               HANDLERS  3                                  */
/* ************************************************************************** */

void		tester_neg_trans(t_data *cub, int finalx, int finaly);
void		door_col_t_neg_ver(t_data *cub, int door_num);
void		door_col_t_neg_hor(t_data *cub, int door_num);
void		control_sides(t_data *cub, int dir);
void		control_sides_dirpos(t_data *cub);

/* ************************************************************************** */
/*                               HANDLERS  4                                  */
/* ************************************************************************** */

void		tester_side_pos(t_data *cub, int finalx, int finaly);
void		door_col_s_pos_ver(t_data *cub, int door_num);
void		door_col_s_pos_hor(t_data *cub, int door_num);
void		control_sides_dirneg(t_data *cub);
void		tester_side_neg(t_data *cub, int finalx, int finaly);

/* ************************************************************************** */
/*                               HANDLERS  5                                  */
/* ************************************************************************** */

void		door_col_s_neg_ver(t_data *cub, int door_num);
void		door_col_s_neg_hor(t_data *cub, int door_num);
void		control_door(t_data *cub);
int			control_door_rest(t_data *cub, double ang);
void		help_dor_col_t(t_data *cub);

/* ************************************************************************** */
/*                               HANDLERS  6                                  */
/* ************************************************************************** */

void		ctrl_trans_helper_neg(t_data *cub);
void		math_helper_door1(t_data *cub);
void		math_helper_door2(t_data *cub);
void		math_helper_door3(t_data *cub);
void		math_door4_helper(t_data *cub);

/* ************************************************************************** */
/*                               CLOSING                                      */
/* ************************************************************************** */

/**/
int			close_win_free(t_data *cub);

/* ************************************************************************** */
/*                               FREEING                                      */
/* ************************************************************************** */

/**/
void		ft_free_split(char **array);
void		general_free(t_data *cub);
void		ft_free_array(t_data *cub, int **array);
void		free_mlx_checker(t_data *cub);

/* ************************************************************************** */
/*                               MINIMAPER                                    */
/* ************************************************************************** */

int			minimaper_bonus(t_data *cub);
void		map_drawing_bonus(t_data *cub, int map_scale);
void		render_direction_bonus(t_data *cub);
void		hit_point_vertical(t_data *cub);
void		hit_point_horizontal(t_data *cub);

/* ************************************************************************** */
/*                           MINIMAPER_RENDERS                                */
/* ************************************************************************** */

void		render_point_player(t_data *img, double pos_x, double pos_y);
void		render_rect_wall(t_data *img, int pos_x, int pos_y, int scale);
void		render_rect_ground(t_data *img, int pos_x, int pos_y, int scale);
void		render_rect_door(t_data *img, \
			double pos_x, double pos_y, int scale);
void		render_h_door(t_data *img, int door_num, int scale);

/* ************************************************************************** */
/*                           MINIMAPER_RENDERS 2                              */
/* ************************************************************************** */

void		render_v_door(t_data *img, int door_num, int scale);

/* ************************************************************************** */
/*                             MINIMAPER_UTILS                                */
/* ************************************************************************** */

void		direction_calc(t_data *cub, double ang);
void		delta_calc(t_data *cub);
void		step_calc(t_data *cub);

/* ************************************************************************** */
/*                          MINIMAPER_EXTRA_UTILS                             */
/* ************************************************************************** */

void		hit_point_vertical_door(t_data *cub);
void		hit_point_horizontal_door(t_data *cub);

/* ************************************************************************** */
/*                           MINIMAPER_HELPERS                                */
/* ************************************************************************** */

int			side_calc_helper(t_data *cub);
int			side_calc_helper_2(t_data *cub);
int			side_calc(t_data *cub);
int			search_door(t_data *cub, double x, double y);
int			search_fire(t_data *cub, double x, double y);

/* ************************************************************************** */
/*                                RAYCASTER                                   */
/* ************************************************************************** */

void		display_bonus(t_data *cub);
void		camera_calculations(t_data *cub, int x);
void		wall_displayer(t_data *cub, int x);
void		sprite_displayer(t_data *cub, int x);

/* ************************************************************************** */
/*                               RAYCASTER_2                                  */
/* ************************************************************************** */

int			side_calc_ray(t_data *cub);
int			smaller_x_step(t_data *cub);
int			smaller_y_step(t_data *cub);
int			side_calc_ray_bonus(t_data *cub, int x);

/* ************************************************************************** */
/*                               RAYCASTER_3                                  */
/* ************************************************************************** */

int			distance_sprites_cam(t_data *cub, int *side, int x);
int			raycaster_recursive(t_data *cub, int x);
t_closest	temp_var_holder(t_data *cub);
int			door_side_calc_x(t_data *cub);
int			door_side_calc_y(t_data *cub);

/* ************************************************************************** */
/*                               RAYCASTER_4                                  */
/* ************************************************************************** */

int			distance_doors_within_cam(t_data *cub, int *side, int x);
void		math_helper_door5(t_data *cub);

/* ************************************************************************** */
/*                               RAYCASTER_5                                  */
/* ************************************************************************** */

int			fire_calc(t_data *cub, int num);
int			wallx_calculator(t_data *cub, double walldist, int side);
int			wallx_calculator_door(t_data *cub, double walldist, \
			int side, int door_num);

/* ************************************************************************** */
/*                             RAYCASTER_UTILS                                */
/* ************************************************************************** */

void		delta_calc_ray(t_data *cub);
void		step_calc_ray(t_data *cub);
int			line_display(t_data *cub, int x, double walldist, int side);
int			line_display_door(t_data *cub, int x, double walldist, int side);
int			line_display_fire(t_data *cub, int x, double walldist, int side);

/* ************************************************************************** */
/*                            RAYCASTER_UTILS_2                               */
/* ************************************************************************** */

int			line_to_print(t_data *cub, int door_num, double walldist);
int			line_maker(t_data *cub, t_castInfo line_prop, int side);
void		liner(t_data *cub, t_castInfo line_prop, t_img tex);
void		liner_fire(t_data *cub, t_castInfo line_prop, int pos);

/* ************************************************************************** */
/*                               FILEREADER                                   */
/* ************************************************************************** */

void		save_path(char *line, t_data *cub, int id);
bool		has_reached_map(char *line, t_data *cub);
void		read_mapfile(t_data *cub, char *filename);
void		read_lines(t_data *cub);
void		check_xpm_exist(t_data *cub);

/* ************************************************************************** */
/*                            FILEREADER UTILS                                */
/* ************************************************************************** */

bool		is_valid_orient(int c);
bool		is_empty_line(char *str);
void		is_fd_invalid(int fd, t_data *cub);
int			ft_iswhitespace(int c);
int			jump_whitepaces(char *line);

/* ************************************************************************** */
/*                            FILEREADER UTILS 2                              */
/* ************************************************************************** */

void		check_scenics_count(t_data *cub);
void		check_scenics(t_data *cub);
void		check_duplicates(t_data *cub, int id);
void		fill_counter(t_data *cub, int id);
void		get_scenic_id(t_data *cub, int i);

/* ************************************************************************** */
/*                            FILEREADER XPM                                  */
/* ************************************************************************** */

bool		is_xpm_file(char *xpm);
bool		compare_id_xpm(char *xpm);
bool		check_texture_match(char *xpm);
bool		check_texture_str(char *xpm);
void		check_xpm_format(t_data *cub);

/* ************************************************************************** */
/*                                MAP_BUILD                                   */
/* ************************************************************************** */

void		get_map_size(t_data *cub);
void		build_map(t_data *cub);
void		make_map_copy(t_data *cub);

/* ************************************************************************** */
/*                                    RGB                                     */
/* ************************************************************************** */

int			ft_confirm_line_rgb(char *color);
void		validate_rgb(char **color, t_data *cub);
void		get_rgb_fr_str(char *line, t_data *cub, int id);
void		check_color_range(t_data *cub);
void		save_rgb(char *line, t_data *cub, int id);

/* ************************************************************************** */
/*                               PARSER_CUB                                   */
/* ************************************************************************** */

void		get_player_pos(t_data *cub);
void		map_space(t_data *cub);
int			floodfill(t_data *cub, int x, int y, int targ);
void		parser_first(t_data *cub);

/* ************************************************************************** */
/*                                  ERRORS                                    */
/* ************************************************************************** */

/*has a free and exit inside to terminate everything when displaying the error*/
void		ft_perror(char *msg);
void		ft_error_plus(int n, t_data *cub);
void		ft_error(int n, t_data *cub);

/* ************************************************************************** */
/*                                  TESTS                                     */
/* ************************************************************************** */

void		print_color_mapcpy(t_data *cub);
void		print_color_map(t_data *cub);
void		color_select(int i);
void		print_scenics(t_data *cub);
char		*clear_path(char *line);

/* ************************************************************************** */
/*                              CONTROLS_BONUS                                */
/* ************************************************************************** */

int			handle_mouse_move(int x, int y, t_data *cub);

/* ************************************************************************** */
/*                                ANIMATION	                                  */
/* ************************************************************************** */

void		animate_door_opening(t_data *cub, int door_num);
void		update_door_position(t_door *door);
void		update_fire(t_data *cub);

/* ************************************************************************** */
/*                              ANIMATION_UTILS	                              */
/* ************************************************************************** */

long		get_time(void);

/*fim*/

void		render_rect_fire(t_data *img, \
			double pos_x, double pos_y, int scale);

int			draw_fire(t_data *cub, double wallDist, int num, int x);

#endif
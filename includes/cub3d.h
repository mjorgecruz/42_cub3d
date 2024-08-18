/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:16:40 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/18 11:28:59 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define WIN_W 1080
# define WIN_H 1080
# define DG_RAD 0.0174533
# define FOV 1.16674601

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

}	t_camera;

typedef struct s_player
{
	double		posx;
	double		posy;
	t_camera	*cam;
	double		fov;
	double		p_ang;
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

}	t_door;

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
	double		u;
	double		v;
	t_player	*player;
	t_door		*doors;
	t_img		texnorth;
	t_img		texsouth;
	t_img		texeast;
	t_img		texwest;
	t_img		door;
}		t_data;

typedef struct s_castInfo
{
	int		ystart;
	int		yend;
	int		x;
	int		line_height;
	int		wallx;
}	t_castInfo;

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

/*Initialize values for struct cub, create window and first image*/
int			init_fields(t_data *cub);

/*Define initial orientation of player*/
void		init_orientation(t_player *player, char player_init_ori);

/*Define initial position of player*/
void		init_position(t_data *cub);

void		init_camera(t_player *player, t_data *cub);

void		textures_definer(t_data *cub);

/* ************************************************************************** */
/*                                 RENDER                                     */
/* ************************************************************************** */

/*manages all window updates and updates based on input*/
void		run_window(t_data *cub);

void		render(t_data *cub);

void		render_cel_gr(t_data *cub);

/* ************************************************************************** */
/*                              RENDER_UTILS                                  */
/* ************************************************************************** */

void		pixel_put(t_data *data, int x, int y, int color);

int			bresenham(t_data *img, double u1, double v1);

int			max_finder(double varu, double varv);

/* ************************************************************************** */
/*                               HANDLERS                                     */
/* ************************************************************************** */

/*define behaviour for specific key pressed*/
int			key_detect(int key, t_data *cub);

void		control_rot(t_data *cub, int dir);

void		control_trans(t_data *cub, int dir);

/* ************************************************************************** */
/*                               CLOSING                                      */
/* ************************************************************************** */

/*closes mlxs and cleares all alocated memory in the running program*/
int			close_win_free(t_data *cub);

/* ************************************************************************** */
/*                               FREEING                                      */
/* ************************************************************************** */

void		ft_free_split(char **array);

void		ft_free_array(t_data *cub, int **array);

void		ft_free_struct_a(t_data *cub);

void		general_free(t_data *cub);

/* ************************************************************************** */
/*                               MINIMAPER                                    */
/* ************************************************************************** */

int			minimaper(t_data *cub);

void		map_drawing(t_data *cub, int map_scale);

void		render_direction(t_data *cub);

void		hit_point_vertical(t_data *cub);

void		hit_point_horizontal(t_data *cub);

/* ************************************************************************** */
/*                           MINIMAPER_RENDERS                                */
/* ************************************************************************** */

void		render_point_player(t_data *img, double pos_x, double pos_y);

void		render_rect_wall(t_data *img, int pos_x, int pos_y, int scale);

void		render_rect_ground(t_data *img, int pos_x, int pos_y, int scale);

/* ************************************************************************** */
/*                             MINIMAPER_UTILS                                */
/* ************************************************************************** */

void		direction_calc(t_data *cub, double ang);

void		delta_calc(t_data *cub);

void		step_calc(t_data *cub);

int			side_calc(t_data *cub);

/* ************************************************************************** */
/*                                RAYCASTER                                   */
/* ************************************************************************** */

void		calculus_display(t_data *cub, double x);

void		display(t_data *cub);

void		delta_calc_ray(t_data *cub);

void		step_calc_ray(t_data *cub);

/* ************************************************************************** */
/*                              RAYCASTER_CONT                                */
/* ************************************************************************** */

int			side_calc_ray(t_data *cub);

int	smaller_x_step(t_data *cub);

int	smaller_y_step(t_data *cub);

/* ************************************************************************** */
/*                             RAYCASTER_CONT_2                               */
/* ************************************************************************** */

int			line_display(t_data *cub, int x, double wallDist, int side);

int			wallx_calculator(t_data *cub, double wallDist, int side);

int			line_maker(t_data *cub, t_castInfo line_prop, int side);

void		liner(t_data *cub, t_castInfo line_prop, t_img tex);

/* ************************************************************************** */
/*                               FILEREADER                                   */
/* ************************************************************************** */

void		save_path(char *line, t_data *cub, int id);

bool		has_reached_map(char *line, t_data *cub);

void		read_mapfile(t_data *cub, char *filename);

void		read_lines(t_data *cub);

void		check_xpm_exist(t_data *cub);

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

void		validate_rgb(char **color, t_data *cube);

void		get_rgb_fr_str(char *line, t_data *cub, int id);

void		check_color_range(t_data *cub);

void		save_rgb(char *line, t_data *cub, int id);

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
/*                               PARSER_CUB                                   */
/* ************************************************************************** */

void		get_player_pos(t_data *cub);

void		map_space(t_data *cub);

int			floodfill(t_data *cub, int x, int y, int targ);

void		parser_first(t_data *cub);

/* ************************************************************************** */
/*                                  PLAYER                                    */
/* ************************************************************************** */

t_player	*init_player(t_data *cub);

/* ************************************************************************** */
/*                                  ERRORS                                    */
/* ************************************************************************** */

/* prints error message to the standard output*/
void		ft_perror(char *msg);

/*has a free and exit inside to terminate everything when displaying the error*/
void		ft_error(int n, t_data *cub);

/* ************************************************************************** */
/*                                  TESTS                                     */
/* ************************************************************************** */

/*cleares texture path from empty spaces at the end*/
char		*clear_path(char *line);

/*testers printing some parser and structure data*/
void		print_color_mapcpy(t_data *cub);

void		print_color_map(t_data *cub);

void		color_select(int i);

void		print_scenics(t_data *cub);

#endif
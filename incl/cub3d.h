#ifndef CUB3D_H
# define CUB3D_H
# include "colors.h"
# include "terminal_colors.h"
# include "MLX42/MLX42.h"
# include "../lib/libft/get_next_line.h"
# include "../lib/libft/libft.h"
# include <stdio.h>
# include <math.h>

# define FAIL 0
# define SUCCESS 1
# define FALSE 0
# define TRUE 1

# define WIDTH 1280
# define HEIGHT 720

# define MAP_ALL_ELEMENTS "NSWE 01"
# define MAP_DIRECTIONS "NSWE"
# define MAP_ELEMENTS "01"

# define NORTH 'N'
# define SOUTH 'S'
# define WEST 'W'
# define EAST 'E'

# define EMPTY '0'
# define WALL '1'

# define MOVEMENT_SPEED 0.1
# define ROTATION_SPEED 0.1

# define MINIMAP_SIZE_PERCENTAGE 40
# define MINIMAP_COLOR_PLAYER YELLOW
# define MINIMAP_COLOR_EMPTY GRAY
# define MINIMAP_COLOR_FLOOR BLACK
# define MINIMAP_COLOR_WALL GRAY

enum elements
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
};

// prototype map_node_t
typedef struct map_node_s map_node_t;

typedef struct texture_s
{
	char	*path;
	int		*img;
	int		width;
	int		height;
}			texture_t;

typedef struct vector_s
{
	int	x;
	int	y;
}		vector_t;

typedef struct dvector_t
{
	double	x;
	double	y;
}			dvector_t;

typedef struct player_s
{
	dvector_t	pos;
	dvector_t	new_pos;
	dvector_t	dir;
	double		angle;
	double		movement_angle;
	int			is_walking;
	int			is_strafing;
}				player_t;

typedef struct map_node_s
{
	char		*line;
	map_node_t	*next;
}			map_node_t;

typedef struct keypress_s
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}			keypress_t;

typedef struct minimap_s
{
	vector_t	pos;
	int			width;
	int			height;
	int			size_percentage;
	int			tile_size;
	int			color;
}			minimap_t;

typedef struct cub3d_s
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	keypress_t	keys;
	player_t	player;
	double		fov;
	vector_t	starting_pos;
	char		starting_dir;
	minimap_t	minimap;
	map_node_t	*map_list;
	int			nodes;
	char		**map;
	int			map_rows;
	int			map_columns;
	texture_t	texture[4];
	int			floor_color;
	int			ceiling_color;
	int			element_found[6];
}			cub3d_t;

// main.c
void free_info(char **info);
int err(char *error_message);

// color.c
int get_rgba(int r, int g, int b, int a);
int get_r(int rgba);
int get_g(int rgba);
int get_b(int rgba);
int get_a(int rgba);

// flooding_algorithm.c
int check_map_validity(char **map);

// get_color.c
int get_color(cub3d_t *cub3d, int element, char **info);

// get_elements.c
int all_elements_found(int *element_found);
void remove_newline(char *line);
int get_elements(cub3d_t *cub3d, int fd);

// get_map.c
int read_cub_file(cub3d_t *cub3d, char *map_path);

// get_texture.c
int get_texture(cub3d_t *cub3d, int element, char **info);

// init_cub3d.c
int init_cub3d(cub3d_t *cub3d);

// handle_close.c
void handle_close_window(void *param);
void handle_escape_key(mlx_key_data_t *keydata, mlx_t *mlx);

// math.c
double to_radians(double degrees);

// minimap.c
void minimap(cub3d_t *cub3d);

// player_movement.c
void player_movement(cub3d_t *cub3d);

// start_game.c
void start_game(cub3d_t *cub3d);

// extra.c
void print_info(cub3d_t *cub3d);
void print_array(char **array, char  *name);
void print_map(char **map);
void test(void);

#endif

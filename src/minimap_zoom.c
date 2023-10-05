#include "../incl/cub3d.h"

int hover_minimap(cub3d_t *cub3d)
{
	int mouse_x;
	int mouse_y;

	mlx_get_mouse_pos(cub3d->mlx, &mouse_x, &mouse_y);
	return (mouse_x >= cub3d->minimap.pos.x
			&& mouse_x <= cub3d->minimap.pos.x + cub3d->minimap.width
			&& mouse_y >= cub3d->minimap.pos.y
			&& mouse_y <= cub3d->minimap.pos.y + cub3d->minimap.height);
}

void zoom_in_minimap(cub3d_t *cub3d)
{
	int new_size_percentage;
	unsigned int new_width;
	unsigned int new_height;
	unsigned int new_tile_size;
	vector_t new_pos;

	new_size_percentage = cub3d->minimap.size_percentage + MINIMAP_ZOOM_INCREMENT;
	if (new_size_percentage > MINIMAP_MAX_SIZE_PERCENTAGE)
		new_size_percentage = MINIMAP_MAX_SIZE_PERCENTAGE;
	new_tile_size = count_minimap_tilesize(cub3d, new_size_percentage);
	new_width = new_tile_size * cub3d->map_columns;
	new_height = new_tile_size * cub3d->map_rows;
	if (new_width > cub3d->img->width || new_height > cub3d->img->height)
		return ;
	new_pos.x = cub3d->minimap.pos.x - (new_width - cub3d->minimap.width) / 2;
	new_pos.y = cub3d->minimap.pos.y - (new_height - cub3d->minimap.height) / 2;
	if (new_pos.x < 0)
		new_pos.x = 0;
	if (new_pos.y < 0)
		new_pos.y = 0;
	if (new_pos.x + new_width > cub3d->img->width)
		new_pos.x = cub3d->img->width - new_width;
	if (new_pos.y + new_height > cub3d->img->height)
		new_pos.y = cub3d->img->height - new_height;
	cub3d->minimap.size_percentage = new_size_percentage;
	cub3d->minimap.tile_size = new_tile_size;
	cub3d->minimap.width = new_width;
	cub3d->minimap.height = new_height;
	cub3d->minimap.pos = new_pos;
}

void zoom_out_minimap(cub3d_t *cub3d)
{
	int new_size_percentage;
	int new_width;
	int new_height;
	int new_tile_size;
	vector_t new_pos;

	new_size_percentage = cub3d->minimap.size_percentage - MINIMAP_ZOOM_INCREMENT;
	if (new_size_percentage < MINIMAP_MIN_SIZE_PERCENTAGE)
		new_size_percentage = MINIMAP_MIN_SIZE_PERCENTAGE;
	new_tile_size = count_minimap_tilesize(cub3d, new_size_percentage);
	new_width = new_tile_size * cub3d->map_columns;
	new_height = new_tile_size * cub3d->map_rows;
	new_pos.x = cub3d->minimap.pos.x + (cub3d->minimap.width - new_width) / 2;
	new_pos.y = cub3d->minimap.pos.y + (cub3d->minimap.height - new_height) / 2;
	cub3d->minimap.size_percentage = new_size_percentage;
	cub3d->minimap.tile_size = new_tile_size;
	cub3d->minimap.width = new_width;
	cub3d->minimap.height = new_height;
	cub3d->minimap.pos = new_pos;
}

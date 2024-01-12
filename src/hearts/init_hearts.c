#include "../incl/cub3d.h"

int	init_hearts(cub3d_t *cub3d)
{
	if (!load_heart_png(cub3d))
		return (FAIL);
	if (!init_full_hearts(cub3d))
		return (FAIL);
	if (!init_empty_hearts(cub3d))
		return (FAIL);
	if (!set_heart_positions(cub3d))
	{
		delete_hearts(cub3d);
		return (FAIL);
	}
	if (!put_hearts_to_window(cub3d))
	{
		delete_hearts(cub3d);
		return (FAIL);
	}
	disable_hearts(cub3d);
	return (SUCCESS);
}
#include "../incl/cub3d.h"

static int	draw_all_entities_in_order(cub3d_t *cub3d)
{
	key_node_t		**ordered_keys;
	t_enemy			**ordered_enemies;
	distraction_t	**ordered_distractions;

	ordered_keys = create_array_of_keys_ordered_by_dist(cub3d);
	ordered_enemies = create_array_of_enemies_ordered_by_dist(cub3d);
	ordered_distractions = create_array_of_distractions_ordered_by_dist(cub3d);
	if (!ordered_keys || !ordered_enemies || !ordered_distractions)
		return (FAIL);
	// maybe in the future z function will need error handling
	assign_z_depth_ordered_by_distance(cub3d, ordered_enemies, ordered_keys, ordered_distractions);
	draw_all_enemies(cub3d, ordered_enemies);
	draw_all_distractions(cub3d, ordered_distractions);
	draw_all_keys(cub3d);
	free(ordered_enemies);
	free(ordered_keys);
	free(ordered_distractions);
	return(SUCCESS);
}

int	draw_game_entities(cub3d_t *cub3d)
{
	int	animation_frame_change;
	int	fps_frame_change;

	animation_frame_change = animation_frames_changed(cub3d);
	fps_frame_change = fps_frame_changed(cub3d);
	// draw everything if update is needed
	if (animation_frame_change || fps_frame_change)
	{
		if (draw_all_entities_in_order(cub3d) == FAIL)
			return (FAIL);
	}
	// update previous frames in the end
	if (animation_frame_change)
		update_prev_frames(cub3d);
	return(SUCCESS);
}

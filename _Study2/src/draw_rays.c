#include "../incl/raycaster.h"

void draw_line(mlx_image_t *img, double_vector_t start, double_vector_t end, int color)
{
	double x;
	double y;
	double x_increment;
	double y_increment;
	int i;
	int iterations = 600;

	x = start.x;
	y = start.y;
	x_increment = (end.x - start.x) / iterations;
	y_increment = (end.y - start.y) / iterations;
	i = 0;
	while (i < iterations)
	{
		x += x_increment;
		y += y_increment;
		mlx_put_pixel(img, x, y, color);
		i++;
	}
}

void find_end_point(map_t *map, player_t *player, double angle, double_vector_t *end)
{
	double_vector_t vRayStart;
	double_vector_t vRayUnitStepSize;
	double_vector_t vRayLength1D;
	double_vector_t vRayDir;
	double_vector_t dvMapCheck;
	vector_t vMapCheck;
	vector_t vStep;
	int end_found = FALSE;

	vRayDir.x = cos(angle);
	vRayDir.y = sin(angle);
	if (vRayDir.x == 0 || vRayDir.y == 0)
		return ;

	vRayStart.x = player->pos.x + vRayDir.x;
	vRayStart.y = player->pos.y + vRayDir.y;

	vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x)) * map->cell_size;
	vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y)) * map->cell_size;

	dvMapCheck.x = vRayStart.x;
	dvMapCheck.y = vRayStart.y;
	vMapCheck.x = (int)vRayStart.x / map->cell_size;
	vMapCheck.y = (int)vRayStart.y / map->cell_size;

	if (vRayDir.x < 0)
	{
		vStep.x = -1;
		vRayLength1D.x = (vRayStart.x - dvMapCheck.x) * vRayUnitStepSize.x;
	}
	else
	{
		vStep.x = 1;
		vRayLength1D.x = (dvMapCheck.x + 1.0 - vRayStart.x) * vRayUnitStepSize.x;
	}
	if (vRayDir.y < 0)
	{
		vStep.y = -1;
		vRayLength1D.y = (vRayStart.y - dvMapCheck.y) * vRayUnitStepSize.y;
	}
	else
	{
		vStep.y = 1;
		vRayLength1D.y = (dvMapCheck.y + 1.0 - vRayStart.y) * vRayUnitStepSize.y;
	}

	// printf("vRayLength1D.x = %f\n", vRayLength1D.x);
	// printf("vRayLength1D.y = %f\n", vRayLength1D.y);
	
	double dist = 0;
	while (!end_found && dist < fmax(WIDTH, HEIGHT))
	{
		if (vRayLength1D.x < vRayLength1D.y)
		{
			vMapCheck.x += vStep.x;
			dist = vRayLength1D.x;
			vRayLength1D.x += vRayUnitStepSize.x;
		}
		else
		{
			vMapCheck.y += vStep.y;
			dist = vRayLength1D.y;
			vRayLength1D.y += vRayUnitStepSize.y; 
		}
		// printf("dist = %f\n", dist);
		// printf("vMapCheck.x = %d\n", vMapCheck.x);
		// printf("vMapCheck.y = %d\n", vMapCheck.y);
		if (vMapCheck.x >= 0 && vMapCheck.x < map->columns && vMapCheck.y >= 0 && vMapCheck.y < map->rows && map->grid[vMapCheck.y][vMapCheck.x] == 1)
		{
			end->x = player->pos.x + vRayDir.x * dist;
			end->y = player->pos.y + vRayDir.y * dist;
			// printf("end = [%f,%f]\n", end->x, end->y);
			end_found = TRUE;
		}
	}
}

void draw_rays(cub3d_t *cub3d)
{
	double_vector_t end;
	double angle;
	int rays;
	int i;

	rays = 10;
	i = 0;
	while (++i <= rays)
	{
		angle = (2 * M_PI) * i / rays;
		// printf("%d, angle = %f\n", i, angle);
		find_end_point(cub3d->map, &cub3d->player, angle, &end);
		draw_line(cub3d->img, cub3d->player.pos, end, WHITE);
	}
}

void connect_player_to_mouse(cub3d_t *cub3d)
{
	double_vector_t mouse;
	int mouse_x;
	int mouse_y;

	mlx_get_mouse_pos(cub3d->mlx, &mouse_x, &mouse_y);
	mouse.x = mouse_x;
	mouse.y = mouse_y;
	draw_line(cub3d->img, cub3d->player.pos, mouse, YELLOW);
}

void draw_direction_ray(cub3d_t *cub3d)
{
	double_vector_t end;

	end.x = cub3d->player.pos.x + cub3d->player.dir.x * 10;
	end.y = cub3d->player.pos.y + cub3d->player.dir.y * 10;
	draw_line(cub3d->img, cub3d->player.pos, end, YELLOW);
}
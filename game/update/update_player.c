/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:15:35 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/18 22:43:08 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

static t_line	*check_wall_intersection(t_line *player_path, t_game *game)
{
	t_line			*wall_line;
	t_wall_node		*node;
	t_point			intersect_point;
	int				is_intersect;

	node = game->scene->map->walls->start;
	while(node)
	{
		wall_line = wall_to_line(node->wall);
		if (!wall_line)
			return (NULL);
		is_intersect = check_intersection(player_path, wall_line, &intersect_point);
		if (is_intersect)
		{
			line_update_by_points(player_path, player_path->start, intersect_point);
			return (wall_line);
		}
	 	free_line(wall_line);
		node = node->next;
	}
	return (NULL);
}

static void	update_player_vector(t_vector *move_vector, t_line *player_path, t_line *wall_line)
{
	t_line	*wall_perpendicular;

	wall_perpendicular = line_perpendicular(wall_line, player_path->start);
	if (!wall_perpendicular)
		return ;
	move_vector->x = - (wall_perpendicular->B + player_path->B) * -1;
	move_vector->y = (wall_perpendicular->A + player_path->A) * -1;
}

t_line offset_line(t_line player_path, int offset_pos_or_neg, float offset_amount)
{
	t_line offset_path;

	float dx = player_path.end.x - player_path.start.x;
	float dy = player_path.end.y - player_path.start.y;

	float length = sqrt(dx * dx + dy * dy);
	dx /= length;
	dy /= length;

	float normal_x = -dy;
	float normal_y = dx;

	offset_path.start.x = player_path.start.x + offset_pos_or_neg * normal_x * offset_amount;
	offset_path.start.y = player_path.start.y + offset_pos_or_neg * normal_y * offset_amount;
	offset_path.end.x = player_path.end.x + offset_pos_or_neg * normal_x * offset_amount;
	offset_path.end.y = player_path.end.y + offset_pos_or_neg * normal_y * offset_amount;

	offset_path.A = player_path.A;
	offset_path.B = player_path.B;
	offset_path.D = player_path.D;
	offset_path.length = player_path.length;

	return (offset_path);
}

// t_vector_fork make_vector_fork(t_game *game, t_vector *move_vector)
// {
// 	t_vector_fork fork;
// 	float			posX;
// 	float			posY;

// 	posX = game->scene->player->pos->x;
// 	posY = game->scene->player->pos->y;
// 	fork = (t_vector_fork *)malloc(sizeof(t_vector_fork));
// 	fork->player_path1 = make_line(posX, posY, posX + move_vector->x, posY + move_vector->y);
// 	if (!fork->player_path1)
// 	{
// 		free(fork);
// 		return (NULL);
// 	}
// 	return (fork);
// }

//CHECK for intersection with forked path
static int	player_intersect_forked(t_game *game, t_vector *move_vector)
{
	t_line			*player_path;
	t_line			*inter_wall;
	float			posX;
	float			posY;

	if (!move_vector)
		return (1);
	posX = game->scene->player->pos->x;
	posY = game->scene->player->pos->y;
	player_path = make_line(posX, posY, posX + move_vector->x, posY + move_vector->y);
	if (!player_path)
		return (1);
	inter_wall = check_wall_intersection(player_path, game);
	if (!inter_wall)
		return (free_line(player_path) ,1);
	return (free_line(player_path), free_line(inter_wall), 0);
}


// Check if player can move in the direction of move_vector
static int	player_intersect_handler_move(t_game *game, t_vector *move_vector)
{
	t_line			*player_path;
	t_line			*inter_wall;
	float			posX;
	float			posY;
	int 			fork_result;

	if (!move_vector)
		return (1);
	posX = game->scene->player->pos->x;
	posY = game->scene->player->pos->y;
	printf("vector x = %f, y = %f\n", move_vector->x, move_vector->y);
	player_path = make_line(posX, posY, posX + move_vector->x, posY + move_vector->y);
	if (!player_path)
		return (1);
	inter_wall = check_wall_intersection(player_path, game);
	if (!inter_wall)
		return (free_line(player_path) ,1);
	fork_result = player_intersect_forked(game, move_vector);
	if (fork_result)
		return (free_line(player_path), free_line(inter_wall), 1);
	update_player_vector(move_vector, player_path, inter_wall);
	return (free_line(player_path), free_line(inter_wall), 0);
}

static int	player_intersect_handler_check(t_game *game, t_vector *move_vector)
{
	t_line			*player_path;
	t_line			*inter_wall;
	float			posX;
	float			posY;
	int 			fork_result;

	if (!move_vector)
		return (1);
	posX = game->scene->player->pos->x;
	posY = game->scene->player->pos->y;
	printf("vector x = %f, y = %f\n", move_vector->x, move_vector->y);
	player_path = make_line(posX, posY, posX + move_vector->x, posY + move_vector->y);
	if (!player_path)
		return (1);
	inter_wall = check_wall_intersection(player_path, game);
	if (!inter_wall)
		return (free_line(player_path) ,1);
	fork_result = player_intersect_forked(game, move_vector);
	if (fork_result)
		return (free_line(player_path), free_line(inter_wall), 1);
	return (free_line(player_path), free_line(inter_wall), 0);
}

//-------------------------------------------------------------------
	// t_line			*player_path;
	// t_line			*inter_wall;


	// float			posX;
	// float			posY;

	// if (!move_vector)
	// 	return ;
	// posX = game->scene->player->pos->x;
	// posY = game->scene->player->pos->y;

	// player_path = make_line(posX, posY, posX + move_vector->x, posY + move_vector->y);
	// inter_wall = check_wall_intersection(player_path, game);
	// update_player_vector(move_vector, player_path, inter_wall);
//-------------------------------------------------------------------
// MODIFYING THE FUCNTION to try create new struct, but trying new method first.
// // Check if player can move in the direction of move_vector
// static void	player_intersect_handler(t_game *game, t_vector *move_vector)
// {
// 	t_line			*player_path1;
// 	t_line			*player_path2;
// 	t_line			*player_path3;
// 	t_line			*inter_wall1;
// 	t_line			*inter_wall2;
// 	t_line			*inter_wall3;

// 	float			posX;
// 	float			posY;

// 	t_vector_fork	*vector_fork;

// 	vector_fork = make_vector_fork(game, move_vector);
// 	if (!vector_fork)
// 		return ;
// 	posX = game->scene->player->pos->x;
// 	posY = game->scene->player->pos->y;
// 	player_path1 = make_line(posX, posY, posX + move_vector->x, posY + move_vector->y);
// 	if (!player_path1)
// 		return ;
// 	inter_wall1 = check_wall_intersection(player_path, game);
	
// 	inter_wall2 = offset_line(*player_path, 1, 0.5);
// 	inter_wall3 = offset_line(*player_path, 1, 0.5);
// 	check_wall_intersection(offset_line(*player_path, 1, 0.5), game);
// 	inter_wall3 = check_wall_intersection(offset_line(*player_path, -1, 0.5), game);
// 	if (!inter_wall1 && !inter_wall2 && !inter_wall3)
// 	{
// 		free_line(player_path1);
// 		free_line(inter_wall2);
// 		free_line(inter_wall3);
// 		return ;
// 	}
// 	update_player_vector(move_vector, player_path1, inter_wall1);
// 	free_line(player_path1);
// 	free_line(inter_wall1);
// 	free_line(inter_wall2);
// 	free_line(inter_wall3);
// }


	// printf("inter_wall1 coords = %f, %f, %f, %f\n", inter_wall1->start.x, inter_wall1->start.y, inter_wall1->end.x, inter_wall1->end.y);
	// printf("inter_wall2 coords = %f, %f, %f, %f\n", inter_wall2->start.x, inter_wall2->start.y, inter_wall2->end.x, inter_wall2->end.y);
	// printf("inter_wall3 coords = %f, %f, %f, %f\n", inter_wall3->start.x, inter_wall3->start.y, inter_wall3->end.x, inter_wall3->end.y);


static void	player_collect(t_game *game, t_player *player)
{
	t_treasure_storage	*storage;
	int					counter;
	t_point				*player_pos;
	t_point				*treasure_center;

	if (!player->pressed_buttons[6])
		return ;
	player_pos = player->pos;
	storage = game->scene->treasures;
	counter = 0;
	while(storage->boxes[counter])
	{
		treasure_center = storage->boxes[counter]->center;
		if (point_distance(*player_pos, *treasure_center) <= TREASURE_COLLECT_DISTANCE \
			&& treasure_collect(storage, storage->boxes[counter], player))
			break ;
		counter++;
	}
}

static void	player_inventory_update(t_game *game)
{
	t_inv_images	images;
	t_sprite_node	*sprite;
	t_player		*player;

	images.bullet_image = NULL;
	images.slot_image = NULL;
	images.active_slot_image = NULL;
	images.pistol_image = NULL;
	sprite = get_sprite_by_name(game->scene->map->sprites, "INV_SLOT");
	if (sprite && sprite->image)
		images.slot_image = sprite->image;
	sprite = get_sprite_by_name(game->scene->map->sprites, "INV_SLOT_ACTIVE");
	if (sprite && sprite->image)
		images.active_slot_image = sprite->image;
	sprite = get_sprite_by_name(game->scene->map->sprites, "INV_BULLET");
	if (sprite && sprite->image)
		images.bullet_image = sprite->image;
	sprite = get_sprite_by_name(game->scene->map->sprites, "PISTOL_ICON");
	if (sprite && sprite->image)
		images.pistol_image = sprite->image;
	player = game->scene->player;
	if (images.pistol_image && images.bullet_image && images.slot_image && images.active_slot_image)
		inv_update_image(player->inventory, player->update_count, \
						images, game->writer);
}

t_vector offset_vector(t_vector move_vector, float offset_amount)
{
    t_vector offset_move_vector;

    // Calculate the direction vector (dx, dy)
    float dx = move_vector.end.x - move_vector.start.x;
    float dy = move_vector.end.y - move_vector.start.y;

    // Normalize the direction vector
    float length = sqrt(dx * dx + dy * dy);
    dx /= length;
    dy /= length;

    // Calculate the normal vector (perpendicular)
    float normal_x = -dy;
    float normal_y = dx;

    // Offset the x and y values by the normal vector
    offset_move_vector.x = move_vector.x + normal_x * offset_amount;
    offset_move_vector.y = move_vector.y + normal_y * offset_amount;

    // Offset the end point by the normal vector
    offset_move_vector.end.x = move_vector.end.x + normal_x * offset_amount;
    offset_move_vector.end.y = move_vector.end.y + normal_y * offset_amount;

    // Copy the start point
    offset_move_vector.start = move_vector.start;

    return offset_move_vector;
}

int	player_intersect_wrapper(t_game *game, t_vector *move_vector)
{
	t_vector	offset_move_vector_up;
	t_vector	offset_move_vector_down;

	player_intersect_handler_check(game, move_vector);
	if (player_intersect_handler_check(game, move_vector);)
}

// Update player data
void	update_player(t_game *game)
{
	t_vector	*move_vector;
	t_player	*player;


	player = game->scene->player;
	player_collect(game, player);
	player_rotate(player);
	player_inventory_update(game);
	move_vector = player_move_vector(player);
	if (!move_vector)
		return ;
	// player_intersect_handler_check(game, move_vector);
	player_intersect_wrapper(game, move_vector);
	// player_intersect_handler(game, offset_vector(*move_vector, 0.5));
	player_move_update(player, move_vector);
	free_vector(move_vector);
}
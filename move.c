/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolau <lnicolau@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:19:21 by lnicolau          #+#    #+#             */
/*   Updated: 2024/06/09 13:19:21 by lnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	calculate_new_position(t_game *game, int direction, int	*new_x, int	*new_y)
{
    *new_x = game->player_x;
    *new_y = game->player_y;
    if (direction == UP)
        (*new_y)--;
    else if (direction == DOWN)
        (*new_y)++;
    else if (direction == RIGHT)
        (*new_x)++;
    else if (direction == LEFT)
        (*new_x)--;
}

static void	update_player_position(t_game *game, int new_x, int new_y)
{
    char	cell;

    if (new_x < 0 || new_x >= game->cols || new_y < 0 || new_y >= game->rows)
        return ;
    cell = game->map[new_y][new_x];
    if (cell == '1')
        return ;
    if (cell == 'C')
    {
        game->map[new_y][new_x] = '0';
        game->collectibles--;
        if (game->collectibles == 0)
            game->exit = 1;
    }
    game->map[game->player_y][game->player_x] = '0';
    game->player_x = new_x;
    game->player_y = new_y;
    game->map[new_y][new_x] = 'P';
}

void	move_player(t_game *game, int direction)
{
    int	new_x;
    int	new_y;

    calculate_new_position(game, direction, &new_x, &new_y);
    update_player_position(game, new_x, new_y);
}

void	ft_move(t_game *game, int direction, int y, int x)
{
    if (y < game->hgt && x < game->wth && y >= 0 && x >= 0)
    {
        if (game->map[y][x] == '1')
            return ;
        else if (game->map[y][x] == 'C' || game->map[y][x] == 'E')
        {
            move_player(game, direction);
        }
        else
            move_player(game, direction);
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolau <lnicolau@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 04:16:02 by lnicolau          #+#    #+#             */
/*   Updated: 2024/05/26 04:16:02 by lnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int parsing(t_game *game, char *argv)
{
	size_t i;
	size_t j;
	int **visit;

	(void)argv;
	i = 0;
	j = 0; 
	check_rect_map(game);
	check_components(game);
	check_walls(game);
	visit = start_check_path(game, i, j);
	check_collectibles(game, visit);
	return (0);
}

void ft_error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
/*int get_map_dimensions(t_game *game, char *argv)
{
    int fd;
    char *current_line;
    int read_result;

    fd = open(argv, O_RDONLY);
    if(fd == -1)
        error(&game, "Error opening file");
    
    game_state->map_width = 0;
    game_state->map_height = 0;
    game_state->screen_width = 0;
    game_state->screen_height = 0;

    while((read_result = get_next_line(fd, &current_line)) > 0)
    {
        game_state->map_height++;
        if(game_state->map_width < ft_strlen(current_line))
            game_state->map_width = ft_strlen(current_line);
        free(current_line);
    }
    if(read_result == -1)
        error(&game, "Error reading file");

    game_state->screen_width = game_state->map_width * TILE_SIZE;
    game_state->screen_height = game_state->map_height * TILE_SIZE;

    close(fd);
    return (0);
}

int allocate_map_memory(t_game *game)
{
    int index;

    game->map = (char **)malloc(sizeof(char *) * game->map_height);
    if(game->map == NULL)
        error(&game, "Error allocating memory");
        return (0);
    index = 0;
    while(index < game->map_height)
    {
        game->map[index] = (char *)malloc(sizeof(char) * game->map_width + 1);
        if(game->map[index] == NULL)
        {
            error(&game, "Error allocating memory");
            free_map(game);
            return(0);
        }
        index++;
    }
    game->map_to_free = 1;
    return (1);
}

int verification_ber(char *str. t_game game)
{
    int i;

    i = 0;
    while(str[i] != '\0')
        i++;
    if(str[i - 4] == '.' && str[i - 3] == 'b' 
        && str[i - 2] == 'e' && str[i - 1] == 'r')
    {
        i = open(str, O_RDONLY);
        if(i == -1)
            error(&game, "Error opening file");
        else
            close(i);
        return (0);
    }
    error(&game, "Invalid file extension, use .ber!");
    return (1);
} */
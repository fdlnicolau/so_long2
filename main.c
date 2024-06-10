/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolau <lnicolau@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:40:29 by lnicolau          #+#    #+#             */
/*   Updated: 2024/05/20 15:40:29 by lnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int main(int argc, char **argv) 
{
	t_game *game;

    game = game_memory_init(&game);
    game_init(game);
	if(argc == 2)
	{
		check_map(argv[1], game);
        game_control(game);
	}
	free_game(game);
	return (0);

}

void free_game(t_game *game) 
{
	int i;
    if (game->map) 
	{
		free_map(game);
    }
    free(game);
}
t_game *game_memory_init(t_game **game)
{
	*game = malloc(sizeof(t_game));
	if (*game == NULL)
		ft_error("Failed to allocate memory for the game");
	(*game)->map = NULL;
	return (*game);
}

void check_map(char *str, t_game *game)
{
	char *final;

	final = ft_strdup (str + ft_strlen(str) - 4);
	if (final == NULL)
    {
        ft_putstr_fd("Error: Memory allocation failed\n", 2);
        exit(EXIT_FAILURE);
    }
	if(ft_strncmp(final, ".ber", 4))
    {
        ft_putstr_fd("Error\nInvalid file extension\n", 2);
		free(final);
        exit(EXIT_FAILURE);
    }
	read_map(game, str);
	free(final);
}

int free_map(t_game *game)
{
	int i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		game->map[i] = NULL;
		i++;
	}
	free(game->map);
	game->map = NULL;
	return (0);
}



//* * Esta función se asegura de que el programa se ejecute con el número correcto de argumentos
/* y que el argumento adicional sea un archivo con la extensión .ber. */
/*char **check_params(int argc, char **argv, t_game *game)
{
	int fl;

	if (argv != 2)
		ft_error();
	fl = ft_strlen(argv[1]);
	if(ft_strrncmp(argv[1] + (fl - 4), ".ber", 4) == NULL)
		ft_error();
}

int map_size(int fd)
{
    char *line;
    int size;

    size = 0;
    while((line = get_next_line(fd)) != NULL)
    {
        size++;
        free(line);
    }
    return (size);
}

int check_line(char *line, int cols)
{
    int i;

    i = 0;
    while(line[i] != '\0')
    {
        if(line[i] != '1' && line[i] != '0' && line[i] != 'P' && line[i] != 'E' && line[i] != 'C')
        {
            ft_putstr_fd("Error\nInvalid character in map\n", 2);
            return(0);
        }
        i++;
    }
    return (i == cols);
}

void init_game(t_game *game)
{
    game->map = NULL;
    game->rows = 0;
    game->cols = 0;
    game->players = 0;
    game->exit = 0;
    game->collectibles = 0;
} */ 
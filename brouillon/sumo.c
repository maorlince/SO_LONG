/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sumo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:27:06 by manon             #+#    #+#             */
/*   Updated: 2025/03/26 18:29:25 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdlib.h>
//#include <time.h>

//srand pas autorisé!!!!!!!!!!!!!

// Cette fonction doit être appelée dans le main avant la boucle principale
void init_random(void)
{
    srand(time(NULL));
}

void move_sumos(t_game *game)
{
    int i, j;
    t_point new_pos;
    int direction;
    
    // Parcourir toutes les cases de la map
    j = 0;
    while (game->map->data[j])
    {
        i = 0;
        while (game->map->data[j][i])
        {
            // Si la case contient un sumo
            if (game->map->data[j][i] == 'S')
            {
                // Générer un nombre aléatoire entre 0 et 3
                direction = rand() % 4;
                new_pos.x = i;
                new_pos.y = j;
                // Déterminer la nouvelle position en fonction de la direction
                if (direction == 0)
                    new_pos.x++; // droite
                else if (direction == 1)
                    new_pos.x--; // gauche
                else if (direction == 2)
                    new_pos.y++; // bas
                else if (direction == 3)
                    new_pos.y--; // haut

                // Vérifier que la nouvelle position est dans les limites et qu'elle est une case d'eau
                if (new_pos.x >= 0 && new_pos.x < game->map->width &&
                    new_pos.y >= 0 && new_pos.y < game->map->height &&
                    game->map->data[new_pos.y][new_pos.x] == WATER) // WATER défini par '0'
                {
                    // Déplacer le sumo : on met la case actuelle à l'eau
                    game->map->data[j][i] = WATER;
                    // Et on place le sumo dans la nouvelle case
                    game->map->data[new_pos.y][new_pos.x] = SUMO;
                }
            }
            i++;
        }
        j++;
    }
}

// Exemple d'utilisation dans votre boucle principale MLX
int loop_hook(t_game *game)
{
    move_sumos(game);
    render_map(game);
    return (0);
}

int main(int argc, char **argv)
{
    t_game game;
    // ... initialisation du jeu, de la map, du MLX, etc.
    
    init_random(); // Initialiser le générateur de nombres aléatoires

    // Après avoir créé la fenêtre et chargé la map, etc.
    mlx_loop_hook(game.mlx_ptr, (int (*)(void *))loop_hook, &game);
    mlx_loop(game.mlx_ptr);
    
    // ... libération des ressources
    return (0);
}

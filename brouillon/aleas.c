/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aleas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:27:33 by manon             #+#    #+#             */
/*   Updated: 2025/03/26 18:29:16 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdint.h>

//stdint?? pas sur de pouvoir

static uint32_t g_seed = 42; // Valeur initiale de la graine

// Fonction pour initialiser la graine
void init_random(uint32_t seed)
{
    g_seed = seed;
}

// Fonction pour générer un nombre pseudo-aléatoire
uint32_t my_rand(void)
{
    // Paramètres du LCG (ces valeurs peuvent être ajustées)
    const uint32_t a = 1664525;
    const uint32_t c = 1013904223;
    const uint32_t m = 4294967296; // 2^32

    g_seed = (a * g_seed + c) % m;
    return g_seed;
}

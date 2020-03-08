/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_retriever.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:12:51 by yaziz             #+#    #+#             */
/*   Updated: 2020/03/08 13:20:51 by yaziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mlx.h>
#include <math.h>
#include "libft/libft.h"

#define IS_MAP_ELEMENT(x) (x == 'N' || x == 'W' || x == 'S' || x == 'E' || x == '2' || x == '1' || x == '0')
#define IS_ZSP(x) (x == 'N' || x == 'W' || x == 'S' || x == 'E' || x == '2')
#define IS_P(x) (x == 'N' || x == 'W' || x == 'S' || x == 'E')
typedef struct	s_file
{
	// Map properties
	char **map;
	int map_w;
	int map_h;
	//	Paths to textures and sprite
	char *no;
	char *so;
	char *we;
	char *ea;
	char *s;
	// Window resolution
	int win_x;
	int win_y;
	// Colors
	int floor;
	int ceil;
}				t_file;

typedef struct	s_tkn
{
	char map;
	char no;
	char so;
	char we;
	char ea;
	char r;
	char s;
	char f;
	char c;
}				t_tkn;

typedef struct s_player
{
	float x;
	float y;
	float dir;
}

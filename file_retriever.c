/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_retriever.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:00:15 by yaziz             #+#    #+#             */
/*   Updated: 2020/03/08 13:06:08 by yaziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * This Code is Copyrighted by DMCA
 * Proudly Coded by Yassine Aziz <Yassine.Aziz@yandex.com>
 * Email me for more and other codes */

#include "file_retriever.h"

t_tkn g_tkn;

void tozero_tkn()
{
	g_tkn = (t_tkn){.map = 0, .no = 0, .so = 0, .we = 0, .ea = 0, .s = 0};
	g_tkn = (t_tkn){.f = 0, .c = 0, .r = 0};
}

int     gnl(char **line, int fd)
{
	char    c;
	int     i;

	i = 0;
	if ((*line = malloc(1000)) == NULL)
		exit(-1);
	while (read(fd, &c, 1) != 0)
	{
		if (c != '\n')
			(*line)[i++] = c;
		else
		{
			(*line)[i] = 0;
			return (1);
		}
	}
	free(*line);
	return (0);
}

void write_exit(char *s)
{
	write(1, s, ft_strlen(s));
	exit(1);
}

void treat_no(char *s, t_file *file)
{
	while (*s == ' ' || *s == '\t')
		s++;
	if (!*s)
		write_exit("Error\nNo value assigned to NO element");
	file -> no = ft_strdup(s);
	g_tkn.no += 1;
	if (g_tkn.no == 2)
		write_exit("Error\nMore than one NO detected in <cub> file");
}

void treat_so(char *s, t_file *file)
{
	while (*s == ' ' || *s == '\t')
		s++;
	if (!*s)
		write_exit("Error\nNo value assigned to SO element");
	file -> so = ft_strdup(s);
	g_tkn.so += 1;
    if (g_tkn.so == 2)
		write_exit("Error\nMore than one SO detected in <cub> file");
}

void treat_we(char *s, t_file *file)
{
	while (*s == ' ' || *s == '\t')
		s++;
	if (!*s)
		write_exit("Error\nNo value assigned to WE element");
	file -> we = ft_strdup(s);
	g_tkn.we += 1;
	if (g_tkn.we == 2)
		write_exit("Error\nMore than one WE detected in <cub> file");
}

void treat_ea(char *s, t_file *file)
{
	while (*s == ' ' || *s == '\t')
		s++;
	if (!*s)
		write_exit("Error\nNo value assigned to EA element");
	file -> ea = ft_strdup(s);
	g_tkn.ea += 1;
	if (g_tkn.ea == 2)
		write_exit("Error\nMore than one EA detected in <cub> file");
}

void treat_s(char *s, t_file *file)
{
	while (*s == ' ' || *s == '\t')
		s++;
	if (!*s)
		write_exit("Error\nNo value assigned to S element");
	file -> s = ft_strdup(s);
	g_tkn.s += 1;
	if (g_tkn.s == 2)
		write_exit("Error\nMore than one S detected in <cub> file");
}

void treat_f(char *s, t_file *file)
{
	int r;
	int g;
	int b;
	
	while (*s == ' ' || *s == '\t')
		s++;
	if (!*s)
		write_exit("Error\nNo value assigned to F element");
	r = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s++;
	g = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s++;
	b = ft_atoi(s);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		write_exit("Error\nColors are invalid");
	r <<= 16;
	g <<= 8;
	file -> floor = r + g + b;
	g_tkn.f += 1;
	if (g_tkn.f == 2)
		write_exit("Error\nMore than one F detected in <cub> file");
}

void treat_c(char *s, t_file *file)
{
	int r;
	int g;
	int b;

	while (*s == ' ' || *s == '\t')
		s++;
	if (!*s)
		write_exit("Error\nNo value assigned to C element");
	r = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s++;
	g = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s++;
	b = ft_atoi(s);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		write_exit("Error\nColors are invalid");
	r <<= 16;
	g <<= 8;
	file -> ceil = r + g + b;
	g_tkn.c += 1;
	if (g_tkn.c == 2)
		write_exit("Error\nMore than one C detected in <cub> file");
}

void treat_r(char *s, t_file *file)
{
	int i;

	i = 0;
	while (*s == ' ' || *s == '\t')
		s++;
	file -> win_x = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	while (*s == ' ' || *s == '\t')
		s++;
	file -> win_y = ft_atoi(s);
	g_tkn.r += 1;
	if (g_tkn.r == 2)
		write_exit("Error\nMore  than one R detected in <cub> file");
	if (file -> win_y <= 0 || file -> win_y > 1440 || file -> win_x <= 0 || file -> win_x > 2560)
		write_exit("Error\nResolution is invalid");
}

int bigger(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

void check_before_map()
{
	if (g_tkn.no == 0 || g_tkn.so == 0 || g_tkn.we == 0 || g_tkn.ea == 0 || g_tkn.s == 0
			|| g_tkn.f == 0 || g_tkn.c == 0)
		write_exit("Error\nNot all elements defined above the map in <cub> file");
}

void treat_m(char *element, t_file *file)
{
	char **temp;

	if (file -> map == NULL)
	{
		check_before_map();
		file -> map = malloc(sizeof(char *));
		file -> map[0] = ft_strdup(element);
		file -> map_h = 1;
		file -> map_w = ft_strlen(element);
		g_tkn.map = 1;
	}
	else
	{
		temp = file -> map;
		file -> map = malloc((file -> map_h + 1) * sizeof(char *));
		ft_memcpy(file -> map, temp, sizeof(char *) * file -> map_h);
		free(temp);
		file -> map[file -> map_h] = ft_strdup(element);
		file -> map_h += 1;
		file -> map_w = bigger(ft_strlen(element), file -> map_w);
	}
}

int skip_spaces(char *s)
{
	int i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (i);
}

void treat_element(char *element, t_file *file)
{
	int i;

	i = skip_spaces(element);
	if (element[i] == 'N' && element[i + 1] == 'O')
		treat_no(element + 2 + i, file);
	else if (element[i] == 'S' && element[i + 1] == 'O')
		treat_so(element + 2 + i, file);
	else if (element[i] == 'W' && element[i + 1] == 'E')
		treat_we(element + 2 + i, file);
	else if (element[i] == 'E' && element[i + 1] == 'A')
		treat_ea(element + 2 + i, file);
	else if (element[i] == 'R')
		treat_r(element + 1 + i, file);
	else if (element[i] == 'S')
		treat_s(element + 1 + i, file);
	else if (element[i] == 'F')
		treat_f(element + 1 + i, file);
	else if (element[i] == 'C')
		treat_c(element + 1 + i, file);
	else if (IS_MAP_ELEMENT(element[i]))
		treat_m(element, file);
	else
		write_exit("Error\n<cub> file isn't well defined");
}

void treat_line(char *line, t_file *file)
{
	int i;

	i = 0;
	treat_element(line + i, file);
}

int empty_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' || line[i] != '\t')
			return (0);
	}
	if (g_tkn.map == 1)
		write_exit("Error\nMap should be the last Element in the <cub> file");
	return (1);
}

void fill_spaces(char *str, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = 0;
}

void adjust_map(t_file *file)
{
	int i;
	int j;
	char **new;

	i = 0;
	j = 0;
	new = malloc(file -> map_h * sizeof(char *));
	while (i < file -> map_h)
	{
		new[i] = malloc(file -> map_w + 1);
		fill_spaces(new[i], file -> map_w);
		i++;
	}
	i = 0;
	while (i < file -> map_h)
	{
		ft_memcpy(new[i], file -> map[i], ft_strlen(file -> map[i]));
		i++;
	}
	i = 0;
	while (i < file -> map_h)
		free(file -> map[i++]);
	free(file -> map);
	file -> map = new;
}

void verify_map(char **map, int w, int h)
{
	int i;
	int j;
	
	i = 0;
	while (i < w)
	{
		if ((map[0][i] != '1' && map[0][i] != ' ') ||
				(map[h - 1][i] != '1' && map[h - 1][i] != ' '))
			write_exit("Error\nIncorrect Map");
		i++;
	}
	i = 0;
	while (i < h)
	{
		if ((map[i][0] != '1' && map[i][0] != ' ') || 
				(map[i][w - 1] != '1' && map[i][w - 1] != ' '))
			write_exit("Error\nIncorrect Map");
		i++;
	}
	i = 1;
	j = 1;
	while (i < h - 1)
	{
		while (j < w - 1)
		{
			if (IS_ZSP(map[i][j]) && (map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' ' || map[i - 1][j + 1] == ' '
						|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ' || map[i + 1][j - 1] == ' ' 
						|| map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' '))
				write_exit("Error\nMap should be rounded by 1");
			j++;
		}
		j = 0;
		i++;
	}
}

void verify_player(char **map, int w, int h)
{
	int i;
	int j;
	int nop;

	i = 0;
	j = 0;
	nop = 0;
	while (i < h)
	{
		while (j < w)
		{
			if (IS_MAP_ELEMENT(map[i][j]) || map[i][j] == ' ')
			{
				if (IS_P(map[i][j]))
					nop++;
			}
			else
				write_exit("Error\nBad character in map");
			j++;
		}
		i++;
		j = 0;
	}
	if (nop == 0)
		write_exit("Error\nNo player detected in map");
	else if (nop > 1)
		write_exit("Error\nMore than one player detected in map");
}

void retrive_from(char *fn, t_file *file)
{
	int fl;
	int fd;
	char *line;

	fl = ft_strlen(fn);
	if (fn[fl - 1] != 'b' || fn[fl - 2] != 'u' || fn[fl - 3] != 'c' || fn[fl - 4] != '.')
		write_exit("Error\nThe filetype isn't <cub>");
	if ((fd = open(fn, O_RDONLY)) == -1)
		write_exit("Error\nFile doesn't exist");
	file -> map = 0;
	while (gnl(&line, fd))
	{
		if (!empty_line(line))
			treat_line(line, file);
		free(line);
	}
	adjust_map(file);
	verify_map(file -> map, file -> map_w, file -> map_h);
	verify_player(file -> map, file -> map_w, file -> map_h);
}

int main()
{
	t_file file;
	int i = 0, j = 0;

	retrive_from("map.cub", &file);
	printf("EA |%s|\nWE |%s|\nSO |%s|\nNO |%s|\nS |%s|\nC |%d|\nR |%d| |%d|\nF |%d|\nMAP_H |%d|\nMAP_W |%d|\n\n",
			file.ea, file.we, file.so, file.no, file.s, file.ceil, file.win_x, file.win_y, file.floor, file.map_h, file.map_w);

	while (i < file.map_h)
	{
		printf("|%s|\n",file.map[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 17:10:35 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/06 13:48:46 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

int				open_read_file(char *path, char **s)
{
	int		fd;
	int		len;

	if ((fd = open(path, O_RDONLY)) < 0 ||
		(len = lseek(fd, 0, SEEK_END)) < 0)
		return (0);
	lseek(fd, 0, SEEK_SET);
	if (!(*s = (char *)malloc(sizeof(char) * len)) ||
		read(fd, *s, len) < 0 || close(fd) < 0)
		return (0);
	return (len);
}

static void		count_line(t_gl *gl)
{
	int		i;

	i = -1;
	gl->nb_line_file = 0;
	while (gl->txt_file[++i] != '\0')
	{
		if (gl->txt_file[i] == '\n')
			gl->nb_line_file++;
	}
	printf("nb_line_file = %d\n", gl->nb_line_file);
}

static void		count_polygone_triange_indices(t_gl *gl, int i)
{
	int	nb_point_polygon;

	nb_point_polygon = count_nb_indices(gl, i);
	gl->nb_indices += nb_point_polygon - 2;
	if (nb_point_polygon == 3)
		gl->nb_indices_triangle++;
	else if (nb_point_polygon > 3)
		gl->nb_indices_polygon++;
	else
	{
		printf("Error : number of indices is inferior to 3 on a line\n");
		exit(1);
	}
}

static void		split_txt_by_line(t_gl *gl)
{
	int		i;

	i = -1;
	gl->nb_vertices = 0;
	gl->nb_indices = 0;
	gl->nb_indices_triangle = 0;
	gl->nb_indices_polygon = 0;
	gl->line_file = (char **)malloc(sizeof(*(gl->line_file)) *
		(gl->nb_line_file + 1));
	if (gl->line_file)
	{
		while (gl->txt_file &&
			(gl->line_file[++i] = strsep(&(gl->txt_file), "\n")))
		{
			if (gl->line_file[i][0] == 'v' && gl->line_file[i][1] == ' ')
				gl->nb_vertices++;
			if (gl->line_file[i][0] == 'f' && gl->line_file[i][1] == ' ')
				count_polygone_triange_indices(gl, i);
		}
		gl->line_file[i] = NULL;
		printf("nb_vertex = %d\n", gl->nb_vertices);
		printf("nb_triangle_faces = %d\n", gl->nb_indices);
		printf("nb_indices_line_triangle = %d\n", gl->nb_indices_triangle);
		printf("nb_indices_line_polygon = %d\n\n", gl->nb_indices_polygon);
	}
}

void			parse_file(t_gl *gl)
{
	count_line(gl);
	split_txt_by_line(gl);
	if (gl->nb_vertices < 3 || gl->nb_indices < 1)
	{
		printf("Error : OBJ file have not enought vertices or face indices\n");
		exit(1);
	}
	if (make_vertices(gl) || make_indices(gl))
	{
		printf("Error during parsing the file,");
		printf("space(s) or number(s) missing\n");
		exit(1);
	}
	calculate_center(gl);
}

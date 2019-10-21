/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 17:10:35 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 12:23:08 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

static int		open_read_file(t_gl *gl)
{
	int		fd;
	int		len;

	if ((fd = open(gl->argv[1], O_RDONLY)) < 0 ||
		(len = lseek(fd, 0, SEEK_END)) < 0)
		return (1);
	lseek(fd, 0, SEEK_SET);
	if (!(gl->txt_file = (char *)malloc(sizeof(*(gl->txt_file)) * len)) ||
		read(fd, gl->txt_file, len) < 0 || close(fd) < 0)
		return (1);
	return (0);
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

static void		split_txt_by_line(t_gl *gl)
{
	int		i;

	i = -1;
	gl->nb_vertices = 0;
	gl->nb_indices = 0;
	gl->line_file = (char **)malloc(sizeof(*(gl->line_file)) *
		(gl->nb_line_file + 1));
	if (gl->line_file)
	{
		while ((gl->line_file[++i] = strsep(&(gl->txt_file), "\n")))
		{
			if (gl->line_file[i][0] <= 0)
				break ;
			if (gl->line_file[i][0] == 'v')
				gl->nb_vertices++;
			if (gl->line_file[i][0] == 'f')
				gl->nb_indices++;
		}
		gl->line_file[i] = NULL;
		printf("nb_vertices = %d\n", gl->nb_vertices);
		printf("nb_indices = %d\n\n", gl->nb_indices);
	}
}

static void		parse_file(t_gl *gl)
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
		printf("Error during parsing the file, spaces missing\n");
		exit(1);
	}
}

void			manage_file(t_gl *gl)
{
	char	*pt;

	if (gl->argc == 2 && (pt = strcasestr(gl->argv[1], ".obj")) &&
		pt[4] == '\0')
	{
		printf("Path file : %s\n\n", gl->argv[1]);
		if (open_read_file(gl))
			printf("Error during reading the file\n");
		parse_file(gl);
	}
	else
	{
		printf("usage : ./scop path/filename.obj\n");
		printf("You forget the path file argument or");
		printf(" the path is wrong or the file is not a .obj\n");
		exit(1);
	}
}

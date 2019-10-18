/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 17:10:35 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/18 15:27:29 by bpajot      ###    #+. /#+    ###.fr     */
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
	printf("len = %d\n", len);
	lseek(fd, 0 , SEEK_SET);
	if (!(gl->txt_file = (char *)malloc(sizeof(*(gl->txt_file)) * len)) ||
		read(fd, gl->txt_file, len) < 0 || close(fd) < 0)
		return (1);
	//printf("%s\n", gl->txt_file);
	return(0);
}

static void		count_line(t_gl *gl)
{
	int		i;

	i = -1;
	gl->nb_line_file = 0;
	while (gl->txt_file[++i] != '\0')
	{
		if(gl->txt_file[i] == '\n')
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
	gl->line_file = (char **)malloc(sizeof(*(gl->line_file)) * (gl->nb_line_file + 1));
	if (gl->line_file)
	{
		while ((gl->line_file[++i] = strsep(&(gl->txt_file), "\n"))) 		
		{
			if(gl->line_file[i][0] == 'v')
				gl->nb_vertices++;
			if(gl->line_file[i][0] == 'f')
				gl->nb_indices++;
		}
		gl->line_file[i] = NULL;
		i = -1;
		while (gl->line_file[++i]) 		
			printf("%d %s\n", i, gl->line_file[i]);
	}
}

static int		parse_file(t_gl *gl)
{
	count_line(gl);
	split_txt_by_line(gl);
	//skip the comment
	//get the v line for vertex
	//get the f line for triangle index
	return (0);
}

void			manage_file(t_gl *gl)
{
	char	*pt;

	if (gl->argc == 2 && (pt = strcasestr(gl->argv[1], ".obj")) && pt[4] == '\0')
	{
		printf("Path file : %s\n", gl->argv[1]);
		if (open_read_file(gl))
			printf("Error during reading the file\n");
		if (parse_file(gl))
			printf("Error during parsing the file\n");
	}
	else
	{
		printf("usage : ./scop path/filename.obj\n");	
		printf("You forget the path file argument or");	
		printf(" the path is wrong or the file is not a .obj\n");
	}
}

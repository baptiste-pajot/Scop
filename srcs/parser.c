/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 17:10:35 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/18 11:41:39 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

//open and read it
//skip the comment
//get the v line for vertex
//get the f line for triangle index



static int		open_read_file(t_gl *gl)
{
	int		fd;
	int		len;

	if ((fd = open(gl->argv[1], O_RDONLY)) < 0)
		return (1);
	len = lseek(fd, 0, SEEK_END);
	printf("len = %d\n", len);
	close(fd);
	return(0);
}

void			manage_file(t_gl *gl)
{
	char	*pt;

	if (gl->argc == 2 && (pt = strcasestr(gl->argv[1], ".obj")) && pt[4] == '\0')
	{
		printf("Path file : %s\n", gl->argv[1]);
		if (open_read_file(gl))
			printf("Error during opening or reading the file\n");
	}
	else
	{
		printf("usage : ./scop path/filename.obj\n");	
		printf("You forget the path file argument or");	
		printf(" the path is wrong or the file is not a .obj\n");	
	}
}

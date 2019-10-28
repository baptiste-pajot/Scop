/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vertices.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/18 16:57:47 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 16:04:42 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
** ┌───────────────┐
** │ Split float   │
** └───────────────┘
** For v lines (triangle vertexes) of .obj file, get the 3 float coordinates
** The 3 float values are separated by space
*/

static int	split_float(t_gl *gl, int i, int v)
{
	int		j;
	char	*p;

	j = -1;
	while (++j < 3)
	{
		if (j == 0)
			p = strchr(gl->line_file[i], ' ');
		else
			p = strchr(p, ' ');
		if (!p)
			return (1);
		p++;
		gl->vertices[v * 3 + j] = atof(p);
	}
	return (0);
}

int			make_vertices(t_gl *gl)
{
	int		i;
	int		v;

	gl->vertices = (GLfloat *)malloc(sizeof(GLfloat) * gl->nb_vertices * 3);
	i = -1;
	v = -1;
	while (gl->line_file[++i])
	{
		if (gl->line_file[i][0] == 'v' && gl->line_file[i][1] == ' ')
		{
			v++;
			if (split_float(gl, i, v))
				return (1);
		}
	}
	return (0);
}

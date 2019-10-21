/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vertices.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/18 16:57:47 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 13:13:33 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
** ┌───────────────┐
** │ Split float   │
** └───────────────┘
** For v lines (triangle vertexes) of .obj file, get the 3 float cooridnates
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
		if (gl->line_file[i][0] == 'v')
		{
			v++;
			if (split_float(gl, i, v))
				return (1);
		}
	}
	return (0);
}

/*
** ┌───────────────┐
** │ Split integer │
** └───────────────┘
** For f lines (triangle indices) of .obj file, get the 3 integer indices
** Warning : indices of vertices start to 0 in vbo and to 1 in .obj
*/

static int	split_int(t_gl *gl, int i, int f)
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
		gl->indices[f * 3 + j] = atoi(p) - 1;
	}
	return (0);
}

int			make_indices(t_gl *gl)
{
	int		i;
	int		f;

	gl->indices = (GLuint *)malloc(sizeof(GLuint) * gl->nb_indices * 3);
	i = -1;
	f = -1;
	while (gl->line_file[++i])
	{
		if (gl->line_file[i][0] == 'f')
		{
			f++;
			if (split_int(gl, i, f))
				return (1);
		}
	}
	return (0);
}

void		count_quad_triange_indices(t_gl *gl, int i)
{
	int	j;
	int	nb_number;

	gl->nb_indices++;
	j = 0;
	nb_number = 0;
	while (gl->line_file[i][++j])
	{
		if (gl->line_file[i][j] == ' ')
			;
		else if (gl->line_file[i][j - 1] == ' ')
			nb_number++;
	}
	if (nb_number == 3)
		gl->nb_indices_triangle++;
	else if (nb_number == 4)
		gl->nb_indices_quad++;
	else
	{
		printf("Error : number of indices different of 3 or 4 on a line\n");
		exit(1);
	}
}

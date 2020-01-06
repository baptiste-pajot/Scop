/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   indices.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 10:55:25 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/06 13:52:03 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
** ┌───────────────┐
** │ Split integer │
** └───────────────┘
** For f lines (triangle or polygon indices) of .obj file,
** Get the 3 or n integer indices
** For polygon faces (quad and more), the function is called n - 2 times :
** For indices {0, 1, 2, 3}, it will create 2 triangles :
** {0, 1, 2} and {0, 2, 3}
** Warning : indices of vertices start to 0 in vbo and to 1 in .obj
*/

static int	split_int(t_gl *gl, int i, int f, int offset_polygon)
{
	int		j;
	int		k;
	char	*p;

	j = -1;
	while (++j < 3 + offset_polygon)
	{
		if (j == 0)
		{
			p = strchr(gl->line_file[i], ' ');
			gl->indices[f * 3] = atoi(p) - 1;
		}
		else
			p = strchr(p, ' ');
		if (!p)
			return (1);
		p++;
		k = (j == 0) ? j : j - offset_polygon;
		if (k > 0 && k < 3)
			gl->indices[f * 3 + k] = atoi(p) - 1;
	}
	return (0);
}

/*
** ┌───────────────┐
** │ Make indices  │
** └───────────────┘
** Make indices table with only one triangle by line
** A polygon will be split in several triangle
*/

int			make_indices(t_gl *gl)
{
	int		i;
	int		j;
	int		f;
	int		nb_pt_polygon;

	if (!(gl->indices = (GLuint *)malloc(sizeof(GLuint) * gl->nb_indices * 3)))
		return (1);
	i = -1;
	f = -1;
	while (gl->line_file[++i])
	{
		if (gl->line_file[i][0] == 'f' && gl->line_file[i][1] == ' ')
		{
			j = -1;
			nb_pt_polygon = count_nb_indices(gl, i);
			while (++j < nb_pt_polygon - 2)
			{
				f++;
				if (split_int(gl, i, f, j))
					return (1);
			}
		}
	}
	return (0);
}

/*
** ┌───────────────────┐
** │ Count nb indices  │
** └───────────────────┘
** Count the number of indices in a "f ..." line of the obj file
*/

int			count_nb_indices(t_gl *gl, int i)
{
	int	j;
	int	nb_number;

	j = 0;
	nb_number = 0;
	while (gl->line_file[i][++j])
	{
		if (gl->line_file[i][j] != ' ' &&
			gl->line_file[i][j - 1] == ' ')
			nb_number++;
	}
	return (nb_number);
}

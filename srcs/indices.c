/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   indices.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 10:55:25 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/22 17:10:33 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
** ┌───────────────┐
** │ Split integer │
** └───────────────┘
** For f lines (triangle or quad indices) of .obj file,
** get the 3 or 4 integer indices
** For quad faces, the function is called 2 times :
** one with bis = 0 and a second time with bis = 1
** For indices {0, 1, 2, 3}, tt will create 2 triangles :
** {0, 1, 2} and {0, 2, 3}
** Warning : indices of vertices start to 0 in vbo and to 1 in .obj
*/

static int	split_int(t_gl *gl, int i, int f, int bis)
{
	int		j;
	int		k;
	char	*p;

	j = -1;
	while (++j < 3 + bis)
	{
		if (j == 0)
			p = strchr(gl->line_file[i], ' ');
		else
			p = strchr(p, ' ');
		if (!p)
			return (1);
		p++;
		if (bis && j != 1)
			k = (j == 0) ? j : j - 1;
		if (!bis)
			k = j;
		gl->indices[f * 3 + k] = atoi(p) - 1;
	}
	return (0);
}

int			make_indices(t_gl *gl)
{
	int		i;
	int		f;

	gl->indices = (GLuint *)malloc(sizeof(GLuint) *
		(gl->nb_indices_triangle + 2 * gl->nb_indices_quad) * 3);
	i = -1;
	f = -1;
	while (gl->line_file[++i])
	{
		if (gl->line_file[i][0] == 'f' && gl->line_file[i][1] == ' ')
		{
			f++;
			if (split_int(gl, i, f, 0))
				return (1);
			if (count_nb_indices(gl, i) == 4)
			{
				f++;
				if (split_int(gl, i, f, 1))
					return (1);
			}
		}
	}
	return (0);
}

int			count_nb_indices(t_gl *gl, int i)
{
	int	j;
	int	nb_number;

	j = 0;
	nb_number = 0;
	while (gl->line_file[i][++j])
	{
		if (gl->line_file[i][j] == ' ')
			;
		else if (gl->line_file[i][j - 1] == ' ')
			nb_number++;
	}
	return (nb_number);
}

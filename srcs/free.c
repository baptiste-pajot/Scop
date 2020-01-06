/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/06 14:31:54 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/06 14:47:59 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

void		free_gl_struct(t_gl *gl)
{
	int		i;

	if (gl->indices)
		free(gl->indices);
	if (gl->vertices)
		free(gl->vertices);
	if (gl->txt_file)
		free(gl->txt_file);
	if (gl->line_file)
		free(gl->line_file);
	i = -1;
	while (++i < 3)
	{
		if (gl->texture[i].bmp)
			free(gl->texture[i].bmp);
	}
}

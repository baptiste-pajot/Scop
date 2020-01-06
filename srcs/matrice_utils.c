/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrice_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/16 18:42:15 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/06 16:01:15 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

GLfloat		*mat_zero(void)
{
	GLfloat	*matrice;
	int		i;

	i = -1;
	if ((matrice = (GLfloat *)malloc(16 * sizeof(GLfloat))) == NULL)
		return (NULL);
	while (++i < 16)
		matrice[i] = 0.0;
	return (matrice);
}

GLfloat		*mat_mult(GLfloat *mat1, GLfloat *mat2)
{
	int		i;
	int		j;
	GLfloat *mat_res;

	mat_res = mat_zero();
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			mat_res[i * 4 + j] = mat1[i * 4] * mat2[j] +
				mat1[i * 4 + 1] * mat2[j + 4] +
				mat1[i * 4 + 2] * mat2[j + 8] +
				mat1[i * 4 + 3] * mat2[j + 12];
	}
	return (mat_res);
}

void		mat_print(GLfloat *mat, char *name)
{
	int		i;
	int		j;

	dprintf(1, "%s\n", name);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			dprintf(1, "%f ", mat[i * 4 + j]);
		dprintf(1, "\n");
	}
}

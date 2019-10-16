/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrice_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/16 18:42:15 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/16 18:42:18 by bpajot      ###    #+. /#+    ###.fr     */
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

/*GLfloat	    *mat_transpose(GLfloat *mat)
{
	int		i;
	int		j;
	float	tmp;

	i = -1;
	while (++i < 4)
	{
		j = i;
		while (++j < 4)
		{
			tmp = mat[i * 4 + j];
			mat[i * 4 + j] = mat [j * 4 + i];
			mat[j * 4 + i] = tmp;
		}
	}
	return (mat);
}

GLfloat	    *mat_translate(float x, float y, float z)
{
	GLfloat	*matrice;

	matrice = mat_zero();
	matrice[3] = x;
	matrice[7] = y;
	matrice[11] = z;
	matrice[0] = 1.0;
	matrice[5] = 1.0;
	matrice[10] = 1.0;
	matrice[15] = 1.0;
	return (matrice);
}

GLfloat	    *mat_mult(GLfloat *mat1, GLfloat *mat2)
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
			mat_res[i * 4 + j] = mat1[] * mat2[] + mat1[] * mat2[] + mat1[] * mat2[] + mat1[] * mat2[];
	}
	return (mat_res);
}*/

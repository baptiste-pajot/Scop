/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrice_tr_proj.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 15:19:14 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 16:28:25 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

GLfloat		*mat_projection(void)
{
	GLfloat	*matrice;
	float	s;

	s = 1 / tan(M_PI / 180.0 * FOV / 2);
	matrice = mat_zero();
	matrice[0] = s * W_HEIGHT / W_WIDTH;
	matrice[5] = s;
	matrice[10] = -FAR / (FAR - NEAR);
	matrice[11] = -1.0;
	matrice[14] = -FAR * NEAR / (FAR - NEAR);
	return (matrice);
}

GLfloat		*mat_transpose(GLfloat *mat)
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
			mat[i * 4 + j] = mat[j * 4 + i];
			mat[j * 4 + i] = tmp;
		}
	}
	return (mat);
}

GLfloat		*mat_translate(float x, float y, float z)
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

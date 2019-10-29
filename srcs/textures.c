/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   textures.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/24 14:41:57 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/29 11:29:43 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

static void    make_uv(t_gl *gl)
{
    int     i;
    int     v;

	gl->uv = (GLfloat *)malloc(sizeof(GLfloat) *
		(gl->nb_indices_triangle + 2 * gl->nb_indices_quad) * 6);
	i = -1;
    while (++i < gl->nb_indices_triangle + 2 * gl->nb_indices_quad)
    {
        v = -1;
        while (++v < 3)
        {   
            if (!v) 
            {
                gl->uv[(i + v) * 2 ] = 0;
                gl->uv[(i + v) * 2 + 1] = 0;
            }
            else if (v == 1)
            {
                gl->uv[(i + v) * 2 ] = 1;
                gl->uv[(i + v) * 2 + 1] = 0;
            }
            else
            {
                gl->uv[(i + v) * 2 ] = 0;
                gl->uv[(i + v) * 2 + 1] = 1;
            }
        }
    }
}

void            manage_texture(t_gl *gl)
{
    int     len;

    if (!(len = open_read_file("./textures/chaton.bmp", &(gl->texture.bmp))))
        exit(printf("Error during reading the texture file\n"));
    if (len < 54 || gl->texture.bmp[0] != 'B' || gl->texture.bmp[1] != 'M')
        exit(printf("The texture file is not a correct BMP file\n"));
    gl->texture.dataPos = *(int*)&(gl->texture.bmp[0x0A]);
    gl->texture.imageSize = *(int*)&(gl->texture.bmp[0x22]);
    gl->texture.witdh = *(int*)&(gl->texture.bmp[0x12]);
    gl->texture.height = *(int*)&(gl->texture.bmp[0x16]);
    gl->texture.data = &(gl->texture.bmp[gl->texture.dataPos]);
    printf("dataPos = %d\n", gl->texture.dataPos);
    printf("imageSize = %d\n", gl->texture.imageSize );
    printf("width = %d\n", gl->texture.witdh);
    printf("height = %d\n\n", gl->texture.height);
    make_uv(gl);
}

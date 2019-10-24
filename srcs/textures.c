/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   textures.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/24 14:41:57 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 15:53:51 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

void        manage_texture(t_gl *gl)
{
    int     len;

    if (!(len = open_read_file("./textures/chaton.bmp", &(gl->texture))))
        exit(printf("Error during reading the texture file\n"));
    if (len < 54 || gl->texture[0] != 'B' || gl->texture[1] != 'M')
        exit(printf("The texture file is not a correct BMP file\n"));
    printf("dataPos = %d\n", *(int*)&(gl->texture[0x0A]));
    printf("imageSize = %d\n", *(int*)&(gl->texture[0x22]));
    printf("width = %d\n", *(int*)&(gl->texture[0x12]));
    printf("height = %d\n\n", *(int*)&(gl->texture[0x16]));
}

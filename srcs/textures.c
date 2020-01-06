/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   textures.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/24 14:41:57 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/06 14:50:28 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

static char		*strjoin3(char *s1, char *s2, char *s3)
{
	int		l1;
	int		l2;
	int		l3;
	char	*s;

	l1 = strlen(s1);
	l2 = strlen(s2);
	l3 = strlen(s3);
	if (!(s = (char*)malloc(sizeof(*s) * (l1 + l2 + l3 + 1))))
		return (NULL);
	strcpy(s, s1);
	strcat(s, s2);
	strcat(s, s3);
	return (s);
}

static void		free_str(char **s)
{
	if (s)
	{
		free(*s);
		*s = NULL;
	}
}

static char		*get_texture_name(int i)
{
	if (!i)
		return ("chaton");
	else if (i == 1)
		return ("poney");
	else
		return ("licorne");
}

static void		manage_texture_2(t_gl *gl, int i)
{
	gl->texture[i].data_pos = *(int *)&(gl->texture[i].bmp[0x0A]);
	gl->texture[i].image_size = *(int *)&(gl->texture[i].bmp[0x22]);
	gl->texture[i].witdh = *(int *)&(gl->texture[i].bmp[0x12]);
	gl->texture[i].height = *(int *)&(gl->texture[i].bmp[0x16]);
	gl->texture[i].data = &(gl->texture[i].bmp[gl->texture[i].data_pos]);
}

void			manage_texture(t_gl *gl)
{
	int		len;
	int		i;
	char	*path;

	i = -1;
	while (++i < 3)
	{
		path = strjoin3("./textures/", get_texture_name(i), ".bmp");
		if (!(len = open_read_file(path, &(gl->texture[i].bmp))))
		{
			free_str(&path);
			free_gl_struct(gl);
			exit(printf("Error during reading the texture file\n"));
		}
		free_str(&path);
		if (len < 54 || gl->texture[i].bmp[0] != 'B' ||
			gl->texture[i].bmp[1] != 'M')
		{
			free_gl_struct(gl);
			exit(printf("The texture file is not a correct BMP file\n"));
		}
		manage_texture_2(gl, i);
	}
}

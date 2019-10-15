/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scop.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 11:31:07 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 16:52:50 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "../minilibx_macos/mlx.h"
# include "../minilibx_macos/mlx_opengl.h"
# include <OpenGL/gl3.h>

# define W_HEIGHT			800
# define W_WIDTH			800
# define W_NAME				"SCOP"

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*image;
	int			bpp;
	int			endian;
}				t_env;

typedef struct	s_gl
{
	GLfloat		*vertices;
	GLuint		*indices;
	GLuint		vao;
	GLuint		vbov;
	GLuint		vboi;
	GLuint		vs;
	GLuint		fs;
	GLuint		sp;
	const char	*txt_vs;
	const char	*txt_fs;
}				t_gl;

void			manage_vbo(t_gl *gl);
void			manage_shader(t_gl *gl);

#endif

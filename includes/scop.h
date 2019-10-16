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
# include <time.h>
# include "../minilibx_macos/mlx.h"
# include "../minilibx_macos/mlx_opengl.h"
# include <OpenGL/gl3.h>

# define W_HEIGHT			800
# define W_WIDTH			800
# define W_NAME				"SCOP"
# define NEAR 				1.0
# define FAR				100.0
# define FOV				60

typedef struct	s_gl
{
	void		*mlx;
	void		*win;
	GLfloat		*vertices;
	GLuint		*indices;
	GLuint		vao;
	GLuint		vbov;
	GLuint		vboc;
	GLuint		vboi;
	GLuint		vs;
	GLuint		fs;
	GLuint		sp;
	const char	*txt_vs;
	const char	*txt_fs;
}				t_gl;

void			display(t_gl *gl, float angle);
void			manage_vbo(t_gl *gl);
void			manage_shader(t_gl *gl, float angle);
int				refresh_funct(t_gl *gl);
int				red_cross_funct(void *pt);
int				keyboard_funct(int keycode, void *pt);
GLfloat			*mat_rot(char axe, float rad_angle);
GLfloat			*mat_proj(void);
GLfloat			*mat_zero(void);

#endif

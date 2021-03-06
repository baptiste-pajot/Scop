/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scop.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 11:31:07 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 14:00:00 by bpajot      ###    #+. /#+    ###.fr     */
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
# define NEAR 				0.1
# define FAR				1000
# define FOV				60
# define KEY_ESC			53
# define KEY_Q				12
# define KEY_LEFT			123
# define KEY_RIGHT			124
# define KEY_DOWN			125
# define KEY_UP				126
# define KEY_PAGE_DOWN		121
# define KEY_PAGE_UP		116
# define KEY_1				83
# define KEY_2				84
# define KEY_3				85
# define KEY_4				86
# define KEY_5				87
# define KEY_6				88
# define KEY_7				89
# define KEY_8				91
# define KEY_9				92
# define KEY_NUM			71
# define KEY_SLASH			75
# define KEY_CROSS			67
# define KEY_MINUS			78
# define KEY_OFFSET_TR		0.1

typedef struct	s_center
{
	GLfloat		min[3];
	GLfloat		max[3];
	GLfloat		mean[3];
	GLfloat		max_size;
	GLfloat		cam_offset_x;
	GLfloat		cam_offset_y;
	GLfloat		cam_offset_z;
	GLfloat		cam_rot_x;
	GLfloat		cam_rot_y;
	GLfloat		cam_rot_z;
	GLfloat		rad_angle;
	GLfloat		old_angle;
}				t_center;

typedef struct	s_texture
{
	int			data_pos;
	int			image_size;
	int			width;
	int			height;
	char		*bmp;
	char		*data;
}				t_texture;

typedef enum	e_paint
{
	chaton,
	poney,
	licorne,
	color
}				t_paint;

typedef struct	s_gl
{
	int			argc;
	char		**argv;
	void		*mlx;
	void		*win;
	GLfloat		*vertices;
	GLuint		*indices;
	GLuint		vao;
	GLuint		vbov;
	GLuint		vboc;
	GLuint		vbot;
	GLuint		vbot_prev;
	GLuint		vboi;
	GLuint		vs;
	GLuint		fs;
	GLuint		sp;
	const char	*txt_vs;
	const char	*txt_fs;
	char		*txt_file;
	int			nb_line_file;
	int			nb_vertices;
	int			nb_indices;
	int			nb_indices_triangle;
	int			nb_indices_polygon;
	char		**line_file;
	t_center	center;
	t_texture	texture[3];
	t_paint		paint;
	t_paint		paint_prev;
	float		ratio;
	GLfloat		*mat_proj;
}				t_gl;

void			display(t_gl *gl);
void			manage_vbo(t_gl *gl);
void			manage_shader(t_gl *gl);
int				refresh_funct(t_gl *gl);
int				keyboard_funct(int keycode, t_gl *gl);
GLfloat			*mat_rot(char axe, float rad_angle);
GLfloat			*mat_projection(void);
GLfloat			*mat_zero(void);
GLfloat			*mat_transpose(GLfloat *mat);
GLfloat			*mat_translate(float x, float y, float z);
GLfloat			*mat_mult(GLfloat *mat1, GLfloat *mat2);
void			mat_print(GLfloat *mat, char *name);
int				make_vertices(t_gl *gl);
int				make_indices(t_gl *gl);
void			parse_file(t_gl *gl);
int				open_read_file(char *path, char **s);
int				count_nb_indices(t_gl *gl, int i);
void			calculate_center(t_gl *gl);
void			manage_texture(t_gl *gl);
char			*fragment_shader_color_to_color(void);
char			*fragment_shader_color_to_texture(void);
char			*fragment_shader_texture_to_color(void);
char			*fragment_shader_texture_to_texture(void);
void			init_struct(t_gl *gl);
void			free_gl_struct(t_gl *gl);
GLfloat			*mat_view(t_gl *gl);
GLfloat			*mat_model(t_gl *gl);

#endif

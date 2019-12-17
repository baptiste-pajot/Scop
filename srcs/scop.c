/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scop.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 11:30:49 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/17 19:29:02 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

static void		delete_gl(t_gl *gl)
{
	glDeleteProgram(gl->sp);
	glDeleteShader(gl->vs);
	glDeleteShader(gl->fs);
	glDeleteBuffers(1, &(gl->vbov));
	glDeleteBuffers(1, &(gl->vboi));
	glDeleteBuffers(1, &(gl->vbot));
	glDeleteBuffers(1, &(gl->vbot_prev));
	glDeleteVertexArrays(1, &(gl->vao));
}

void			display(t_gl *gl)
{
	manage_vbo(gl);
	manage_shader(gl);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES, gl->nb_indices * 3, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 1);
	glUseProgram(0);
	delete_gl(gl);
}

static void		manage_file(t_gl *gl)
{
	char	*pt;

	if (gl->argc == 2 && (pt = strcasestr(gl->argv[1], ".obj")) &&
		pt[4] == '\0')
	{
		printf("Path file : %s\n\n", gl->argv[1]);
		if (!open_read_file(gl->argv[1], &(gl->txt_file)))
		{
			printf("Error during reading the file\n");
			exit(1);
		}
		parse_file(gl);
	}
	else
	{
		printf("usage : ./scop path/filename.obj\n");
		printf("You forget the path file argument or");
		printf(" the path is wrong or the file is not a .obj\n");
		exit(1);
	}
	manage_texture(gl);
}

/*
** ┌───────────────────────┐
** │ Red Cross Function    │
** └───────────────────────┘
** Close Graphic Window when you click on the Red Cross on the top-left corner
*/

int				red_cross_funct(void *pt)
{
	pt = NULL;
	exit(0);
}

/*
** ┌───────┐
** │ Main  │
** └───────┘
** mlx initialisation & loop & event function
** to get information on Graphic Card & OpenGl version :
** printf("Graphic Card : %s\n", (char *)glGetString(GL_RENDERER));
** printf("Version : %s\n", (char *)glGetString(GL_VERSION));
** printf("GLSL : %s\n\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
*/

int				main(int argc, char **argv)
{
	t_gl gl;

	gl.argc = argc;
	gl.argv = argv;
	gl.paint = color;
	gl.paint_prev = gl.paint;
	gl.ratio = 1.0;
	gl.center.rad_angle = 0.0;
	gl.center.old_angle = 0.0;
	manage_file(&gl);
	gl.mlx = mlx_init();
	gl.win = mlx_new_opengl_window(gl.mlx, W_WIDTH, W_HEIGHT, W_NAME);
	mlx_opengl_window_set_context(gl.win);
	mlx_key_hook(gl.win, &keyboard_funct, &gl);
	mlx_hook(gl.win, 17, (1L << 17), &red_cross_funct, NULL);
	mlx_loop_hook(gl.mlx, &refresh_funct, &gl);
	mlx_loop(gl.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scop.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 11:30:49 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 12:48:02 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

static void	delete_gl(t_gl *gl)
{
	glDeleteProgram(gl->sp);
	glDeleteShader(gl->vs);
	glDeleteShader(gl->fs);
	glDeleteBuffers(1, &(gl->vbov));
	glDeleteBuffers(1, &(gl->vboc));
	glDeleteBuffers(1, &(gl->vboi));
	glDeleteVertexArrays(1, &(gl->vao));
}

void		display(t_gl *gl, float angle)
{
	manage_vbo(gl);
	manage_shader(gl, angle);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (gl->nb_indices)
		glDrawElements(GL_TRIANGLES, gl->nb_indices * 3, GL_UNSIGNED_INT, 0);
	else
		glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 1);
	glUseProgram(0);
	delete_gl(gl);
}

static void	display_info(void)
{
	printf("Graphic Card : %s\n", (char *)glGetString(GL_RENDERER));
	printf("Version : %s\n", (char *)glGetString(GL_VERSION));
	printf("GLSL : %s\n\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
}

int			main(int argc, char **argv)
{
	t_gl gl;

	gl.argc = argc;
	gl.argv = argv;
	manage_file(&gl);
	gl.mlx = mlx_init();
	gl.win = mlx_new_opengl_window(gl.mlx, W_WIDTH, W_HEIGHT, W_NAME);
	mlx_opengl_window_set_context(gl.win);
	display_info();
	mlx_key_hook(gl.win, &keyboard_funct, NULL);
	mlx_hook(gl.win, 17, (1L << 17), &red_cross_funct, NULL);
	mlx_loop_hook(gl.mlx, &refresh_funct, &gl);
	mlx_loop(gl.mlx);
	return (0);
}

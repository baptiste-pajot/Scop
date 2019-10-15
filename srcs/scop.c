/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scop.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 11:30:49 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 12:24:05 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

static void			delete_gl(t_gl *gl)
{
	glDeleteProgram(gl->sp);
	glDeleteShader(gl->vs);
	glDeleteShader(gl->fs);
	glDeleteBuffers(1, &(gl->vbov));
	glDeleteBuffers(1, &(gl->vboi));
	glDeleteVertexArrays(1, &(gl->vao));
}

static void			display(t_gl *gl)
{
	manage_vbo(gl);
	manage_shader(gl);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	delete_gl(gl);
}

static void			display_info(void)
{
	printf("Graphic Card : %s\n", (char *)glGetString(GL_RENDERER));
	printf("Version : %s\n", (char *)glGetString(GL_VERSION));
	printf("GLSL : %s\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
}

static int			keyboard_funct(int keycode, void *pt)
{
	if (keycode == 53 || keycode == 12)
	{
		pt = NULL;
		exit(0);
	}
	return(0);
}

static int			red_cross_funct(void *pt)
{
	pt = NULL;
	exit(0);
}

int					main(void)
{
	t_env	e;
	t_gl	gl;

	e.mlx = mlx_init();
	e.win = mlx_new_opengl_window(e.mlx, W_WIDTH, W_HEIGHT, W_NAME);
	mlx_opengl_window_set_context(e.win);
	display_info();
	display(&gl);
	mlx_opengl_swap_buffers(e.win);
	mlx_key_hook(e.win, keyboard_funct, NULL);
	mlx_hook(e.win, 17, (1L<<17), red_cross_funct, NULL);
	mlx_loop(e.mlx);
	return (0);
}

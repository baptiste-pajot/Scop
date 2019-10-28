/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vbo.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 14:22:35 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 16:49:05 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
** ┌───────────────┐
** │ Create VAO    │
** └───────────────┘
** Generate and Activate the Vertex Array Object
*/

static void		create_vao(t_gl *gl)
{
	glGenVertexArrays(1, &(gl->vao));
	glBindVertexArray(gl->vao);
}

/*
** ┌────────────────────────┐
** │ Create VBO Vertices    │
** └────────────────────────┘
** Generate and activate the Vertex Buffer Object Vertices
** Then, copy data and prepare for Vertex Shader
*/

static void		create_vbov(t_gl *gl)
{
	glGenBuffers(1, &(gl->vbov));
	glBindBuffer(GL_ARRAY_BUFFER, gl->vbov);
	glBufferData(GL_ARRAY_BUFFER, 3 * gl->nb_vertices * sizeof(GLfloat),
		gl->vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

/*
** ┌────────────────────────┐
** │ Create VBO Texture     │
** └────────────────────────┘
*/

static void		create_vbot(t_gl *gl)
{
	glGenTextures(1, &(gl->vbot));
	glBindTexture(GL_TEXTURE_2D, gl->vbot);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, gl->texture.witdh,
		gl->texture.height, 0, GL_BGR, GL_UNSIGNED_BYTE, gl->texture.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

/*
** ┌────────────────────────┐
** │ Create VBO Colors      │
** └────────────────────────┘
** Generate and Activate the Vertex Buffer Object Colors
** Then, copy data and prepare for Vertex Shader
*/

/*static void		create_vboc(t_gl *gl)
{
	glGenBuffers(1, &(gl->vboc));
	glBindBuffer(GL_ARRAY_BUFFER, gl->vboc);
	glBufferData(GL_ARRAY_BUFFER, 3 * gl->nb_vertices * sizeof(GLfloat),
		gl->colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}*/

/*
** ┌────────────────────────┐
** │ Create VBO Indices     │
** └────────────────────────┘
** Generate and Activate the Vertex Buffer Object Indices
** Then, Copy data
*/

static void		create_vboi(t_gl *gl)
{
	glGenBuffers(1, &(gl->vboi));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl->vboi);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		3 * (gl->nb_indices_triangle + 2 * gl->nb_indices_quad)
		* sizeof(GLuint), gl->indices, GL_STATIC_DRAW);
}

void			manage_vbo(t_gl *gl)
{
	create_vao(gl);
	create_vbov(gl);
	//create_vboc(gl);
	create_vbot(gl);
	create_vboi(gl);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shader2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 15:57:33 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/22 16:15:48 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

char		*fragment_shader_color_to_color(void)
{
	return ("#version 410\n"
	"in vec2 textureUV;\n"
	"out vec4 glFragColor;\n"
	"uniform float ratio;\n"
	"uniform sampler2D textureBMP;\n"
	"uniform sampler2D texturePrev;\n"
	"void main() {\n"
	"	float	grey;\n"
	"	grey = (gl_PrimitiveID % 6) / 10.0;\n"
	"	glFragColor = vec4(grey, grey, grey, 1.0);\n"
	"}\n");
}

char		*fragment_shader_texture_to_color(void)
{
	return ("#version 410\n"
	"in vec2 textureUV;\n"
	"out vec4 glFragColor;\n"
	"uniform float ratio;\n"
	"uniform sampler2D textureBMP;\n"
	"uniform sampler2D texturePrev;\n"
	"void main() {\n"
	"	float	grey;\n"
	"	grey = (gl_PrimitiveID % 6) / 10.0;\n"
	"	glFragColor = ratio * vec4(grey, grey, grey, 1.0)"
	"		+ (1.0 - ratio) * texture(texturePrev, textureUV);\n"
	"}\n");
}

char		*fragment_shader_color_to_texture(void)
{
	return ("#version 410\n"
	"in vec2 textureUV;\n"
	"out vec4 glFragColor;\n"
	"uniform float ratio;\n"
	"uniform sampler2D textureBMP;\n"
	"uniform sampler2D texturePrev;\n"
	"void main() {\n"
	"	float	grey;\n"
	"	grey = (gl_PrimitiveID % 6) / 10.0;\n"
	"	glFragColor = ratio * texture(textureBMP, textureUV)"
	"		+ (1.0 - ratio) * vec4(grey, grey, grey, 1.0);\n"
	"}\n");
}

char		*fragment_shader_texture_to_texture(void)
{
	return ("#version 410\n"
	"in vec2 textureUV;\n"
	"out vec4 glFragColor;\n"
	"uniform float ratio;\n"
	"uniform sampler2D textureBMP;\n"
	"uniform sampler2D texturePrev;\n"
	"void main() {\n"
	"	float	grey;\n"
	"	grey = (gl_PrimitiveID % 6) / 10.0;\n"
	"	glFragColor = ratio * texture(textureBMP, textureUV)"
	"		+ (1.0 - ratio) * texture(texturePrev, textureUV);\n"
	"}\n");
}

#shader vertex
#version 330 core
layout (location=0) in vec2 VertexPosition;
layout (location=1) in vec2 aTexCoord;
out vec2 TexCoord;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
void main()
{
	TexCoord = aTexCoord;
	gl_Position = proj*view*model*vec4(VertexPosition.x, VertexPosition.y, 0.f, 1.f);
};

#shader fragment
#version 330 core

layout (location=0) out vec4 Fragcolor;
in vec2 TexCoord;
uniform sampler2D Tex;
//uniform float b;
void main()
{	
	Fragcolor = texture(Tex, TexCoord);
	//if (b)
	//color = vec4(b, 0.3, 0.8, 1.0);
	//else
		//color = vec4(0.0, 1.0, 0.0, 1.0);
};
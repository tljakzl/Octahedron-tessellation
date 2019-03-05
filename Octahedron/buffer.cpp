#include "pch.h"
#include "buffer.h"


void buffer::gen(std::vector<GLfloat> vec)
{

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vec.size() * sizeof(GLfloat), vec.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
void buffer::delete_buff() const
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(2, &vao);
	glDeleteBuffers(2, &vbo);
}
void buffer::bind() const
{
	glBindVertexArray(vao);
}

buffer::buffer(): vao(0), vbo(0)
{
}


buffer::~buffer()
{
}


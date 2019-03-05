#pragma once
class buffer
{
	
public:
	GLuint vao;
	GLuint vbo;
	
	buffer();
	void gen(std::vector<GLfloat>);
	void delete_buff() const;
	void bind() const;
	~buffer();
};

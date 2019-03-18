#pragma once
#define GLEW_STATIC


#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <vector>

struct point
{
	point(GLfloat const x = 0, GLfloat const y = 0, GLfloat const  z = 0) :x_(x), y_(y), z_(z) {}
	point& operator=(point const & assignment)
	{
		if (this != &assignment)
		{
			x_ = assignment.x_;
			y_ = assignment.y_;
			z_ = assignment.z_;
		}
		return *this;
	}
	point& operator=(double const & assignment)
	{
		x_ = assignment;
		y_ = assignment;
		z_ = assignment;
		return *this;
	}
	point operator-(point const & subtrahend) const
	{
		point temp = *this;
		temp.x_ -= subtrahend.x_;
		temp.y_ -= subtrahend.y_;
		temp.z_ -= subtrahend.z_;
		return temp;
	}

	point operator+(point const & subtrahend) const
	{
		point temp = *this;
		temp.x_ += subtrahend.x_;
		temp.y_ += subtrahend.y_;
		temp.z_ += subtrahend.z_;
		return temp;
	}
	point operator/(GLfloat const & divisor) const
	{
		point temp = *this;
		temp.x_ /= divisor;
		temp.y_ /= divisor;
		temp.z_ /= divisor;
		return temp;
	}

	GLfloat  operator[](size_t i) const
	{
		if (i == 0)
			return x_;
		if (i == 1)
			return y_;
		if (i == 2)
			return z_;
		throw;
	}

	GLfloat& operator[](size_t i)
	{
		if (i == 0)
			return x_;
		if (i == 1)
			return y_;
		if (i == 2)
			return z_;
		throw;
	}
private:
	GLfloat x_;
	GLfloat y_;
	GLfloat z_;
};
struct triangle
{
	explicit triangle(point const a = 0, point const b = 0, point const c = 0) :a_(a), b_(b), c_(c) {}

	point operator[](const size_t i) const
	{
		if (i == 0)
			return a_;
		if (i == 1)
			return b_;
		if (i == 2)
			return c_;
		throw;
	}

	point& operator[](const size_t i)
	{
		if (i == 0)
			return a_;
		if (i == 1)
			return b_;
		if (i == 2)
			return c_;
		throw;
	}
private:
	point a_;
	point b_;
	point c_;
};


std::vector<GLfloat> tessleation(std::vector<GLfloat>const & mass);
void do_movement();
void disclaimer();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void use_tessleation(std::vector<GLfloat>& test);
std::vector<triangle> fragmentation(triangle const & specimen);

const size_t max_tessellation = 6;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const GLfloat a = 0.5, b = 0.5, c = ((a + b)*sqrt(3)) / 2;

const std::vector<GLfloat>  sourse_octahedron = {
		-a, -0.0f, -b,  // Left 
		 a, -0.0f, -b,  // Right
		0.0f,  c,  0.0f,  // Top

		 a, -0.0f, -b,  // Left 
		 a, -0.0f,  b,  // Right
		0.0f, c,  0.0f,  // Top

		-a, -0.0f,  b,  // Left 
		 a, -0.0f,  b,  // Right
		0.0f, c,  0.0f,  // Top

		-a, -0.0f, -b,  // Left 
		-a, -0.0f,  b,  // Right
		0.0f, c,  0.0f,  // Top


		-a, -0.0f, -b,  // Left 
		 a, -0.0f, -b,  // Right
		0.0f,  -c,  0.0f,  // Top

		 a, -0.0f, -b,  // Left 
		 a, -0.0f,  b,  // Right
		0.0f, -c,  0.0f,  // Top

		-a, -0.0f,  b,  // Left 
		 a, -0.0f,  b,  // Right
		0.0f, -c,  0.0f,  // Top

		-a, -0.0f, -b,  // Left 
		-a, -0.0f,  b,  // Right
		0.0f, -c,  0.0f,  // Top

};






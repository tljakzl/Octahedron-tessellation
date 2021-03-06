
#include "pch.h"
#include "main.h"
#include "Shader.h"
#include "Camera.h"
#include "buffer.h"

namespace {
	buffer buff_oct;
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));			 // Исходное направление камеры
	bool keys[1024];										 // Кнопки
	GLfloat deltaTime = 0.0f;							 // Время, прошедшее между последним и текущим кадром
	GLfloat lastFrame = 0.0f;  							 // Время вывода последнего кадра
	GLfloat lastX = 00, lastY = 00;						 // Последнее положение мыши
	size_t current_tessell = 0;							 // Степень тесселяции
	std::vector<GLfloat>  octahedron = sourse_octahedron; // Исходная фигура
}

int main()
{

	//Инициализация GLFW
	glfwInit();
	//Настройка GLFW
	//Задается минимальная требуемая версия OpenGL. 
	//Мажорная 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//Минорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	disclaimer();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window, scroll_callback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}



	Shader spere_shader("path/to/shaders/Vertex.ver", "path/to/shaders/Farg.fg");

	buff_oct.gen(octahedron);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		do_movement();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		const glm::mat4 model;
		const glm::mat4 projection = glm::perspective(camera.Zoom, static_cast<float>(SCR_WIDTH) / SCR_HEIGHT, 0.1f, 100.0f);
		const glm::mat4 view = camera.GetViewMatrix();
		const float length = static_cast<float>(glfwGetTime());


		spere_shader.setM4fv("model", model);
		spere_shader.setM4fv("view", view);
		spere_shader.setM4fv("projection", projection);
		spere_shader.setFloat("length", length);
		spere_shader.Use();

		buff_oct.bind();
		glDrawArrays(GL_TRIANGLES, 0, octahedron.size());
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}
	buff_oct.delete_buff();
	glfwTerminate();
	return 0;
}



void use_tessleation(std::vector<GLfloat>& value)
{
	value = tessleation(value);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}



void tessell_up()
{
	if (current_tessell < max_tessellation)
	{
		++current_tessell;
		use_tessleation(octahedron);
		buff_oct.gen(octahedron);
	}
}


void tessell_down()
{

	if (current_tessell != 0)
	{
		--current_tessell;
		octahedron = sourse_octahedron;
		for (size_t i = 0; i != current_tessell; ++i)
		{
			use_tessleation(octahedron);
			buff_oct.gen(octahedron);
		}


	}
	if (current_tessell == 0)

	{
		octahedron = sourse_octahedron;
		buff_oct.gen(octahedron);
	}
}

void disclaimer()
{
	std::cout << "----Control keys----" << std::endl;
	std::cout << "Movement:" << std::endl;
	std::cout << "W - forward" << std::endl;
	std::cout << "S - back" << std::endl;
	std::cout << "D - right" << std::endl;
	std::cout << "A - left" << std::endl;
	std::cout << "Mouse - camera rotate" << std::endl;
	std::cout << "Up - add tessellation level" << std::endl;
	std::cout << "Down - remove tessellation level" << std::endl;
	std::cout << "P - point mode" << std::endl;
	std::cout << "L - line mode" << std::endl;
	std::cout << "F - fill mode" << std::endl;
}

void count()
{
	const auto numcoor = octahedron.size();
	const auto poincoor = numcoor / 3;
	const auto trlcoor = poincoor / 3;

	std::cout << "Coords:" << numcoor << std::endl;
	std::cout << "Points:" << poincoor << std::endl;
	std::cout << "Triangle:" << trlcoor << std::endl << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
	// и приложение после этого закроется

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_UP:
			tessell_up();
			count();
			break;
		case GLFW_KEY_DOWN:
			tessell_down();
			count();
			break;
		case  GLFW_KEY_P:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		case GLFW_KEY_F:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case GLFW_KEY_L:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		default: ;
		}
	}
}
void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	const GLfloat xoffset = xpos - lastX;
	const GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}


std::vector<GLfloat> tessleation(std::vector<GLfloat> const& mass)
{
	std::vector<GLfloat> output;
	for (size_t i = 0; i < mass.size();)
	{
		triangle temp_tiangle;

		for (size_t j = 0; j < 3; ++j)
		{
			for (size_t k = 0; k < 3; ++k)
			{
				temp_tiangle[j][k] = mass[i++];
			}
		}

		std::vector<triangle> frag = fragmentation(temp_tiangle);
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t h = 0; h < 3; h++)
			{
				for (size_t k = 0; k < 3; k++)
				{
					output.push_back(frag[j][h][k]);
				}
			}
		}

	}
	return output;
}


std::vector<triangle> fragmentation(triangle const & specimen)
{
	point const  middle_down = point(specimen[1] + specimen[0]) / 2.0f;
	point const  middle_left = point(specimen[2] + specimen[0]) / 2.0f;
	point const  middle_right = point(specimen[2] + specimen[1]) / 2.0f;

	std::vector<triangle> t = {
		   triangle(specimen[0], middle_down, middle_left),
		   triangle(middle_down, specimen[1], middle_right),
		   triangle(middle_left, middle_right, specimen[2]),
		   triangle(middle_left, middle_right, middle_down)
	};

	return t;
}

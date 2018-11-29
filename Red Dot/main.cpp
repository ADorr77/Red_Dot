//
// The main of the Project which sets up the window, renderer, and game loop.
// 
// Written by Aaron Dorrance
// 11/26/18


#include<glad.h>
#include<glfw3.h>
#include<iostream>
#include<vector>
#include"TowerDefense.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow * window);

int main()

{
	TowerDefense td;
	td.mapinit();
	std::cout << td.mapValue(3, 4) << std::endl;
	td.renderAscii();
	std::vector<Enemy> e(20, 1);
	Tower t1(6, 5, 1);
	for (int j = 0; j < 10; ++j) {
		e[j].setTimer(10 * j);
	}
	while (true) {
		Sleep(100);
		td.mapinit();
		td.mapSet(6, 5, 'T');
		t1.cool();
		for (int j = 0; j < e.size(); ++j) {
			e[j].advance();
			t1.detect(e[j].get_xPos(), e[j].get_yPos());

			
			td.mapSet((int)e[j].get_xPos(), (int)e[j].get_yPos(), 'e');
		}
		int c = t1.get_pnumber();
		while (c > 0) {
			t1.advanceProjectiles(c - 1);
			double x = t1.get_projectile_x(c - 1);
			double y = t1.get_projectile_y(c - 1);
			td.mapSet((int) x, (int) y, '.');
			for (int j = 0; j < e.size(); ++j) {
				if (e[j].detect(x, y)) {
					td.add_money(e[j].get_reward());
					e.erase(e.begin()+j);
					t1.eraseProjectile(c - 1);
				}
				
			}
			--c;
		}
		std::cout << "Money: " << td.get_money() << std::endl;
		td.renderAscii();
		//std::cout << e[0].get_xPos() << ", \t" << e[0].get_yPos() << "\t \t" << e[1].get_xPos() << ", \t" << e[1].get_yPos() << std::endl;
	}









	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
#endif

	GLFWwindow * window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// have to write shaders for opengl so that it knows how to process info
	// The code for these is stored in a cstring
	const char *vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n" // the position variable has attribute position 0
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n" // output color to the fragment shader
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n" // see how we directly give a vec3 to vec4's constructor
		"   ourColor = aColor;\n"
		"}\0";

	const char * fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 ourColor;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(ourColor, 1.0);\n"
		"}\n\0";

	// Compile the Vertex Shader 
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
	}

	// Compile the fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
	}

	// Link the shaders togeather 
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKER::LINK_FAILED" << std::endl << infoLog << std::endl;
	}

	// delete un-needed objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Way to draw a Triangle

	float data[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	unsigned int VBO, VAO; // Vertex Buffer Object that 
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// the vertex array object stores everything so bind first 
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // makes sure that the buffer is configured correctly
										// copies the vertex data into buffers memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// can unbind VBO after this because its bound to VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// can unbind VAO as well to avoid accidental modification 
	// generally unnesscary so generally won't unbind VAOs or VBOs if not nesscarry 
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		// input
		glfwPollEvents();
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Activate the shader
		glUseProgram(shaderProgram);

		// Draw Triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		// swap buffer to show screen
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
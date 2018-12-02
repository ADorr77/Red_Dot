#include "Render.h"
#include <string>
#include <cmath>

#define PI 3.14159265

void getPolygon(int sides, float * vertices);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


Render::Render()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(800, 800, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		window = NULL;
	}

	glViewport(0, 0, 800, 800);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	numMapPoints = 0;

	// create Vertex Array Objects for all regular Polygons with 25 or less sides
	glGenVertexArrays(MAX_SIDES - 2, shapesArray);
	glGenBuffers(MAX_SIDES - 2, shapesBuffer);
	glGenBuffers(MAX_SIDES - 2, shapesElements);
	float vertices[MAX_SIDES * 2];

	// generate the order in which to render the points
	unsigned int order[MAX_SIDES * 3];

	for (int i = 0; i < MAX_SIDES * 3; i +=3)
	{
		order[i] = 0;
		order[i + 1] = (i / 3) + 1;
		order[i + 2] = (i / 3) + 2;
	}

	// create the vertex array objects
	for (int i = 0; i < MAX_SIDES - 2; i++)
	{
		getPolygon(i + 3, vertices);

		glBindVertexArray(shapesArray[i]);

		glBindBuffer(GL_ARRAY_BUFFER, shapesBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapesElements[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(order), order, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);	// Vertex attributes stay the same
		glEnableVertexAttribArray(0);
	}
}

void getPolygon(int sides, float * vertices)
{
	if (sides < 3)
		sides = 3;
	if (sides > MAX_SIDES)
		sides = MAX_SIDES;

	double period = (2 * PI) / sides;
	
	for (int i = 0; i < sides * 2; i+=2)
	{
		vertices[i] = .25 * float(cos(period * i / 2));
		vertices[i+1] = .25 * float(sin(period * i / 2));
	}
}

// mess with this later
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Render::init(Dungeon& game)
{
	
}

void Render::init(TowerDefense& game)
{

	float squarePoints[] = {
		0.05f, 0.05f,
		//1.0f, 0.0f,
		//1.0f, 1.0f,
		//0.0f, 1.0f
		0.95f, 0.05f,
		0.95f, 0.95f,
		0.05f, 0.95f
	};

	unsigned int squareIndices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	std::vector<float> vertices;
	std::vector<unsigned int> indicies;
	unsigned int count = 0;

	for(int x = 0; x < game.width; x++)
	{
		for(int y = 0; y < game.height; y++)
		{
			if(game.get_map_value(x, y) == -37)
			{
				for (int i = 0; i < 4; i++)
				{
					vertices.push_back((x + squarePoints[2 * i] - 12.5) / 12.5);
					vertices.push_back((-1 * (y + squarePoints[(2 * i) + 1]) + 12.5) / 12.5);
				}

				for (int i = 0; i < 6; i++)
				{
					indicies.push_back(count + squareIndices[i]);
				}
				count += 4;
			}
			
		}
	}
	//add buttons at bottom
	for (int x = 0; x < 5; x++)
	{
		for (int y = 3; y < 5; y++)
		{
			for (int i = 0; i < 4; i++)
			{
				vertices.push_back((x + squarePoints[2 * i] - 2.5) / 2.5);
				vertices.push_back((-1 * (y + squarePoints[(2 * i) + 1]) + 2.5) / 2.5);
			}
			for (int i = 0; i < 6; i++)
			{
				indicies.push_back(count + squareIndices[i]);
			}
			count += 4;
			

		}
	}
	
	numMapPoints = indicies.size();
	
	float mapPoints[3000]; 
	unsigned int mapIndicies[3000];

	for (int i = 0; i < 3000; i++)
	{
		if (i < vertices.size())
			mapPoints[i] = vertices[i];
		else
			mapPoints[i] = 0;

		if (i < indicies.size())
			mapIndicies[i] = indicies[i];
		else
			mapIndicies[i] = 0;
	}

	glGenVertexArrays(1, &mapVAO);
	glGenBuffers(1, &mapVBO);
	glGenBuffers(1, &mapEBO);

	glBindVertexArray(mapVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mapVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mapPoints), mapPoints, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mapEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mapIndicies), mapIndicies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// create the shader obj for the map
	mapShader = Shader("mapVertShader.txt", "fragShader.txt");
}



void Render::render(const TowerDefense & game)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	mapShader.use();
	glBindVertexArray(mapVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mapEBO);
	glDrawElements(GL_TRIANGLES, numMapPoints, GL_UNSIGNED_INT, 0);

	//drawPolygon(5);

}

void Render::drawPolygon(int sides)
{
	if (sides < 3)
		sides = 3;
	if (sides > MAX_SIDES)
		sides = MAX_SIDES;

	glBindVertexArray(shapesArray[sides - 3]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapesElements[sides - 3]);
	glDrawElements(GL_TRIANGLES, (sides - 2) * 3, GL_UNSIGNED_INT, 0);
}


void Render::renderASCII(const Dungeon& dungeon)
{
	auto map = dungeon.get_map();

	std::vector<std::string> print(map.size(), "");

	for (int x = 0; x < map.size(); x++)
	{
		for (int y = 0; y < map[0].size(); y++)
		{
			if (map[x][y] == 0)
				print[y] += (char)219;
			else
				print[y] += ' ';
		}
	}

	const std::vector<Monster>& monsters = dungeon.get_monsters();

	for (int i = 0; i < monsters.size(); i++)
	{
		print[monsters[i].get_yPos()][monsters[i].get_xPos()] = 'M';
	}

	Hero hero = dungeon.get_hero();
	print[hero.get_yPos()][hero.get_xPos()] = 'H';

	for (int y = print.size() - 1; y >= 0; y--)
	{
		for (int x = 0; x < print[y].size(); x++)
		{
			std::cout << print[y][x] << print[y][x];
		}
		std::cout << std::endl;
	}
}




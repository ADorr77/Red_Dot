#include "Render.h"
#include <iostream>
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

	// create the vertex array objects for regular Polygons
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

	// create shader for game
	shader = Shader("vertShader.txt", "fragShader.txt");
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
		vertices[i] = 0.5 * float(cos(period * i / 2));
		vertices[i+1] = 0.5 * float(sin(period * i / 2));
	}
}

// mess with this later
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Render::init(Dungeon& game)
{
	float squarePoints[] = {
		0.05f, 0.05f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	unsigned int squareIndices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	std::vector<float> vertices;
	std::vector<unsigned int> indicies;
	const auto& map = game.get_map();
	unsigned int count = 0;

	for (int x = 0; x < map.size(); x++)
	{
		for(int y = 0; y < map[0].size(); y++)
		{
			if (map[x][y] == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					vertices.push_back(x + squarePoints[2 * i]);
					vertices.push_back(y + squarePoints[(2 * i) + 1]);
				}

				for (int i = 0; i < 6; i++)
				{
					indicies.push_back(count + squareIndices[i]);
				}
				count += 4;
			}
		}
	}

	numMapPoints = indicies.size();

	float mapPoints[80000];
	unsigned int mapIndicies[80000];

	for (int i = 0; i < 80000; i++)
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
}

void Render::init(TowerDefense& game)
{

	float squarePoints[] = {
		0.05f, 0.05f,
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
					vertices.push_back(x + squarePoints[2 * i]);
					vertices.push_back(-1 * (y + squarePoints[(2 * i) + 1]));
				}

				for (int i = 0; i < 6; i++)
				{
					indicies.push_back(count + squareIndices[i]);
				}
				count += 4;
			}
			
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

	vertices.clear();
	indicies.clear();
	count = 0;

	//add buttons at bottom
	for (int x = 0; x < 25; x += 5)
	{
		for (int y = 15; y < 25; y += 5)
		{
			for (int i = 0; i < 4; i++)
			{
				vertices.push_back(x + (squarePoints[2 * i] * 5));
				vertices.push_back(-1 * (y + (squarePoints[(2 * i) + 1] * 5 )));
			}
			for (int i = 0; i < 6; i++)
			{
				indicies.push_back(count + squareIndices[i]);
			}
			count += 4;
		}
	}

	numButtonPoints = indicies.size();

	float buttonPoints[80];
	unsigned int buttonIndices[80];

	for (int i = 0; i < 80; i++)
	{
		if (i < vertices.size())
			buttonPoints[i] = vertices[i];
		else
			buttonPoints[i] = 0;

		if (i < indicies.size())
			buttonIndices[i] = indicies[i];
		else
			buttonIndices[i] = 0;
	}

	glGenVertexArrays(1, &buttonVAO);
	glGenBuffers(1, &buttonVBO);
	glGenBuffers(1, &buttonEBO);

	glBindVertexArray(buttonVAO);

	glBindBuffer(GL_ARRAY_BUFFER, buttonVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buttonPoints), buttonPoints, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buttonEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(buttonIndices), buttonIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Render::render(const Dungeon& dungeon)
{
	float mapSize = dungeon.get_map().size();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader.use();

	shader.setUniform("color", 0.0f, 0.0f, 1.0f, 1.0f);
	shader.setUniform("radius", 1.0f);
	shader.setUniform("shift", -0.5 * mapSize, -0.5 * mapSize);
	shader.setUniform("scale", (2.0f / mapSize));

	glBindVertexArray(mapVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mapEBO);
	glDrawElements(GL_TRIANGLES, numMapPoints, GL_UNSIGNED_INT, 0);

	float entityRadius = 0.6;

	// render monsters
	const std::vector<Monster>& monsters = dungeon.get_monsters();
	float shift[2];
	shader.setUniform("color", 1.0, 0.0, 0.0, 1.0);
	shader.setUniform("radius", entityRadius);
	for (int i = 0; i < monsters.size(); i++)
	{
		shift[0] = monsters[i].get_xPos() + 0.5 - (mapSize * 0.5);
		shift[1] = monsters[i].get_yPos() + 0.5 - (mapSize * 0.5);
		shader.setUniform("shift", shift[0], shift[1]);
		drawPolygon(20);
	}


	const std::vector<Bolt>& bolts = dungeon.get_bolts();
	for (int i = 0; i < bolts.size(); i++)
	{
		// render Bolts
		shader.setUniform("color", 1.0, 0.0, 1.0, 1.0);
		shader.setUniform("radius", entityRadius);
		shift[0] = bolts[i].get_xPos() + 0.5 - (mapSize * 0.5);
		shift[1] = bolts[i].get_yPos() + 0.5 - (mapSize * 0.5);
		shader.setUniform("shift", shift[0], shift[1]);
		drawPolygon(20);
	}

	// render hero
	Hero hero = dungeon.get_hero();
	shader.setUniform("color", 0.0, 1.0, 0.0, 1.0);
	shader.setUniform("radius", entityRadius);
	shift[0] = hero.get_xPos() + 0.5 - (mapSize * 0.5);
	shift[1] = hero.get_yPos() + 0.5 - (mapSize * 0.5);
	shader.setUniform("shift", shift[0], shift[1]);
	drawPolygon(20);
}


void Render::render(const TowerDefense & game)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader.use();

	// set the uniforms for tower map
	shader.setUniform("color", 0.0f, 0.0f, 1.0f, 1.0f);
	shader.setUniform("radius", 1.0f);
	shader.setUniform("shift", -12.5f, 12.5f);
	shader.setUniform("scale", (1.0f / 12.5f));

	glBindVertexArray(mapVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mapEBO);
	glDrawElements(GL_TRIANGLES, numMapPoints, GL_UNSIGNED_INT, 0);

	shader.setUniform("color", 0.4, 0.4, 0.4, 1.0);
	glBindVertexArray(buttonVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buttonEBO);
	glDrawElements(GL_TRIANGLES, numButtonPoints, GL_UNSIGNED_INT, 0);

	float entityRadius = 0.6;

	// render enemies
	const std::vector<Enemy>& enemies = game.get_enemies();
	float shift[2];
	shader.setUniform("color", 1.0, 0.0, 0.0, 1.0);
	shader.setUniform("radius", entityRadius);
	for(int i = 0; i < enemies.size(); i++)
	{
		shift[0] = enemies[i].get_xPos() + 0.5 - 12.5;
		shift[1] = (-1 * enemies[i].get_yPos()) - 0.5 + 12.5;
		shader.setUniform("shift", shift[0], shift[1]);
		drawPolygon(20);
	}

	
	const std::vector<Tower>& towers = game.get_towers();
	for (int i = 0; i < towers.size(); i++)
	{
		// render towers
		shader.setUniform("color", 0.0, 1.0, 0.0, 1.0);
		shader.setUniform("radius", entityRadius);
		shift[0] = towers[i].get_xPos() + 0.5 - 12.5;
		shift[1] = (-1 * towers[i].get_yPos()) - 0.5 + 12.5;
		shader.setUniform("shift", shift[0], shift[1]);
		drawPolygon(6);

		// render projectiles
		const std::vector<Projectile>& bolts = towers[i].get_projectiles();
		shader.setUniform("color", 1.0, 0.0, 1.0, 1.0);
		shader.setUniform("radius", 0.5 * entityRadius);
		for (int i = 0; i < bolts.size(); i++)
		{
			shift[0] = bolts[i].get_xPos() + 0.5 - 12.5;
			shift[1] = (-1 * bolts[i].get_yPos()) - 0.5 + 12.5;
			shader.setUniform("shift", shift[0], shift[1]);
			drawPolygon(20);
		}
	}
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
	std::vector<Bolt> bolts = dungeon.get_bolts();

	for (int i = 0; i < bolts.size(); i++)
	{
		print[bolts[i].get_yPos()][bolts[i].get_xPos()] = '-';
	}

	for (int y = print.size() - 1; y >= 0; y--)
	{
		for (int x = 0; x < print[y].size(); x++)
		{
			std::cout << print[y][x] << print[y][x];
		}
		std::cout << std::endl;
	}
}




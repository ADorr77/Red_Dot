#include "Render.h"
#include <string>

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
		0.0f, 0.0f,
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
	
	numMapPoints = indicies.size();
	//numMapPoints = 6;

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


	//float mapPoints[] = {
	//	0.5f,  0.5f,   // top right
	//	0.5f, -0.5f,   // bottom right
	//	-0.5f, -0.5f,   // bottom left
	//	-0.5f,  0.5f,    // top left 
	//};
	//unsigned int mapIndicies[] = {  // note that we start from 0!
	//	0, 1, 3,  // first Triangle
	//	1, 2, 3   // second Triangle
	//};

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




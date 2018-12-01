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
}

void init(Dungeon& game)
{
	
}

void init(TowerDefense& game)
{
	float squarePoints[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	std::vector<float> vertices;
	std::vector<unsigned int> indicies;

	for(int x = 0; x < game.width; x++)
	{
		for(int y = 0; y < game.height; y++)
		{
			for (int i = 0; i < 4; i++)
			{
				;
			}
		}
	}
}


// mess with this later
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}



void Render::render(const TowerDefense & game)
{

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




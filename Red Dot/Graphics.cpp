#include "Graphics.h"

void new_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Graphics::Graphics(int nWidth, int nHeight)
{
	m_nWindowWidth = nWidth;
	m_nWindowHeight = nHeight;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	m_window = glfwCreateWindow(nWidth, nHeight, "Learn OpenGL", NULL, NULL);
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glViewport(0, 0, nWidth, nHeight);

	glfwSetFramebufferSizeCallback(m_window, new_framebuffer_size_callback);

	m_pPlainShader = new Shader("Shaders/VertexShader.txt", "Shaders/PlainFragmentShader.txt");
	m_pColorShader = new Shader("Shaders/VertexShader.txt", "Shaders/ColorFragmentShader.txt");
	m_pTextureShader = new Shader("Shaders/VertexShader.txt", "Shaders/TextureFragmentShader.txt");
	m_pColorTextureShader = new Shader("Shaders/VertexShader.txt", "Shaders/ColorAndTextureFragmentShader.txt");
	m_pTextShader = new Shader("Shaders/VertexShader.txt", "Shaders/TextFragmentShader.txt");

	std::vector<float> vcfVertices;
	std::vector<unsigned int> vciIndices;
	double dPeriod;

	// no polygons with less than three sides
	m_regularPolygons.push_back(NULL); // 0 sides
	m_regularPolygons.push_back(NULL); // 1 side
	m_regularPolygons.push_back(NULL); // 2 sides

	for (int nSides = 3; nSides < 25; ++nSides)
	{
		dPeriod = (2.0 * 3.12159265) / nSides;

		for (int i = 0; i < nSides * 2; i += 2)
		{
			vcfVertices.push_back(float(cos(dPeriod * i / 2)));
			vcfVertices.push_back(float(sin(dPeriod * i / 2)));
		}

		vciIndices.push_back(0);
		vciIndices.push_back(1 + (nSides - 3));
		vciIndices.push_back(2 + (nSides - 3));

		m_regularPolygons.push_back(new Model(vcfVertices, vciIndices));
		vcfVertices.clear();
	}

	std::vector<float> vcfSquarePoints = {
		0.0f, 0.0f,		
		1.0f, 0.0f,		
		1.0f, 1.0f,		
		0.0f, 1.0f,		
	};

	std::vector<unsigned int> puiSquareIndices = {  
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	m_pSquareModel = new Model(vcfSquarePoints, vciIndices);
}

void Graphics::loadMap(const std::vector<std::vector<int>> & vciMap, int idMapElement,
	const std::vector<float>& vcfElementVertices, const std::vector<unsigned int>& vciElementIndices, 
	float fRed, float fGreen, float fBlue, bool bMapFlipped)
{
	std::vector<float> vcfVertices;
	std::vector<unsigned int> vciIndices;
	unsigned int count = 0;
	int nElementPoints = (vcfElementVertices.size() / 2);
	float yMult = (bMapFlipped ? -1.0f : 1.0f);
	float fShiftUp = (bMapFlipped ? vciMap[0].size() : 0.0f);

	for (int x = 0; x < vciMap.size(); x++)
	{
		for (int y = 0; y < vciMap[0].size(); y++)
		{
			if (vciMap[x][y] == idMapElement)
			{
				for (int i = 0; i < nElementPoints; i++)
				{
					vcfVertices.push_back(x + vcfElementVertices[2 * i]);
					vcfVertices.push_back(
						(yMult * (y + vcfElementVertices[(2 * i) + 1])) + fShiftUp
					);
					
				}

				for (int i = 0; i < vciElementIndices.size(); i++)
				{
					vciIndices.push_back(count + vciElementIndices[i]);
				}
				count += nElementPoints;
			}
		}
	}

	m_nMapWidth = vciMap.size();
	m_nMapHeight = vciMap[0].size();
	m_bMapFliped = bMapFlipped;

	if (m_mapElements.empty())
		setMapTransform();

	m_mapElements.push_back(new Model(vcfVertices, vciIndices));
	m_mapColors.push_back(glm::vec3(fRed, fGreen, fBlue));
	m_mapTypes.push_back(PLAIN_MAP);
}


void Graphics::loadMap(const std::vector<std::vector<int>> & vciMap, int idMapElement,
	const std::string& strTexture, bool bMapFlipped)
{
	float pfSquarePoints[] = {
		0.0f, 0.0f,		0.0f, 0.0f,
		1.0f, 0.0f,		1.0f, 0.0f,
		1.0f, 1.0f,		1.0f, 1.0f,
		0.0f, 1.0f,		0.0f, 1.0f
	};

	unsigned int puiSquareIndices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	std::vector<float> vcfVertices;
	std::vector<unsigned int> vciIndices;
	unsigned int count = 0;
	float yMult = (bMapFlipped ? -1.0f : 1.0f);
	float fShiftUp = (bMapFlipped ? vciMap[0].size() : 0.0f);

	for (int x = 0; x < vciMap.size(); x++)
	{
		for (int y = 0; y < vciMap[0].size(); y++)
		{
			if (vciMap[x][y] == idMapElement)
			{
				for (int i = 0; i < 8; i++)
				{
					vcfVertices.push_back(x + pfSquarePoints[2 * i]);
					vcfVertices.push_back(
						(yMult * (y + pfSquarePoints[(2 * i) + 1])) + fShiftUp
					);
				}

				for (int i = 0; i < 6; i++)
				{
					vciIndices.push_back(count + puiSquareIndices[i]);
				}
				count += 4;
			}
		}
	}

	m_nMapWidth = vciMap.size();
	m_nMapHeight = vciMap[0].size();
	m_bMapFliped = bMapFlipped;

	if (m_mapElements.empty())
		setMapTransform();
	
	m_mapElements.push_back(new Model(vcfVertices, vciIndices, 2, strTexture));
	m_mapColors.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	m_mapTypes.push_back(TEXTURE_MAP);
}

void Graphics::setMapTransform()
{
	// correction for flipped map
	/*glm::mat4 reflection = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	glm::mat4 reflectionTransform;
	if (m_bMapFliped)
	{
		reflectionTransform = glm::translate(reflectionTransform, glm::vec3(0.0f, m_nMapHeight, 0.0f));
		reflectionTransform = reflectionTransform * reflection;
	}*/

	// normal map transform
	glm::mat4 mapTransform;
	float fMapScale = 2.0f / (m_nMapWidth > m_nMapHeight ? m_nMapWidth : m_nMapHeight);
	mapTransform = glm::scale(mapTransform, glm::vec3(fMapScale, fMapScale, 1.0));
	mapTransform = glm::translate(mapTransform,
		glm::vec3(m_nMapWidth / -2.0f, m_nMapHeight / -2.0f, 0.0f)
	);
	if (m_nMapWidth > m_nMapHeight)
	{
		mapTransform = glm::translate(mapTransform,
			glm::vec3(0.0f, (m_nMapWidth - m_nMapHeight) / 2.0f, 0.0f)
		);
	}

	//mapTransform = mapTransform * reflectionTransform;

	m_pPlainShader->use();
	m_pPlainShader->setUniform("mapTransform", mapTransform);
	m_pColorShader->use();
	m_pColorShader->setUniform("mapTransform", mapTransform);
	m_pTextureShader->use();
	m_pTextureShader->setUniform("mapTransform", mapTransform);
	m_pColorTextureShader->use();
	m_pColorTextureShader->setUniform("mapTransform", mapTransform);
	m_pTextShader->use();
	m_pTextShader->setUniform("mapTransform", mapTransform);
}

void Graphics::clearMap()
{
	m_mapElements.clear();
	m_mapColors.clear();
	m_mapTypes.clear();
}


#include "Font.h"

Font::Font(const std::string & strFileName)
{
	load(strFileName);

	// create Model for full bitmap for testing mostly
	std::vector<float> vcfVertices = {
		// positions    // texture coords
		1.0f,  1.0f,    1.0f, 1.0f,   // top right
		1.0f, -1.0f,    1.0f, 0.0f,   // bottom right
		-1.0f, -1.0f,   0.0f, 0.0f,   // bottom left
		-1.0f,  1.0f,   0.0f, 1.0f    // top left 
	};
	std::vector<unsigned int> vciIndices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	m_FullBitmap = new Model(vcfVertices, vciIndices, 2, m_uidTexture);

	/*for (int i = 0; i < 256; i++)
		std::cout << i << ": " << (int)m_aszWidth[i] << std::endl;*/

	m_vcCharacters.resize(m_chBase);

	std::vector<float> vcfCharVertices;
	int i = m_chBase;
	int nCellsPerRow = (m_szImgX / m_szCellX);
	int nCellsPerCol = (m_szImgY / m_szCellY);
	float fRowStep = 1.0f / nCellsPerRow;
	float fColStep = 1.0f / nCellsPerCol;
	Model * pModel = NULL;
	for (int y = nCellsPerCol - 1; y >= 0; --y)
	{
		for (int x = 0; x < nCellsPerRow; ++x)
		{
			if (i < 255)
			{
				vcfCharVertices = {
					// positions    // texture coords
					1.0f,  1.0f,    (fRowStep * (x + 1)),	(fColStep * (y + 1)),   // top right
					1.0f,  0.0f,    (fRowStep * (x + 1)),	(fColStep * y),			// bottom right
					0.0f,  0.0f,    (fRowStep * x),			(fColStep * y),			// bottom left
					0.0f,  1.0f,    (fRowStep * x),			(fColStep * (y + 1))    // top left 
				};
				pModel = new Model(vcfCharVertices, vciIndices, 2, m_uidTexture);
				m_vcCharacters.push_back(pModel);
			}
			else
			{
				break;
			}
			++i;
		}
		if (i > 255)
			break;
	}

	m_TextShader = new Shader("Shaders/VertexShader.txt", "Shaders/TextFragmentShader.txt");
}


bool Font::load(const std::string & strFileName)
{
	char start = 32;

	char * pchData;
	char * pchImage;
	std::fstream input;
	unsigned long ulFileSize;
	char bpp;

	input.open(strFileName.c_str(), std::ios_base::binary | std::ios_base::in);

	if (input.fail())
		return false;

	// Get File Size
	input.seekg(0, std::ios_base::end);
	ulFileSize = input.tellg();
	input.seekg(0, std::ios_base::beg);

	// allocate space for file data
	pchData = new char[ulFileSize];

	// Read file data
	if (!pchData)
		return false;

	input.read(pchData, ulFileSize);

	if (input.fail())
	{
		delete[] pchData;
		input.close();
		return false;
	}

	input.close();

	// Check ID is 'BFF2'
	if ((unsigned char)pchData[0] != 0xBF || (unsigned char)pchData[1] != 0xF2)
	{
		delete[] pchData;
		return false;
	}

	// Grab the rest of the header
	memcpy(&m_szImgX, &pchData[2], sizeof(int));
	memcpy(&m_szImgY, &pchData[6], sizeof(int));
	memcpy(&m_szCellX, &pchData[10], sizeof(int));
	memcpy(&m_szCellY, &pchData[14], sizeof(int));
	bpp = pchData[18];
	m_chBase = pchData[19];

	// Check filesize
	if (ulFileSize != ((MAP_DATA_OFFSET)+((m_szImgX*m_szImgY)*(bpp / 8))))
		return false;

	int nCellsPerRow = m_szImgX / m_szCellX;
	int nCellsPerCol = m_szImgY / m_szCellY;
	float fRowFactor = 1.0f / nCellsPerRow;
	float fColFactor = 1.0f / nCellsPerCol;
	int YOffset = m_szCellY;

	// Determine blending options based on BPP
	switch (bpp)
	{
	case 8: // Greyscale
		m_idRenderStyle = BFG_RS_ALPHA;
		break;

	case 24: // RGB
		m_idRenderStyle = BFG_RS_RGB;
		break;

	case 32: // RGBA
		m_idRenderStyle = BFG_RS_RGBA;
		break;

	default: // Unsupported BPP
		delete[] pchData;
		return false;
		break;
	}

	int szImageSize = (m_szImgX*m_szImgY)*(bpp / 8);

	// Allocate space for image
	pchImage = new char[szImageSize];

	if (!pchImage)
	{
		delete[] pchImage;
		return false;
	}

	// Grab char widths
	memcpy(m_aszWidth, &pchData[WIDTH_DATA_OFFSET], 256);

	// Grab image data
	memcpy(pchImage, &pchData[MAP_DATA_OFFSET], szImageSize);

	char * pchFlippedImage = new char[szImageSize];

	// Flips the image.
	std::vector<std::string> vcstrImage;
	std::string strRow;
	// loops through all the image data
	for (int i = 0; i < szImageSize;)
	{
		strRow = "";
		for (int x = 0; x < m_szImgX * 4; ++x)
		{
			strRow += pchImage[i];
			++i;
		}
		vcstrImage.insert(vcstrImage.begin(), strRow);
	}
	int i = 0;
	for (int y = 0; y < vcstrImage.size(); y++)
	{
		for (int x = 0; x < vcstrImage[y].size(); x++)
		{
			pchFlippedImage[i] = vcstrImage[y][x];
			++i;
		}
	}

	// Create Texture
	glGenTextures(1, &m_uidTexture);
	glBindTexture(GL_TEXTURE_2D, m_uidTexture);
	// Fonts should be rendered at native resolution so no need for texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Stop chararcters from bleeding over edges
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Tex creation params are dependent on BPP
	switch (m_idRenderStyle)
	{
	case BFG_RS_ALPHA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_szImgX, m_szImgY, 0, GL_RED, GL_UNSIGNED_BYTE, pchFlippedImage);
		break;

	case BFG_RS_RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_szImgX, m_szImgY, 0, GL_RGB, GL_UNSIGNED_BYTE, pchFlippedImage);
		break;

	case BFG_RS_RGBA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_szImgX, m_szImgY, 0, GL_RGBA, GL_UNSIGNED_BYTE, pchFlippedImage);
		break;
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	// Clean up
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] pchImage;
	delete[] pchFlippedImage;
	delete[] pchData;

	return true;
}

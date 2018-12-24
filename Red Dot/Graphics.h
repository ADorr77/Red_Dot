#pragma once

#include "Includes.h"
#include "Font.h"
#include "Model.h"
#include "Shader.h"
#include <iostream>
#include <vector>

enum GraphcisInfo
{
	PLAIN_MAP,
	COLOR_MAP,
	TEXTURE_MAP,
	MAP_CLAMP_TOP,
	MAP_CLAMP_BOTTOM,
	MAP_CLAMP_LEFT,
	MAP_CLAMP_RIGHT,
	MAP_CLAMP_CENTERED,
	MAP_CAMERA_FOLLOWING
};

class Graphics
{
public:
	Graphics(int nWidth, int nHeight);
	Graphics() : Graphics(800, 800) {};

	void loadMap(const std::vector<std::vector<int>> & vciMap, int idMapElement,
		const std::vector<float> & vcfElementVertices, const std::vector<unsigned int> & vciElementIndices,
		float fRed, float fGreen, float fBlue, bool bMapFlipped = false);
	void loadMap(const std::vector<std::vector<int>> & vciMap, int idMapElement,
		const std::vector<float> &  vcfElementVertices, const std::vector<unsigned int> & vciElementIndices,
		int nColorDimensions = 3, bool bMapFlipped = false);
	void loadMap(const std::vector<std::vector<int>> & vciMap, int idMapElement,
		const std::string & strTexture, bool bMapFlipped = false);
	void setMapTransform();
	void clearMap();

	GLFWwindow * getWindow() const { return m_window; }
	void setWindowSize(int nWidth, int nHeight);

	void clear(float fRed, float fGreen, float fBlue, float fAlpha = 1.0f);

	void drawMap();

	void drawModel(Model * pModel,
		float fScale, float fDegreesRotated, float fXShift, float fYShift,
		float fRed = 0.0f, float fGreen = 0.0f, float fBlue = 0.0f, float fAlpha = 1.0f);

	void drawRegularPolygon(int nSides,
		float fRadius, float fDegreesRotated, float fXPos, float fYPos,
		float fRed = 0.0f, float fGreen = 0.0f, float fBlue = 0.0f, float fAlpha = 1.0f);

	void drawText(const std::string & strText, const Font & font,
		float fXPos, float fYPos, float fWidth, float fHeight, float fDegreesRotated,
		float fRed = 0.0f, float fGreen = 0.0f, float fBlue = 0.0f, float fAlpha = 1.0f);
	
	static unsigned int getTexture(const std::string & strTexture,
		int iBorderCondition = GL_REPEAT, int iFilterParam = GL_NEAREST);
	static void makeBuffers(unsigned int &uidVAO, unsigned int &uidVBO, unsigned int &uidEBO,
		const std::vector<float> & vcfVertices, const std::vector<unsigned int> & vciIndices = {});

private:
	GLFWwindow * m_window;
	int m_nWindowWidth, m_nWindowHeight;

	std::vector<Model*> m_regularPolygons;

	std::vector<Model*> m_mapElements;
	std::vector<glm::vec3> m_mapColors;
	std::vector<int> m_mapTypes;
	int m_nMapWidth, m_nMapHeight;
	bool m_bMapFliped;

	Shader * m_pPlainShader;
	Shader * m_pColorShader;
	Shader * m_pTextureShader;
	Shader * m_pColorTextureShader;
	Shader * m_pTextShader;
};

inline void Graphics::setWindowSize(int nWidth, int nHeight)
{
	m_nWindowWidth = nWidth;
	m_nWindowHeight = nHeight;
	glViewport(0, 0, nWidth, nHeight);
}

inline void Graphics::clear(float fRed, float fGreen, float fBlue, float fAlpha)
{
	glClearColor(fRed, fGreen, fBlue, fAlpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


inline void Graphics::drawMap()
{
	for (int i = 0; i < m_mapElements.size(); ++i)
	{
		switch (m_mapTypes[i])
		{
		case PLAIN_MAP:
			m_pPlainShader->use();
			m_pPlainShader->setUniform("Color",
				m_mapColors[i].x, m_mapColors[i].y, m_mapColors[i].z, 1.0
			);
			m_pPlainShader->setUniform("posTransform", glm::mat4(1.0f));
			break;
		case COLOR_MAP:
			m_pColorShader->use();
			m_pColorShader->setUniform("posTransform", glm::mat4(1.0f));
			break;
		case TEXTURE_MAP:
			m_pTextureShader->use();
			m_pColorShader->setUniform("posTransform", glm::mat4(1.0f));
			break;
		}
		m_mapElements[i]->render();
	}
	
}

inline void Graphics::drawModel(Model* pModel,
	float fScale, float fDegreesRotated, float fXShift, float fYShift,
	float fRed, float fGreen, float fBlue, float fAlpha)
{
	Shader * pShader;
	if (pModel->hasColor() && pModel->hasTexture())
		pShader = m_pColorTextureShader;
	else if (pModel->hasTexture())
		pShader = m_pTextureShader;
	else if (pModel->hasColor())
		pShader = m_pColorShader;
	else
		pShader = m_pPlainShader;

	pShader->use();
	pShader->setUniform("Color", fRed, fGreen, fBlue, fAlpha);
	

	if (m_bMapFliped)
		fYShift = m_nMapHeight - fYShift;

	glm::mat4 posTransform;
	posTransform = glm::translate(posTransform, glm::vec3(fXShift, fYShift, 0.0f));
	posTransform = glm::rotate(posTransform, glm::radians(fDegreesRotated), glm::vec3(0.0f, 0.0f, 1.0f));
	posTransform = glm::scale(posTransform, glm::vec3(fScale, fScale, 0.0f));

	pShader->setUniform("posTransform", posTransform);

	pModel->render();
}


inline void Graphics::drawRegularPolygon(int nSides, 
	float fRadius, float fDegreesRotated, float fXPos, float fYPos,
	float fRed, float fGreen, float fBlue, float fAlpha)
{
	m_pPlainShader->use();
	m_pPlainShader->setUniform("Color", fRed, fGreen, fBlue, fAlpha);

	if (m_bMapFliped)
		fYPos = m_nMapHeight - fYPos - 1;

	glm::mat4 posTransform;
	if(fRadius <= 0.5)
		posTransform = glm::translate(posTransform, glm::vec3(fXPos + 0.5f, fYPos + 0.5f, 0.0f));
	else
		posTransform = glm::translate(posTransform, glm::vec3(fXPos + fRadius, fYPos + fRadius, 0.0f));
	posTransform = glm::rotate(posTransform, glm::radians(fDegreesRotated), glm::vec3(0.0f, 0.0f, 1.0f));
	posTransform = glm::scale(posTransform, glm::vec3(fRadius, fRadius, 0.0f));

	m_pPlainShader->setUniform("posTransform", posTransform);

	if (nSides < 3)
		nSides = 3;

	if (nSides >= m_regularPolygons.size())
		nSides = m_regularPolygons.size() - 1;

	m_regularPolygons[nSides]->render();
}

inline void Graphics::drawText(const std::string & strText, const Font & font,
	float fXPos, float fYPos, float fWidth, float fHeight, float fDegreesRotated,
	float fRed, float fGreen, float fBlue, float fAlpha)
{
	m_pTextShader->use();
	m_pTextShader->setUniform("Color", fRed, fGreen, fBlue, fAlpha);

	if (m_bMapFliped)
		fYPos = m_nMapHeight - fYPos - 1;

	float fStringWidth = 0;
	for (auto chChar : strText)
	{
		fStringWidth += font.getWidth(chChar);
	}

	glm::mat4 posTransform;
	posTransform = glm::translate(posTransform, 
		glm::vec3(fXPos + (fWidth / 2), fYPos + (fHeight / 2), 0.0f));
	posTransform = glm::rotate(posTransform, glm::radians(fDegreesRotated), glm::vec3(0.0f, 0.0f, 1.0f));
	posTransform = glm::scale(posTransform, glm::vec3(fWidth/fStringWidth, fHeight, 0.0f));

	float fLetterShift = 0;
	glm::mat4 ShiftTransform;
	glm::mat4 finalTransform;

	for (auto chChar : strText)
	{
		ShiftTransform = glm::translate(ShiftTransform, glm::vec3(fStringWidth / -2.0f, -0.5f, 0.0f));
		ShiftTransform = glm::translate(ShiftTransform, glm::vec3(fLetterShift, 0.0f, 0.0f));
		finalTransform = posTransform * ShiftTransform;
		m_pTextShader->setUniform("posTransform", finalTransform);

		font.render(chChar);

		ShiftTransform = glm::mat4(1.0);
		fLetterShift += font.getWidth(chChar);
	}
}



inline unsigned int Graphics::getTexture(const std::string & strTexture, 
	int iBorderCondition, int iFilterParam)
{
	unsigned int uidTexture;
	glGenTextures(1, &uidTexture);
	glBindTexture(GL_TEXTURE_2D, uidTexture);

	// These are set to be best for a retro 2d Game
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, iBorderCondition);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, iBorderCondition);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, iFilterParam);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, iFilterParam);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(strTexture.c_str(), &width, &height, &nrChannels, 0);

	int idFlag = (strTexture[strTexture.size() - 2] == 'n' ? GL_RGBA : GL_RGB);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, idFlag, width, height, 0, idFlag, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return uidTexture;
}

inline void Graphics::makeBuffers(unsigned int &uidVAO, unsigned int &uidVBO, unsigned int &uidEBO,
	const std::vector<float> & vcfVertices, const std::vector<unsigned int> & vciIndices)
{
	glGenVertexArrays(1, &uidVAO);
	glGenBuffers(1, &uidVBO);
	

	glBindVertexArray(uidVAO);

	glBindBuffer(GL_ARRAY_BUFFER, uidVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vcfVertices.size(), &(vcfVertices[0]), GL_STATIC_DRAW);

	if (!vciIndices.empty())
	{
		glGenBuffers(1, &uidEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uidEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * vciIndices.size(), &(vciIndices[0]), GL_STATIC_DRAW);
	}
}


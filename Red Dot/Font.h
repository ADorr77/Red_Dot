#pragma once

#include "Includes.h"
#include "Model.h"
#include "Shader.h"
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
#include <iostream>

#define BFG_RS_NONE  0x0      // Blend flags
#define BFG_RS_ALPHA 0x1
#define BFG_RS_RGB   0x2
#define BFG_RS_RGBA  0x4

#define BFG_MAXSTRING 255     // Maximum string length

#define WIDTH_DATA_OFFSET  20 // Offset to width data with BFF file
#define MAP_DATA_OFFSET   276 // Offset to texture image data with BFF file

class Font
{
public:
	Font(const std::string & strFileName);

	bool load(const std::string & strFileName);

	void bind() const { glBindTexture(GL_TEXTURE_2D, m_uidTexture); }
	void setBlend() const;
	void render() const;
	void render(char chChar) const;
	void render(const std::string & strText, glm::mat4 Transform,
		float fRed = 0.0f, float fGreen = 0.0f, float fBlue = 0.0f, float fAlpha = 1.0f);

	void printInfo() const;

	float getWidth(char chChar) const { return float((int)m_aszWidth[(int)chChar]) / m_szCellX; }


private:
	unsigned int m_uidTexture;

	int m_szImgX, m_szImgY;
	int m_szCellX, m_szCellY;
	char m_chBase;

	char m_aszWidth[256];
	std::vector<Model *> m_vcCharacters;
	Model * m_FullBitmap;

	Shader * m_TextShader;

	int m_idRenderStyle;
};

inline void Font::setBlend() const
{
	switch (m_idRenderStyle)
	{
	case BFG_RS_ALPHA: // 8Bit
		glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
		glEnable(GL_BLEND);
		break;

	case BFG_RS_RGB:   // 24Bit
		glDisable(GL_BLEND);
		break;

	case BFG_RS_RGBA:  // 32Bit
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		break;
	}
}

inline void Font::render() const
{
	setBlend();
	m_FullBitmap->render();
	glDisable(GL_BLEND);
}

inline void Font::render(char chChar) const
{
	setBlend();
	m_vcCharacters[(int)chChar]->render();
	glDisable(GL_BLEND);
}

inline void Font::render(const std::string& strText, glm::mat4 Transform,
	float fRed, float fGreen, float fBlue, float fAlpha)
{
	m_TextShader->use();
	m_TextShader->setUniform("Color", fRed, fGreen, fBlue, fAlpha);
	setBlend();

	float fNormalizedWidth;
	float fLetterShift = 0;
	glm::mat4 ShiftTransform;
	glm::mat4 FinalTransform;

	for (auto chChar : strText)
	{
		ShiftTransform = glm::translate(ShiftTransform, glm::vec3(fLetterShift, 0.0f, 0.0f));
		FinalTransform = Transform * ShiftTransform;
		m_TextShader->setUniform("transform", FinalTransform);

		m_vcCharacters[(int)chChar]->render();

		ShiftTransform = glm::mat4(1.0);
		fLetterShift += float(((int)m_aszWidth[(int)chChar])) / m_szCellX;
	}

	glDisable(GL_BLEND);
}

inline void Font::printInfo() const 
{
	std::cout << "Cell Width X:  " << m_szCellX << std::endl;
	std::cout << "Cell Width Y:  " << m_szCellY << std::endl;
	std::cout << "Image Width X: " << m_szImgX << std::endl;
	std::cout << "Image Width Y: " << m_szImgY << std::endl;
	std::cout << "Base:          " << (int)m_chBase << std::endl;
}


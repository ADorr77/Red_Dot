#pragma once
#include "Includes.h"
#include <vector>

class Model
{
public:
	Model();
	Model(const std::vector<float> & vcfVertices, 
		int nVectorDimension = 2, int nColorDimension = 0, const std::string & strTexture = {});
	Model(const std::vector<float> & vcfVertices, const std::vector<unsigned int> & vciIndices, 
		int nVectorDimension = 2, int nColorDimension = 0, const std::string & strTexture = {});
	Model(const std::vector<float> & vcfVertices, const std::vector<unsigned int> & vciIndices,
		int nVectorDimension, unsigned int & uidTexture);
	Model(const std::vector<float> & vcfVertices, const std::vector<unsigned int> & vciIndices,
		int nVectorDimension, const std::string & strTexture)
		: Model(vcfVertices, vciIndices, nVectorDimension, 0, strTexture) {};

	Model(const Model &obj) : Model() {};
	Model& operator=(const Model& obj)
	{
		Model m = Model(); 
		return m;
	}
	~Model();

	void createAttributes(int nVectorDimension, int nColorDimension, const std::string & strTexture);

	bool hasIndices() const { return m_bHasIndices; }
	bool hasColor() const { return m_bHasColor; }
	bool hasTexture() const { return m_bHasTexture; }

	void render() const;


private:
	unsigned int m_uidVertexArrayObject;
	unsigned int m_uidVertexBufferObject;
	unsigned int m_uidElementBufferObject;

	std::vector<int> m_vcAttributes;
	unsigned int m_uidTexture;

	bool m_bHasIndices;
	bool m_bHasColor;
	bool m_bHasTexture;
	int m_nDrawPoints;
};


inline void Model::render() const
{
	glBindVertexArray(m_uidVertexArrayObject);
	for (auto element : m_vcAttributes) { glEnableVertexAttribArray(element); }
	glBindTexture(GL_TEXTURE_2D, m_uidTexture);

	if (m_bHasIndices)
		glDrawElements(GL_TRIANGLES, m_nDrawPoints, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, m_nDrawPoints);

	for (auto element : m_vcAttributes) { glDisableVertexAttribArray(element); }
}

#include "Model.h"
#include "Graphics.h"

Model::Model()
{
	m_bHasIndices = true;

	std::vector<float> vcfVertices = {
		// positions         
		0.5f,  0.5f,		// top right
		0.5f, -0.5f,		// bottom right
		-0.5f, -0.5f,		// bottom left
		-0.5f,  0.5f,		// top left 
	};

	std::vector<unsigned int> vcuiIndices  = {
		0, 1, 2, // first triangle
		0, 2, 3  // second triangle
	};

	Graphics::makeBuffers(
		m_uidVertexArrayObject,
		m_uidVertexBufferObject,
		m_uidElementBufferObject,
		vcfVertices,
		vcuiIndices
	);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	m_vcAttributes = { 0 };
	m_nDrawPoints = vcuiIndices.size();
}

Model::Model(const std::vector<float> & vcfVertices, 
	int nVectorDimension, int nColorDimension, const std::string & strTexture)
{
	m_bHasIndices = false;
	Graphics::makeBuffers(
		m_uidVertexArrayObject,
		m_uidVertexBufferObject,
		m_uidElementBufferObject,
		vcfVertices
	);

	if (!strTexture.empty())
	{
		m_uidTexture = Graphics::getTexture(strTexture);
	}

	createAttributes(nVectorDimension, nColorDimension, strTexture);

	m_nDrawPoints = vcfVertices.size();
}

Model::Model(const std::vector<float>& vcfVertices, const std::vector<unsigned int>& vciIndices, 
	int nVectorDimension, int nColorDimension, const std::string & strTexture)
{
	m_bHasIndices = true;
	Graphics::makeBuffers(
		m_uidVertexArrayObject,
		m_uidVertexBufferObject,
		m_uidElementBufferObject,
		vcfVertices,
		vciIndices
	);

	if (!strTexture.empty())
	{
		m_uidTexture = Graphics::getTexture(strTexture);
	}

	createAttributes(nVectorDimension, nColorDimension, strTexture);

	m_nDrawPoints = vciIndices.size();
}

Model::Model(const std::vector<float>& vcfVertices, const std::vector<unsigned>& vciIndices,
	int nVectorDimension, unsigned int & uidTexture)
{
	m_bHasIndices = true;
	Graphics::makeBuffers(
		m_uidVertexArrayObject,
		m_uidVertexBufferObject,
		m_uidElementBufferObject,
		vcfVertices,
		vciIndices
	);

	m_uidTexture = uidTexture;

	createAttributes(nVectorDimension, 0, "Full");

	m_nDrawPoints = vciIndices.size();
}

void Model::createAttributes(int nVectorDimension, int nColorDimension, const std::string & strTexture)
{
	const int stride = (nVectorDimension * sizeof(float)) +
		(nColorDimension * sizeof(float)) +
		(strTexture.empty() ? 0 : 2 * sizeof(float));

	glVertexAttribPointer(0, nVectorDimension, GL_FLOAT, GL_FALSE, stride, (void*)0);
	m_vcAttributes = { 0 };

	if (nColorDimension > 0)
	{
		glVertexAttribPointer(1, nColorDimension,
			GL_FLOAT, GL_FALSE,
			stride, (void*)(nVectorDimension * sizeof(float)));
		m_vcAttributes.push_back(1);
		m_bHasColor = true;
	}

	if (!strTexture.empty())
	{
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
			stride, (void*)(stride - (2 * sizeof(float))));
		m_vcAttributes.push_back(2);
		m_bHasTexture = true;
	}
}


Model::~Model()
{
	glDeleteVertexArrays(1, &m_uidVertexArrayObject);
	glDeleteBuffers(1, &m_uidVertexBufferObject);
	glDeleteBuffers(1, &m_uidElementBufferObject);
}


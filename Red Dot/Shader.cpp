#include "Shader.h"

unsigned int compileShader(const char * code, GLenum type)
{
	unsigned int shaderID = glCreateShader(type);
	int success;
	char infoLog[512];

	glShaderSource(shaderID, 1, &code, NULL);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shaderID;
}

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath, const GLchar * geoPath)
{
	std::string vertCode, fragCode, geoCode;
	std::ifstream vertFile, fragFile, geoFile;

	vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	geoFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);


	try
	{
		vertFile.open(vertexPath);
		fragFile.open(fragmentPath);
		geoFile.open(geoPath);

		std::stringstream vertStream, fragStream, geoStream;
		vertStream << vertFile.rdbuf();
		fragStream << fragFile.rdbuf();
		geoStream << geoFile.rdbuf();

		vertFile.close();
		fragFile.close();
		geoFile.close();

		vertCode = vertStream.str();
		fragCode = fragStream.str();
		geoCode = geoStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char * vCode = vertCode.c_str();
	const char * fCode = fragCode.c_str();
	const char * gCode = geoCode.c_str();

	unsigned int vertex = compileShader(vCode, GL_VERTEX_SHADER);
	unsigned int fragment = compileShader(fCode, GL_FRAGMENT_SHADER);
	unsigned int geo = compileShader(gCode, GL_GEOMETRY_SHADER);

	//link shaders
	int success;
	char infoLog[512];
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glAttachShader(id, geo);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteShader(geo);
}

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	std::string vertCode, fragCode;
	std::ifstream vertFile, fragFile;

	vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);


	try
	{
		vertFile.open(vertexPath);
		fragFile.open(fragmentPath);

		std::stringstream vertStream, fragStream;
		vertStream << vertFile.rdbuf();
		fragStream << fragFile.rdbuf();

		vertFile.close();
		fragFile.close();

		vertCode = vertStream.str();
		fragCode = fragStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char * vCode = vertCode.c_str();
	const char * fCode = fragCode.c_str();

	unsigned int vertex = compileShader(vCode, GL_VERTEX_SHADER);
	unsigned int fragment = compileShader(fCode, GL_FRAGMENT_SHADER);

	//link shaders
	int success;
	char infoLog[512];
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(id);
}

void Shader::setUniform(const std::string& name, int count, const int* values)
{
	switch (count)
	{
	case 2:
		glUniform2i(glGetUniformLocation(id, name.c_str()), values[0], values[1]);
		break;

	case 3:
		glUniform3i(glGetUniformLocation(id, name.c_str()), values[0], values[1], values[2]);
		break;

	case 4:
		glUniform4i(glGetUniformLocation(id, name.c_str()), values[0], values[1], values[2], values[4]);
		break;

	default:
		glUniform1i(glGetUniformLocation(id, name.c_str()), values[0]);
		break;
	}
}

void Shader::setUniform(const std::string& name, int count, const float* values)
{
	switch (count)
	{
	case 2:
		glUniform2f(glGetUniformLocation(id, name.c_str()), values[0], values[1]);
		break;

	case 3:
		glUniform3f(glGetUniformLocation(id, name.c_str()), values[0], values[1], values[2]);
		break;

	case 4:
		glUniform4f(glGetUniformLocation(id, name.c_str()), values[0], values[1], values[2], values[4]);
		break;

	default:
		glUniform1f(glGetUniformLocation(id, name.c_str()), values[0]);
		break;
	}
}

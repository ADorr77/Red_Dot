#pragma once

// Custom Class to handle shaders based off of code written and copyrighted by Joey de Vries
// https://learnopengl.com/Getting-started/Shaders
// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader_s.h
// https://creativecommons.org/licenses/by-nc/4.0/legalcode
// Code is free to modify and use. 
//
// Modified by Aaron Dorrance
// 11/21/18

#ifndef SHADER_H
#define SHADER_H

#include "Includes.h"
#include <string>

class Shader
{
public:
	// the program ID
	unsigned int id;

	// constructor reads and builds the shader
	Shader() = default;
	Shader(const GLchar * vertexPath, const GLchar * fragmentPath, const GLchar * geoPath);
	Shader(const GLchar * vertexPath, const GLchar * fragmentPath);

	// use/activate the shader
	void use();
	// utility uniform functions
	void setUniform(const std::string &name, float one);
	void setUniform(const std::string &name, float one, float two);
	void setUniform(const std::string &name, float one, float two, float three);
	void setUniform(const std::string &name, float one, float two, float three, float four);
};

#endif

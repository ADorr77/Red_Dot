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

#include <glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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
	void setUniform(const std::string &name, int count, const int * values);
	void setUniform(const std::string &name, int count, const float * values);
};

#endif

#ifndef _SHADERSZASOP_
#define _SHADERSZASOP_


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader {

	

	Shader() =delete;

	Shader(const Shader&) = delete;

	Shader(const Shader&&) = delete;

public:

	GLuint progId;

	Shader(const std::string& vertexshaderpath, const std::string& fragmentshaderpath, const std::string& geometryshaderpath);

	Shader(const std::string& vertexshaderpath, const std::string& fragmentshaderpath);

	void Use();
	
};

#endif
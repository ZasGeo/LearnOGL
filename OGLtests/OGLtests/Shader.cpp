#include "Shader.h"



Shader::Shader(const GLchar * vertexshaderpath, const GLchar * fragmentshaderpath)
{
	std::ifstream vertexfile;
	std::ifstream fragmentfile;
	std::string vertexSource;
	std::string fragmentSource;

	vertexfile.exceptions(std::ifstream::failbit);
	fragmentfile.exceptions(std::ifstream::failbit);

	try {
		vertexfile.open(vertexshaderpath);
		fragmentfile.open(fragmentshaderpath);
		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexfile.rdbuf();
		fragmentStream << fragmentfile.rdbuf();

		vertexSource = vertexStream.str();
		fragmentSource = fragmentStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::ERROR WHILE FILE READ" << std::endl;
		progId = 0;
	}
	const GLchar* vShaderCode = vertexSource.c_str();
	const GLchar* fShaderCode = fragmentSource.c_str();


	//vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	progId = glCreateProgram();
	glAttachShader(progId, vertexShader);
	glAttachShader(progId, fragmentShader);
	glLinkProgram(progId);

	// Check for linking errors
	glGetProgramiv(progId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(progId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
    
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Use()
{
	glUseProgram(progId);
}

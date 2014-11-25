#ifndef SHADER_H
#define SHADER_H

#include <string>


class Shader
{
public:
	Shader();
	~Shader();
private:
	std::string shadername;
	std::string shaderfilepath;
	std::string vertexshader;
	std::string pixelshader;
	std::string vertexdeclaration;
	std::string constanttable;

};

#endif
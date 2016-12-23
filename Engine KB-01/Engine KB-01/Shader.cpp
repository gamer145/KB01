#include "Shader.h"

/*
* Work in progress, doesn't work.
* Probably never will
* Ne pas toucher!
*/

Shader::Shader()
{

}

Shader::~Shader()
{

}

std::string Shader::GetShaderName()
{
	return shadername;
}

LPDIRECT3DVERTEXSHADER9 Shader::GetVertexShader()
{
	return vertexshader;
}
LPDIRECT3DPIXELSHADER9 Shader::GetPixelShader()
{
	return pixelshader;
}
LPDIRECT3DVERTEXDECLARATION9 Shader::GetVertexDeclaration()
{
	return vertexdeclaration;
}
LPD3DXCONSTANTTABLE Shader::GetConstantTable()
{
	return constanttable;
}

void Shader::SetShaderName(std::string newname)
{
	shadername = newname;
}
void Shader::SetVertexShader(LPDIRECT3DVERTEXSHADER9 newvertexshader)
{
	vertexshader = newvertexshader;
}
void Shader::SetPixelShader(LPDIRECT3DPIXELSHADER9 newpixelshader)
{
	pixelshader = newpixelshader;
}
void Shader::SetVertexDeclaration(LPDIRECT3DVERTEXDECLARATION9 newvertexdeclaration)
{
	vertexdeclaration = newvertexdeclaration;
}
void Shader::SetConstantTable(LPD3DXCONSTANTTABLE newconstanttable)
{
	constanttable = newconstanttable;
}
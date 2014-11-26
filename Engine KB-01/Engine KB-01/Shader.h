#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <d3dx9.h>

class Shader
{
public:
	Shader();
	~Shader();

	std::string GetShaderName();
	LPDIRECT3DVERTEXSHADER9 GetVertexShader();
	LPDIRECT3DPIXELSHADER9 GetPixelShader();
	LPDIRECT3DVERTEXDECLARATION9 GetVertexDeclaration();
	LPD3DXCONSTANTTABLE GetConstantTable();

	void SetShaderName(std::string newname);
	void SetVertexShader(LPDIRECT3DVERTEXSHADER9 newvertexshader);
	void SetPixelShader(LPDIRECT3DPIXELSHADER9 newpixelshader);
	void SetVertexDeclaration(LPDIRECT3DVERTEXDECLARATION9 newvertexdeclaration);
	void SetConstantTable(LPD3DXCONSTANTTABLE newconstanttable);

private:
	std::string shadername;
	LPDIRECT3DVERTEXSHADER9 vertexshader;
	LPDIRECT3DPIXELSHADER9 pixelshader;
	LPDIRECT3DVERTEXDECLARATION9 vertexdeclaration;
	LPD3DXCONSTANTTABLE constanttable;
};

#endif
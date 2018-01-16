#pragma once

////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderClass.h
////////////////////////////////////////////////////////////////////////////////

#pragma comment ( lib, "d3dcompiler.lib" )
#pragma comment ( lib, "d3d11.lib" )

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dcompiler.h>
#include <fstream>
#include <wrl/client.h>
#include <string.h>
#include <stdlib.h>

using namespace Microsoft::WRL;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderClass
// Description: Used to invoke the HLSL shaders for drawing the 3D models that are on the GPU.
////////////////////////////////////////////////////////////////////////////////
class ShaderClass
{
public:
	ShaderClass();
	ShaderClass(const ShaderClass&);
	~ShaderClass();

protected:
	bool CreateShaders(ID3D11Device * device,HWND hwnd,	wstring vsFilename,	wstring psFilename);
	/*,
		char* vsDesc,
		char* psDesc,
		ID3D10Blob* errorMessage = nullptr*/

	ComPtr<ID3D10Blob> _vertexShaderBuffer;
	ComPtr<ID3D10Blob> _pixelShaderBuffer;

	ComPtr <ID3D11VertexShader> m_vertexShader;
	ComPtr <ID3D11PixelShader> m_pixelShader;
};
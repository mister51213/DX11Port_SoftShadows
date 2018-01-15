////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "textureclass.h"
#include "DDSTextureLoader.h"

using namespace DirectX;


TextureClass::TextureClass()
{}


TextureClass::TextureClass(const TextureClass& other)
{
}


TextureClass::~TextureClass()
{
}


bool TextureClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* d3dContext, WCHAR* filename)
{
	HRESULT result;


	// Load the texture in.
	//result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_texture, NULL);
	//if(FAILED(result))
	//{
	//	return false;
	//}

	//result = CreateDDSTextureFromFile(device, d3dContext, filename, &m_texture, &m_textureView);
	result = CreateDDSTextureFromFile(device, d3dContext, filename, &m_texture, &m_textureView);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}


void TextureClass::Shutdown()
{
	return;
}


ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_textureView.Get();
}
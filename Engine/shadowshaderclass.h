////////////////////////////////////////////////////////////////////////////////
// Filename: shadowshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHADOWSHADERCLASS_H_
#define _SHADOWSHADERCLASS_H_

#pragma comment ( lib, "d3dcompiler.lib" )
#pragma comment ( lib, "d3d11.lib" )

//////////////
// INCLUDES //
//////////////
#include <d3dcompiler.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>
#include "ShaderClass.h"

using namespace std;
using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: ShadowShaderClass
////////////////////////////////////////////////////////////////////////////////
class ShadowShaderClass:public ShaderClass
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		XMMATRIX lightView;
		XMMATRIX lightProjection;
		XMMATRIX lightView2;
		XMMATRIX lightProjection2;
	};

	struct LightBufferType2
	{
		XMFLOAT3 lightPosition;
		float padding;
		XMFLOAT3 lightPosition2;
		float padding2;
	};

public:
	ShadowShaderClass();
	ShadowShaderClass(const ShadowShaderClass&);
	~ShadowShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
		XMMATRIX projectionMatrix, XMMATRIX lightViewMatrix, XMMATRIX lightProjectionMatrix,
		XMMATRIX lightViewMatrix2, XMMATRIX lightProjectionMatrix2,
		ID3D11ShaderResourceView* depthMapTexture, ID3D11ShaderResourceView* depthMapTexture2, XMFLOAT3 lightPosition, XMFLOAT3 lightPosition2);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,	XMMATRIX projectionMatrix, 
		XMMATRIX lightViewMatrix, XMMATRIX lightProjectionMatrix, XMMATRIX lightViewMatrix2, XMMATRIX lightProjectionMatrix2,
		ID3D11ShaderResourceView* depthMapTexture, ID3D11ShaderResourceView* depthMapTexture2, XMFLOAT3 lightPosition, XMFLOAT3 lightPosition2);

	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

private:
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleStateClamp;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_lightBuffer2;
};

#endif
////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightclass.h"
#include "rendertextureclass.h"
#include "depthshaderclass.h"
#include "shadowshaderclass.h"
#include "orthowindowclass.h"
#include "textureshaderclass.h"
#include "horizontalblurshaderclass.h"
#include "verticalblurshaderclass.h"
#include "softshadowshaderclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 100.0f;
const float SCREEN_NEAR = 1.0f;
const int SHADOWMAP_WIDTH = 1024;
const int SHADOWMAP_HEIGHT = 1024;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(float, float, float, float, float, float);

private:
	bool RenderShadowsToTexture();
	bool RenderBlackAndWhiteShadows();

	//bool DownSampleTexture(XMMATRIX worldMatrix, XMMATRIX baseViewMatrix);
	//bool RenderHorizontalBlurToTexture(XMMATRIX worldMatrix, XMMATRIX baseViewMatrix);
	//bool RenderVerticalBlurToTexture(XMMATRIX worldMatrix, XMMATRIX baseViewMatrix);
	//bool UpSampleTexture(XMMATRIX worldMatrix, XMMATRIX baseViewMatrix);

	ID3D11ShaderResourceView* ApplyBlur(ID3D11ShaderResourceView* viewToBlur, RenderTextureClass* outputRenderTarget);

	bool Render();

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass *m_CubeModel, *m_GroundModel, *m_SphereModel;
	LightClass* m_Light;
	
	TextureShaderClass* m_TextureShader;
	DepthShaderClass* m_DepthShader;
	ShadowShaderClass* m_ShadowShader;

	// NEW CLASSES
	RenderTextureClass *m_RenderTexture, *m_BlackWhiteRenderTexture, *m_DownSampleTexure;
	RenderTextureClass *m_HorizontalBlurTexture, *m_VerticalBlurTexture, *m_UpSampleTexure;
	//TEST
	RenderTextureClass *_BlurredScene;

	OrthoWindowClass *m_SmallWindow, *m_FullScreenWindow;
	HorizontalBlurShaderClass* m_HorizontalBlurShader;
	VerticalBlurShaderClass* m_VerticalBlurShader;

	SoftShadowShaderClass* m_SoftShadowShader;
};

#endif
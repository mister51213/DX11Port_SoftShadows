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
	bool Frame(float, float, float, float, float, float);

private:
	ID3D11ShaderResourceView* ApplyBlur(ID3D11ShaderResourceView* viewToBlur, RenderTextureClass* outputRenderTarget);

	void RenderShadows();

	bool Render();

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass *m_CubeModel, *m_GroundModel, *m_SphereModel;
	LightClass* m_Light1;
	LightClass* m_Light2;
	const int NUM_LIGHTS = 2;
	
	TextureShaderClass* m_TextureShader;
	DepthShaderClass* m_DepthShader;
	ShadowShaderClass* m_ShadowShader;

	RenderTextureClass *m_ShadowTexture1, *m_ShadowTexture2, *m_BlackWhiteRenderTexture1;// , *m_BlackWhiteRenderTexture2;
	RenderTextureClass *m_DownSampleTexure, *m_HorizontalBlurTexture, *m_VerticalBlurTexture, *m_UpSampleTexure;

	OrthoWindowClass *m_SmallWindow, *m_FullScreenWindow;
	HorizontalBlurShaderClass* m_HorizontalBlurShader;
	VerticalBlurShaderClass* m_VerticalBlurShader;
	SoftShadowShaderClass* m_SoftShadowShader;
};

#endif
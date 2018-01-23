////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_CubeModel = 0;
	m_GroundModel = 0;
	m_SphereModel = 0;
	m_Light1 = 0;
	m_ShadowTexture1 = 0;
	m_DepthShader = 0;	
	m_BlackWhiteRenderTexture1 = 0;
	m_ShadowShader = 0;
	m_DownSampleTexure = 0;
	m_SmallWindow = 0;
	m_TextureShader = 0;
	m_HorizontalBlurTexture = 0;
	m_HorizontalBlurShader = 0;
	m_VerticalBlurTexture = 0;
	m_VerticalBlurShader = 0;
	m_UpSampleTexure = 0;
	m_FullScreenWindow = 0;
	m_SoftShadowShader = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	int downSampleWidth, downSampleHeight;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->RenderBaseViewMatrix();

	// Create the cube model object.
	m_CubeModel = new ModelClass;
	if(!m_CubeModel)
	{
		return false;
	}

	// Initialize the cube model object.
	result = m_CubeModel->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), "../Engine/data/cube.txt", L"../Engine/data/wall01.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the cube model object.", L"Error", MB_OK);
		return false;
	}

	// Set the position for the cube model.
	m_CubeModel->SetPosition(-2.0f, 2.0f, 0.0f);

	// Create the sphere model object.
	m_SphereModel = new ModelClass;
	if(!m_SphereModel)
	{
		return false;
	}

	// Initialize the sphere model object.
	result = m_SphereModel->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), "../Engine/data/sphere.txt", L"../Engine/data/ice.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sphere model object.", L"Error", MB_OK);
		return false;
	}

	// Set the position for the sphere model.
	m_SphereModel->SetPosition(2.0f, 2.0f, 0.0f);

	// Create the ground model object.
	m_GroundModel = new ModelClass;
	if(!m_GroundModel)
	{
		return false;
	}

	// Initialize the ground model object.
	result = m_GroundModel->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), "../Engine/data/plane01.txt", L"../Engine/data/metal001.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the ground model object.", L"Error", MB_OK);
		return false;
	}

	// Set the position for the ground model.
	m_GroundModel->SetPosition(0.0f, 1.0f, 0.0f);

	// LIGHT # 1
	m_Light1 = new LightClass;
	if(!m_Light1)
	{
		return false;
	}

	m_Light1->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light1->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light1->SetLookAt(0.0f, 0.0f, 0.0f);
	m_Light1->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);

	// LIGHT # 2
	m_Light2 = new LightClass;
	if (!m_Light2)
	{
		return false;
	}

	// Initialize the light object.
	m_Light2->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light2->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light2->SetLookAt(0.0f, 0.0f, 0.0f);
	m_Light2->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);
	
	// Create the render to texture object.
	m_ShadowTexture1 = new RenderTextureClass;
	if(!m_ShadowTexture1)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_ShadowTexture1->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the render to texture object.
	m_ShadowTexture2 = new RenderTextureClass;
	if (!m_ShadowTexture1)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_ShadowTexture2->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the depth shader object.
	m_DepthShader = new DepthShaderClass;
	if(!m_DepthShader)
	{
		return false;
	}

	// Initialize the depth shader object.
	result = m_DepthShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the black and white render to texture object.
	m_BlackWhiteRenderTexture1 = new RenderTextureClass;
	if(!m_BlackWhiteRenderTexture1)
	{
		return false;
	}

	// Initialize the black and white render to texture object.
	result = m_BlackWhiteRenderTexture1->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the black and white render to texture object.", L"Error", MB_OK);
		return false;
	}

	//// Create the black and white render to texture object.
	//m_BlackWhiteRenderTexture2 = new RenderTextureClass;
	//if (!m_BlackWhiteRenderTexture2)
	//{
	//	return false;
	//}

	//// Initialize the black and white render to texture object.
	//result = m_BlackWhiteRenderTexture2->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the black and white render to texture object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the shadow shader object.
	m_ShadowShader = new ShadowShaderClass;
	if(!m_ShadowShader)
	{
		return false;
	}

	// Initialize the shadow shader object.
	result = m_ShadowShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shadow shader object.", L"Error", MB_OK);
		return false;
	}

	// Set the size to sample down to.
	downSampleWidth = SHADOWMAP_WIDTH / 2;
	downSampleHeight = SHADOWMAP_HEIGHT / 2;

	// Create the down sample render to texture object.
	m_DownSampleTexure = new RenderTextureClass;
	if(!m_DownSampleTexure)
	{
		return false;
	}

	// Initialize the down sample render to texture object.
	result = m_DownSampleTexure->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, 100.0f, 1.0f);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the down sample render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the small ortho window object.
	m_SmallWindow = new OrthoWindowClass;
	if(!m_SmallWindow)
	{
		return false;
	}

	// Initialize the small ortho window object.
	result = m_SmallWindow->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the small ortho window object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the horizontal blur render to texture object.
	m_HorizontalBlurTexture = new RenderTextureClass;
	if(!m_HorizontalBlurTexture)
	{
		return false;
	}

	// Initialize the horizontal blur render to texture object.
	result = m_HorizontalBlurTexture->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, 0.1f);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the horizontal blur render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the horizontal blur shader object.
	m_HorizontalBlurShader = new HorizontalBlurShaderClass;
	if(!m_HorizontalBlurShader)
	{
		return false;
	}

	// Initialize the horizontal blur shader object.
	result = m_HorizontalBlurShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the horizontal blur shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the vertical blur render to texture object.
	m_VerticalBlurTexture = new RenderTextureClass;
	if(!m_VerticalBlurTexture)
	{
		return false;
	}

	// Initialize the vertical blur render to texture object.
	result = m_VerticalBlurTexture->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, 0.1f);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the vertical blur render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the vertical blur shader object.
	m_VerticalBlurShader = new VerticalBlurShaderClass;
	if(!m_VerticalBlurShader)
	{
		return false;
	}

	// Initialize the vertical blur shader object.
	result = m_VerticalBlurShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the vertical blur shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the up sample render to texture object.
	m_UpSampleTexure = new RenderTextureClass;
	if(!m_UpSampleTexure)
	{
		return false;
	}

	// Initialize the up sample render to texture object.
	result = m_UpSampleTexure->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, 0.1f);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the up sample render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the full screen ortho window object.
	m_FullScreenWindow = new OrthoWindowClass;
	if(!m_FullScreenWindow)
	{
		return false;
	}

	// Initialize the full screen ortho window object.
	result = m_FullScreenWindow->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the full screen ortho window object.", L"Error", MB_OK);
		return false;
	}

	// Create the soft shadow shader object.
	m_SoftShadowShader = new SoftShadowShaderClass;
	if(!m_SoftShadowShader)
	{
		return false;
	}

	// Initialize the soft shadow shader object.
	result = m_SoftShadowShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the soft shadow shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

bool GraphicsClass::Frame(float posX, float posY, float posZ, float rotX, float rotY, float rotZ)
{
	bool result;
	static float lightPositionX = -5.0f;


	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Update the position of the light each frame.
	lightPositionX += 0.05f;
	if(lightPositionX > 5.0f)
	{
		lightPositionX = -5.0f;
	}
	// Update the position of the light.
	m_Light1->SetPosition(lightPositionX/*5.0f*/, 8.0f, -5.0f);
	m_Light2->SetPosition(-5.0f, 8.0f, 5.0f);

	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Render()
{
	bool result;
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	float posX, posY, posZ;

	RenderShadows();

	//ApplyBlur(m_BlackWhiteRenderTexture1->GetShaderResourceView());
	ID3D11ShaderResourceView* blurredShadows = ApplyBlur(m_BlackWhiteRenderTexture1->GetShaderResourceView(), m_UpSampleTexure);

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);

	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_CubeModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(posX, posY, posZ));
	m_CubeModel->Render(m_D3D->GetDeviceContext());
	result = m_SoftShadowShader->Render(m_D3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
										m_CubeModel->GetTexture(), 
										blurredShadows, /*m_UpSampleTexure->GetShaderResourceView(), */
										m_Light2->GetPosition(), m_Light2->GetAmbientColor(), m_Light2->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_SphereModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(posX, posY, posZ));
	m_SphereModel->Render(m_D3D->GetDeviceContext());
	result = m_SoftShadowShader->Render(m_D3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
										m_SphereModel->GetTexture(), 
										blurredShadows, //m_UpSampleTexure->GetShaderResourceView(),
										m_Light2->GetPosition(), m_Light2->GetAmbientColor(), m_Light2->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_GroundModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(posX, posY, posZ));
	m_GroundModel->Render(m_D3D->GetDeviceContext());
	result = m_SoftShadowShader->Render(m_D3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
										m_GroundModel->GetTexture(), 
										blurredShadows,
										m_Light2->GetPosition(),m_Light2->GetAmbientColor(), m_Light2->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

ID3D11ShaderResourceView* GraphicsClass::ApplyBlur(ID3D11ShaderResourceView* viewToBlur, RenderTextureClass* outputRenderTarget)
{
	XMMATRIX worldMatrix, baseViewMatrix, orthoMatrix;

	m_Camera->Render();
	m_D3D->TurnZBufferOff();
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);

	// Down sample texture
	m_DownSampleTexure->SetRenderTarget(m_D3D->GetDeviceContext());
	m_DownSampleTexure->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f); // REALLY UNNECESSARY???
	m_DownSampleTexure->GetOrthoMatrix(orthoMatrix);
	m_SmallWindow->RenderBuffers(m_D3D->GetDeviceContext());
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_SmallWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,viewToBlur);

	// Apply horizontal blur
	m_HorizontalBlurTexture->SetRenderTarget(m_D3D->GetDeviceContext());
	m_HorizontalBlurShader->Render(m_D3D->GetDeviceContext(), m_SmallWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
		m_DownSampleTexure->GetShaderResourceView(), (float)(SHADOWMAP_WIDTH * 0.5f));

	// Apply vertical blur
	m_VerticalBlurTexture->SetRenderTarget(m_D3D->GetDeviceContext());
	m_VerticalBlurShader->Render(m_D3D->GetDeviceContext(), m_SmallWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
		m_HorizontalBlurTexture->GetShaderResourceView(), (float)(SHADOWMAP_HEIGHT * 0.5f));

	// Up sample texture to output
	outputRenderTarget->SetRenderTarget(m_D3D->GetDeviceContext());
	outputRenderTarget->GetOrthoMatrix(orthoMatrix);
	m_FullScreenWindow->RenderBuffers(m_D3D->GetDeviceContext());
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_FullScreenWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
		m_VerticalBlurTexture->GetShaderResourceView());

	m_D3D->TurnZBufferOn();
	m_D3D->SetBackBufferRenderTarget();
	m_D3D->ResetViewport();

	//return m_UpSampleTexure->GetShaderResourceView();
	return outputRenderTarget->GetShaderResourceView();
	//return true;
}

void GraphicsClass::RenderShadows()
{
	XMMATRIX worldMatrix, lightViewMatrix, lightProjectionMatrix;
	XMMATRIX lightViewMatrix2, lightProjectionMatrix2;
	float posX, posY, posZ;

	// CALCULATE LIGHTS
	m_Light1->GenerateViewMatrix();
	m_Light1->GetViewMatrix(lightViewMatrix);
	m_Light1->GetProjectionMatrix(lightProjectionMatrix);

	m_Light2->GenerateViewMatrix();
	m_Light2->GetViewMatrix(lightViewMatrix2);
	m_Light2->GetProjectionMatrix(lightProjectionMatrix2);

// RENDER SCENE TO DEPTH TEXTURE 1
	m_ShadowTexture1->SetRenderTarget(m_D3D->GetDeviceContext());
	m_ShadowTexture1->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Render cube.
	m_CubeModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);
	m_CubeModel->Render(m_D3D->GetDeviceContext());
	m_DepthShader->Render(m_D3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);

	// Render sphere.
	m_SphereModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);
	m_SphereModel->Render(m_D3D->GetDeviceContext());
	m_DepthShader->Render(m_D3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);

	// Render ground.
	m_GroundModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);
	m_GroundModel->Render(m_D3D->GetDeviceContext());
	m_DepthShader->Render(m_D3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();
	m_D3D->ResetViewport();

// RENDER SCENE TO DEPTH TEXTURE 2
	m_ShadowTexture2->SetRenderTarget(m_D3D->GetDeviceContext());
	m_ShadowTexture2->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Render cube.
	m_CubeModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);
	m_CubeModel->Render(m_D3D->GetDeviceContext());
	m_DepthShader->Render(m_D3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, lightViewMatrix2, lightProjectionMatrix2);

	// Render sphere.
	m_SphereModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);
	m_SphereModel->Render(m_D3D->GetDeviceContext());
	m_DepthShader->Render(m_D3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix, lightViewMatrix2, lightProjectionMatrix2);

	// Render ground.
	m_GroundModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);
	m_GroundModel->Render(m_D3D->GetDeviceContext());
	m_DepthShader->Render(m_D3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, lightViewMatrix2, lightProjectionMatrix2);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();
	m_D3D->ResetViewport();

// RENDER BLACK AND WHITE SHADOWS TO ONE TEXTURE
	XMMATRIX viewMatrix, projectionMatrix;

	// Set the render target to be the render to texture.
	m_BlackWhiteRenderTexture1->SetRenderTarget(m_D3D->GetDeviceContext());
	m_BlackWhiteRenderTexture1->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_CubeModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	// Render the cube model using the shadow shader.
	m_CubeModel->Render(m_D3D->GetDeviceContext());
	m_ShadowShader->Render(m_D3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), 
		worldMatrix, viewMatrix, projectionMatrix, 
		lightViewMatrix,lightProjectionMatrix, 
		lightViewMatrix2, lightProjectionMatrix2, 
		m_ShadowTexture1->GetShaderResourceView(), m_ShadowTexture2->GetShaderResourceView(),
		m_Light1->GetPosition(), m_Light2->GetPosition());

	m_SphereModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);
	m_SphereModel->Render(m_D3D->GetDeviceContext());
	m_ShadowShader->Render(m_D3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
		lightViewMatrix, lightProjectionMatrix,
		lightViewMatrix2, lightProjectionMatrix2,
		m_ShadowTexture1->GetShaderResourceView(), m_ShadowTexture2->GetShaderResourceView(),
		m_Light1->GetPosition(), m_Light2->GetPosition());

	// Setup the translation matrix for the ground model.
	m_GroundModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);
	m_GroundModel->Render(m_D3D->GetDeviceContext());
	m_ShadowShader->Render(m_D3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
		lightViewMatrix, lightProjectionMatrix,
		lightViewMatrix2, lightProjectionMatrix2,
		m_ShadowTexture1->GetShaderResourceView(), m_ShadowTexture2->GetShaderResourceView(),
		m_Light1->GetPosition(), m_Light2->GetPosition());

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();
	m_D3D->ResetViewport();
}
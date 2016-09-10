//	DX11Renderer - VDemo | DirectX11 Renderer
//	Copyright(C) 2016  - Volkan Ilbeyli
//
//	This program is free software : you can redistribute it and / or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.If not, see <http://www.gnu.org/licenses/>.
//
//	Contact: volkanilbeyli@gmail.com
#pragma once

#include <windows.h>
#include "GeometryGenerator.h"
#include "Shader.h"
#include "Texture.h"
//#include <string>
//#include <vector>

#include "Mesh.h"
#include "GameObject.h"

#include <memory>

// forward declarations
class D3DManager;
struct ID3D11Device;
struct ID3D11DeviceContext;

class BufferObject;
class Camera;
class Shader;

namespace DirectX
{
	class ScratchImage;
}

// typedefs
typedef int ShaderID;
typedef int BufferID;
typedef int TextureID;
typedef int RasterizerStateID;
typedef ID3D11RasterizerState RasterizerState;

enum RASTERIZER_STATE
{
	CULL_NONE = 0,
	CULL_FRONT,
	CULL_BACK,

	RS_COUNT
};

struct Skydome
{
	void Render(Renderer* renderer, const XMMATRIX& view, const XMMATRIX& proj) const;
	void Init(Renderer* renderer_in, const char* tex, float scale);

	GameObject skydomeObj;
	TextureID skydomeTex;
	ShaderID skydomeShader;
	Renderer* renderer;
};

struct TextureSetCommand
{
	TextureID texID;
	ShaderTexture shdTex;
};

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Init(int width, int height, HWND hwnd);
	void Exit();
	HWND GetWindow() const;
	float AspectRatio() const;
	unsigned WindowHeight() const;
	unsigned WindowWidth() const;

	void EnableAlphaBlending(bool enable);
	void EnableZBuffer(bool enable);

	// resource interface
	ShaderID	AddShader(const std::string& shdFileName, const std::string& fileRoot, const std::vector<InputLayout>& layouts);
	TextureID	AddTexture(const std::string& shdFileName, const std::string& fileRoot);

	// state management
	void SetViewport(const unsigned width, const unsigned height);
	void SetCamera(Camera* m_camera);
	void SetShader(ShaderID);
	void SetBufferObj(int BufferID);
	void SetConstant4x4f(const char* cName, const XMMATRIX& matrix);
	void SetConstant3f(const char* cName, const XMFLOAT3& float3);
	void SetConstant1f(const char* cName, const float data);
	void SetConstantStruct(const char * cName, void* data);
	void SetTexture(const char* texName, TextureID tex);
	void SetRasterizerState(int stateID);

	void Begin(const float clearColor[4]);
	void Reset();
	void Apply();
	void End();
	void DrawIndexed();
	void PollShaderFiles();
private:

	void GeneratePrimitives();
	void PollThread();
	void OnShaderChange(LPTSTR dir);

	void InitRasterizerStates();

public:
	static const bool FULL_SCREEN  = false;
	static const bool VSYNC = false;	// insane input lag; turned off

private:
	D3DManager*						m_Direct3D;
	HWND							m_hWnd;
	ID3D11Device*					m_device;
	ID3D11DeviceContext*			m_deviceContext;

	GeometryGenerator				m_geom;

	// render data
	Camera*							m_mainCamera;
	D3D11_VIEWPORT					m_viewPort;
	Skydome							m_skydome;

	std::vector<BufferObject*>		m_bufferObjects;
	std::vector<Shader*>			m_shaders;
	std::vector<Texture>			m_textures;

	std::queue<TextureSetCommand>	m_texSetCommands;

	// state variables
	ShaderID						m_activeShader;
	BufferID						m_activeBuffer;
	
	std::vector<RasterizerState*>	m_rasterizerStates;
	
	// performance counters
	unsigned long long				m_frameCount;
};


 
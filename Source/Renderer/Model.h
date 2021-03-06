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

#include "Material.h"

class Model
{
public:
	Model() : mMesh(-1) {}
	//Model()  = default;
	~Model() = default;

	void SetDiffuseAlpha(const LinearColor & diffuseColor, float alpha);
	void SetDiffuseColor(const LinearColor & diffuseColor);
	void SetNormalMap(const TextureID normalMap);
	void SetDiffuseMap(const TextureID diffuseMap);
	void SetTextureTiling(const vec2& tiling);

public:
	int				mMesh;
	BRDF_Material		mBRDF_Material;
	BlinnPhong_Material mBlinnPhong_Material;
};
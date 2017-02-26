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

#ifndef UTILS_CPP
#define UTILS_CPP

#include <string>
#include <vector>
#include <DirectXMath.h>
using namespace DirectX;

// macros
#define DEG2RAD (XM_PI / 180.0f)
#define RAD2DEG (180.0f / XM_PI)

// typedefs
using VecPair = std::pair<XMVECTOR, XMVECTOR>;

// consts
const XMFLOAT3 ZeroF3 = XMFLOAT3(0.0f, 0.0f, 0.0f);

/// STRING PROCESSING
//===============================================================================================
std::vector<std::string> split(const char* s,			char c = ' ');
std::vector<std::string> split(const std::string& s,	char c = ' ');
std::string	GetFileNameFromPath(const std::string&);

bool isNormalMap(const std::string& fileName);
std::string GetTextureNameFromDirectory(const std::string& dir);

/// RANDOM
//===============================================================================================
float	RandF(float l, float h);
int		RandI(int l, int h);
size_t	RandU(size_t l, size_t h);

/// 3D
//===============================================================================================
struct Point
{
	Point() : pos(0, 0, 0) {}
	Point(float x, float y, float z)	: pos(x, y, z)					{}
	Point(const XMFLOAT3& f3)			: pos(f3)						{}
	Point(const XMVECTOR& vec)											{ XMStoreFloat3(&pos, vec); }
	Point(const Point& r)				: pos(r.pos.x, r.pos.y, r.pos.z){}
	//-------------------------------------------------------------------
	operator XMFLOAT3() const											{ return pos; }
	operator XMVECTOR() const											{ return XMLoadFloat3(&pos);}
	Point					operator*(float f)	const					{ return Point(pos.x*f, pos.y*f, pos.z*f); }
	Point					operator-(const Point& p)					{ return Point(pos.x - p.pos.x, pos.y - p.pos.y, pos.z - p.pos.z); }
	inline static float		Distance(const Point& p1, const Point& p2)	{ XMVECTOR AB = XMLoadFloat3(&p2.pos) - XMLoadFloat3(&p1.pos); return sqrtf(XMVector3Dot(AB, AB).m128_f32[0]); }
	//-------------------------------------------------------------------
	XMFLOAT3 pos;
};
#endif
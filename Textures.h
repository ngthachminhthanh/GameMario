#pragma once
#include <unordered_map>
#include <d3d10.h>

/*
	Manage texture database
*/
class CTextures
{
	static CTextures* __instance;

	std::unordered_map<int, ID3D10ShaderResourceView*> textures;

public:
	CTextures();
	void Add(int id, LPCWSTR filePath);
	ID3D10ShaderResourceView* Get(unsigned int i);

	void Clear();
	static CTextures* GetInstance();
};

#pragma once
#include "Singleton.h"
#include "GameManager.h"

class Textures
{
public:
	Textures();
	~Textures();

	virtual bool Create(std::string pFileName, std::string pName);

	std::string GetName();
	sf::Texture* GetTexture();
private:

	std::string _name;
	sf::Texture _texture;
};

class Fonts
{
public:
	Fonts();
	~Fonts();

	virtual bool Create(std::string pFileName, std::string pName);

	std::string GetName();
	sf::Font* GetFont();
private:

	std::string _name;
	sf::Font _font;
};

class SoundBuffers
{
public:
	SoundBuffers();
	~SoundBuffers();

	virtual bool Create(std::string pFileName, std::string pName);

	std::string GetName();
	sf::SoundBuffer* GetSoundBuffer();
private:

	std::string _name;
	sf::SoundBuffer _SoundBuffer;
};


class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();

	void Load();
	sf::Texture* GetTexture(std::string _FileName);
	sf::Font* GetFont(std::string _FileName);
	sf::SoundBuffer* GetSoundBuffer(std::string _FileName);
	std::vector<Textures*> GetTextureVector();
	std::vector<Fonts*> GetFontVector();
	std::vector<SoundBuffers*> GetSoundBufferVector();
	float GetVectorsSize();

private:
	std::vector<Textures*> _textures;
	std::vector<Fonts*> _fonts;
	std::vector<SoundBuffers*> _soundBuffers;
};
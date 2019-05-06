#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Font.h"
#include "Canvas.h"
#include <string>

namespace e
{
	using namespace std;
	ResourceManager::~ResourceManager()
	{
		for (pair<string, SDL_Texture*> pair : m_pSDLTexturesByFile)
		{
			SDL_DestroyTexture(pair.second);
		}
	}
	void ResourceManager::Init(const string& gameName)
	{
		m_TexturePath = "../" + gameName + "/Resources/Textures/";
		m_FontPath = "../" + gameName + "/Resources/Fonts/";

		// load support for png and jpg, this takes a while!
		if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) throw runtime_error(string("Failed to load support for png's: ") + SDL_GetError());
		if((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) throw runtime_error(string("Failed to load support for jpg's: ") + SDL_GetError());
		if(TTF_Init() != 0) throw runtime_error(string("Failed to load support for fonts: ") + SDL_GetError());
	}

	shared_ptr<Font> ResourceManager::LoadFont(const std::string& fileName, unsigned int fontSize) const
	{
		return make_shared<Font>(m_FontPath + fileName, fontSize);
	}

	void ResourceManager::PrintTextureNames()
	{
		cout << "TEXTURE NAMES\n";
		for (pair<const string, ExtraTexture>& p : m_TexturesByName)
		{
			cout << p.first << '\n';
		}
		cout << '\n';
	}

	void ResourceManager::AddTexture(const std::string & name, const std::string & file)
	{
		ExtraTexture& Texture = m_TexturesByName[name] = { LoadpSDLTexture(file), {}, {} };
		SDL_QueryTexture(Texture.pSDLTexture, nullptr, nullptr, &Texture.source.w, &Texture.source.h);
		Texture.center = { Texture.source.w / 2, Texture.source.h / 2 };
	}

	void ResourceManager::AddTexture(const std::string& name, const std::string& file, const Frame& frame)
	{
		m_TexturesByName[name] = { LoadpSDLTexture(file), frame };
	}

	void ResourceManager::AddAnimation(const std::string & name, const std::string & file, float secondsPerFrame, const std::vector<Frame>& frames)
	{
		m_AnimationsByName[name] = { secondsPerFrame, {} };
		SDL_Texture* pSDLTexture{ LoadpSDLTexture(file) };
		for (const Frame& frame : frames) m_AnimationsByName[name].frames.push_back({ pSDLTexture, frame });
	}

	ExtraTexture* ResourceManager::GetpTexture(const string& name)
	{
		return &m_TexturesByName.at(name);
	}

	Animation* ResourceManager::GetpAnimation(const std::string & name)
	{
		return &m_AnimationsByName.at(name);
	}

	SDL_Texture* ResourceManager::LoadpSDLTexture(const std::string& file)
	{
		SDL_Texture* pSDLTexture{ m_pSDLTexturesByFile[file] };
		if (pSDLTexture == nullptr)
		{	//ADD TEXTURE
			const std::string path{ m_TexturePath + file };
			pSDLTexture = IMG_LoadTexture(Canvas::GetInstance().GetpRenderer(), path.c_str());
			if (pSDLTexture == nullptr) throw runtime_error(string("Failed to load texture from \"" + path + "\": ") + SDL_GetError());
			m_pSDLTexturesByFile[file] = pSDLTexture;
		}
		return pSDLTexture;
	}
}
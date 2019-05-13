#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Canvas.h"
#include <string>

namespace e
{
	using namespace std;
	ResourceManager::~ResourceManager()
	{
		for (const pair<string, SDL_Texture*>& pair : m_pSDLTexturesByFile)
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

	void ResourceManager::PrintTextureNames()
	{
		cout << "TEXTURE NAMES\n";
		for (pair<const string, Frame>& p : m_FramesByName)
		{
			cout << p.first << '\n';
		}
		cout << '\n';
	}

	void ResourceManager::AddTexture(const std::string& name, const std::string& file)
	{
		m_pSDLTexturesByName[name] = LoadpSDLTexture(file);
		Frame& frame = m_FramesByName[name];
		SDL_QueryTexture(m_pSDLTexturesByName[name], nullptr, nullptr, &frame.source.w, &frame.source.h);
		frame.center = { frame.source.w / 2, frame.source.h / 2 };
	}

	void ResourceManager::AddTexture(const std::string& name, const std::string& file, const Frame& frame)
	{
		m_pSDLTexturesByName[name] = LoadpSDLTexture(file);
		m_FramesByName[name] = frame;
	}

	void ResourceManager::AddAnimation(const std::string & name, const std::string& file, float secondsPerFrame, const std::vector<Frame>& frames)
	{
		m_pSDLTexturesByName[name] = LoadpSDLTexture(file);
		m_AnimationsByName[name] = { secondsPerFrame, {} };
		for (const Frame& frame : frames) m_AnimationsByName[name].frames.push_back(frame);
	}
	void ResourceManager::AddFont(const std::string& name, const std::string& file, unsigned fontSize)
	{
		m_pTTFFontsByName[name] = LoadpTTFFont(file, fontSize);
	}
	SDL_Texture* ResourceManager::GetSDLTexture(const std::string& name)
	{
		return m_pSDLTexturesByName.at(name);
	}
	Frame ResourceManager::GetFrame(const std::string& name)
	{
		if(m_FramesByName.find(name) != m_FramesByName.end()) return m_FramesByName.at(name);
		else return Frame(); //TODO
	}
	Animation* ResourceManager::GetpAnimation(const std::string & name)
	{
		return &m_AnimationsByName.at(name);
	}
	SDL_Texture* ResourceManager::LoadpSDLTexture(const std::string& file)
	{
		SDL_Texture*& pSDLTexture{ m_pSDLTexturesByFile[file] };
		if (pSDLTexture == nullptr)
		{	//ADD TEXTURE
			const std::string path{ m_TexturePath + file };
			pSDLTexture = IMG_LoadTexture(Canvas::GetInstance().GetpRenderer(), path.c_str());
			if (pSDLTexture == nullptr) throw runtime_error(string("Failed to load texture from \"" + path + "\": ") + SDL_GetError());
		}
		return pSDLTexture;
	}
	TTF_Font* ResourceManager::LoadpTTFFont(const std::string& file, const unsigned int fontSize)
	{
		TTF_Font*& pFont{ m_pTTFFontByFontIdentifier[file + std::to_string(fontSize)] };
		if (pFont == nullptr)
		{	//ADD FONT
			const std::string path{ m_FontPath + file };
			pFont = TTF_OpenFont(path.c_str(), fontSize);
			if (pFont == nullptr) throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
		}
		return pFont;
	}
}
#pragma once
#include "Singleton.h"
#include <SDL_ttf.h>
#include <unordered_map>
namespace e
{
	struct ExtraTexture;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		ResourceManager() = default;
		~ResourceManager();
		void Init(const std::string& gameName);
		void PrintTextureNames();
		void AddTexture(const std::string& name, const std::string& file);
		void AddTexture(const std::string& name, const std::string& file, const Frame& frame);
		void AddAnimation(const std::string& name, const std::string& file, float secondsPerFrame, const std::vector<Frame>& frames);
		void AddFont(const std::string& name, const std::string& file, unsigned int fontSize);
		SDL_Texture* GetSDLTexture(const std::string& name);
		Frame GetFrame(const std::string& name);
		Animation* GetpAnimation(const std::string& name);
		//TTF_Font* GetpTTFFont(const std::string& name);

		//FOR ADVANCED USERS
		SDL_Texture* LoadpSDLTexture(const std::string& file);
		TTF_Font* LoadpTTFFont(const std::string& file, const unsigned int fontSize);

	private:
		//MAPS TO AVOID LOADING THE SAME RESOURCE MORE THAN ONCE
		std::unordered_map<std::string, SDL_Texture*> m_pSDLTexturesByFile; 
		std::unordered_map<std::string, TTF_Font*> m_pTTFFontByFontIdentifier;

		std::string m_TexturePath;
		std::string m_FontPath;

		std::unordered_map<std::string, TTF_Font*> m_pTTFFontsByName; //TODO REMOVE THIS
		std::unordered_map<std::string, SDL_Texture*> m_pSDLTexturesByName; //TODO REMOVE THIS

		std::unordered_map<std::string, Frame> m_FramesByName;
		std::unordered_map<std::string, Animation> m_AnimationsByName;
	};
}

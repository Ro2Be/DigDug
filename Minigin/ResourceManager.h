#pragma once
#include "Singleton.h"
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
		std::shared_ptr<Font> LoadFont(const std::string& fontName, unsigned int fontSize) const;

		void PrintTextureNames();
		void AddTexture(const std::string& name, const std::string& file);
		void AddTexture(const std::string& name, const std::string& file, const Frame& frame);
		void AddAnimation(const std::string& name, const std::string& file, float secondsPerFrame, const std::vector<Frame>& frames);
		ExtraTexture* GetpTexture(const std::string& name);
		Animation* GetpAnimation(const std::string& name);

	private:
		std::string m_TexturePath;
		std::string m_FontPath;
		std::unordered_map<std::string, SDL_Texture*> m_pSDLTexturesByFile; //TO AVOID LOADING THE SAME SDL TEXTURE MORE THAN ONCE
		std::unordered_map<std::string, ExtraTexture> m_TexturesByName;
		std::unordered_map<std::string, Animation> m_AnimationsByName;

		SDL_Texture* LoadpSDLTexture(const std::string& file);
	};
}
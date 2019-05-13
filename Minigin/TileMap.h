#pragma once
namespace e
{
	template<char T, char X, char Y>
	class TileMap
	{
	public:
		TileMap(const char tiles[X][Y]);
		~TileMap();
	private:
		char m_Tiles[X][Y];
		SDL_Texture* m_pSDLTexture;
		SDL_Rect m_Sources[T];
	};
}
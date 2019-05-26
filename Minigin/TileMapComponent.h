#pragma once
#include <fstream>
#include "RenderableComponent.h"

namespace e
{
	template<unsigned char X, unsigned char Y> //TODO SWAP X AND Y
	class TileMapComponent final : public RenderableComponent
	{
	public:
		explicit TileMapComponent(const std::string& textureName, const TileSet& tileSet, unsigned char tiles[X][Y]) :
			RenderableComponent(textureName),
			m_TileSet{ std::move(tileSet) }
		{
			for (unsigned char y{}; y < Y; ++y) for (unsigned char x{}; x < X; ++x) m_Tiles[x][y] = tiles[x][y];
		}
		~TileMapComponent() override = default;
		void Draw(SDL_Renderer* pRenderer) const override
		{
			const IVector tileSize{ int(float(m_TileSet.sources[0].w) * m_pTransformComponent->scale.x), int(float(m_TileSet.sources[0].h) * m_pTransformComponent->scale.y) };
			SDL_Rect destination{ m_pTransformComponent->position.x, m_pTransformComponent->position.y, tileSize.x, tileSize.y };
			for (unsigned char y{}; y < Y; ++y)
			{
				for (unsigned char x{}; x < X; ++x)
				{
					SDL_RenderCopy(pRenderer, m_pTexture, &m_TileSet.sources[m_Tiles[x][y]], &destination);
					destination.y += tileSize.y;
				}
				destination.y = m_pTransformComponent->position.y;
				destination.x += tileSize.x;
			}
		}
		void SetTile(unsigned char x, unsigned char y, unsigned char value)
		{
			m_Tiles[x][y] = value;
		}
	private:
		TileSet m_TileSet;
		unsigned char m_Tiles[X][Y];
	};
}
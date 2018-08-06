#ifndef TERRAINTEXTUREPACK_H
#define TERRAINTEXTUREPACK_H

#include "TerrainTexture.h"

class TerrainTexturePack {
public:
	TerrainTexturePack(TerrainTexture& backgroundTexture, TerrainTexture& rTexture, TerrainTexture& gTexture, TerrainTexture& bTexture) {
		m_backgroundTexture = backgroundTexture;
		m_rTexture = rTexture;
		m_gTexture = gTexture;
		m_bTexture = bTexture;
	}
	TerrainTexturePack() {}

	inline TerrainTexture GetBackgroundTexture() { return m_backgroundTexture; }
	inline TerrainTexture GetRTexture() { return m_rTexture; }
	inline TerrainTexture GetGTexture() { return m_gTexture; }
	inline TerrainTexture GetBTexture() { return m_bTexture; }
private:
	TerrainTexture m_backgroundTexture;
	TerrainTexture m_rTexture;
	TerrainTexture m_gTexture;
	TerrainTexture m_bTexture;
};

#endif // !TERRAINTEXTUREPACK_H

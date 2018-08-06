#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

class TextureData {
public:
	TextureData(int width, int height, int numComponents, unsigned char* chars) :
		m_width(width), m_height(height), m_numComponents(numComponents), m_chars(chars) {}

	inline int GetWidth() { return m_width; }
	inline int GetHeight() { return m_height; }
	inline int GetNumComponents() { return m_numComponents; }
	inline unsigned char* GetChars() { return m_chars; }

private:
	int m_width;
	int m_height;
	int m_numComponents;
	unsigned char* m_chars;
};

#endif // !TEXTUREDATA_H

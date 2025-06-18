#include "TextRenderer.h"
#include <glm/gtc/matrix_transform.hpp>

TextRenderer::~TextRenderer() {
	// Clean up loaded fonts
	for (auto& [fontName, font] : fonts) {
		glDeleteTextures(1, &font.textureId);
		delete[] font.cdata;
	}
}

bool TextRenderer::loadFont(const std::string fontName, const std::filesystem::path &fontPath) {
	// Load the font file into memory
	std::ifstream fontFile(fontPath, std::ios::binary);
	if (!fontFile) {
		return false; // Failed to open the font file
	}

	FontData fontData(fontName);
	// Allocate memory for the baked font data
	fontData.cdata = new stbtt_bakedchar[96]; // 96 characters for ASCII range

	// Read the font data into a buffer
	const std::vector<unsigned char> fontBuffer((std::istreambuf_iterator<char>(fontFile)), std::istreambuf_iterator<char>());
	fontFile.close();

	unsigned char* temp_bitmap = new unsigned char[512 * 512]; // 512x512 bitmap for the baked font texture
	stbtt_BakeFontBitmap(fontBuffer.data(), 0, 32.0, temp_bitmap, 512, 512, 32, 96, fontData.cdata);

	glGenTextures(1, &fontData.textureId);
	glBindTexture(GL_TEXTURE_2D, fontData.textureId);
	GLint swizzleMask[] = { GL_ALPHA, GL_ALPHA, GL_ALPHA, GL_ALPHA };
	glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	this->fonts.insert({ fontName, fontData });

	return true; // Font loaded successfully
}

void TextRenderer::writeText(const std::string& text, const std::string &fontName, const glm::vec4 &color)
{
    if (!this->fonts.contains(fontName)) {
        throw std::runtime_error("Font not loaded: " + fontName);
        return; // Font not loaded
    }

	FontData font = this->fonts.at(fontName);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
	//tigl::shader->use();
    tigl::shader->setProjectionMatrix(glm::ortho(0.0f, (float)viewport[2], (float)viewport[3], 0.0f, -100.0f, 100.0f));
    tigl::shader->setViewMatrix(glm::mat4(1.0f));
    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    tigl::shader->enableColor(false);
    tigl::shader->enableLighting(false);
    tigl::shader->enableTexture(true);
    tigl::shader->enableColorMult(true);
    tigl::shader->setColorMult(color);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, font.textureId);

    float x = 400, y = 300;
    stbtt_aligned_quad q;
    tigl::begin(GL_QUADS);
    for (int i = 0; i < text.size(); i++) {
        if (text[i] >= 32 && text[i] < 128) {
            stbtt_GetBakedQuad(font.cdata, 512, 512, text[i] - 32, &x, &y, &q, 1);
            tigl::addVertex(tigl::Vertex::PT(glm::vec3(q.x0, q.y0, 0), glm::vec2(q.s0, q.t0)));
            tigl::addVertex(tigl::Vertex::PT(glm::vec3(q.x1, q.y0, 0), glm::vec2(q.s1, q.t0)));
            tigl::addVertex(tigl::Vertex::PT(glm::vec3(q.x1, q.y1, 0), glm::vec2(q.s1, q.t1)));
            tigl::addVertex(tigl::Vertex::PT(glm::vec3(q.x0, q.y1, 0), glm::vec2(q.s0, q.t1)));
        }
    }
    tigl::end();
    tigl::shader->enableColorMult(false);
}

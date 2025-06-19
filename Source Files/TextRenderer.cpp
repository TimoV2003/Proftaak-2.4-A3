#include "TextRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

const uint32_t codePointOfFirstChar = 32;
const uint32_t codePointOfLastChar = 122;
constexpr uint32_t charsToIncludeInFontAtlas = codePointOfFirstChar + codePointOfLastChar;

const uint32_t fontAtlasWidth = 1024;  // The width of font atlas texture
const uint32_t fontAtlasHeight = 1024; // The height of font atlas texture

stbtt_packedchar packedChars[charsToIncludeInFontAtlas];
stbtt_aligned_quad alignedQuads[charsToIncludeInFontAtlas];

float fontSize = 64.0f;


static void setupVAOAndVBO(const size_t size, uint32_t &vboId, uint32_t &vaoId)
{
	// Setting up the VAO and VBO: -----------------------
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	// position attribute:
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// color attribute:
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texCoord attribute:
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

static void setupFontTexture(uint8_t* fontAtlasBitmap, const uint32_t fontAtlasWidth, const uint32_t fontAtlasHeight, FontData &fontData) {
	uint32_t fontAtlasTextureID;

	glGenTextures(1, &fontAtlasTextureID);
	glBindTexture(GL_TEXTURE_2D, fontAtlasTextureID);

	// Upload the data to the GPU.
	// Important thing to note down is that the internal format of the
	// texture is GL_R8 and the format of the texture data is GL_UNSIGNED_BYTE 

	GLint swizzleMask[] = { GL_RED, GL_RED, GL_RED, GL_RED };
	glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, fontAtlasWidth, fontAtlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, fontAtlasBitmap);

	// Set the parameters of the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	fontData.fontAtlasTextureID = fontAtlasTextureID; // Store the texture ID in the FontData struct
}

static std::shared_ptr<uint8_t> loadFont(const std::string fontName, const std::filesystem::path& fontPath, FontData& fontData) {
	// Load the font file into memory
	std::ifstream fontFile(fontPath, std::ios::binary);
	if (!fontFile) {
		throw std::runtime_error("Failed to open font file: " + fontPath.string());
	}

	// Read the font data into a buffer
	const std::vector<unsigned char> fontBuffer((std::istreambuf_iterator<char>(fontFile)), std::istreambuf_iterator<char>());
	fontFile.close();

	int32_t fontCount = stbtt_GetNumberOfFonts(fontBuffer.data());

	if (fontCount != 1) {
		throw std::runtime_error("Font file must contain exactly one font. Found: " + std::to_string(fontCount));
	}

	constexpr uint32_t fontAtlasSize = fontAtlasWidth * fontAtlasHeight;

	std::shared_ptr<uint8_t> fontAtlasBitmap(new uint8_t[fontAtlasSize]); // Allocate memory for the font atlas bitmap

	stbtt_pack_context ctx;

	stbtt_PackBegin(
		&ctx,                                     // stbtt_pack_context (this call will initialize it) 
		(unsigned char*)fontAtlasBitmap.get(),          // Font Atlas bitmap data
		fontAtlasWidth,                           // Width of the font atlas texture
		fontAtlasHeight,                          // Height of the font atlas texture
		0,                                        // Stride in bytes
		1,                                        // Padding between the glyphs
		nullptr);

	stbtt_PackFontRange(
		&ctx,                                     // stbtt_pack_context
		fontBuffer.data(),                        // Font Atlas texture data
		0,                                        // Font Index                                 
		fontSize,                                 // Size of font in pixels. (Use STBTT_POINT_SIZE(fontSize) to use points) 
		codePointOfFirstChar,                     // Code point of the first character
		charsToIncludeInFontAtlas,                // No. of charecters to be included in the font atlas 
		packedChars                               // stbtt_packedchar array, this struct will contain the data to render a glyph
	);
	stbtt_PackEnd(&ctx);

	for (int i = 0; i < charsToIncludeInFontAtlas; i++)
	{
		float unusedX, unusedY;

		stbtt_GetPackedQuad(
			packedChars,                         // Array of stbtt_packedchar
			fontAtlasWidth,                      // Width of the font atlas texture
			fontAtlasHeight,                     // Height of the font atlas texture
			i,                                   // Index of the glyph
			&unusedX, &unusedY,                  // current position of the glyph in screen pixel coordinates, (not required as we have a different corrdinate system)
			&alignedQuads[i],                    // stbtt_alligned_quad struct. (this struct mainly consists of the texture coordinates)
			0                                    // Allign X and Y position to a integer (doesn't matter because we are not using 'unusedX' and 'unusedY')
		);
	}

	return fontAtlasBitmap;
}

void TextRenderer::initFont(const std::string fontName, const std::filesystem::path& fontPath) {

	FontData fontData(fontName);

	std::shared_ptr<uint8_t> fontAtlasBitmap = loadFont(fontName, fontPath, fontData);

	setupFontTexture(fontAtlasBitmap.get(), fontAtlasWidth, fontAtlasHeight, fontData);

	this->fonts.insert({ fontName, fontData });
}

uint32_t TextRenderer::createTextFrame(uint16_t size) {
	if (size <= 0) {
		throw std::runtime_error("Text frame size must be greater than 0");
	}

	TextFrame textFrame = TextFrame();
	textFrame.bufferSize = size * sizeof(Vertex) * 6; // 6 vertices per character (2 triangles per quad)
	setupVAOAndVBO(textFrame.bufferSize, textFrame.vboID, textFrame.vaoID);

	size_t position = this->textFrames.size();
	this->textFrames.push_back(textFrame);

	return position;
}

void TextRenderer::writeText(uint32_t textFrameId, const std::string& text, const float fontSize, const glm::vec2& position)
{
	FontData font = this->fonts.at(this->activeFontName);
	glm::vec4& color = this->activeColor;

	//TODO: find out why i have to multiply by 10 to get the correctish size
	const float size = fontSize * 10;
	uint32_t vertexIndex = 0;

	const int order[6] = { 0, 1, 2, 0, 2, 3 };
	float pixelScale = 2.0f / this->windowHeight;

	glm::vec3 localPosition(position[0], position[1], 0);

	std::vector<Vertex> vertices(text.size() * 6); // Reserve space for the vertices, each character will take 6 vertices
	for (char ch : text)
	{
		// Check if the charecter glyph is in the font atlas.
		if (ch >= codePointOfFirstChar && ch <= codePointOfFirstChar + charsToIncludeInFontAtlas)
		{
			if (vertices.size() <= vertexIndex)
				vertices.resize(vertices.size() + 6);

			// Retrive the data that is used to render a glyph of charecter 'ch'
			stbtt_packedchar* packedChar = &packedChars[ch - codePointOfFirstChar];
			stbtt_aligned_quad* alignedQuad = &alignedQuads[ch - codePointOfFirstChar];

			const unsigned short height = packedChar->y1 - packedChar->y0;
			const unsigned short width = packedChar->x1 - packedChar->x0;

			// The units of the fields of the above structs are in pixels, 
			// convert them to a unit of what we want be multilplying to pixelScale  
			glm::vec2 glyphSize =
			{
				width * pixelScale * size,
				height * pixelScale * size
			};

			glm::vec2 glyphBoundingBoxBottomLeft =
			{
				localPosition.x,
				localPosition.y
			};

			// The order of vertices of a quad goes top-right, top-left, bottom-left, bottom-right
			//Dit klopt allemaal, nagelopen door Luuk
			glm::vec2 glyphVertices[4] =
			{
				{ glyphBoundingBoxBottomLeft.x + glyphSize.x, glyphBoundingBoxBottomLeft.y - glyphSize.y },
				{ glyphBoundingBoxBottomLeft.x, glyphBoundingBoxBottomLeft.y - glyphSize.y },
				{ glyphBoundingBoxBottomLeft.x, glyphBoundingBoxBottomLeft.y },
				{ glyphBoundingBoxBottomLeft.x + glyphSize.x, glyphBoundingBoxBottomLeft.y },
			};

			glm::vec2 glyphTextureCoords[4] =
			{
				{ alignedQuad->s1, alignedQuad->t0 },
				{ alignedQuad->s0, alignedQuad->t0 },
				{ alignedQuad->s0, alignedQuad->t1 },
				{ alignedQuad->s1, alignedQuad->t1 },
			};

			// We need to fill the vertex buffer by 6 vertices to render a quad as we are rendering a quad as 2 triangles
			// The order used is in the 'order' array
			// order = [0, 1, 2, 0, 2, 3] is meant to represent 2 triangles: 
			// one by glyphVertices[0], glyphVertices[1], glyphVertices[2] and one by glyphVertices[0], glyphVertices[2], glyphVertices[3]
			for (int i = 0; i < 6; i++)
			{
				Vertex& vertex = vertices[vertexIndex + i];
				vertex.position = glm::vec3(glyphVertices[order[i]], 0);
				vertex.color = color;
				vertex.texCoord = glyphTextureCoords[order[i]];
			}

			vertexIndex += 6;

			// Update the position to render the next glyph specified by packedChar->xadvance.
			localPosition.x += packedChar->xadvance * pixelScale * size;
		}

		// Handle newlines seperately.
		else if (ch == '\n')
		{
			// advance y by fontSize, reset x-coordinate
			localPosition.y -= fontSize * pixelScale * size;
			localPosition.x = position.x;
		}
	}

	TextFrame &textFrame = this->textFrames.at(textFrameId);
	textFrame.vertexCount = vertices.size();
	const int vertexSize = sizeof(Vertex);
	size_t sizeOfVertices = vertices.size() * vertexSize;

	const Vertex* data = vertices.data();

	glBindVertexArray(textFrame.vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, textFrame.vboID);
	glBufferSubData(GL_ARRAY_BUFFER,
		0,
		sizeOfVertices,
		vertices.data());
	glBindVertexArray(0); // Unbind the VAO after updating the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the VBO after updating it
}

void TextRenderer::draw() {
	FontData font = this->fonts.at(this->activeFontName);

	tigl::shader->use();
	tigl::shader->setProjectionMatrix(glm::ortho(0.0f, this->windowWidth, this->windowHeight, 0.0f, -100.0f, 100.0f));
	tigl::shader->setViewMatrix(glm::mat4(1.0f));
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(true);
	tigl::shader->enableLighting(false);
	tigl::shader->enableTexture(true);
	tigl::shader->enableColorMult(false);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, font.fontAtlasTextureID);

	for(TextFrame &textFrame : this->textFrames) {
		glBindVertexArray(textFrame.vaoID);
		glDrawArrays(GL_TRIANGLES, 0, textFrame.vertexCount);
		glBindVertexArray(0); // Unbind the VAO after drawing
	}
}

void TextRenderer::setActiveFont(const std::string& fontName) {
	if (fonts.find(fontName) != fonts.end()) {
		this->activeFontName = fontName;
	}
	else {
		throw std::runtime_error("Font not loaded: " + fontName);
	}
}

void TextRenderer::setActiveColor(const glm::vec4& color) {
	this->activeColor = color;
}

void TextRenderer::startFrame() {
}

void TextRenderer::setWindowSize(float width, float height) {
	windowWidth = width;
	windowHeight = height;
}

TextRenderer::~TextRenderer() {
	// Clean up loaded fonts
	for (auto& [fontName, font] : fonts) {
		glDeleteTextures(1, &font.fontAtlasTextureID);
	}
}

//
// Created by Trevor Starick on 2015-11-14.
//

#ifndef ASTER_SPRITEBATCH_H
#define ASTER_SPRITEBATCH_H

#ifdef __APPLE__
# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl3w.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <glm/glm.hpp>

#include <vector>

#include "Vertex.h"

namespace Thanos {
    enum class GlyphSortType {
        NONE,
        FRONT_TO_BACK,
        BACK_TO_FRONT,
        TEXTURE
    };

    struct Glyph {
        GLuint texture;
        float depth;

        Vertex topRight;
        Vertex bottomRight;
        Vertex bottomLeft;
        Vertex topLeft;
    };

    class RenderBatch {
    public:
        RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) :
                offset(Offset),
                numVertices(NumVertices),
                texture(Texture) {};

        GLuint offset;
        GLuint numVertices;
        GLuint texture;
    };

    class SpriteBatch {
    public:
        SpriteBatch();
        ~SpriteBatch();

        void init();

        void begin(GlyphSortType _sortType = GlyphSortType::TEXTURE);
        void end();

        void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, ColorRGBA8 &color);

        void renderBatch();
    private:

        void createRenderBatches();
        void createVertexArray();
        void sortGlyphs();

        static bool compareFrontToBack(Glyph *a, Glyph *b);
        static bool compareBackToFront(Glyph *a, Glyph *b);
        static bool compareTexture(Glyph *a, Glyph *b);

        GLuint _vbo;
        GLuint _vao;

        GlyphSortType _sortType;

        std::vector<Glyph*> _glyphs;
        std::vector<RenderBatch> _renderBatches;
    };

}

#endif //ASTER_SPRITEBATCH_H

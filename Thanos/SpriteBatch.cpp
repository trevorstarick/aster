//
// Created by Trevor Starick on 2015-11-14.
//

#include <iostream>
#include "SpriteBatch.h"

#ifdef _WIN32
#include <algorithm>
#endif

namespace Thanos {
    SpriteBatch::SpriteBatch() : _vao(0), _vbo(0) {}
    SpriteBatch::~SpriteBatch() {}

    void SpriteBatch::init() {
        createVertexArray();
    }

    void SpriteBatch::begin(GlyphSortType sortType) {
        _sortType = sortType;
        _renderBatches.clear();

        for(unsigned int i = 0; i < _glyphs.size(); i++) {
            delete _glyphs[i];
        }

        _glyphs.clear();
    }

    void SpriteBatch::end() {
        sortGlyphs();
        createRenderBatches();
    }

    void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, ColorRGBA8 &color) {
        Glyph* newGlyph = new Glyph;
        newGlyph->texture = texture;
        newGlyph->depth = depth;


        newGlyph->topLeft.color = color;
        newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
        newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

        newGlyph->bottomLeft.color = color;
        newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
        newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

        newGlyph->bottomRight.color = color;
        newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
        newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

        newGlyph->topRight.color = color;
        newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
        newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);


        _glyphs.push_back(newGlyph);
    }

    void SpriteBatch::renderBatch() {

        glBindVertexArray(_vao);
        for(unsigned int i = 0; i < _renderBatches.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
            glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
        }
    }

    void SpriteBatch::createRenderBatches() {
        // This will store all the vertices that we need to upload
        std::vector <Vertex> vertices;
        // Resize the buffer to the exact size we need so we can treat
        // it like an array
        vertices.resize(_glyphs.size() * 6);

        if (_glyphs.empty()) {
            return;
        }

        int offset = 0; // current offset
        int cv = 0; // current vertex

        //Add the first batch
        _renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
        vertices[cv++] = _glyphs[0]->topLeft;
        vertices[cv++] = _glyphs[0]->bottomLeft;
        vertices[cv++] = _glyphs[0]->bottomRight;
        vertices[cv++] = _glyphs[0]->bottomRight;
        vertices[cv++] = _glyphs[0]->topRight;
        vertices[cv++] = _glyphs[0]->topLeft;
        offset += 6;

        //Add all the rest of the glyphs
        for (unsigned int cg = 1; cg < _glyphs.size(); cg++) {

            // Check if this glyph can be part of the current batch
            if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture) {
                // Make a new batch
                _renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
            } else {
                // If its part of the current batch, just increase numVertices
                _renderBatches.back().numVertices += 6;
            }
            vertices[cv++] = _glyphs[cg]->topLeft;
            vertices[cv++] = _glyphs[cg]->bottomLeft;
            vertices[cv++] = _glyphs[cg]->bottomRight;
            vertices[cv++] = _glyphs[cg]->bottomRight;
            vertices[cv++] = _glyphs[cg]->topRight;
            vertices[cv++] = _glyphs[cg]->topLeft;
            offset += 6;
        }

        // Bind our VBO
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        // Orphan the buffer (for speed)
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
        // Upload the data
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

        // Unbind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }

    void SpriteBatch::createVertexArray() {
        if(_vao == 0) {
            glGenVertexArrays(1, &_vao);
        }

        glBindVertexArray(_vao);

        if(_vbo == 0) {
            glGenBuffers(1, &_vbo);

        }

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *) offsetof(Vertex, color));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, uv));

        glBindVertexArray(0);

    }

    void SpriteBatch::sortGlyphs() {
        switch(_sortType) {
            case GlyphSortType::BACK_TO_FRONT:
                std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
                break;
            case GlyphSortType::FRONT_TO_BACK:
                std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
                break;
            case GlyphSortType::TEXTURE:
                std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
                break;
            case GlyphSortType::NONE:
                break;
        }
    }

    bool SpriteBatch::compareFrontToBack(Glyph *a, Glyph *b) {
        return (a->depth < b->depth);
    }
    bool SpriteBatch::compareBackToFront(Glyph *a, Glyph *b) {
        return (a->depth > b->depth);
    }
    bool SpriteBatch::compareTexture(Glyph *a, Glyph *b) {
        return (a->texture < b->depth);
    }
}

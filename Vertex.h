//
// Created by Trevor Starick on 2015-11-13.
//

#ifndef ASTER_VERTEX_H
#define ASTER_VERTEX_H

struct Vertex {
    struct Position {
        float x;
        float y;
    } position;

    struct UV {
        float u,v;
    } uv;

    struct Color {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    } color;

    void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }

    void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    void setUV(float u, float v) {
        uv.u = u;
        uv.v = v;
    }
};

#endif //ASTER_VERTEX_H

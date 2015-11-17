//
// Created by Trevor Starick on 2015-11-13.
//

#ifndef ASTER_VERTEX_H
#define ASTER_VERTEX_H

namespace Thanos {
    struct Position {
        float x;
        float y;
    };

    struct UV {
        float u, v;
    };

    struct ColorRGBA8 {
        ColorRGBA8(): r(0), g(0), b(0), a(0) {};
        ColorRGBA8(unsigned char R, unsigned char G, unsigned char B, unsigned char A):
            r(R), g(G), b(B), a(A) {};
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

    struct Vertex {


        Position position;
        UV uv;
        ColorRGBA8 color;

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

}
#endif //ASTER_VERTEX_H

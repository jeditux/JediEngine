#pragma once

#include "glad/glad.h"

namespace Rendering {
    class Texture2D {
    public:
        Texture2D(int width, int height, int nChannels, const unsigned char* data);
        ~Texture2D();
        void bind() const;
    private:
        GLuint m_Id;
    };
}

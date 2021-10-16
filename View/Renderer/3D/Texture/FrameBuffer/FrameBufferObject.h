//
// Created by Benjam on 26-05-21.
//

#ifndef MATH4BG_FRAMEBUFFEROBJECT_H
#define MATH4BG_FRAMEBUFFEROBJECT_H

#include <memory>
#include "RenderedTexture.h"

namespace Math4BG
{
    class FrameBufferObject
    {
    public:
        FrameBufferObject(unsigned int width, unsigned int height);
        ~FrameBufferObject();

        bool IsComplete() const;
        void Bind(bool fullViewport) const;
        void Unbind() const;

        inline std::shared_ptr<Texture> GetTexture() const { return m_texture; }
        inline unsigned int GetId() const { return m_colBuffer; }

    private:
        unsigned int m_colBuffer;
        unsigned int m_depthBuffer;

        unsigned int m_width;
        unsigned int m_height;

        std::shared_ptr<RenderedTexture> m_texture;
    };
}

#endif //MATH4BG_FRAMEBUFFEROBJECT_H

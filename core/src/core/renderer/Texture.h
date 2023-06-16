#pragma once
#include "_Core.h"
#include "utility.h"

namespace core {

    enum class ImageFormat
    {
        None = 0,
        R8,
        RGB8,
        RGBA8,
        RGBA32F
    };

    struct TextureSpecification
    {
        uint32_t Width = 1;
        uint32_t Height = 1;
        ImageFormat Format = ImageFormat::RGBA8;
        bool GenerateMips = true;
    };

    class Texture {
    private:
    public:
    	virtual void Bind(unsigned int slot) = 0;
        virtual void Unbind() = 0;

        virtual uint32_t GetID() const = 0;
        virtual int GetWidth() = 0;
        virtual int GetHeight() = 0;
        virtual std::string GetFilePath() = 0;
        virtual std::string GetName() = 0;

        virtual void SetData(void* data, uint32_t size) = 0;

        virtual bool operator==(const Texture& other) const = 0;

        virtual bool IsLoaded() = 0;

        virtual ~Texture() = default;

        static Shr<Texture> CreateTexture(std::string filePath, std::string name);

        static Shr<Texture> CreateTexture(TextureSpecification specification);
    };

}
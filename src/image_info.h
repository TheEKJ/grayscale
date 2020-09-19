#ifndef IMAGE_INFO_H
#define IMAGE_INFO_H
#include <cstdint>

#include "file_format.h"

class ImageInfo
{
public:
    ImageInfo();

    ImageInfo(const uint32_t& width, const uint32_t& height,
    const FileFormat& file_format);

    uint32_t width() const;
    uint32_t height() const;
    uint8_t components() const;
    FileFormat format() const;
private:
    FileFormat m_format;
    uint32_t m_width;
    uint32_t m_height;
    uint8_t m_components;
};

#endif
#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include <cstdint>

#include "size.h"
#include "image_info.h"

typedef uint8_t pixel;
typedef pixel* pixel_row;
typedef pixel_row* pixel_array;

class IO;

class Image
{
public:
    Image();

    uint32_t width() const;
    uint32_t height() const;
    uint8_t components() const;//RGB or RGBA

    void writePixels(pixel_array pixels);
    pixel_array readPixels() const;

    void save(const char* name);

    static Image MakeFromInfo(const ImageInfo& info);
    static Image MakeFromFilename(const char* filename);
private:
    ImageInfo m_info;
    pixel_array m_pixels;
};

#endif
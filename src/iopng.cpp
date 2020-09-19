#include "iopng.h"

#include <cstdio>
#include <csetjmp>

#include "image.h"
#include "png.h" 

IOPng::IOPng(const char* filename) :
m_filename(filename)
{}

Image IOPng::readImage()
{
    FILE* file = fopen(m_filename, "rb");
    Image image;
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                            NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);
    
    if(setjmp(png_jmpbuf(png))) system("pause"), exit(1);

    png_init_io(png, file);
    png_read_info(png, info);    

    uint32_t width = png_get_image_width(png, info);
    uint32_t height = png_get_image_height(png, info);
    uint8_t bit_depth = png_get_bit_depth(png, info);
    uint8_t color_type = png_get_color_type(png, info);

    if(bit_depth == 16) png_set_strip_16(png);
    if(color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png);
    if(png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);

    if(color_type == PNG_COLOR_TYPE_RGB ||
       color_type == PNG_COLOR_TYPE_PALETTE ||
       color_type == PNG_COLOR_TYPE_GRAY)
       png_set_filler(png, 0xff, PNG_FILLER_AFTER);

    if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    pixel_array pixels = new png_bytep[height];

    for(int y = 0; y < height; y++){
        pixels[y] = (pixel_row)png_malloc(png, png_get_rowbytes(png, info));
    }

    png_read_image(png, pixels);
    
    image = Image::MakeFromInfo(ImageInfo(width, height, FileFormat::PNG));

    image.writePixels(pixels);

    fclose(file);

    png_destroy_read_struct(&png, &info, NULL);

    return image;
}

void IOPng::writeImage(const Image& image)
{
    FILE* file = fopen(m_filename, "wb");
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);

    if(setjmp(png_jmpbuf(png))) system("pause"), exit(1);

    png_init_io(png, file);

    png_set_IHDR(png, info, image.width(), image.height(),
    8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_BASE,
    PNG_FILTER_TYPE_BASE);

    png_write_info(png, info);

    png_write_image(png, image.readPixels());

    png_write_end(png, info);

    fclose(file);

    png_destroy_write_struct(&png, &info);
}
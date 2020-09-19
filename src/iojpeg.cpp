#include "iojpeg.h"

#include "image.h"

#include <csetjmp>
#include <cstdio>
extern "C"
{
#include "jpeglib.h"
}

namespace
{
    struct error_mgr
    {
        jpeg_error_mgr pub;
        jmp_buf setjmp_buf;
    };

    void error_exit(j_common_ptr cinfo)
    {
        error_mgr* error = reinterpret_cast<error_mgr*>(cinfo->err);

        cinfo->err->output_message(cinfo);

        longjmp(error->setjmp_buf, 1);
    }
}

IOJpeg::IOJpeg(const char* filename) : 
m_filename(filename)
{}

Image IOJpeg::readImage()
{
    FILE* file = fopen(m_filename, "rb");
    Image image;
    jpeg_decompress_struct cinfo;
    error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = error_exit;

    if(setjmp(jerr.setjmp_buf)) system("pause"), exit(1);

    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);
    
    uint32_t width = cinfo.output_width;
    uint32_t height = cinfo.output_height;
    uint8_t num_components = cinfo.output_components;
    
    image = Image::MakeFromInfo(ImageInfo(width, height, FileFormat::JPEG));

    pixel_array pixels = new pixel_row[height];

    uint32_t row_stride = width * num_components;

    while(cinfo.output_scanline < cinfo.output_height){
        pixels[cinfo.output_scanline] = new pixel[row_stride];
        jpeg_read_scanlines(&cinfo, &pixels[cinfo.output_scanline], 1);
    }

    image.writePixels(pixels);

    jpeg_finish_decompress(&cinfo);
    fclose(file);
    jpeg_destroy_decompress(&cinfo);

    return image;
}

void IOJpeg::writeImage(const Image& image)
{
    FILE* file = fopen(m_filename, "wb");
    jpeg_compress_struct cinfo;
    error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = error_exit;

    if(setjmp(jerr.setjmp_buf)) system("pause"), exit(1);

    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, file);

    cinfo.image_width = image.width();
    cinfo.image_height = image.height();
    cinfo.input_components = image.components();
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 100, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    uint32_t row_stride = image.width() * image.components();

    pixel_array pixels = image.readPixels();

    while(cinfo.next_scanline < cinfo.image_height){
        jpeg_write_scanlines(&cinfo, &pixels[cinfo.next_scanline], 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(file);
    jpeg_destroy_compress(&cinfo);
}
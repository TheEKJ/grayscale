#include "image.h"

#include "file.h"
#include "iopng.h"
#include "iojpeg.h"

#include <memory>

Image::Image() :
m_pixels(nullptr)
{}

Image Image::MakeFromInfo(const ImageInfo& info)
{
    Image image;
    image.m_info = info;

    return image;
}

Image Image::MakeFromFilename(const char* filename)
{
    Image image;
    FileFormat format = get_file_format(filename);
    std::unique_ptr<IO> io(nullptr);

    switch(format){
    case FileFormat::PNG:
        io.reset(new IOPng(filename));
        break;
    case FileFormat::JPEG:
        io.reset(new IOJpeg(filename));
        break;
    default:
        puts("El archivo que usted introdujo es incompatible!");
        system("pause");
        exit(1);
        break;
    }

    image = io->readImage();

    return image;
}

uint32_t Image::width() const{return m_info.width();}
uint32_t Image::height() const{return m_info.height();}
uint8_t Image::components() const{return m_info.components();}

void Image::writePixels(pixel_array pixels)
{
    m_pixels = pixels;
}

pixel_array Image::readPixels() const
{
    return m_pixels;
}

void Image::save(const char* name)
{
    std::unique_ptr<IO> io(nullptr);
    std::string export_filename = name;

    switch(m_info.format()){
    case FileFormat::JPEG:
        export_filename.insert(export_filename.size(), ".jpg");
        io.reset(new IOJpeg(export_filename.c_str()));
    break;
    case FileFormat::PNG:
        export_filename.insert(export_filename.size(), ".png");
        io.reset(new IOPng(export_filename.c_str()));
    break;
    default: return; break;
    }

    io->writeImage(*this);
}
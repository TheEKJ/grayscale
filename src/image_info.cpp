#include "image_info.h"

ImageInfo::ImageInfo() :
m_width(0),
m_height(0),
m_components(0),
m_format(FileFormat::UNKNOWN)
{}

ImageInfo::ImageInfo(const uint32_t& width, const uint32_t& height,
                     const FileFormat& file_format) :
m_width(width),
m_height(height),
m_components(0),
m_format(file_format)
{
    switch(m_format){
    case FileFormat::PNG:  m_components = 4; break;
    case FileFormat::JPEG: m_components = 3; break;
    default:               m_components = 0; break;
    }
}

uint32_t ImageInfo::width() const{return m_width;}
uint32_t ImageInfo::height() const{return m_height;}
uint8_t ImageInfo::components() const{return m_components;}
FileFormat ImageInfo::format() const{return m_format;}
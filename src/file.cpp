#include "file.h"

#include "string.h"

#include <algorithm>

FileFormat get_file_format(std::string filename)
{
    std::string ext = to_lower(get_file_extension(filename));
    FileFormat format = FileFormat::UNKNOWN;

    if(ext == "png") format = FileFormat::PNG;
    if(ext == "jpeg" || ext == "jpg") format = FileFormat::JPEG;

    return format;
}

std::string get_file_extension(std::string filename)
{
    std::string result;

    int pos = filename.find_last_of('.');
    
    if(pos == -1) return std::string();

    result = filename.substr(pos + 1);

    return result;
}

std::string get_filename(std::string filename, const bool& extension)
{
    // 18/09/2020
    // TODO: AÑADIR LAS FUNCIONES DE ESCRIBIR DE LOS IO
    // TODO: CAMBIAR EL NOMBRE DEL OUTPUT DEL ARCHIVO
    // TODO: CAMBIAR RGB A GRAYSCALE

    std::string::const_reverse_iterator rit, point;
    std::string result;

    for(rit = filename.rbegin(); rit != filename.rend(); rit++){
        if(is_path_separator(*rit)) break;
        if(*rit == '.') point = rit + 1;
    }

    if(!extension) std::copy(rit.base(), point.base(), std::back_inserter(result));
    else std::copy(rit.base(), filename.cend(), std::back_inserter(result));

    return result;
}
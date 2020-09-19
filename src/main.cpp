#include "image.h"
#include "file.h"

#include <iostream>

int main(int argc, char* argv[])
{
    if(!argv[1]){
        puts("Error: No se ha pasado algun archivo");
        system("pause");
        return 1;
    }

    Image image = Image::MakeFromFilename(argv[1]);

    for(int y = 0; y < image.height(); y++){
        for(int x = 0; x < image.width(); x++){
            pixel_row px (&image.readPixels()[y][x * image.components()]);
// https://en.wikipedia.org/wiki/Luma_(video)
            uint32_t grayscale = ((0.2126f * px[0]) + (0.7152f * px[1]) + (0.0722f * px[2]));
            px[0] = px[1] = px[2] = grayscale;
        }
    }

    std::string export_name = get_filename(argv[1], false);
    export_name.insert(export_name.size(), " - grayscale");

    image.save(export_name.c_str());
    return 0;
}
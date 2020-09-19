#ifndef IO_H
#define IO_H
#include <string>

class Image;

class IO
{
public:
    virtual Image readImage() = 0;
    virtual void writeImage(const Image&) = 0;
};

#endif
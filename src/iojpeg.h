#ifndef IOJPEG_H
#define IOJPEG_H
#include "io.h"

class IOJpeg : public IO
{
public:
    IOJpeg(const char* filename);

    virtual Image readImage() override;
    virtual void writeImage(const Image& image) override;
private:
    const char* m_filename;
};

#endif
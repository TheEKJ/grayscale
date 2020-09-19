#ifndef IOPNG_H
#define IOPNG_H
#include "io.h"

class IOPng : public IO
{
public:
    IOPng(const char* filename);

    virtual Image readImage() override;
    virtual void writeImage(const Image& image) override;
private:
    const char* m_filename;
};

#endif
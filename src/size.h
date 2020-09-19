#ifndef SIZE_H
#define SIZE_H

template<typename T>
class SizeT
{
public:
    T width, height;

    SizeT() : width(0), height(0) {}
    SizeT(const T& Width, const T& Height) : width(Width), height(Height) {}
};

typedef SizeT<unsigned int> SizeU;

#endif
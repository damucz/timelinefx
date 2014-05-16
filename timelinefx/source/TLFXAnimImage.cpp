#include "TLFXAnimImage.h"

namespace TLFX
{


    AnimImage::AnimImage()
        : _width(0)
        , _height(0)
        , _maxRadius(0)
        , _index(0)
        , _frames(1)
    {

    }

    void AnimImage::SetMaxRadius( float radius )
    {
        _maxRadius = radius;
    }

    float AnimImage::GetMaxRadius() const
    {
        return _maxRadius;
    }

    void AnimImage::SetWidth( float width )
    {
        _width = width;
    }

    float AnimImage::GetWidth() const
    {
        return _width;
    }

    void AnimImage::SetHeight( float height )
    {
        _height = height;
    }

    float AnimImage::GetHeight() const
    {
        return _height;
    }

    void AnimImage::SetFramesCount( int frames )
    {
        _frames = frames;
    }

    int AnimImage::GetFramesCount() const
    {
        return _frames;
    }

    void AnimImage::SetIndex( int index )
    {
        _index = index;
    }

    int AnimImage::GetIndex() const
    {
        return _index;
    }

    void AnimImage::SetFilename( const char *filename )
    {
        _filename = filename;
    }

    const char * AnimImage::GetFilename() const
    {
        return _filename.c_str();
    }

    void AnimImage::SetName( const char *name )
    {
        _name = name;
    }

    const char * AnimImage::GetName() const
    {
        return _name.c_str();
    }

} // namespace TLFX

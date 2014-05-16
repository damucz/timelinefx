#ifdef _MSC_VER
#pragma once
#endif

#ifndef _TLFX_ANIMIMAGE_H
#define _TLFX_ANIMIMAGE_H

#include <string>

namespace TLFX
{

    class AnimImage
    {
    public:
        AnimImage();
        virtual ~AnimImage() {}

        virtual bool Load(const char *filename) = 0;

        void                SetWidth(float width);
        virtual float       GetWidth() const;
        void                SetHeight(float height);
        virtual float       GetHeight() const;
        void                SetMaxRadius(float radius);
        virtual float       GetMaxRadius() const;
        void                SetFramesCount(int frames);
        virtual int         GetFramesCount() const;
        void                SetIndex(int index);
        virtual int         GetIndex() const;
        void                SetFilename(const char *filename);
        virtual const char *GetFilename() const;
        void                SetName(const char *name);
        virtual const char *GetName() const;

        virtual void        FindRadius() {}

    protected:
        float _width;
        float _height;
        float _maxRadius;
        int _index;
        int _frames;
        std::string _filename;
        std::string _name;
    };

} // namespace TLFX

#endif // _TLFX_ANIMIMAGE_H

#ifdef _MSC_VER
#pragma once
#endif

#ifndef _TLFX_XMLLOADER_H
#define _TLFX_XMLLOADER_H

#include <string>
#include <list>

namespace TLFX
{

    class AnimImage;
    class Effect;
    class Emitter;

    class XMLLoader
    {
    public:
        virtual ~XMLLoader() {}

        virtual bool        Open(const char *filename) = 0;
        virtual bool        GetNextShape(AnimImage *shape) = 0;
        virtual Effect*     GetNextEffect(const std::list<AnimImage*>& sprites) = 0;

        virtual const char* GetLastError() const { return "no error reporting implemented"; }
    };

} // namespace TLFX

#endif // _TLFX_XMLLOADER_H

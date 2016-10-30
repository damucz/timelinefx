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
		XMLLoader(int shapes) : _existingShapeCount(shapes) {}
		virtual ~XMLLoader() {}

        virtual bool        Open(const char *filename) = 0;
        virtual bool        GetNextShape(AnimImage *shape) = 0;
        virtual Effect*     GetNextEffect(const std::list<AnimImage*>& sprites) = 0;
        virtual Effect*     GetNextSuperEffect(const std::list<AnimImage*>& sprites) = 0;
        virtual void        LocateEffect() = 0;
        virtual void        LocateSuperEffect() = 0;

        virtual const char* GetLastError() const { return "no error reporting implemented"; }
		
		int _existingShapeCount;
    };

} // namespace TLFX

#endif // _TLFX_XMLLOADER_H

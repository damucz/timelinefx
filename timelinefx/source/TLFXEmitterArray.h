#ifdef _MSC_VER
#pragma once
#endif

#ifndef _TLFX_EMITTERARRAY_H
#define _TLFX_EMITTERARRAY_H

#include "TLFXAttributeNode.h"

#include <vector>
#include <list>

namespace TLFX
{

    class EmitterArray
    {
    public:
        EmitterArray(float min, float max);

        void           Clear(unsigned int size = 0);
        AttributeNode* Add(float frame, float value);
        float          Get(float frame, bool bezier = true) const;
        float          operator()(float frame, bool bezier = true) const;
        float          GetOT(float age, float lifetime, bool bezier = true) const;
        float          operator()(float age, float lifetime, bool bezier = true) const;

        float          Interpolate(float frame, bool bezier = true) const;
        float          InterpolateOT(float age, float lifetime, bool bezier = true) const;

        void           Sort();

        unsigned int   GetAttributesCount() const;

        float           GetMaxValue() const;

        // compiled
        void           Compile();
        void           CompileOT(float longestLife);
        void           CompileOT();

        unsigned int   GetLastFrame() const;
        float          GetCompiled(unsigned int frame) const;
        void           SetCompiled(unsigned int frame, float value);

        float&         operator[](unsigned int frame);
        const float&   operator[](unsigned int frame) const;

        int            GetLife() const;
        void           SetLife(int life);

    protected:
        std::list<AttributeNode> _attributes;

        // compiled
        std::vector<float>       _changes;
        int                      _life;
        bool                     _compiled;
        float                    _min, _max;

        static float GetBezierValue(const AttributeNode& lastec, const AttributeNode& a, float t, float yMin, float yMax);
        static void GetQuadBezier(float p0x, float p0y, float p1x, float p1y, float p2x, float p2y, float t, float yMin, float yMax, float& outX, float& outY, bool clamp = true);
        static void GetCubicBezier(float p0x, float p0y, float p1x, float p1y, float p2x, float p2y, float p3x, float p3y,
            float t, float yMin, float yMax, float& outX, float& outY, bool clamp = true);
    };

} // namespace TLFX

#endif // _TLFX_EMITTERARRAY_H

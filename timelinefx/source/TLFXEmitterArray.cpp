#include "TLFXEmitterArray.h"
#include "TLFXEffectsLibrary.h"

#include <cassert>
#include <algorithm>
#include <cmath>

namespace TLFX
{

    EmitterArray::EmitterArray(float min, float max)
        : _life(0)
        , _compiled(false)
        , _min(min)
        , _max(max)
    {

    }

    unsigned int EmitterArray::GetLastFrame() const
    {
        return _changes.size() - 1;
    }

    float EmitterArray::GetCompiled( unsigned int frame ) const
    {
        unsigned int lastFrame = GetLastFrame();
        if (frame <= lastFrame)
        {
            return _changes[frame];
        }
        else
        {
            return _changes[lastFrame];
        }
    }

    void EmitterArray::SetCompiled( unsigned int frame, float value )
    {
        assert(frame >= 0 && frame < _changes.size());
        if (frame >= 0 && frame < _changes.size())
            _changes[frame] = value;
    }

    float& EmitterArray::operator[]( unsigned int index )
    {
        assert(index >= 0 && index < _changes.size());
        return _changes[index];
    }

    const float& EmitterArray::operator[]( unsigned int index ) const
    {
        assert(index >= 0 && index < _changes.size());
        return _changes[index];
    }

    int EmitterArray::GetLife() const
    {
        return _life;
    }

    void EmitterArray::SetLife( int life )
    {
        _life = life;
    }

    void EmitterArray::Compile()
    {
        if (_attributes.size() > 0)
        {
            const AttributeNode* lastec = &_attributes.back();
            float lookupFrequency = EffectsLibrary::GetLookupFrequency();
            int frame = (int)ceilf(lastec->frame / lookupFrequency);
            /*
            while (age < lastec->frame)
            {
                ++frame;
                age += lookupFrequency;
            }
            */
            _changes.resize(frame+1);
            frame = 0;
            float age = 0;
            while (age < lastec->frame)
            {
                SetCompiled(frame, Interpolate(age));
                ++frame;
                age = frame * lookupFrequency;
            }
            SetCompiled(frame, lastec->value);
        }
        else
        {
            _changes.resize(1);
        }
        _compiled = true;
    }

    void EmitterArray::CompileOT(float longestLife)
    {
        if (_attributes.size() > 0)
        {
            const AttributeNode* lastec = &_attributes.back();
            float lookupFrequency = EffectsLibrary::GetLookupFrequencyOverTime();
            int frame = (int)ceilf(longestLife / lookupFrequency);
            /*
            while (age < longestLife)
            {
                ++frame;
                age += lookupFrequency;
            }
            */
            _changes.resize(frame+1);
            frame = 0;
            float age = 0;
            while (age < longestLife)
            {
                SetCompiled(frame, InterpolateOT(age, longestLife));
                ++frame;
                age = frame * lookupFrequency;
            }
            SetCompiled(frame, lastec->value);
            SetLife((int)longestLife);
        }
        else
        {
            _changes.resize(1);
        }
        _compiled = true;
    }

    void EmitterArray::CompileOT()
    {
        CompileOT(_attributes.back().frame);
    }

    void EmitterArray::Sort()
    {
        _attributes.sort();
        //std::sort_heap(_attributes.begin(), _attributes.end());
        _compiled = false;
    }

    AttributeNode* EmitterArray::Add( float frame, float value )
    {
        _compiled = false;

        AttributeNode e;
        e.frame = frame;
        e.value = value;
        _attributes.push_back(e);
        return &(_attributes.back());
    }

    void EmitterArray::Clear(unsigned int size /*= 0*/)
    {
        _attributes.resize(size);
        _compiled = true;
    }

    float EmitterArray::GetBezierValue( const AttributeNode& lastec, const AttributeNode& a, float t, float yMin, float yMax )
    {
        if (a.isCurve)
        {
            if (lastec.isCurve)
            {
                float p0x = lastec.frame, p0y = lastec.value;
                float p1x = lastec.c1x  , p1y = lastec.c1y;
                float p2x = a.c0x       , p2y = a.c0y;
                float p3x = a.frame     , p3y = a.value;

                float x, y;
                GetCubicBezier(p0x, p0y, p1x, p1y, p2x, p2y, p3x, p3y, t, yMin, yMax, x, y);
                return y;
            }
            else
            {
                float p0x = lastec.frame, p0y = lastec.value;
                float p1x = a.c0x       , p1y = a.c0y;
                float p2x = a.frame     , p2y = a.value;

                float x, y;
                GetQuadBezier(p0x, p0y, p1x, p1y, p2x, p2y, t, yMin, yMax, x, y);
                return y;
            }
        }
        else if (lastec.isCurve)
        {
            float p0x = lastec.frame, p0y = lastec.value;
            float p1x = lastec.c1x  , p1y = lastec.c1y;
            float p2x = a.frame     , p2y = a.value;

            float x, y;
            GetQuadBezier(p0x, p0y, p1x, p1y, p2x, p2y, t, yMin, yMax, x, y);
            return y;
        }
        else
        {
            return 0;
        }
    }

    void EmitterArray::GetQuadBezier( float p0x, float p0y, float p1x, float p1y, float p2x, float p2y, float t, float yMin, float yMax, float& x, float& y, bool clamp /*= true*/ )
    {
        x = (1 - t) * (1 - t) * p0x + 2 * t * (1 - t) * p1x + t * t * p2x;
        y = (1 - t) * (1 - t) * p0y + 2 * t * (1 - t) * p1y + t * t * p2y;

        if (x < p0x) x = p0x;
        if (x > p2x) x = p2x;

        if (clamp)
        {
            if (y < yMin) y = yMin;
            if (y > yMax) y = yMax;
        }
    }

    void EmitterArray::GetCubicBezier( float p0x, float p0y, float p1x, float p1y, float p2x, float p2y, float p3x, float p3y, float t, float yMin, float yMax, float& x, float& y, bool clamp /*= true*/ )
    {
        x = (1 - t) * (1 - t) * (1 - t) * p0x + 3 * t * (1 - t) * (1 - t) * p1x + 3 * t * t * (1 - t) * p2x + t * t * t * p3x;
        y = (1 - t) * (1 - t) * (1 - t) * p0y + 3 * t * (1 - t) * (1 - t) * p1y + 3 * t * t * (1 - t) * p2y + t * t * t * p3y;

        if (x < p0x) x = p0x;
        if (x > p3x) x = p3x;

        if (clamp)
        {
            if (y < yMin) y = yMin;
            if (y > yMax) y = yMax;
        }
    }

    float EmitterArray::Interpolate( float frame, bool bezier /*= true*/ ) const
    {
        return InterpolateOT(frame, 1.0f);
    }

    float EmitterArray::InterpolateOT( float age, float lifetime, bool bezier /*= true*/ ) const
    {
        float lasty = 0;
        float lastf = 0;
        const AttributeNode* lastec = NULL;

        for (auto it = _attributes.begin(); it != _attributes.end(); ++it)
        {
            float frame = it->frame * lifetime;
            if (age < frame)
            {
                float p = float(age - lastf) / (frame - lastf);
                if (bezier)
                {
                    float bezierValue = GetBezierValue(*lastec, *it, p, _min, _max);
                    if (bezierValue != 0)
                    {
                        return bezierValue;
                    }
                }
                return lasty - p * (lasty - it->value);
            }
            lasty = it->value;
            lastf = frame/* - 1*/;
            if (bezier) lastec = &(*it);
        }
        return lasty;
    }

    float EmitterArray::Get( float frame, bool bezier /*= true*/ ) const
    {
        if (_compiled)
            return GetCompiled((unsigned int)frame);
        else
            return Interpolate(frame, bezier);
    }

    float EmitterArray::operator()( float frame, bool bezier /*= true*/ ) const
    {
        return Get(frame, bezier);
    }

    float EmitterArray::GetOT( float age, float lifetime, bool bezier /*= true*/ ) const
    {
        float frame = 0;
        if (lifetime > 0)
        {
            frame = age / lifetime * _life / EffectsLibrary::GetLookupFrequencyOverTime();
        }
        return Get(frame);
    }

    float EmitterArray::operator()( float age, float lifetime, bool bezier /*= true*/ ) const
    {
        return GetOT(age, lifetime);
    }

    unsigned int EmitterArray::GetAttributesCount() const
    {
        return _attributes.size();
    }

    float EmitterArray::GetMaxValue() const
    {
        float max = 0;
        for (auto it = _attributes.begin(); it != _attributes.end(); ++it)
        {
            if (it->value > max)
                max = it->value;
        }
        return max;
    }

} // namespace TLFX

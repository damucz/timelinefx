/**
 * TimelineFX for C++
 * 
 * <p>TimelineFX is a system for creating particle effects within your games and applications</p>
 * <p>Big thanks to the following: Bruce Henderson (Brucey) for all the great modules, Garritt Grandberg (gman) for the zipengine module,
 * Manel Ibáñez (Ziggy) for a great IDE, Doug Stastny for the DX9 module and Mark Sibly of course for everything Blitz.</p>
 * <p>For more help and tutorials that expand on the Docs below visit <a href="http://www.rigzsoft.co.uk" target="_blank">www.rigzsoft.co.uk</a></p>
 * 
 * Author: Peter J. Rigby
 * Copyright: Peter J. Rigby 2009-2010
 * Purpose: To add rich particle effects to games and applications, quickly and easily
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef _TLFX_EFFECTSLIBRARY_H
#define _TLFX_EFFECTSLIBRARY_H

#include "TLFXXMLLoader.h"

#include <map>
#include <list>
#include <string>

//#define MARMALADE_DEBUG_TRACE 

#ifdef MARMALADE_DEBUG_TRACE
    #include <IwDebug.h>
    #define TLFXLOG(chan, arg) IwTrace(chan, arg)
#else
    #define TLFXLOG(chan, arg)
#endif

namespace TLFX
{
    class Entity;
    class Effect;
    class Emitter;
    class AnimImage;

    /**
     * Effects library for storing a list of effects and particle images/animations
     * When using #LoadEffects, all the effects and images that go with them are stored in this type.
     */
    class EffectsLibrary
    {
    public:

        enum Time
        {
            TimeContinuous,
            TimeFinite,
        };

        enum AreaEffect
        {
            AEffTopEdge,
            AEffRightEdge,
            AEffBottomEdge,
            AEffLeftEdge,
        };

        static const float globalPercentMin;
        static const float globalPercentMax;
        static const float globalPercentSteps;

        static const float globalPercentVMin;
        static const float globalPercentVMax;
        static const float globalPercentVSteps;

        static const float angleMin;
        static const float angleMax;
        static const float angleSteps;

        static const float emissionRangeMin;
        static const float emissionRangeMax;
        static const float emissionRangeSteps;

        static const float dimensionsMin;
        static const float dimensionsMax;
        static const float dimensionsSteps;

        static const float lifeMin;
        static const float lifeMax;
        static const float lifeSteps;

        static const float amountMin;
        static const float amountMax;
        static const float amountSteps;

        static const float velocityMin;
        static const float velocityMax;
        static const float velocitySteps;

        static const float velocityOverTimeMin;
        static const float velocityOverTimeMax;
        static const float velocityOverTimeSteps;

        static const float weightMin;
        static const float weightMax;
        static const float weightSteps;

        static const float weightVariationMin;
        static const float weightVariationMax;
        static const float weightVariationSteps;

        static const float spinMin;
        static const float spinMax;
        static const float spinSteps;

        static const float spinVariationMin;
        static const float spinVariationMax;
        static const float spinVariationSteps;

        static const float spinOverTimeMin;
        static const float spinOverTimeMax;
        static const float spinOverTimeSteps;

        static const float directionOverTimeMin;
        static const float directionOverTimeMax;
        static const float directionOverTimeSteps;

        static const float framerateMin;
        static const float framerateMax;
        static const float framerateSteps;

        static const float maxDirectionVariation;
        static const float maxVelocityVariation;
        static const int   motionVariationInterval;

        EffectsLibrary();
        virtual ~EffectsLibrary();

        bool Load(const char *filename, bool compile = true);

        /**
         * Set the current Update Frequency.
         * the default update frequency is 30 times per second
         */
        static void SetUpdateFrequency(float freq);
        static float GetUpdateFrequency();
        static float GetUpdateTime();
        static float GetCurrentUpdateTime();

        /**
         * Set the lookup frequency for base, variation and global attributes
         * Default is 30 times per second. This means that the lookup tables for attribute nodes will be accurate to 30 milliseconds
         * which should be accurate enough.
         */
        static void SetLookupFrequency(float freq);
        static float GetLookupFrequency();

        /**
         * Set the lookup frequency for overtime attributes
         * Default is 1 time per second. This means that the lookup tables for attribute nodes will be accurate to 1 millisecond which is as accurate as it can be. Higher
         * values will save memory but effect will judder more and be less accurate the higher you go. The memory foot print is very small so 1 should be fine for 99% of apps.
         */
        static void SetLookupFrequencyOverTime(float freq);
        static float GetLookupFrequencyOverTime();

        /**
         * Add a new effect to the library including any sub effects and emitters.
         * Effects are stored using a map and can be retrieved using #GetEffect.
         */
        void AddEffect(Effect *effect);

        /**
         * Add a new emitter to the library. Emitters are stored using a map and can be retrieved using #GetEmitter.
         * Generally you don't want to call this at all unless you're building your effects manually, just use #AddEffect
         * and all its emitters will be added also.
         */
        void AddEmitter(Emitter *emitter);

        /**
         * Clear all effects in the library
         * Use this to empty the library of all effects and shapes.
         */
        void ClearAll();

        /**
         * Retrieve an effect from the library
         * <p>Use this to get an effect from the library by passing the name of the effect you want. Example:</p>
         * &{Effect* explosion = myEffectsLibrary->GetEffect("explosion")}
         * <p>All effects and emitters are stored using a directory like path structure so to get at sub effects you can do:</p>
         * &{Effect* explosion = myEffectsLibrary->GetEffect("Effect/Emitter/Sub Effect/Another Emitter/A deeper sub effect")}
         * <p>Note that you should always use forward slashes.</p>
         * @return Effect*
         */
        Effect* GetEffect(const char *name) const;

        /**
         * Retrieve an emitter from the library
         * <p> Use this To get an emitter from the library by passing the name of the emitter you want. All effects And emitters are
         * stored using a map with a directory like path structure. So retrieving an emitter called blast wave inside an effect called explosion
         * would be done like so:</p>
         * &{Emitter* blastwave = myEffectsLibrary->GetEmitter("explosion/blast wave")}
         * <p>Note that you should always use forward slashes.</p>
         * @return Emitter*
         */
        Emitter* GetEmitter(const char *name) const;

        bool AddSprite(AnimImage* image);

        virtual XMLLoader* CreateLoader() const = 0;
        virtual AnimImage* CreateImage() const = 0;

#ifdef _DEBUG
        static int particlesCreated;
#endif

    protected:
        std::map<std::string, Effect*>  _effects;
        std::map<std::string, Emitter*> _emitters;
        std::string                     _name;
        std::list<AnimImage*>           _shapeList;

        static float                    _updateFrequency;                  //  times per second
        static float                    _updateTime;
        static float                    _currentUpdateTime;
        static float                    _lookupFrequency;
        static float                    _lookupFrequencyOverTime;
    };

} // namespace TLFX

#endif // _TLFX_EFFECTSLIBRARY_H

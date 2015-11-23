#ifdef _MSC_VER
#pragma once
#endif

#ifndef _TLFX_PARTICLE_H
#define _TLFX_PARTICLE_H

#include "TLFXEntity.h"

#include <list>

namespace TLFX
{

    class Emitter;
    class ParticleManager;
	class Particle;
	
	typedef std::list<Particle*> ParticleList;

    /**
     * Particle Type - extends tlEntity
     * This is the object that is spawned by emitter types and maintained by a Particle Manager. Particles are controlled by the emitters and effects they're
     * parented to.
     */
    class Particle : public Entity
    {
        typedef Entity base;
    public:
        friend class Emitter;

        Particle();

        /**
         * Updates the particle.
         * This is called by the emitter the particle is parented to.
         */
        bool Update();

        /**
         * Resets the particle so it's ready to be recycled by the particle manager
         */
        void Reset();

        void Destroy(bool releaseChildren = true);

        /**
         * Set the current x coordinate of the particle and capture the old value
         */
        void SetX(float x);

        /**
         * Set the current y coordinate of the particle and capture the old value
         */
        void SetY(float y);

        /**
         * Set the current zoom factor of the particle and capture the old value
         */
        void SetZ(float z);

        void SetGroupParticles(bool value);
        bool IsGroupParticles() const;

        void SetLayer(int layer);
        int GetLayer() const;

        void SetEffectLayer(int layer);
        int GetEffectLayer() const;

        void SetEmitter(Emitter *e);
        Emitter* GetEmitter() const;

        void SetParticleManager(ParticleManager *pm);

        void SetReleaseSingleParticles(bool value);

        void SetVelVariation(float velVariation);
        float GetVelVariation() const;

        void SetGSizeX(float gSizeX);
        float GetGSizeX() const;
        void SetGSizeY(float gSizeY);
        float GetGSizeY() const;

        void SetScaleVariationX(float scaleVarX);
        float GetScaleVariationX() const;
        void SetScaleVariationY(float scaleVarY);
        float GetScaleVariationY() const;

        void SetEmissionAngle(float emissionAngle);
        float GetEmissionAngle() const;

        void SetDirectionVairation(float dirVar);
        float GetDirectionVariation() const;

        void SetSpinVariation(float spinVar);
        float GetSpinVariation() const;

        void SetWeightVariation(float weightVar);
        float GetWeightVariation() const;
		
		void SetIter(ParticleList::iterator iter);
		ParticleList::iterator GetIter() const;

    protected:
        Emitter*                    _emitter;                       // emitter it belongs to
        // -----------------------------
        float                       _weightVariation;               // Particle weight variation
        float                       _scaleVariationX;               // particle size x variation
        float                       _scaleVariationY;               // particle size y variation
        float                       _gSizeX;                        // Particle global size x
        float                       _gSizeY;                        // Particle global size y
        // -----------------------------
        float                       _velVariation;                  // velocity variation
        // -----------------------------
        float                       _spinVariation;                 // variation of spin speed
        // -----------------------------
        float                       _directionVariation;            // Direction variation at spawn time
        int                         _timeTracker;                   // This is used to keep track of game ticks so that some things can be updated between specific time intervals
        float                       _randomDirection;               // current direction of the random motion that pulls the particle in different directions
        float                       _randomSpeed;                   // random speed to apply to the particle movement
        float                       _emissionAngle;                 // Direction variation at spawn time
        bool                        _releaseSingleParticle;         // set to true to release single particles and let them decay and die
        // ----------------------------
        ParticleManager*            _particleManager;               // link to the particle manager
        int                         _layer;                         // layer the particle belongs to
        bool                        _groupParticles;                // whether the particle is added the PM pool or kept in the emitter's pool
        int                         _effectLayer;
		
		ParticleList::iterator      _listIter;                      // for quick deletes from ParticleList
    };

} // namespace TLFX

#endif // _TLFX_PARTICLE_H

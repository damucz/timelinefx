#ifdef _MSC_VER
#pragma once
#endif

#ifndef _TLFX_PARTICLEMANAGER_H
#define _TLFX_PARTICLEMANAGER_H

#include "TLFXMatrix2.h"
#include "TLFXVector2.h"

#include <vector>
#include <set>
#include <stack>

namespace TLFX
{

    class Particle;
    class Effect;
    class AnimImage;

    /**
     * Particle manager for managing a list of effects and all the emitters and particles they contain
     * <p>The particle manger is the main type you can use to easily manage all of the effects you want to use in your application. It will automatically update 
     * all of the effects and draw the particles with a simple call to #Update and #DrawParticles.</p>
     * <p>The simplest use of the particle manager would be to, create it, add an effect and then update and draw in your main loop:</p>
     * &{<pre>
     * EffectsLibrary* myEffectsLib = EffectsLibrary::LoadEffects("MyEffects.eff");
     * Effect* myEffect = myEffectsLib->GetEffect("Explosion");
     * ParticleManager* myParticleManager = ParticleManager::Create();
     * myParticleManager->SetScreenSize(GraphicsWidth(),GraphicsHeight());
     * myParticleManager->AddEffect(myEffect)
     * while(forever) {
     *     ClearScreen();
     *     myParticleManager->Update();
     *     myParticleManager->DrawParticles();
     *     FlipScreenBuffers();
     * }</pre>
     * }
     * <p>The particle manager maintains 2 lists of particles, an Inuse list for particles currently in the rendering pipeline and an UnUsed list for a pool of particles
     * that can be used by emitters at any time. You can control the maximum number of particles a particle manager can use when you create it:</p>
     * &{
     * int maximumParticles = 2500;
     * ParticleManager* myParticleManager = ParticleManager::CreateParticleManager(maximumParticles);
     * }
     * <p>When emitters need to spawn new particles they will try and grab the next available particle in the Unused list.</p>
     * <p>The command #SetScreenSize tells the particle manager the size of the viewport currently being rendered to. With this information it locates the center of the
     * screen. This is important because the effects do not locate themselves using screen coordinates, they instead use an abritrary set of world coordinates. So if you 
     * place an effect at the coordinates 0,0 it will be drawn at the center of the screen. But don't worry, if you want to use screen coordinates to place your
     * effects you can use the #SetOrigin command to offset the world coordinates to screen space:</p>
     * &{
     * myParticleManager->SetScreenSize(GraphicsWidth(),GraphicsHeight());
     * myParticleManager->SetOrigin(GraphicsWidth()/2,GraphicsHeight()/2);
     * }
     * <p>This will place the origin at the top-left of the viewport so effects placed at 0,0 now will be drawn in the top-left corner of the screen in the same way DrawImage
     * would. If however you application uses it's own world coordinate system to position entities then it should be easy to use #SetOrigin to synchronize the location of any 
     * effects with your app.</p>
     * <p>You can now also define a number of effect layers when creating a particle manager. This enables you to control more easily the order
     * in which effects are drawn. For example, if you create a particle manager with 10 layers, when you use #AddEffect you can specify
     * which layer the effect is added to. Effects on layers 1 will draw on top of layers on layer 0, 2 over 1 etc. The layer index starts from 0, 
     * so if you create 10 layers, their index will range from 0 to 9.</p>
     */
    class ParticleManager
    {
    public:
        static const int   particleLimit;

        /**
         * Create a new Particle Manager
         * Creates a new particle manager and sets the maximum number of particles. Default maximum is 5000.
         */
        ParticleManager(int particles /*= particleLimit*/, int layers /*= 1*/);
        virtual ~ParticleManager();

        /**
         * Update the Particle Manager
         * Run this method in your main loop to update all particle effects.
         */
        void Update();

        Particle* GrabParticle(Effect *effect, bool pool, int layer = 0);

        void ReleaseParticle(Particle *p);

        /**
         * Draw all particles currently in use
         * Draws all particles in use and uses the tween value you pass to use render tween in order to smooth out the movement of effects assuming you
         * use some kind of tweening code in your app. You can also specify the effect layer that is drawn, otherwise by default, all layers will be drawn.
         */
        void DrawParticles(float tween = 1.0f, int layer = -1);

        void DrawBoundingBoxes();

        /**
         * Set the Origin of the particle Manager.
         * An origin at 0,0 represents the center of the screen assuming you have called #SetScreenSize. Passing a z value will zoom in or out. Values above 1
         * will zoom out whilst values from 1 - 0 will zoom in. Values less then 0 will flip the particles being drawn.
         */
        void SetOrigin(float x, float y, float z = 1.0f);

        /**
         * Set the x origin
         * See #SetOrigin
         */
        void SetOriginX(float x);

        /**
         * Set the y origin
         * See #SetOrigin
         */
        void SetOriginY(float y);

        /**
         * Set the level of zoom
         * Values above 1 will zoom out whilst values from 1 - 0 will zoom in. Values less then 0 will flip the particles being drawn.
         */
        void SetOriginZ(float z);

        /**
         * Set the angle of the particle manager
         * Setting the angle of the particle manager will rotate all of the particles around the origin
         */
        void SetAngle(float angle);

        /**
         * Set the current screen size
         * Tells the particle manager the current size of the view port, whether its the screen size or canvas size if you're using a gui. 
         */
        void SetScreenSize(int w, int h);

        /**
         * Set the current screen position
         * If you're rendering to a particular section of the screen then you can set the position of the viewport's top left coordinates using
         * this command. Thanks to Imphy for the suggestion!
         */
        void SetScreenPosition(int x, int y);

        /**
         * Set the amount of time before idle effects are deleted from the particle manager
         * Any effects that have no active particles being drawn on the screen will be automatically removed from the particle manager
         * after a given time set by this function.
         */
        void SetIdleTimeLimit(int limit);
        int GetIdleTimeLimit() const;

        /**
         * Get the current x origin of the particle manager
         */
        float GetOriginX() const;

        /**
         * Get the current y origin of the particle manager
         */
        float GetOriginY() const;

        /**
         * Get the current z origin/zoom factor of the particle manager
         */
        float GetOriginZ() const;

        /**
         * Get the globalamountscale value of the particle manager
         * see #SetGlobalAmountScale for info about setting this value
         */
        float GetGlobalAmountScale() const;

        /**
         * Set the globalamountscale value of the particle manager
         * Setting this value will scale the amount of the particles spawned by all emitters contained within the particle manager, making it a handy way
         * to control globally, the amount of particles that are spawned. This can help improve performance on lower end hardware that struggle to draw
         * lots of particles. A value of 1 (the default value) will spawn the default amount for each effect. A value of 0.5 though for example, will spawn
         * half the amount of particles of each effect.
         */
        void SetGlobalAmountScale(float scale);

        /**
         * Get the current number of particles in use
         */
        int GetParticlesInUse() const;

        /**
         * Get the current number of unused particles
         */
        int GetParticlesUnused() const;

        /**
         * Adds a New effect To the particle manager, and pre loads a given number of frames
         * Use this method to add a new effect to the particle and start the effect running from whatever number of frames you pass to it.
         * In most cases the overhead for this will be small, but for extremely heavy effects with many particles you may experience some performance hit.
         * Use this instead of #AddEffect if you want to pre load an effect. If the particle manager has more then one layer, then you can specify
         * which layer the effect is added to. If the layer you pass does not exist then it will default to 0.
         */
        void AddPreLoadedEffect(Effect* effect, int frames, int layer = 0);

        /**
         * Adds a new effect to the particle manager
         * Use this method to add new effects to the particle manager which will be updated automatically. If the particle manager has more 
         * then one layer, then you can specify which layer the effect is added to. If the layer you pass does not exist then it will default to 0.
         */
        void AddEffect(Effect* effect, int layer = 0);

        /**
         * Removes an effect from the particle manager
         * Use this method to remove effects from the particle manager. It's best to destroy the effect as well to avoid memory leaks
         */
        void RemoveEffect(Effect* effect);

        /**
         * Clear all particles in use
         * Call this method to empty the list of in use particles and move them to the unused list.
         */
        void ClearInUse();

        /**
         * Destroy the particle manager
         * This will destroy the particle, clearing all effects and particles. Use only when you are finished with the particle manager and want it removed
         * to avoid any memory leaks.
         */
        void Destroy();

        /**
         * Remove all effects and clear all particles in use
         * If you want to remove all effects and particles from the manager then use this command. Every effect will instantly stop being
         * rendered.
         */
        void ClearAll();

        /**
         * Remove all effects and particles from a specific layer
         * If you want to remove all effects and particles from a specific layer in the particle manager then use this command. Every effect will instantly stop being
         * rendered.
         */
        void ClearLayer(int layer);

        /**
         * Release single particles
         * If there are any singleparticles (see #SetSingleParticle) this will release all of them and allow them to age and die.
         */
        void ReleaseSingleParticles();

        /**
         * Pause and unpause the particle manager
         * Pauses the drawing and updating of all effects within the particle manager.
         */
        void TogglePause();

        /**
         * Interpolate between 2 values
         * This is the function used to achieve render tweening by taking the old and new values and interpolating between the 2
         */
        float TweenValues(float oldValue, float value, float tween);

        float GetCurrentTime() const;

        bool IsSpawningAllowed() const;

    protected:
        std::vector<std::vector<std::set<Particle*> > > _inUse;
        std::stack<Particle*>                _unused;
        int                                  _inUseCount;                           // the Particle doesn't have to be managed by ParticleManager (seed GrabParticle)

        std::vector<std::set<Effect*> >      _effects;

        float                                _originX, _originY, _originZ;
        float                                _oldOriginX, _oldOriginY, _oldOriginZ;

        float                                _angle;
        float                                _oldAngle;

        Matrix2                              _matrix;
        Vector2                              _rotVec;

        float                                _vpW, _vpH, _vpX, _vpY;
        float                                _centerX, _centerY;

        float                                _tv, _tx, _ty, _tz, _px, _py;
        float                                _angleTweened;

        float                                _globalAmountScale;

        float                                _camtx, _camty, _camtz;

        bool                                 _spawningAllowed;
        int                                  _testCount;

        bool                                 _paused;

        float                                _currentTime;
        int                                  _currentTick;
        int                                  _idleTimeLimit;         // The time in game ticks before idle effects are automatically deleted

        int                                  _renderCount;
        float                                _currentTween;

        int                                  _effectLayers;

        // internal methods
        void DrawEffects();
        void DrawEffect(Effect *effect);
        void DrawParticle(Particle *particle);

        virtual void DrawSprite(AnimImage* sprite, float px, float py, float frame, float x, float y, float rotation,
            float scaleX, float scaleY, unsigned char r, unsigned char g, unsigned char b, float a, bool additive) = 0;
    };

} // namespace TLFX

#endif // _TLFX_PARTICLEMANAGER_H

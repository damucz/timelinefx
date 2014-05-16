/**
 * Effect type - extension of tlEntity
 *
 * <p>Effect types are the main containers for emitters and has a set of global attributes that can effect any emitters it stores.</p>
 * <p>The basic entity structure of an effect is: Effect -> Emitter(s) -> Particle(s)</p>
 * Both Effect types and Emitter types have a set of attributes that control how the Particles behave over the duration of the effect and over the duration of
 * the particles lifetime. Most of the effects' attributes scale the equivalent attribute of the emitters to enable a more global control of the emitters 
 * within the effect.</p>
 * <p>The value of these attributes is then looked up over the course of the effect using methods that interpolate between values - the equivalent to looking them up on 
 * a graph. There are 2 ways of doing this: either by interpolating in realtime, or by pre-compiling into lookup tables stored in arrays for faster performance.
 * There is very little difference in accuracy between the two.</p>
 * <p>To do this the EmitterArray is used which stores the value of each attribute overtime for each frame. A frame can be whatever length of time in millisecs
 * you set it to, eg. 30 millisecs. Because there are 2 types of attribute - base attributes and overtime - you can can change the resolution of each one separately. It's
 * more necessary to have a higher resolution for overtime attributes as it becomes much more noticeable. The default resolution for overtime attributes is 1 millisec - the 
 * most precise resolution possible.
 * <p>To adjust the resolution of the lookup tables you can call #SetLookupFrequency which affects the base attributes resolution and 
 * #SetLookupFrequencyOverTime to adjust the overtime attributes.</p>
 * <p>The following table shows each method used to either interpolate in realtime, or compile and lookup the values in an array plus the method used
 * to actually add an attribute value. Click on the add methods for a more detailed description of what that attribute actually does.</p>
 * <table>
 * <tr><th>Interpolation Methods</th><th>Equivalent Compiler Methods</th><th>Lookup Table Methods</th><th>Add Methods</th></tr>
 * <tr><td>InterpolateAmount</td><td>CompileAmount</td><td>GetLife</td><td> #AddLife</td></tr>
 * <tr><td>InterpolateLife</td><td>CompileLife</td><td>GetAmount</td><td> #AddAmount</td></tr>
 * <tr><td>InterpolateSizeX</td><td>CompileSizeX</td><td>GetSizeX</td><td> #AddSizeX</td></tr>
 * <tr><td>InterpolateSizeY</td><td>CompileSizeY</td><td>GetSizeY</td><td> #AddSizeY</td></tr>
 * <tr><td>InterpolateVelocity</td><td>CompileVelocity</td><td>GetVelocity</td><td> #AddVelocity</td></tr>
 * <tr><td>InterpolateWeight</td><td>CompileWeight</td><td>GetWeight</td><td> #AddWeight</td></tr>
 * <tr><td>InterpolateSpin</td><td>CompileSpin</td><td>GetSpin</td><td> #AddSpin</td></tr>
 * <tr><td>InterpolateAlpha</td><td>CompileAlpha</td><td>GetAlpha</td><td> #AddAlpha</td></tr>
 * <tr><td>InterpolateEmissionAngle</td><td>CompileEmissionAngle</td><td>GetEmissionAngle</td><td> #AddEmissionAngle</td></tr>
 * <tr><td>InterpolateEmissionRange</td><td>CompileEmissionRange</td><td>GetEmissionRange</td><td> #AddEmissionRange</td></tr>
 * <tr><td>InterpolateWidth</td><td>CompileWidth</td><td>GetWidth</td><td> #AddWidth</td></tr>
 * <tr><td>InterpolateHeight</td><td>CompileHeight</td><td>GetHeight</td><td> #AddHeight</td></tr>
 * <tr><td>InterpolateAngle</td><td>CompileAngle</td><td>GetAngle</td><td> #AddAngle</td></tr>
 * </table>
 * <p>Generally most of the values returned by these values are stored temporarily in the following variables for quicker access rather then having to
 * look them up again that frame:</p>
 * <table><tr><th>Variable name</th></tr>
 * <tr><td>currentAmount</td></tr>
 * <tr><td>currentLife</td></tr>
 * <tr><td>currentSizeX</td></tr>
 * <tr><td>currentSizeY</td></tr>
 * <tr><td>currentVelocity</td></tr>
 * <tr><td>currentWeight</td></tr>
 * <tr><td>currentSpin</td></tr>
 * <tr><td>currentAlpha</td></tr>
 * <tr><td>currentEmissionAngle</td></tr>
 * <tr><td>currentEmissionRange</td></tr>
 * <tr><td>currentWidth</td></tr>
 * <tr><td>currentHeight</td></tr>
 * </table>
 * <p>To precompile all attributes in the effect and any emitters and sub effects then you can call #CompileAll</p>
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef _TLFX_EFFECT_H
#define _TLFX_EFFECT_H

#include "TLFXEntity.h"
#include "TLFXAttributeNode.h"
#include "TLFXEmitterArray.h"

#include <string>
#include <map>
#include <vector>
#include <set>

namespace TLFX
{
    class Emitter;
    class Particle;
    class ParticleManager;
    class Shape;

    class Effect : public Entity
    {
        typedef Entity base;
    public:

        enum Type
        {
            TypePoint,
            TypeArea,
            TypeLine,
            TypeEllipse,
        };

        enum Emission
        {
            EmInwards,
            EmOutwards,
            EmSpecified,
            EmInAndOut,
        };

        enum End
        {
            EndKill,
            EndLoopAround,
            EndLetFree,
        };

        Effect();

        /**
         * Makes a copy of the effect passed to it
         * @return A new clone of the effect entire, including all emitters and sub effects.
         */
        Effect(const Effect& other, ParticleManager* particleManager, bool copyDirectory = false);

        ~Effect();

        void New();

        /**
         * Sort all attribute lists
         * Sorts all the graph nodes into the proper order for every effect attribute
         */
        void SortAll();

        /**
         * Show all Emitters
         * Sets all emitters to visible so that they will be rendered. This also applies to any sub effects and their emitters.
         */
        void ShowAll();

        /**
         * Hide all Emitters
         * Sets all emitters to hidden so that they will no longer be rendered. This also applies to any sub effects and their emitters.
         */
        void HideAll();

        /**
         * Show one Emitter
         * Sets the emitter passed to the method to visible so that it will be rendered, all the other emitters are made invisible.
         */
        void ShowOne(Emitter *emitter);

        /**
         * Get count of emitters within this effect
         * Use this to find out how many emitters the effect has
         * @return Number of emitters
         */
        int EmitterCount() const;

        /**
         * Assign Particle Manager
         * Sets the Particle Manager that this effect is managed by. See #_particleManager
         */
        void SetParticleManager(ParticleManager *particleManager);
        ParticleManager* GetParticleManager() const;

        /**
         * Assigns a shape to each emitter
         * <p>Recursively goes through each emitter within this effect and any sub effects and assigns a shape to each emitter.</p>
         * <p>The list passed to the method should contain the list of shapes, which will then be searched using the name stored in emitter.image.name and assigned if one is found, 
         * Otherwise null is assign to the shape. Generally used only when the effects library is loaded.</p>
         */
        void AssignShapes(const std::vector<Shape>& shapes);

        /**
         * Add an amount attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This scales the number of particles that are spawned per second for all particles within the effect.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddAmount(float f, float v);

        /**
         * Add a life attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p> This scales each particle's lifetime attribute within the effect thus affecting how Long the particles last for. Note that this attribute only effects 
         * the lifetime as they are spawned and will not extend or reduce the lifetime of particles already in existence.</P>
         * @return Emitter change object.
         */
        AttributeNode* AddLife(float f, float v);

        /**
         * Add a size x attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This scales each particle's width attribute within the effect thus controlling the overall width of the particle. </p>
         * <p>If <i>_lockAspect</i> is set to true then this attribute is used to control the particles height as well so it scales uniformly</p>
         * @return Emitter change object.
         */
        AttributeNode* AddSizeX(float f, float v);

        /**
         * Add a size y attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This scales each particle's height attribute within the effect thus controlling the overall height of the particle. </p>
         * <p>if <i>_lockAspect</i> is set to true then this attribute will not have any effect.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddSizeY(float f, float v);

        /**
         * Add a velocity attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This scales each particle's basespeed attribute within the effect thus controlling fast the particle can travel. 
         * Note that this attribute only effects the base speed of the particle therefore only effecting newly spawned particles. 
         * It does not effect the particles over their lifetime.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddVelocity(float f, float v);

        /**
         * Add a weight attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This scales each particle's baseweigth attribute within the effect thus controlling how much the particle is effected by gravity. 
         * Note that this attribute only effects the base weight of the particle therefore only effecting newly spawned particles. 
         * It does not effect the particles over their lifetime.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddWeight(float f, float v);

        /**
         * Add a spin attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>Global spin scales each particle's spin attribute within the effect thus controlling how fast the particle spins. 
         * Note that this attribute will instantly effect all particles within the effect.</p>
         * @returnsEmitter change object.
         */
        AttributeNode* AddSpin(float f, float v);

        /**
         * Add an alpha attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>Alpha effects the visibility of all particles within the effect. Global alpha is a scaling factor, so a value of 1 will not effect 
         * any of the individual alpha values of particles. A global alpha value of 0.5 will half the value of all particle alpha values. 
         * For example if global alpha is 0.5 and a particles alpha is 1 then the particles alpha wil be reduced to 0.5 (0.5*1=0.5). 
         * Note that this attribute will instantly effect all particles within the effect.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddAlpha(float f, float v);

        /**
         * Add an emission angle attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>Emission angle determines the direction particles will travel initially when they spawn.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddEmissionAngle(float f, float v);

        /**
         * Add an emission range attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This specifies the range of direction that particles will spawn and travel. Each degree on the graph represents both sides of 
         * the emission angle. So for example if you set it to 10 degrees that means 10 degrees to the left and 10 degrees to the right of 
         * the emission angle equally a total arc of 20 degrees. So setting an emission range of 180 degrees will mean particles travel 360 
         * degrees randomly around the emission angle.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddEmissionRange(float f, float v);

        /**
         * Add a width attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>If the effect is of an area or ellipse type this controls the width. If the effect is a line then this controls the line length. 
         * New particles that are created will only spawn within the area defined here.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddWidth(float f, float v);

        /**
         * Add a height attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p><p>If the effect is of an area or ellipse type this controls the height. If the effect is a line then this control is not used. 
         * New particles that are created will only spawn within the area defined here.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddHeight(float f, float v);

        /**
         * Add an angle attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>Controls the angle of the effect over the life time of the effect. Particles that are set to Relative will rotate according to the effect, 
         * otherwise they will only take into account the effect angle when they spawn.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddAngle(float f, float v);

        /**
         * Add a stretch attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This will scale the stretch overtime attribute of all particles within the effect.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddStretch(float f, float v);

        /**
         * Add a globalz attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This will affect the overall scale of the effect, effectively zooming into or out of the effect</p>
         * @return Emitter change object.
         */
        AttributeNode* AddGlobalZ(float f, float v);

        /**
         * Set the class of the Effect
         * <p>Sets the effect to one of 4 types - point, area, ellipse and line. To set one of these use one of the 4 corresponding consts:
         * TypePoint, TypeArea, TypeLine, TypeEllipse
         */
        void SetClass(Type type);
        void SetClass(int type);

        /**
         * Sets lockaspect
         * <p>Set to true to make the size of particles scale uniformly</p>
         */
        void SetLockAspect(bool value);

        /**
         * Sets effect's path
         */
        void SetPath(const char *path);

        /**
         * Set maximum width grid points
         * In area and ellipse effects this value represents the number of grid points along the width, in the case of area and line effect, or around the 
         * circumference, in the case of ellipses.
         */
        void SetMGX(int value);

        /**
         * Set maximum height grid points
         * In area effects this value represents the number of grid points along the height, it has no relevence for other effect types.
         */
        void SetMGY(int value);

        /**
         * Sets whether the effect should emit at points
         * If set to true then the particles within the effect will emit from evenly spaced points with the area, line or ellipse. The number of points is determined
         * by <i>mgx</i> and <i>mgy</i>. The value is not applicable to point effects.
         */
        void SetEmitAtPoints(bool value);

        /**
         * Set the emission type
         * <p>In area, line and ellipse effects the emission type determines the direction that the particles travel once spawned. Use the following consts to determine
         * the direction:</p>
         * <p><b>EmInwards: </b>Particles will emit towards the handle of the effect.<br/>
         * <b>EmOutwards: </b>Particles will emit away from the handle of the effect.<br/>
         * <b>EmSpecified: </b>Particles will emit in the direction specified by the <i>emission_angle</i> and <i>emission_range</i> attributes.<br/>
         * <b>EmInAndOut: </b>Particles will alternative between emitting towards and away from the handle of the effect.</p>
         */
        void SetEmissionType(Emission type);
        void SetEmissionType(int type);

        /**
         * Set the length of the effect
         * Effects can be looped by setting the effect length. Just pass it the length in milliseconds that you want it to loop by or set to 0 if 
         * you don't want the effect to loop.
         */
        void SetEffectLength(int length);

        /**
         * Set the parent emitter
         * Effects can be sub effects within effects. To do this emitters can store a list of effects that they attach to particles they spawn. This sets the emitter
         * that the effect is parented to.
         */
        void SetParentEmitter(Emitter* emitter);

        /**
         * Sets the number of frames
         * Currently only relevant to the Timeline Particles editor
         */
        void SetFrames(int frames);

        /**
         * Sets the anim width
         * Currently only relevant to the Timeline Particles editor
         */
        void SetAnimWidth(int width);

        /**
         * Sets the anim height
         * Currently only relevant to the Timeline Particles editor
         */
        void SetAnimHeight(int height);

        /**
         * Sets the whether the animation loops seamlessly
         * Currently only relevant to the Timeline Particles editor
         */
        void SetLooped(bool looped);

        /**
         * Sets the x offset
         * Currently only relevant to the Timeline Particles editor
         */
        void SetAnimX(int x);

        /**
         * Sets the y offset
         * Currently only relevant to the Timeline Particles editor
         */
        void SetAnimY(int y);

        /**
         * Sets the random seed for the effect animation
         * Currently only relevant to the Timeline Particles editor
         */
        void SetSeed(int seed);

        /**
         * Sets the zoom of the animation
         * Currently only relevant to the Timeline Particles editor
         */
        void SetZoom(float zoom);

        /**
         * Sets the frame offset of the animation
         * Currently only relevant to the Timeline Particles editor
         */
        void SetFrameOffset(int offset);

        /**
         * Set to true for particles to traverse line type effects
         * Only applying to line effects, setting this to true makes the particles travel along the length of the line always remaining relative to it.
         */
        void SetTraverseEdge(bool edge);

        /**
         * Set the end behavior of particles traversing a line
         * <p>If an effect if set so that particles traverse the edge of the line, then this makes the particles behave in one of 3 ways when they reach 
         * the end of the line.  By passing it either of the following const they can:</p>
         * <p><b>tlEND_LOOPAROUND</b>: The particles will loop back round to the beginning of the line.<br/>
         * <b>tlEND_KILL</b>: The particles will be killed even if they haven't reached the end of their lifetimes yet.<br/>
         * <b>tlLET_FREE</b>: The particles will be free to continue on their merry way.</p>
         */
        void SetEndBehavior(End behavior);
        void SetEndBehavior(int behavior);

        /**
         * Set to true to make the distance traveled determined by the life of the particle.
         * When <i>_traverseEdge</i> is set to true and <i>_endBehavior</i> is set to true then the distance traveled along the line will be determined by the 
         * age of the particle.
         */
        void SetDistanceSetByLife(bool value);

        /**
         * Sets to true to center the handle of the effect
         * If set to true then then position of the handle is automatically set to to the center of the effect.
         */
        void SetHandleCenter(bool center);

        /**
         * Set the order particles spawn
         * A value of true means that in area, line and ellipse effects, particles will spawn from right to left or anti-clockwise.
         */
        void SetReverseSpawn(bool reverse);

        /**
         * This sets the direction particles are spawned.
         * theres no need to call this, as its called internally by the emitter depending on the reverse spawn flag. see #SetReverseSpawn.
         */
        void SetSpawnDirection();

        /**
         * Set the area size of the effect
         * For area and ellipse effects, use this function to override the graph and set the width and height of the area to whatever you want.
         */
        void SetAreaSize(float width, float height);

        /**
         * Set the line length of the effect
         * For line effects, use this function to override the graph and set the length of the line to whatever you want.
         **/
        void SetLineLength(float length);

        /**
         * Set the Emission Angle of the effect
         * This overrides whatever angle is set on the graph and sets the emission angle of the effect. This won't effect emitters that have <i>UseEffectEmission</i> set
         * to FALSE.
         */
        void SetEmissionAngle(float angle);

        /**
         * Set the Angle of the effect
         * This overrides the whatever angle is set on the graph and sets the angle of the effect.
         */
        void SetEffectAngle(float angle);

        /**
         * Set the Global attribute Life of the effect
         * This overrides the graph the effect uses to set the Global Attribute _life
         */
        void SetLife(float life);

        /**
         * Set the Global attribute Amount of the effect
         * This overrides the graph the effect uses to set the Global Attribute _amount
         */
        void SetAmount(float amount);

        /**
         * Set the Global attribute velocity of the effect
         * This overrides the graph the effect uses to set the Global Attribute _velocity
         */
        void SetVelocity(float velocity);

        /**
         * Set the Global attribute Spin of the effect
         * This overrides the graph the effect uses to set the Global Attribute _spin
         */
        void SetSpin(float spin);

        /**
         * Set the Global attribute Weight of the effect
         * This overrides the graph the effect uses to set the Global Attribute _weight
         */
        void SetWeight(float weight);

        /**
         * Set the Global attribute _sizeX of the effect
         * This overrides the graph the effect uses to set the Global Attribute _sizeX and _sizeY
         */
        void SetEffectParticleSize(float sizeX, float sizeY);

        /**
         * Set the Global attribute _sizeX of the effect
         * This overrides the graph the effect uses to set the Global Attribute _sizeX
         */
        void SetSizeX(float sizeX);

        /**
         * Set the Global attribute _sizeY of the effect
         * This overrides the graph the effect uses to set the Global Attribute _sizeY
         */
        void SetSizeY(float sizeY);

        /**
         * Set the Global attribute _alpha of the effect
         * This overrides the graph the effect uses to set the Global Attribute _alpha
         */
        void SetEffectAlpha(float alpha);

        /**
         * Set the Global attribute _eEmissionRange of the effect
         * This overrides the graph the effect uses to set the Global Attribute _emissionRange
         */
        void SetEffectEmissionRange(float emissionRange);

        /**
         * Set range in degrees of the arc
         * When an effect uses an ellipse as its effect type, you can adjust how far round the ellipse particles will spawn
         * by setting the ellipse arc. 360 degrees will spawn around the full amount.
         */
        void SetEllipseArc(float degrees);

        /**
         * Set the current zoom level of the effect
         * This overrides the graph the effect uses to set the Global Attribute Global _zoom
         */
        void SetZ(float z);

        /**
         * Set the Global attribute _stretch of the effect
         * This overrides the graph the effect uses to set the Global Attribute Stretch
         */
        void SetStretch(float stretch);

        /**
         * Sets the current state of whether spawned particles are added to the particle managers pool, or the emitters own pool. True means that
         * they're grouped together under each emitter. This will change all emitters with the effect, and is recommended you use this rather then individually
         * for each emitter.
         */
        void SetGroupParticles(bool v);

        /**
         * Get class
         * @return The current class of the effect - TypePoint, TypeArea, TypeLine, TypeEllipse
         */
        Type GetClass() const;

        /**
         * Returns the <i>_lockAspect</i> 
         * @return Either TRUE or FALSE
         */
        bool GetLockAspect() const;

        /**
         * Get the path of the entity
         * the path will be the address of where the entity is within the hierarchy of parent and child entities
         */
        const char *GetPath() const;

        /**
         * Get the current maximum grid points along the width
         */
        int GetMGX() const;

        /**
         * Get the current maximum grid points along the height
         */
        int GetMGY() const;

        /**
         * Get whether the effect is currently set to emit at points
         * @return Either TRUE or FALS
         */
        bool GetEmitAtPoints() const;

        /**
         * Get the current emission type
         * @return The current emission type: EmInwards, EmOutwards, EmSpecified, EmInAndOut
         */
        Emission GetEmissionType() const;

        /**
         * Get the effect length
         * return Length in millisecs
         */
        int GetEffectLength() const;

        /**
         * Get the parent emitter of the effect
         */
        Emitter* GetParentEmitter() const;

        /**
         * Get the parent entity of the effect
         */
        Entity* GetParent() const;

        /**
         * Get the number of frames in the animation
         */
        int GetFrames() const;

        /**
         * Get the width of the animation
         */
        int GetAnimWidth() const;

        /**
         * Get the height of the animation
         */
        int GetAnimHeight() const;

        /**
         * Get whether the animation is looped or not
         * @return either TRUE or FALSE
         */
        bool GetLooped() const;

        /**
         * Get the x offset of the effect in the animation
         */
        int GetAnimX() const;

        /**
         * Get the y offset of the effect in the animation
         */
        int GetAnimY() const;

        /**
         * Get the current random seed value of the animation
         */
        int GetSeed() const;

        /**
         * Get the current zoom factor of the animation
         */
        float GetZoom() const;

        /**
         * Get the frame offset of the animation
         */
        int GetFrameOffset() const;

        /**
         * Get whether particles should traverse the line (if it's a line effect)
         * @return Either TRUE or FALSE
         */
        bool GetTraverseEdge() const;

        /**
         * Gets the end behavior for when particles reach the end of the line
         * @return Either EndKill, EndLoopAround, EndLetFree,
         */
        End GetEndBehavior() const;

        /**
         * Gets whether the distance along the traversed line is determined by the particle age
         * @return Either TRUE or FALSE
         */
        bool GetDistanceSetByLife() const;

        /**
         * Get whether the effect's handle is automatically set to center
         * @return Either TRUE or FALSE
         */
        bool GetHandleCenter() const;

        /**
         * Gets whether the particles should spawn in the opposite direction
         * @return Either TRUE or FALSE
         */
        bool GetReverseSpawn() const;

        /**
         * Gets the current number of particles spawned by this effects' emitters including any sub effects
         */
        int GetParticleCount() const;

        /**
         * get the range in degrees of the arc
         * see #SetEllipseArc
         */
        float GetEllipseArc() const;
        int GetEllipseOffset() const;

        bool HasParticles() const;

        /**
         * Add a new effect to the directory including any sub effects and emitters. Effects are stored using a map and can be retrieved using #GetEffect.
         */
        void AddEffect(Effect* effect);

        /**
         * Add a new emitter to the directory. Emitters are stored using a map and can be retrieved using #GetEmitter. Generally you don't want to call this at all, 
         * just use #AddEffect and all its emitters will be added also.
         */
        void AddEmitter(Emitter* emitter);

        /**
         * Retrieve an effect from the directory of the effect
         * <p>Use this to get an effect from the effect directory by passing the name of the effect you want. Example:</p>
         * &{Effect* explosion = myEffectsLibrary->Geteffect("explosion")}
         * <p>All effects and emitters are stored using a directory like path structure so to get at sub effects you can do:</p>
         * &{Effect* explosion = myEffectsLibrary->Geteffect("Effect/Emitter/Sub Effect/Another Emitter/A deeper sub effect")}
         * <p>Note that you should always use forward slashes.</p>
         * @return Effect*
         */
        Effect* GetEffect(const char *name) const;

        /**
         * Retrieve an emitter from the of the effect
         * < p > Use this To get an emitter from the effect directory by passing the name of the emitter you want. All effects And emitters are
         * stored using a map with a directory like path structure. So retrieving an emitter called blast wave inside an effect called explosion
         * would be done like so:</p>
         * &{Emitter* blastwave = myEffectsLibrary->GetEmitter("explosion/blast wave")}
         * <p>Note that you should always use forward slashes.</p>
         * @return Emitter*
         */
        Emitter* GetEmitter(const char *name) const;

        /**
         * Stop the effect from timing out and be automatically removed
         * By default, if the effect has no particles, it will timeout and destroy itself after a certain amount of time as dictated by
         * the particle manager it belongs to. Call this method to stop the process from happening. Bear in mind that if you do this
         * you will have to destroy the effect yourself, either by calling Destroy, Hardkill or Softkill. This method propagates to all subeffects
         * as well. For best results this method should be called when the effect is created before it starts spawning particles.
         */
        void DoNotTimeout(bool value = true);

        /**
         * Updates the effect
         * Call this once every frame to update the effect. Updating effects is handled by the Particle Manager unless you want to manage things on your own.
         */
        virtual bool Update();

        /**
         * Softly kill an effect
         * Call this to kill an effect by stopping it from spawning any more particles. This will make the effect slowly die about as any remaining 
         * particles cease to exist. Any single particles are converted to one shot particles.
         */
        void SoftKill();

        /**
         * Hard kill an effect
         * Immediately kills an effect by destroying all particles created by it.
         */
        void HardKill();

        virtual void Destroy(bool releaseChildren = true);

        // Compilers

        // Pre-Compile all attributes.
        // In order to use look-up arrays to access attribute values over the course of the effects life you need to compile all of the attribute values
        // into an array. This method will compile all of them together in one go including all of it children emiters and any sub effects and so on.
        void CompileAll();
        void CompileQuick();

        void CompileAmount();
        void CompileLife();
        void CompileSizeX();
        void CompileSizeY();
        void CompileVelocity();
        void CompileWeight();
        void CompileSpin();
        void CompileAlpha();
        void CompileEmissionAngle();
        void CompileEmissionRange();
        void CompileWidth();
        void CompileHeight();
        void CompileAngle();
        void CompileStretch();
        void CompileGlobalZ();

        // Lookups
        float GetLife(float frame) const;
        float GetAmount(float frame) const;
        float GetSizeX(float frame) const;
        float GetSizeY(float frame) const;
        float GetVelocity(float frame) const;
        float GetWeight(float frame) const;
        float GetSpin(float frame) const;
        float GetAlpha(float frame) const;
        float GetEmissionAngle(float frame) const;
        float GetEmissionRange(float frame) const;
        float GetWidth(float frame) const;
        float GetHeight(float frame) const;
        float GetEffectAngle(float frame) const;
        float GetStretch(float frame) const;
        float GetGlobalZ(float frame) const;

        float GetCurrentAmount() const;
        float GetCurrentLife() const;
        float GetCurrentEmissionAngle() const;
        float GetCurrentEmissionRange() const;
        int GetSpawnDirection() const;
        float GetCurrentWidth() const;
        float GetCurrentHeight() const;
        float GetCurrentVelocity() const;
        float GetCurrentSizeX() const;
        float GetCurrentSizeY() const;
        float GetCurrentWeight() const;
        float GetCurrentAlpha() const;
        float GetCurrentSpin() const;
        float GetCurrentStretch() const;

        unsigned int GetLifeLastFrame() const;
        float GetLifeMaxValue() const;

        bool IsBypassWeight() const;

        void SetParticlesCreated(bool value);

        void ChangeDoB(float dob);

        /**
         * Set the particle to be managed by Effect instead of ParticleManager (see ParticleManager::GrabParticle)
         */
        void AddInUse(int layer, Particle *p);
        void RemoveInUse(int layer, Particle *p);

        void SetEffectLayer(int layer);
        int GetEffectLayer() const;

        void SetCurrentEffectFrame(float frame);
        float GetCurrentEffectFrame() const;

        const std::set<Particle*>& GetParticles(int layer) const;

        bool IsDying() const;

    protected:
        std::map<std::string, Effect*> _directoryEffects;       /// The directory of all the effect's sub effects and emitters.
        std::map<std::string, Emitter*> _directoryEmitters;     /// The directory of all the effect's emitters.
        Type                           _class;                  /// The type of effect - point, area, line or ellipse
        float                          _currentEffectFrame;     /// the current frame, each frame lasts x amount of millisecs according to the global tp_UPDATE_FREQUENCY
        bool                           _handleCenter;           /// Whether the handle of the effect is automatically at the center
        std::string                    _path;                   /// the path to the effect for where in the effect hierarchy the effect is
        Entity*                        _source;
        bool                           _lockAspect;             /// Set to true if the effect should scale uniformly
        bool                           _particlesCreated;       /// Set to true if the effect's emitters have created any particles
        int                            _suspendTime;
        float                          _gx;                     /// Grid x coords for emitting at points
        float                          _gy;                     /// Grid y coords for emitting at points
        int                            _mgx;                    /// The maximum value of gx
        int                            _mgy;                    /// The maximum value of gy
        bool                           _emitAtPoints;           /// True to set the effect to emit at points
        Emission                       _emissionType;           /// Set to either inwards, outwards or specified according to emission angle
        int                            _effectLength;           /// How long the effect lasts before looping back round to the beginning
        Emitter*                       _parentEmitter;          /// If the effect is a sub effect then this is set to the emitter that it's a sub effect of
        float                          _spawnAge;               /// length of time (millisecs) the effect has been spawning for
        int                            _index;
        int                            _particleCount;          /// Number of particles this effect has active
        int                            _idleTime;               /// Length of time the effect has been idle for without any particles
        bool                           _traverseEdge;           /// Whether the particles within this effect should traverse the edge of the line (line effects only)
        End                            _endBehavior;            /// Set to whatever the particles should do when they reach the end of the line
        bool                           _distanceSetByLife;      /// True if the distance traveled along the line is set according to the age of the particles traversing it
        bool                           _reverseSpawn;           /// True if the particles should spawn from right to left or anti clockwise (n/a for point effects)
        int                            _spawnDirection;         /// set to 1 or -1 if reverse spawn is true or false
        bool                           _dying;                  /// Set to true if the effect is in the process of dying, ie no long producing particles.
        bool                           _allowSpawning;          /// Set to false to disable emitters from spawning any new particles
        float                          _ellipseArc;             /// With ellipse effects this sets the degrees of which particles emit around the edge
        int                            _ellipseOffset;          /// This is the offset needed to make arc center at the top of the circle.
        std::vector<std::set<Particle*> > _inUse;               /// This stores particles created by the effect, for drawing purposes only.
        int                            _effectLayer;            /// The layer that the effect resides on in its particle manager
        bool                           _doesNotTimeout;         /// Whether the effect never timeouts automatically

        ParticleManager*               _particleManager;        /// The particle manager that this effect belongs to

        // Animation Properties
        int                            _frames;                 /// Number number of frames the animation has
        int                            _animWidth;              /// Width of the animation
        int                            _animHeight;             /// Height of the animation
        bool                           _looped;                 /// True if the animation should loop
        int                            _animX;                  /// the x offset from the center of the animation
        int                            _animY;                  /// the y offset from the center of the animation
        int                            _seed;                   /// the number used for the random number generator
        float                          _zoom;                   /// level of zoom of the animation
        int                            _frameOffset;            /// Starting frame offset

        // ----Global Settings, Graph attributes----
        EmitterArray*                  _cLife;
        EmitterArray*                  _cAmount;
        EmitterArray*                  _cSizeX;
        EmitterArray*                  _cSizeY;
        EmitterArray*                  _cVelocity;
        EmitterArray*                  _cWeight;
        EmitterArray*                  _cSpin;
        EmitterArray*                  _cAlpha;
        EmitterArray*                  _cEmissionAngle;
        EmitterArray*                  _cEmissionRange;
        EmitterArray*                  _cWidth;
        EmitterArray*                  _cHeight;
        EmitterArray*                  _cEffectAngle;
        EmitterArray*                  _cStretch;
        EmitterArray*                  _cGlobalZ;
        bool                           _arrayOwner;             // only the effects/emitters in EffectsLibrary should be the owners, not the copies

        float                          _currentLife;
        float                          _currentAmount;
        float                          _currentSizeX;
        float                          _currentSizeY;
        float                          _currentVelocity;
        float                          _currentSpin;
        float                          _currentWeight;
        float                          _currentWidth;
        float                          _currentHeight;
        float                          _currentAlpha;
        float                          _currentEmissionAngle;
        float                          _currentEmissionRange;
        float                          _currentStretch;
        float                          _currentGlobalZ;

        bool                           _overrideSize;
        bool                           _overrideEmissionAngle;
        bool                           _overrideEmissionRange;
        bool                           _overrideAngle;
        bool                           _overrideLife;
        bool                           _overrideAmount;
        bool                           _overrideVelocity;
        bool                           _overrideSpin;
        bool                           _overrideSizeX;
        bool                           _overrideSizeY;
        bool                           _overrideWeight;
        bool                           _overrideAlpha;
        bool                           _overrideStretch;
        bool                           _overrideGlobalZ;

        bool                           _bypassWeight;
    };

} // namespace TLFX

#endif // _TLFX_EFFECT_H

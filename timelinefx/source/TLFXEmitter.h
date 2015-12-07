/**
 * Emitter Type - Extension of Entity
 * <p>An emitter type is an entity whose sole purpose is to spawn particles. Like the effect type it too has number of attributes that can tell the particles
 * that it spawns how to move, orientate and scale themselves on screen to create the effects.</p>
 * <p>The attributes an emitter has can be put into a few different categories:</p>
 * <h4>Base Attributes</h4>
 * <p>Base attributes set the base level that life overtime values will scale to. 	The x axis of the graph represents the time in seconds the the 
 * effect has been running for. So for example you may set the velocity to 200 for at the start of the effect then have it slowly reduce to 0 over 5 
 * seconds of the effect running.</p>
 * <h3>Life</h3>
 * <p>This attribute determines how long the particle will live before before ceasing to exist. You can plot points on the graph so that the life of 
 * particles will vary over the lifetime of the effect.</p>
 * <h3>Amount</h3>
 * <p>This controls how many particles per second that the emitter will spawn at that point in time of the effect running.</p>
 * <h3>Size</h3>
 * <p>Size controls the base level that the size over-life attributes scale to. By right clicking the particle attributes list you can toggle 
 * "Uniform Size" which will enable the size attribute to split into width and height attributes so that these can be changed independantly of each other.</p>
 * <h3>Velocity</h3>
 * <p>This controls the base speed of the particles being spawned that the velocity over-life attributes scale to.</p>
 * <h3>Spin</h3>
 * <p>Spin controls the base speed with which particles rotate in either direction and determines what the spin over-life scales too.</p>
 * <h3>Weight</h3>
 * <p>This controls the base weight of the particle that the weight over-life attribute is scaled to.</p>
 * <H4>Variation Attributes</H4>
 * <p>Variation attributes represent random values that are added to the base values in order to add some variation and unpredicatability to the particles 
 * behavior.</p>
 * <h3>Life Variation</h3>
 * <p>This will add a random amount of seconds onto the base attribute of life so that particles that spawn will vary in the amount of time they stay alive.</p>
 * <h3>Amount Variation</h3>
 * <p>This will apply variation to the base amount attribute so that the amount of particles spawned over the effect's life time will vary.</p>
 * <h3>Size Variation</h3>
 * <p>Applies a random value onto the base size so the particles spawned will vary in size.</p>
 * <h3>Velocity Variation</h3>
 * <p>This will vary the base velocity of the particle based by the amount you plot on the graph so that particles will spawn and move with varying speeds.</p>
 * <h3>Spin Variation</h3>
 * <p>This will vary the speed at which the particles spawned will rotate.</p>
 * <h3>Weight Variation</h3>
 * <p>Applies a random amount of weight onto the base weight of the particles that are spawned.</p>
 * <h3>Motion Randomness</h3>
 * <p>Motion randomness does not vary any of the base values, but it does dictate to what degree the particle will move about in a random fashion. 
 * Motion randomness effects the speed and direction of the particle so the higher this value the more erratically the particles will move about.</p>
 * <H4>Overtime Attributes</H4>
 * <p>These attribute control how the particle behaves over the lifetime of the particle. The x axis of the graph represents the life time of the 
 * particle so you can control exactly how the particle behaves at each stage of its life. The y axis represents a percentage of the base value set in the 
 * Base Attributes and Variation Attributes. So if for example you have velocity set at 100 and the velocity overtime is set to 0.5 then the particle will 
 * therefore be traveling at half it's speed; 50 pixels per second.</p>
 * <h3>Alpha Overtime</h3>
 * <p>This doesn't actually scale any base attribute, it simply controls the alpha value of the particle, or how visible the particle is. Values should range
 * from 0 to 1.</p>
 * <h3>Size Overtime</h3>
 * <p>This enables you to control the size of the particle over its life time by scaling the base size attribute.</p>
 * <h3>Velocity Overtime</h3>
 * <p>This enables you to control how fast the the particle travels over its life time by scaling the base velocity attribute.</p>
 * <h3>Spin Overtime</h3>
 * <p>This controls the speed with which the particle spins by scaling the base spin attribute.</p>
 * <h3>Weight Overtime</h3>
 * <p>This controls the weight overtime of the particle by scaling the base weight attribute.</p>
 * <h3>Direction Overtime</h3>
 * <p>This dictates the direction that the particle travels in over its lifetime.</p>
 * <h3>Motion Randomness Overtime</h3>
 * <p>This scales the Motion Randomness attribute over the particles lifetime so you can finely tune how erratically the particle moves.</p>
 * <h3>Frame Rate</h3>
 * <p>If the particle is set to animate then you can use this attribute to control how fast is animates over the lifetime of the particle.</p>
 * <H4>Velocity Adjuster</H4>
 * <p>This attribute scales the speed of all particles currently in existence for a more global control</p>
 * <h3>Adding and retrieving attribute values</h3>
 * <p>This is all handled by the effect, emitter and particle update methods so theres not much need to worry about these methods 
 * but here is some info about how this is achieved.</p>
 * <p>To add a value to each of these attributes use the corresponding add method ie., #AddLife
 * <p>As in the effect type the values of attributes are looked up using interpolation or pre compiled in arrays. The following table lists all the interpolation
 * methods and their equivalent compiler methods, look-up methods and add methods for adding new attribute values.</p>
 * <table>
 * <tr><th>Interpolation Methods</th><th>Equivalent Compiler Methods</th><th>Lookup Table Methods</th><th>Add Methods</th></tr>
 * <tr><td>InterpolateAmount</td><td>CompileAmount</td><td>GetAmount</td><td> #AddAmount</td></tr>
 * <tr><td>InterpolateLife</td><td>CompileLife</td><td>GetLife</td><td> #AddLife</td></tr>
 * <tr><td>InterpolateSizeX</td><td>CompileSizeX</td><td>GetSizeX</td><td> #AddSizeX</td></tr>
 * <tr><td>InterpolateSizeY</td><td>CompileSizeY</td><td>GetSizeY</td><td> #AddSizeY</td></tr>
 * <tr><td>InterpolateBaseSpeed</td><td>CompileBaseSpeed</td><td>GetBaseSpeed</td><td> #AddBaseSpeed</td></tr>
 * <tr><td>InterpolateBaseWeight</td><td>CompileBaseWeight</td><td>GetBaseWeight</td><td> #AddBaseWeight</td></tr>
 * <tr><td>InterpolateBaseSpin</td><td>CompileBaseSpin</td><td>GetBaseSpin</td><td> #AddBaseSpin</td></tr>
 * <tr><td>InterpolateEmissionAngle</td><td>CompileEmissionAngle</td><td>GetEmissionAngle</td><td> #AddEmissionAngle</td></tr>
 * <tr><td>InterpolateEmissionRange</td><td>CompileEmissionRange</td><td>GetEmissionRange</td><td> #AddEmissionRange</td></tr>
 * <tr><td>InterpolateVelVariation</td><td>CompileVelVariation</td><td>GetVelVariation</td><td> #AddVelVariation</td></tr>
 * <tr><td>InterpolateWeightVariation</td><td>CompileWeightVariation</td><td>GetWeightVariation</td><td> #AddWeightVariation</td></tr>
 * <tr><td>InterpolateLifeVariation</td><td>CompileLifeVariation</td><td>GetLifeVariation</td><td> #AddLifeVariation</td></tr>
 * <tr><td>InterpolateAmountVariation</td><td>CompileAmountVariation</td><td>GetAmountVariation</td><td> #AddAmountVariation</td></tr>
 * <tr><td>InterpolateSizexVariation</td><td>CompileSizeXVariation</td><td>GetSizeXVariation</td><td> #AddSizeXVariation</td></tr>
 * <tr><td>InterpolateSizeyVariation</td><td>CompileSizeYVariation</td><td>GetSizeYVariation</td><td> #AddSizeYVariation</td></tr>
 * <tr><td>InterpolateSpinVariation</td><td>CompileSpinVariation</td><td>GetSpinVariation</td><td> #AddSpinVariation</td></tr>
 * <tr><td>InterpolateDirectionVariation</td><td>CompileDirectionVariation</td><td>GetDirectionVariation</td><td> #AddDirectionVariation</td></tr>
 * <tr><td>InterpolateAlpha</td><td>CompileAlpha</td><td>GetAlpha</td><td> #AddAlpha</td></tr>
 * <tr><td>InterpolateR</td><td>CompileR</td><td>GetR</td><td> #AddR</td></tr>
 * <tr><td>InterpolateG</td><td>CompileG</td><td>GetG</td><td> #AddG</td></tr>
 * <tr><td>InterpolateB</td><td>CompileB</td><td>GetB</td><td> #AddB</td></tr>
 * <tr><td>InterpolateScaleX</td><td>CompileScaleX</td><td>GetScaleX</td><td> #AddScaleX</td></tr>
 * <tr><td>InterpolateScaleY</td><td>CompileScaleY</td><td>GetScaleY</td><td> #AddScaleY</td></tr>
 * <tr><td>InterpolateSpin</td><td>CompileSpin</td><td>GetSpin</td><td> #AddSpin</td></tr>
 * <tr><td>InterpolateVelocity</td><td>CompileVelocity</td><td>GetVelocity</td><td> #AddVelocity</td></tr>
 * <tr><td>InterpolateWeight</td><td>CompileWeight</td><td>GetWeight</td><td> #AddWeight</td></tr>
 * <tr><td>InterpolateDirection</td><td>CompileDirection</td><td>GetDirection</td><td> #AddDirection</td></tr>
 * <tr><td>InterpolateDirectionVariationOT</td><td>CompileDirectionVariationOT</td><td>GetDirectionVariationOT</td><td> #AddDirectionVariationOT</td></tr>
 * <tr><td>InterpolateFramerate</td><td>CompileFramerate</td><td>GetFramerate</td><td> #AddFramerate</td></tr>
 * <tr><td>InterpolateGlobalVelocity</td><td>CompileGlobalVelocity</td><td>GetGlobalVelocity</td><td> #AddGlobalVelocity</td></tr>
 * </table>
 * <p>There are also a number of properties that control further how the particles look, how they're spawned and how they're drawn:</p>
 * <table><th>Property</th>
 * <tr><td> #SetImage</td></tr>
 * <tr><td> #SetFrame</td></tr>
 * <tr><td> #SetAngleOffset</td></tr>
 * <tr><td> #SetUniform</td></tr>
 * <tr><td> #SetSplatter</td></tr>
 * <tr><td> #SetAngleType</td></tr>
 * <tr><td> #SetUseEffectEmission</td></tr>
 * <tr><td> #SetSingleParticle</td></tr>
 * <tr><td> #SetRandomColor</td></tr>
 * <tr><td> #SetZLayer</td></tr>
 * <tr><td> #SetAnimate</td></tr>
 * <tr><td> #SetRandomStartFrame</td></tr>
 * <tr><td> #SetAnimationDirection</td></tr>
 * <tr><td> #SetColorRepeat</td></tr>
 * <tr><td> #SetAlphaRepeat</td></tr>
 * <tr><td> #SetOneShot</td></tr>
 * <tr><td> #SetHandleCenter</td></tr>
 * <tr><td> #SetParticlesRelative</td></tr>
 * <tr><td> #SetTweenSpawns</td></tr>
 * </table>
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef _TLFX_EMITTER_H
#define _TLFX_EMITTER_H

#include "TLFXEntity.h"
#include "TLFXAttributeNode.h"
#include "TLFXEmitterArray.h"

#include <list>
#include <vector>
#include <string>

namespace TLFX
{

    class Effect;
    class AnimImage;
    class EmitterArray;
    class Particle;
    class ParticleManager;

    class Emitter : public Entity
    {
        typedef Entity base;
    public:
        enum Angle
        {
            AngAlign,
            AngRandom,
            AngSpecify,
        };

        Emitter();

        /**
         * Makes a copy of the emitter passed to it
         * Generally you will want to copy an effect, which will in turn copy all emitters within it recursively
         * @return A new clone of the emitter
         */
        Emitter(const Emitter& other, ParticleManager *pm);

        ~Emitter();

        /**
         * Sort all attribute lists
         * Sorts all the graph nodes into the proper order for every emitter attribute
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
         * Add a scale x attribute node
         * <p>Pass the method a value between 0 and 1 representing the percentage of the lifetime of the particle (f) and the value (v)</p>
         * <p>This is an <b>Overtime Attribute</b>, meaning it is a scaling factor for the equivalent <b>Base Attribute</b> - in this case <i>_sizeX</i>. This enables you to control the width of the 
         * particle over its life time by scaling the _sizeX attribute. If uniform is set to true then this also controls the height of the particle as well</p>
         * <p>So for example, if you pass AddScaleX(0.5,2), this will tell the particle to be twice it's base width (_sizeX) halfway through its life.</p>
         * @return Emitter change object
         */
        AttributeNode* AddScaleX(float f, float v);

        /**
         * Add a scale y attribute node
         * <p>Pass the method a value between 0 and 1 representing the percentage of the lifetime of the particle (f) and the value (v)</p>
         * <p>This is an <b>Overtime Attribute</b>, meaning it is a scaling factor for the equivalent <b>Base Attribute</b> - in this case <i>_sizeY</i>. This enables you to control the width of the 
         * particle over its life time by scaling the _sizeY attribute. If uniform is set to true then this also controls the height of the particle as well</p>
         * <p>So for example, if you pass AddScaleY(0.5,2), this will tell the particle to be twice it's base width (_sizeY) halfway through its life.</p>
         * @return Emitter change object
         */
        AttributeNode* AddScaleY(float f, float v);

        /**
         * Add a Size x attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p> This is a <b>Base Attribute</b> for setting the base width of the particles.This value is Then scaled using the <b>Overtime Attribute</b> %_scaleX.
         * If %uniform is true then this attribute also sets the base height.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddSizeX(float f, float v);

        /**
         * Add a Size y attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p> This is a <b>Base Attribute</b> for setting the base height of the particles. This value is then scaled using the <b>Overtime Attribute</b> %_scaleY.
         * @return Emitter change object.
         */
        AttributeNode* AddSizeY(float f, float v);

        /**
         * Add a Size x variation attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This is a <b>Variation Attribute</b> for effecting how much the base sizex attribute varies. So if sizex is 100, and the sizexvariation is 50 then
         * the base particle width can carry from 100-150.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddSizeXVariation(float f, float v);

        /**
         * Add a Size y variation attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This is a <b>Variation Attribute</b> for effecting how much the base sizey attribute varies. So if sizey is 100, and the sizeyvariation is 50 then
         * the base particle height can vary from 100-150. This attribute is ignores if %uniform is true.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddSizeYVariation(float f, float v);

        /**
         * Add a Base Speed attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This is a <b>Base Attribute</b> for setting the base speed of the particle. Speed is then scaled over the lifetime of the particle using the 
         * <b>Overtime Attribute</b> Velocity</p>
         * @return Emitter change object.
         */
        AttributeNode* AddBaseSpeed(float f, float v);

        /**
         * Add a Velocity attribute node
         * <p>Pass the method a value between 0 and 1 representing the percentage of the lifetime of the particle (f) and the value (v)</p>
         * <p>This is an <b>Overtime Attribute</b> for scaling the base speed of the particle. For example if you wanted a particle to start off travelling fast
         * and slow down to a stop over the course of its life time you would add the following attribute values:</p>
         * &{
              AddBaseSpeed(0,200);
              AddVelocity(0,1);
              AddVelocity(1,0);
         * }
         * <p>This would mean that the particle starts out traveling at 200 pixels per second which reduces to 0 over the particles lifetime.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddVelocity(float f, float v);

        /**
         * Add a Base weight attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This is a <b>Base Attribute</b> for setting the base weight of the particle. weight is then scaled over the lifetime of the particle using the 
         * <b>Overtime Attribute</b> weight</p>
         * @return Emitter change object.
         */
        AttributeNode* AddBaseWeight(float f, float v);

        /**
         * Add a weight variation attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This is a <b>Variation Attribute</b> for effecting how much the base weight attribute varies. So if weight is 20, and the weightvariation is 10 then
         * the base particle width can carry from 10-30.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddWeightVariation(float f, float v);

        /**
         * Add a weight attribute node
         * <p>Pass the method a value between 0 and 1 representing the percentage of the lifetime of the particle (f) and the value (v)</p>
         * <p>This is an <b>Overtime Attribute</b> for scaling the base weight of the particle.
         * @return Emitter change object.
         */
        AttributeNode* AddWeight(float f, float v);

        /**
         * Add a velocity variation attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This is a <b>Variation Attribute</b> for effecting how much the base speed attribute varies. So if basespeed is 100, and the velvariation is 50 then
         * the base particle speed can vary from 50-150 pixels per second.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddVelVariation(float f, float v);

        /**
         * Currently unused, will probably be deleted at some point
         */
        //AttributeNode* AddAS(float f, float v);

        /**
         * Add an alpha attribute node
         * <p>Pass the method a value between 0 and 1 representing the percentage of the lifetime of the particle (f) and the value (v)</p>
         * <p>This is an <b>Overtime Attribute</b> for adjust the visibility of the particle over its lifetime where 1 is opaque and 0 is transparent.
         * @return Emitter change object.
         */
        AttributeNode* AddAlpha(float f, float v);

        /**
         * Add a spin attribute node
         * <p>Pass the method a value between 0 and 1 representing the percentage of the lifetime of the particle (f) and the value (v)</p>
         * <p>This is an <b>Overtime Attribute</b> for scaling the base spin of the particle.
         * @return Emitter change object.
         */
        AttributeNode* AddSpin(float f, float v);

        /**
         * Add a Base spin attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This is a <b>Base Attribute</b> for setting the base spin of the particle which effects the speed of rotation of the particle. You can also 
         * effect the direction that the particle spins by using values less then 0. Spin is then scaled over the lifetime of the particle using the 
         * <b>Overtime Attribute</b> spin</p>
         * @return Emitter change object.
         */
        AttributeNode* AddBaseSpin(float f, float v);

        /**
         * Add a spin variation attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This is a <b>Variation Attribute</b> for effecting how much the base spin attribute varies. So if basespin is 50, and the spinvariation is 25 then
         * the base particle spin can vary from 25-75 degrees per second.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddSpinVariation(float f, float v);

        /**
         * Add a Color Red attribute node
         * <p>Pass the method a value between 0 and 1 representing the percentage of the lifetime of the particle (f) and the value (v)</p>
         * <p>This is an <b>Overtime Attribute</b> for effecting the red color channel of the particle. Values can range from 0 to 255.
         * @return Emitter change object.
         */
        AttributeNode* AddR(float f, float v);

        /**
         * Add a Color Green attribute node
         * <p>Pass the method a value between 0 and 1 representing the percentage of the lifetime of the particle (f) and the value (v)</p>
         * <p>This is an <b>Overtime Attribute</b> for effecting the Green color channel of the particle. Values can range from 0 to 255.
         * @return Emitter change object.
         */
        AttributeNode* AddG(float f, float v);

        /**
         * Add a Color Blue attribute node
         * <p>Pass the method a value between 0 and 1 representing the percentage of the lifetime of the particle (f) and the value (v)</p>
         * <p>This is an <b>Overtime Attribute</b> for effecting the Blue color channel of the particle. Values can range from 0 to 255.
         * @return Emitter change object.
         */
        AttributeNode* AddB(float f, float v);

        /**
         * Add a life variation attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This is a <b>Variation Attribute</b> for varying how long the particle lives for. So if life is 5000, and the lifevariation is 1000 then
         * the life can vary from 4000-6000 milliseconds.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddLifeVariation(float f, float v);

        /**
         * Add a Base life attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This is a <b>Base Attribute</b> for setting how long the particle lives for in milliseconds.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddLife(float f, float v);

        /**
         * Add a Base amount attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This is a <b>Base Attribute</b> for setting how many particles are spawned per second by the emitter.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddAmount(float f, float v);

        /**
         * Add an amount variation attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This is a <b>Variation Attribute</b> for varying how many particles are spawned per second by the emitter. So if amount is 50, 
         * and the amountvariation is 10 then the amount spawned can vary from 50-60.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddAmountVariation(float f, float v);

        /**
         * Add an emission angle attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This attribute controls the direction newly spawned particles travel in but only if %useeffectemission is false.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddEmissionAngle(float f, float v);

        /**
         * Add an emission range attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This attribute controls the random range newly spawned particles travel in but only if %useeffectemission is false. So if the emission range is 
         * 45 degrees and the emission angle is 0 then the range can vary from -45 to 45 degrees (or 315-45 degrees). emission range can be passed any value from 0-180</p>
         * @return Emitter change object.
         */
        AttributeNode* AddEmissionRange(float f, float v);

        /**
         * Add a global velocity attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This attribute effects all particles currently in existence that the emitter has spawned. It will instantly scale the velocity of all particles essentially
         * controlling their speed globally.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddGlobalVelocity(float f, float v);

        /**
         * Add a direction attribute node
         * <p>Pass the method a value between 0 and 1 representing the percentage of the lifetime of the particle (f) and the value (v)</p>
         * <p>This is an <b>Overtime Attribute</b> for effecting the direction the particle travels in over the lifetime of the particle.
         * @return Emitter change object.
         */
        AttributeNode* AddDirection(float f, float v);

        /**
         * Add a direction variation attribute node
         * <p>Pass the method the time in millisecs (f) and the value (v)</p>
         * <p>This is a <b>Variation Attribute</b> for giving particles a degree of motion randomness. This value is further scaled by %directionvariationot</p>
         * @return Emitter change object.
         */
        AttributeNode* AddDirectionVariation(float f, float v);

        /**
         * Add a direction variation overtime attribute node
         * <p>Pass the method a value between 0 and 1 representing the percentage of the lifetime of the particle (f) and the value (v)</p>
         * <p>This is an <b>Overtime Attribute</b> scaling the direction variation over the lifetime of the particle. This gives the particle a motion randomness effecting
         * its direction and speed at vary degrees of variation.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddDirectionVariationOT(float f, float v);

        /**
         * Add a framerate overtime attribute node
         * <p>Pass the method a value between 0 and 1 representing the percentage of the lifetime of the particle (f) and the value (v)</p>
         * <p>This is an <b>Overtime Attribute</b> for controlling the framerate of particles that have more then one frame of animation. This attribute is only relevant
         * if %animate is true.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddFramerate(float f, float v);

        /**
         * Add a stretch overtime attribute node
         * about: <p>Pass the method a value between 0 and 1 representing the percentage of the lifetime of the particle (f) and the value (v)</p>
         * <p>This is an <b>Overtime Attribute</b> for controlling how much the particle stretches depending on the speed it is travelling.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddStretch(float f, float v);

        /**
         * Add a splatter overtime attribute node
         * <p>Pass the time in milliseconds (f) and the value (v)</p>
         * <p>This will control how close to the point the particle will spawn. Higher values mean the particle will appear randomnly around the point of spawning.</p>
         * @return Emitter change object.
         */
        AttributeNode* AddSplatter(float f, float v);

        /**
         * Add an effect to the emitters list of effects.
         * Effects that are in the effects list are basically sub effects that are added to any particles that this emitter spawns which in turn should
         * contain their own emitters that spawn more particles and so on.</p>
         */
        void AddEffect(Effect* effect);

        /**
         * Set Parent Effect
         * Assigns the effect that is the parent to this emitter
         */
        void SetParentEffect(Effect *parent);

        /**
         * Set image
         * When Particles are spawned this image is the image that is assigned to them. Not a tImage but a tAnimImage, a custom image type written by indiepath.
         */
        void SetImage(AnimImage* image);

        /**
         * Set the angle offset or variation
         * Depending on the value of %angletype (AngAlign, AngRandom or AngSpecify), this will either set the angle offset of the particle in the 
         * case of AngAlign and AngSpecify, or act as the range of degrees for AngRandom.
         */
        void SetAngleOffset(int offset);

        /**
         * Set Uniform
         * Dictates whether the particles size scales uniformally. Set to either TRUE or FALSE.
         */
        void SetUniform(bool value);

        /**
         * Set the angle type
         * <p>Angle type tells the particle how it show orientate itself when spawning. Either AngAlign, AngRandom or AngSpecify.</p>
         * <p> @AngAlign: Force the particle to align itself with the direction that it's traveling in.<br/>
         * @AngRandom: Choose a random angle.<br/>
         * @AngSpecify: Specify the angle that the particle spawns with.</p>
         * <p>Use %angleoffset to control the either both the specific angle, random range of angles and an offset if aligning.</p>
         */
        void SetAngleType(Angle type);
        void SetAngleType(int type);

        /**
         * Set Use effect emission
         * Set to TRUE by default, this tells the emitter to take the emission range and emission angle attributes from the parent effect, otherwise if set to FALSE it
         * will take the values from the emitters own emission attributes.
         */
        void SetUseEffectEmission(bool value);

        /**
         * Set to FALSE to stop drawing the particles this emitter spawns
         */
        void SetVisible(bool value);

        /**
         * Set Single Particle
         * You can have particles that do not age and will only be spawned once for point emitters, or just for one frame with area, line and ellipse emitters.
         * Single particles will remain until they are destroyed and will one behave according the values stored in the first emitter change nodes - in other words they
         * will not change at all over time.
         */
        void SetSingleParticle(bool value);

        /**
         * Sets whether the particle chooses random color from the color attributes
         */
        void SetRandomColor(bool value);

        /**
         * Set the z layer
         * Emitters can be set to draw on different layers depending on what kind of effect you need. By default everything is drawn on layer 0, higher layers
         * makes those particles spawned by that emitter drawn on top of emitters below them in layers. The layer value can range from 0-8 giving a total of 9 layers.
         */
        void SetZLayer(int zLayer);

        /**
         * Set whether the particle should animate
         * Only applies if the particle's image has more then one frame of animation.
         */
        void SetAnimate(bool value);

        /**
         * Set the particles to spawn with a random frame
         * Only applies if the particle has more then one frame of animation
         */
        void SetRandomStartFrame(bool value);

        /**
         * Set the direction the animation plays in
         * Set to 1 for forwards playback and set to -1 for reverse playback of the image animation
         */
        void SetAnimationDirection(int direction);

        /**
         * Set to the number of times the color should cycle within the particle lifetime
         * Timeline Particles editor allows values from 1 to 10. 1 is the default.
         */
        void SetColorRepeat(int repeat);

        /**
         * Set to the number of times the alpha of the particle should cycle within the particle lifetime.
         * Timeline Particles editor allows values from 1 to 10. 1 is the default.
         */
        void SetAlphaRepeat(int repeat);

        /**
         * Make a particle a one shot particle or not.
         * Emitters that have this set to true will only spawn one particle and that particle will just play out once and die. The is only relevant if
         * %singleparticle is also set to true.
         */
        void SetOneShot(bool value);

        /**
         * Set the handle of the particle to its center
         * Set to TRUE for the handle to be placed automatically at the center of the particle, or FALSE for the handle to be dictated by %handlex and %handley.
         */
        void SetHandleCenter(bool value);

        /**
         * Set whether the particles and emitter remain relative to the effect.
         * Emitters that are relative spawn particles that move and rotate with the effect they're contained in.
         */
        void SetParticlesRelative(bool value);

        /**
         * Set to TRUE for particles to spawn in between the effects old and new coordinates.
         * This creates better spawning behavior especially for smoke trails.
         */
        void SetTweenSpawns(bool value);

        /**
         * Set to TRUE to make th particles spawned have their angle of rotation locked to direction
         */
        void SetLockAngle(bool value);

        /**
         * Set to TRUE to make th particles spawned have their angle of rotation relative to the parent effect
         */
        void SetAngleRelative(bool value);

        /**
         * Set to TRUE to make the particles spawned playback the animation just once 
         */
        void SetOnce(bool value);

        /**
         * Sets the current state of whether spawned particles are added to the particle managers pool, or the emitters own pool. True means that
         * they're grouped together under each emitter
         */
        void SetGroupParticles(bool value);

        /**
         * Sets emitter's path
         */
        void SetPath(const char *path);

        /**
         * Get the current parent effect
         * @return Effect*
         */
        Effect* GetParentEffect() const;

        /**
         * Get the tAnimImage currently used by the emitter
         * @return AnimImage*
         */
        AnimImage* GetImage() const;

        /**
         * Get the current angle offset used by %angletype (see #setangletype)
         */
        int GetAngleOffset() const;

        /**
         * Get whether the particles spawned by this emitter scale uniformally
         * @return TRUE or FALSE
         */
        bool IsUniform() const;

        /**
         * Get the current angletype for particles spawned by this emitter
         * @return either AngAlign, AngRandom or AngSpecify
         */
        Angle GetAngleType() const;

        /**
         * Get whether the emitter uses the effect emission instead of its own
         * @return either TRUE or FALSE
         */
        bool IsUseEffectEmmision() const;

        /**
         * Get the visibility status of the emitter
         * @return either TRUE or FALSE
         */
        bool IsVisible() const;

        /**
         * Find out if the emitter spawns a single particle
         * @return Either TRUE or FALSE
         */
        bool IsSingleParticle() const;

        /**
         * Get whether the emitter chooses a random color for the particles it spawns
         * @return Either TRUE or FALSE
         */
        bool IsRandomColor() const;

        /**
         * Get the current z layer of the emitter
         * @return Value from 0 - 8
         */
        int GetZLayer() const;

        /**
         * Get whether this emitter spawns particles that animate
         * @return Either TRUE or FALSE
         */
        bool IsAnimate() const;

        /**
         * Get whether the emitter chooses a random start frame for the particles it spawns
         * @return Either TRUE or FALS
         */
        bool IsRandomStartFrame() const;

        /**
         * Get the current animation direction
         * @return Either -1 for reverse playback or 1 for normal playback for particles spawned by this emitter.
         */
        int GetAnimationDirection() const;

        /**
         * Get the number of times the color cycles over the lifetime of the particles spawned by this emitter.
         */
        int GetColorRepeat() const;

        /**
         * Get the number of times the alpha cycles over the lifetime of the particles spawned by this emitter.
         */
        int GetAlphaRepeat() const;

        /**
         * Get whether this emitter spawns a one shot particle (see #SetOneShot)
         * @return either TRUE or FALSE
         */
        bool IsOneShot() const;

        /**
         * Get whether the handle of the particles spawned by this emitter are set to the center.
         * @return Either TRUE or FALSE
         */
        bool IsHandleCenter() const;

        /**
         * Get whether the particles spawned by this emitter remain relative to the containing effect
         * @return Either TRUE or FALSE
         */
        bool IsParticlesRelative() const;

        /**
         * Get whether particles are being spawned from the old effect coordinates to the new.
         * @return Either TRUE or FALSE
         */
        bool IsTweenSpawns() const;

        /**
         * Get whether particles spawned are having their angles locked to direction
         * @return Either TRUE or FALSE
         */
        bool IsLockAngle() const;

        /**
         * Get whether particles spawned will have there angle relative to the parent
         * @return Either TRUE or FALSE
         */
        bool IsAngleRelative() const;

        /**
         * Returns the current state of whether spawned particles playback the animation just once
         */
        bool IsOnce() const;

        /**
         * Returns the current state of whether spawned particles are added to the particle managers pool, or the emitters own pool. True means that
         * they're added to the particle managers pool.
         */
        bool IsGroupParticles() const;

        /**
         * Get the path of the entity
         * the path will be the address of where the entity is within the hierarchy of parent and child entities
         */
        const char *GetPath() const;

        /**
         * Set the Radius Calculate value for this Entity object.
         * This overrides the Entity method so that the effects list can be updated too
         */
        void SetRadiusCalculate(bool value);

        virtual void Destroy(bool releaseChildren = true);

        /**
         * Change the dob of the emitter. dob being date of birth, or time it was created.
         * This will also change the dob of any effects the emitter contains. This is more of an internal method used by
         * the ParticleManager method #AddPreLoadedEffect
         */
        void ChangeDoB(float dob);

        /**
         * Update the emitter
         * This is an internal method called by the parent effect when updating each frame. This method will update its position and spawn new particles
         * depending on whatever settings the emitter has by calling #UpdateSpawns
         */
        virtual bool Update();

        /**
         * Spawns a new lot of particles if necessary and assign all properties and attributes to the particle.
         * This method is called by #Update each frame.
         */
        void UpdateSpawns(Particle *eSingle = NULL);

        /**
         * Control a particle
         * Any particle spawned by an emitter is controlled by it. When a particle is updated it calls this method to find out how it should behave.
         */
        void ControlParticle(Particle *particle);

        /**
         * Draws the current image frame
         * Draws on screen the current frame of the image the emitter uses to create particles with. Mainly just a Timeline Particles Editor method.
         */
        void DrawCurrentFrame(float x = 0, float y = 0, float w = 128.0f, float h = 128.0f);

        float RandomizeR(Particle *e, float randomAge);
        float RandomizeG(Particle *e, float randomAge);
        float RandomizeB(Particle *e, float randomAge);

        // Compilers
        void CompileAll();
        void CompileQuick();

        void AnalyseEmitter();
        void ResetBypassers();

        float GetLongestLife() const;

        // base
        float GetEmitterLife(float frame) const;
        float GetEmitterLifeVariation(float frame) const;
        float GetEmitterAmount(float frame) const;
        float GetEmitterSizeX(float frame) const;
        float GetEmitterSizeY(float frame) const;
        float GetEmitterBaseSpeed(float frame) const;
        float GetEmitterBaseWeight(float frame) const;
        float GetEmitterBaseSpin(float frame) const;
        float GetEmitterEmissionAngle(float frame) const;
        float GetEmitterEmissionRange(float frame) const;
        float GetEmitterSplatter(float frame) const;
        float GetEmitterVelVariation(float frame) const;
        float GetEmitterWeightVariation(float frame) const;
        float GetEmitterAmountVariation(float frame) const;
        float GetEmitterSizeXVariation(float frame) const;
        float GetEmitterSizeYVariation(float frame) const;
        float GetEmitterSpinVariation(float frame) const;
        float GetEmitterDirectionVariation(float frame) const;
        // over lifetime
        float GetEmitterAlpha(float age, float lifetime = 0) const;
        float GetEmitterR(float age, float lifetime = 0) const;
        float GetEmitterG(float age, float lifetime = 0) const;
        float GetEmitterB(float age, float lifetime = 0) const;
        float GetEmitterScaleX(float age, float lifetime = 0) const;
        float GetEmitterScaleY(float age, float lifetime = 0) const;
        float GetEmitterSpin(float age, float lifetime = 0) const;
        float GetEmitterVelocity(float age, float lifetime = 0) const;
        float GetEmitterWeight(float age, float lifetime = 0) const;
        float GetEmitterDirection(float age, float lifetime = 0) const;
        float GetEmitterDirectionVariationOT(float age, float lifetime = 0) const;
        float GetEmitterFramerate(float age, float lifetime = 0) const;
        float GetEmitterStretch(float age, float lifetime = 0) const;
        // global adjusters
        float GetEmitterGlobalVelocity(float frame);

        const std::list<Effect*>& GetEffects() const;

        bool IsDying() const;

    protected:
        float                                   _currentLife;           /// the current life of the emitter as it will vary over time
        bool                                    _uniform;               /// whether it scales uniformly
        Effect*                                 _parentEffect;          /// the effect it belongs to
        AnimImage*                              _image;                 /// the sprite of the emitter
        bool                                    _handleCenter;          /// Whether or not the particle's handle is in centered automatically
        int                                     _angleOffset;           /// angle variation and offset
        bool                                    _lockedAngle;           /// entity rotation is locked to the direction it's going
        float                                   _gx, _gy;               /// Grid Coords from grid spawning in an area
        float                                   _counter;               /// counter for the spawning of particles
        float                                   _oldCounter;            /// old counter value for tweening
        Angle                                   _angleType;             /// Set to either AngAlign to motion, AngRandom or AngSpecify
        bool                                    _angleRelative;         /// Whether the angle of the particles should be drawn relative to the parent
        bool                                    _useEffectEmission;     /// whether the emitter has it's own set of emission settings
        bool                                    _deleted;               /// Whether it's been deleted and awaiting removal from emitter list
        bool                                    _visible;               /// Whether this children particles will be drawn
        bool                                    _singleParticle;        /// Whether the emitter spawns just a one-off particle, for glow children and blast waves etc.
        bool                                    _startedSpawning;       /// Whether any particles have been spawned yet
        int                                     _spawned;               /// count of how many particles spawned so far
        bool                                    _randomColor;           /// Whether or not the particle picks a color at random from the gradient
        int                                     _zLayer;                /// The z order that the emitter should be drawn in (1-8 layers)
        bool                                    _animate;               /// Whether or not to use only 1 frame of the animation
        bool                                    _randomStartFrame;      /// should the animation start from a random frame each spawn?
        int                                     _animationDirection;    /// Play the animation backwards or forwards
        int                                     _colorRepeat;           /// Number of times the color sequence should be repeated over the particles lifetime
        int                                     _alphaRepeat;           /// Number of times the alpha sequence should be repeated over the particles lifetime
        bool                                    _dirAlternater;         /// can use this to alternate between traveling inwards and outwards.
        bool                                    _oneShot;               /// a singleparticle that just fires once and dies
        bool                                    _particlesRelative;     /// Whether or not the particles are relative
        bool                                    _tweenSpawns;           /// whether the emitter should tween spawning between old and current coords
        std::list<Effect*>                      _effects;               /// list of sub effects added to each particle when they're spawned
        bool                                    _once;                  /// Whether the particles of this emitter should animate just the once
        std::string                             _path;                  /// the path to the emitter for where in the effect hierarchy the emitter is
        bool                                    _dying;                 /// true if the emitter is in the process of dying ie, no longer spawning particles
        bool                                    _groupParticles;        /// Set to true to add particles to one big pool, instead of the emitters own pool.

        // ----All the lists for controlling the particle over time
        EmitterArray*                           _cR;                    /// Red
        EmitterArray*                           _cG;                    /// Green
        EmitterArray*                           _cB;                    /// Blue
        EmitterArray*                           _cBaseSpin;             /// base speed of spin
        EmitterArray*                           _cSpin;                 /// spin speed
        EmitterArray*                           _cSpinVariation;        /// spin variation
        EmitterArray*                           _cVelocity;             /// speed overtime
        EmitterArray*                           _cBaseWeight;           /// base weight of particle
        EmitterArray*                           _cWeight;               /// weight overtime
        EmitterArray*                           _cWeightVariation;      /// weight variation
        EmitterArray*                           _cBaseSpeed;            /// speed of it
        EmitterArray*                           _cVelVariation;         /// Velocity variation over time
        //EmitterArray*                           _cAs;                   /// how fast it accelerates to velocity
        EmitterArray*                           _cAlpha;                /// how visible it is
        EmitterArray*                           _cSizeX;                /// spawn size over time
        EmitterArray*                           _cSizeY;                /// spawn size over time
        EmitterArray*                           _cScaleX;               /// size over time
        EmitterArray*                           _cScaleY;               /// size over time
        EmitterArray*                           _cSizeXVariation;       /// Size x variation
        EmitterArray*                           _cSizeYVariation;       /// Size y variation
        EmitterArray*                           _cLifeVariation;        /// how much the lifetime varies
        EmitterArray*                           _cLife;                 /// how long the particles last in frames
        EmitterArray*                           _cAmount;               /// the amount of particles per frame
        EmitterArray*                           _cAmountVariation;      /// the variable amount of particles per frame
        EmitterArray*                           _cEmissionAngle;        /// direction of travel when the particle is spawned
        EmitterArray*                           _cEmissionRange;        /// range of direction
        EmitterArray*                           _cGlobalVelocity;       /// children the velocity of all particles at any time in the children lifetime
        EmitterArray*                           _cDirection;            /// direction the particle is going over the life of the particle
        EmitterArray*                           _cDirectionVariation;   /// direction variation
        EmitterArray*                           _cDirectionVariationOT; /// direction variation overtime
        EmitterArray*                           _cFramerate;            /// the speed of the animation over time
        EmitterArray*                           _cStretch;              /// amount the particle is stretched by the speed it's traveling
        EmitterArray*                           _cSplatter;             /// this will randomize the distance where the particle spawns to it's point.
        bool                                    _arrayOwner;            /// only the effects/emitters in EffectsLibrary should be the owners, not the copies

        // Bypassers
        bool                                    _bypassWeight;
        bool                                    _bypassSpeed;
        bool                                    _bypassSpin;
        bool                                    _bypassDirectionvariation;
        bool                                    _bypassColor;
        bool                                    _bRed;
        bool                                    _bGreen;
        bool                                    _bBlue;
        bool                                    _bypassScaleX;
        bool                                    _bypassScaleY;
        bool                                    _bypassLifeVariation;
        bool                                    _bypassFramerate;
        bool                                    _bypassStretch;
        bool                                    _bypassSplatter;

        // Bounding Box Info
        float                                   _AABB_ParticleMaxWidth;
        float                                   _AABB_ParticleMaxHeight;
        float                                   _AABB_ParticleMinWidth;
        float                                   _AABB_ParticleMinHeight;

        float                                   _currentLifeVariation;
        float                                   _currentWeight;
        float                                   _currentWeightVariation;
        float                                   _currentSpeed;
        float                                   _currentSpeedVariation;
        float                                   _currentSpin;
        float                                   _currentSpinVariation;
        float                                   _currentDirectionVariation;
        float                                   _currentEmissionAngle;
        float                                   _currentEmissionRange;
        float                                   _currentSizeX;
        float                                   _currentSizeY;
        float                                   _currentSizeXVariation;
        float                                   _currentSizeYVariation;
        float                                   _currentFramerate;
    };

} // namespace TLFX

#endif // _TLFX_EMITTER_H

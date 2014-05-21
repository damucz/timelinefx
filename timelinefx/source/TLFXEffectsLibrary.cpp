#include "TLFXEffectsLibrary.h"
#include "TLFXEffect.h"
#include "TLFXEmitter.h"
#include "TLFXAnimImage.h"

#include <cassert>

namespace TLFX
{

const float EffectsLibrary::globalPercentMin        = 0;
const float EffectsLibrary::globalPercentMax        = 20.0f;
const float EffectsLibrary::globalPercentSteps      = 100.0f;

const float EffectsLibrary::globalPercentVMin       = 0;
const float EffectsLibrary::globalPercentVMax       = 10.0f;
const float EffectsLibrary::globalPercentVSteps     = 200.0f;

const float EffectsLibrary::angleMin                = 0;
const float EffectsLibrary::angleMax                = 1080.0f;
const float EffectsLibrary::angleSteps              = 54.0f;

const float EffectsLibrary::emissionRangeMin        = 0;
const float EffectsLibrary::emissionRangeMax        = 180.0f;
const float EffectsLibrary::emissionRangeSteps      = 30.0f;

const float EffectsLibrary::dimensionsMin           = 0;
const float EffectsLibrary::dimensionsMax           = 200.0f;
const float EffectsLibrary::dimensionsSteps         = 40.0f;

const float EffectsLibrary::lifeMin                 = 0;
const float EffectsLibrary::lifeMax                 = 100000.0f;
const float EffectsLibrary::lifeSteps               = 200.0f;

const float EffectsLibrary::amountMin               = 0;
const float EffectsLibrary::amountMax               = 2000.f;
const float EffectsLibrary::amountSteps             = 100.f;

const float EffectsLibrary::velocityMin             = 0;
const float EffectsLibrary::velocityMax             = 10000.0f;
const float EffectsLibrary::velocitySteps           = 100.0f;

const float EffectsLibrary::velocityOverTimeMin     = -20.0f;
const float EffectsLibrary::velocityOverTimeMax     = 20.0f;
const float EffectsLibrary::velocityOverTimeSteps   = 200.f;

const float EffectsLibrary::weightMin               = -2500.0f;
const float EffectsLibrary::weightMax               = 2500.0f;
const float EffectsLibrary::weightSteps             = 200.0f;

const float EffectsLibrary::weightVariationMin      = 0;
const float EffectsLibrary::weightVariationMax      = 2500.0f;
const float EffectsLibrary::weightVariationSteps    = 250.0f;

const float EffectsLibrary::spinMin                 = -2000.0f;
const float EffectsLibrary::spinMax                 = 2000.0f;
const float EffectsLibrary::spinSteps               = 100.0f;

const float EffectsLibrary::spinVariationMin        = 0;
const float EffectsLibrary::spinVariationMax        = 2000.0f;
const float EffectsLibrary::spinVariationSteps      = 100.0f;

const float EffectsLibrary::spinOverTimeMin         = -20.0f;
const float EffectsLibrary::spinOverTimeMax         = 20.0f;
const float EffectsLibrary::spinOverTimeSteps       = 200.0f;

const float EffectsLibrary::directionOverTimeMin    = 0;
const float EffectsLibrary::directionOverTimeMax    = 4320.0f;
const float EffectsLibrary::directionOverTimeSteps  = 216.0f;

const float EffectsLibrary::framerateMin            = 0;
const float EffectsLibrary::framerateMax            = 200.0f;
const float EffectsLibrary::framerateSteps          = 100.0f;

const float EffectsLibrary::maxDirectionVariation   = 22.5f;
const float EffectsLibrary::maxVelocityVariation    = 30.0f;
const int   EffectsLibrary::motionVariationInterval = 30;

#ifdef _DEBUG
int EffectsLibrary::particlesCreated = 0;
#endif


float EffectsLibrary::_updateFrequency           = 30.0f;                  //  times per second
float EffectsLibrary::_updateTime                = 1000.0f / EffectsLibrary::_updateFrequency;
float EffectsLibrary::_currentUpdateTime         = EffectsLibrary::_updateFrequency;
float EffectsLibrary::_lookupFrequency           = EffectsLibrary::_updateTime;
float EffectsLibrary::_lookupFrequencyOverTime   = 1.0f;


EffectsLibrary::EffectsLibrary()
{

}

EffectsLibrary::~EffectsLibrary()
{
    ClearAll();
}

bool EffectsLibrary::Load( const char *filename, bool compile /*= true*/ )
{
    XMLLoader *loader = CreateLoader();
    bool loaded;
    if (loaded = loader->Open(filename))
    {
        AnimImage *shape;
        while ((shape = CreateImage()), loader->GetNextShape(shape))
        {
            AddSprite(shape);
        }
        delete shape;               // last even shape is safe to delete

        Effect *effect;
        while (effect = loader->GetNextEffect(_shapeList))
        {
            if (compile)
                effect->CompileAll();

            AddEffect(effect);
            // ??? effect->NewDirectory();
            // ??? effect->AddEffect(effect);
        }

        _name = filename;
    }

    delete loader;
    return false;
}

void EffectsLibrary::AddEffect( Effect *e )
{
    std::string name = e->GetPath();

    auto old = _effects.find(name);
    if (old != _effects.end())
    {
        delete old->second;
        // no need to erase, we are assigning new one immediately
    }

    _effects[name] = e;

    auto emitters = e->GetChildren();
    for (auto it = emitters.begin(); it != emitters.end(); ++it)
    {
        AddEmitter(static_cast<Emitter*>(*it));
    }
}

void EffectsLibrary::AddEmitter( Emitter *e )
{
    std::string name = e->GetPath();

    auto old = _emitters.find(name);
    if (old != _emitters.end())
    {
        delete old->second;
        // no need to erase, we are assigning new one immediately
    }

    _emitters[name] = e;

    auto effects = e->GetEffects();
    for (auto it = effects.begin(); it != effects.end(); ++it)
    {
        AddEffect(*it);
    }
}

void EffectsLibrary::ClearAll()
{
    _name = "";

    for (auto it = _effects.begin(); it != _effects.end(); ++it)
        delete it->second;
    _effects.clear();

    for (auto it = _emitters.begin(); it != _emitters.end(); ++it)
        delete it->second;
    _emitters.clear();

    for (auto it = _shapeList.begin(); it != _shapeList.end(); ++it)
        delete *it;
    _shapeList.clear();
}

Effect* EffectsLibrary::GetEffect( const char *name ) const
{
    auto effect = _effects.find(name);
    if (effect != _effects.end())
        return effect->second;
    return NULL;
}

Emitter* EffectsLibrary::GetEmitter( const char *name ) const
{
    auto emitter = _emitters.find(name);
    if (emitter != _emitters.end())
        return emitter->second;
    return NULL;
}

void EffectsLibrary::SetUpdateFrequency( float freq )
{
    _updateFrequency = freq;
    _updateTime = 1000.f / _updateFrequency;
    _currentUpdateTime = _updateFrequency;
}

float EffectsLibrary::GetUpdateFrequency()
{
    return _updateFrequency;
}

float EffectsLibrary::GetUpdateTime()
{
    return _updateTime;
}

float EffectsLibrary::GetCurrentUpdateTime()
{
    return _currentUpdateTime;
}

void EffectsLibrary::SetLookupFrequency( float freq )
{
    _lookupFrequency = freq;
}

float EffectsLibrary::GetLookupFrequency()
{
    return _lookupFrequency;
}

void EffectsLibrary::SetLookupFrequencyOverTime( float freq )
{
    _lookupFrequencyOverTime = freq;
}

float EffectsLibrary::GetLookupFrequencyOverTime()
{
    return _lookupFrequencyOverTime;
}

bool EffectsLibrary::AddSprite( AnimImage *sprite )
{
    const char *filename = sprite->GetFilename();

    if (strlen(sprite->GetName()) == 0)
    {
        const char *name = strrchr(filename, '/');
        if (name)
            ++name;                         // char right after /
        else
            name = filename;
        sprite->SetName(name);
    }

    if (!sprite->Load(filename))
        return false;

    _shapeList.push_back(sprite);
    return true;
}

} // namespace TLFX

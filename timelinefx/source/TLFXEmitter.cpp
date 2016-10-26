#include "TLFXEmitter.h"
#include "TLFXEffect.h"
#include "TLFXEffectsLibrary.h"  // UpdateMode
#include "TLFXAnimImage.h"
#include "TLFXParticleManager.h"
#include "TLFXParticle.h"

#include <algorithm>
#include <cmath>
#include <cassert>

namespace TLFX
{

    Emitter::Emitter()
        : Entity()
        , _currentLife(0)
        , _uniform(true)
        , _parentEffect(NULL)
        , _image(NULL)
        , _handleCenter(false)
        , _angleOffset(0)
        , _lockedAngle(false)
        , _gx(0)
        , _gy(0)
        , _counter(0)
        , _oldCounter(0)
        , _angleType(AngAlign)
        , _angleRelative(false)
        , _useEffectEmission(false)
        , _deleted(false)
        , _visible(true)
        , _singleParticle(false)
        , _startedSpawning(false)
        , _spawned(0)
        , _randomColor(false)
        , _zLayer(0)
        , _animate(false)
        , _randomStartFrame(false)
        , _animationDirection(1)
        , _colorRepeat(0)
        , _alphaRepeat(0)
        , _dirAlternater(false)
        , _oneShot(false)
        , _particlesRelative(false)
        , _tweenSpawns(false)
        , _once(false)
        , _dying(false)
        , _groupParticles(false)

        , _bypassWeight(false)
        , _bypassSpeed(false)
        , _bypassSpin(false)
        , _bypassDirectionvariation(false)
        , _bypassColor(false)
        , _bRed(false)
        , _bGreen(false)
        , _bBlue(false)
        , _bypassScaleX(false)
        , _bypassScaleY(false)
        , _bypassLifeVariation(false)
        , _bypassFramerate(false)
        , _bypassStretch(false)
        , _bypassSplatter(false)

        , _AABB_ParticleMaxWidth(0)
        , _AABB_ParticleMaxHeight(0)
        , _AABB_ParticleMinWidth(0)
        , _AABB_ParticleMinHeight(0)

        , _currentLifeVariation(0)
        , _currentWeight(0)
        , _currentWeightVariation(0)
        , _currentSpeed(0)
        , _currentSpeedVariation(0)
        , _currentSpin(0)
        , _currentSpinVariation(0)
        , _currentDirectionVariation(0)
        , _currentEmissionAngle(0)
        , _currentEmissionRange(0)
        , _currentSizeX(0)
        , _currentSizeY(0)
        , _currentSizeXVariation(0)
        , _currentSizeYVariation(0)
        , _currentFramerate(0)

        , _arrayOwner(true)
    {
        _childrenOwner = false;         // the Particles are managing by pool

        _cAmount = new EmitterArray(EffectsLibrary::amountMin, EffectsLibrary::amountMax);
        _cLife = new EmitterArray(EffectsLibrary::lifeMin, EffectsLibrary::lifeMax);
        _cSizeX = new EmitterArray(EffectsLibrary::dimensionsMin, EffectsLibrary::dimensionsMax);
        _cSizeY = new EmitterArray(EffectsLibrary::dimensionsMin, EffectsLibrary::dimensionsMax);
        _cBaseSpeed = new EmitterArray(EffectsLibrary::velocityMin, EffectsLibrary::velocityMax);
        _cBaseWeight = new EmitterArray(EffectsLibrary::weightMin, EffectsLibrary::weightMax);
        _cBaseSpin = new EmitterArray(EffectsLibrary::spinMin, EffectsLibrary::spinMax);
        _cEmissionAngle = new EmitterArray(EffectsLibrary::angleMin, EffectsLibrary::angleMax);
        _cEmissionRange = new EmitterArray(EffectsLibrary::emissionRangeMin, EffectsLibrary::emissionRangeMax);
        _cSplatter = new EmitterArray(EffectsLibrary::dimensionsMin, EffectsLibrary::dimensionsMax);
        _cVelVariation = new EmitterArray(EffectsLibrary::velocityMin, EffectsLibrary::velocityMax);
        _cWeightVariation = new EmitterArray(EffectsLibrary::weightVariationMin, EffectsLibrary::weightVariationMax);
        _cLifeVariation = new EmitterArray(EffectsLibrary::lifeMin, EffectsLibrary::lifeMax);
        _cAmountVariation = new EmitterArray(EffectsLibrary::amountMin, EffectsLibrary::amountMax);
        _cSizeXVariation = new EmitterArray(EffectsLibrary::dimensionsMin, EffectsLibrary::dimensionsMax);
        _cSizeYVariation = new EmitterArray(EffectsLibrary::dimensionsMin, EffectsLibrary::dimensionsMax);
        _cSpinVariation = new EmitterArray(EffectsLibrary::spinVariationMin, EffectsLibrary::spinVariationMax);
        _cDirectionVariation = new EmitterArray(EffectsLibrary::globalPercentMin, EffectsLibrary::globalPercentMax);
        _cAlpha = new EmitterArray(0, 1.0f);
        _cR = new EmitterArray(0, 0);
        _cG = new EmitterArray(0, 0);
        _cB = new EmitterArray(0, 0);
        _cScaleX = new EmitterArray(EffectsLibrary::globalPercentMin, EffectsLibrary::globalPercentMax);
        _cScaleY = new EmitterArray(EffectsLibrary::globalPercentMin, EffectsLibrary::globalPercentMax);
        _cSpin = new EmitterArray(EffectsLibrary::spinOverTimeMin, EffectsLibrary::spinOverTimeMax);
        _cVelocity = new EmitterArray(EffectsLibrary::velocityOverTimeMin, EffectsLibrary::velocityOverTimeMax);
        _cWeight = new EmitterArray(EffectsLibrary::globalPercentMin, EffectsLibrary::globalPercentMax);
        _cDirection = new EmitterArray(EffectsLibrary::directionOverTimeMin, EffectsLibrary::directionOverTimeMax);
        _cDirectionVariationOT = new EmitterArray(EffectsLibrary::globalPercentMin, EffectsLibrary::globalPercentMax);
        _cFramerate = new EmitterArray(EffectsLibrary::framerateMin, EffectsLibrary::framerateMax);
        _cStretch = new EmitterArray(EffectsLibrary::globalPercentMin, EffectsLibrary::globalPercentMax);
        _cGlobalVelocity = new EmitterArray(EffectsLibrary::globalPercentMin, EffectsLibrary::globalPercentMax);
    }

    Emitter::Emitter( const Emitter& o, ParticleManager *pm )
        : Entity(o)

        , _currentLife(o._currentLife)
        , _uniform(o._uniform)
        , _parentEffect(NULL)
        , _image(o._image)
        , _handleCenter(o._handleCenter)
        , _angleOffset(o._angleOffset)
        , _lockedAngle(o._lockedAngle)
        , _gx(o._gx)
        , _gy(o._gy)
        , _counter(o._counter)
        , _oldCounter(o._oldCounter)
        , _angleType(o._angleType)
        , _angleRelative(o._angleRelative)
        , _useEffectEmission(o._useEffectEmission)
        , _deleted(o._deleted)
        , _visible(o._visible)
        , _singleParticle(o._singleParticle)
        , _startedSpawning(o._startedSpawning)
        , _spawned(o._spawned)
        , _randomColor(o._randomColor)
        , _zLayer(o._zLayer)
        , _animate(o._animate)
        , _randomStartFrame(o._randomStartFrame)
        , _animationDirection(o._animationDirection)
        , _colorRepeat(o._colorRepeat)
        , _alphaRepeat(o._alphaRepeat)
        , _dirAlternater(o._dirAlternater)
        , _oneShot(o._oneShot)
        , _particlesRelative(o._particlesRelative)
        , _tweenSpawns(o._tweenSpawns)
        , _once(o._once)
        , _dying(o._dying)
        , _groupParticles(o._groupParticles)

        , _bypassWeight(o._bypassWeight)
        , _bypassSpeed(o._bypassSpeed)
        , _bypassSpin(o._bypassSpin)
        , _bypassDirectionvariation(o._bypassDirectionvariation)
        , _bypassColor(o._bypassColor)
        , _bRed(o._bRed)
        , _bGreen(o._bGreen)
        , _bBlue(o._bBlue)
        , _bypassScaleX(o._bypassScaleX)
        , _bypassScaleY(o._bypassScaleY)
        , _bypassLifeVariation(o._bypassLifeVariation)
        , _bypassFramerate(o._bypassFramerate)
        , _bypassStretch(o._bypassStretch)
        , _bypassSplatter(o._bypassSplatter)

        , _AABB_ParticleMaxWidth(o._AABB_ParticleMaxWidth)
        , _AABB_ParticleMaxHeight(o._AABB_ParticleMaxHeight)
        , _AABB_ParticleMinWidth(o._AABB_ParticleMinWidth)
        , _AABB_ParticleMinHeight(o._AABB_ParticleMinHeight)

        , _currentLifeVariation(o._currentLifeVariation)
        , _currentWeight(o._currentWeight)
        , _currentWeightVariation(o._currentWeightVariation)
        , _currentSpeed(o._currentSpeed)
        , _currentSpeedVariation(o._currentSpeedVariation)
        , _currentSpin(o._currentSpin)
        , _currentSpinVariation(o._currentSpinVariation)
        , _currentDirectionVariation(o._currentDirectionVariation)
        , _currentEmissionAngle(o._currentEmissionAngle)
        , _currentEmissionRange(o._currentEmissionRange)
        , _currentSizeX(o._currentSizeX)
        , _currentSizeY(o._currentSizeY)
        , _currentSizeXVariation(o._currentSizeXVariation)
        , _currentSizeYVariation(o._currentSizeYVariation)
        , _currentFramerate(o._currentFramerate)

        , _path(o._path)

        , _arrayOwner(false)                // this copy (instance) is not owner
        , _cR(o._cR)                        // copy the links to the templates
        , _cG(o._cG)
        , _cB(o._cB)
        , _cBaseSpin(o._cBaseSpin)
        , _cSpin(o._cSpin)
        , _cSpinVariation(o._cSpinVariation)
        , _cVelocity(o._cVelocity)
        , _cBaseWeight(o._cBaseWeight)
        , _cWeight(o._cWeight)
        , _cWeightVariation(o._cWeightVariation)
        , _cBaseSpeed(o._cBaseSpeed)
        , _cVelVariation(o._cVelVariation)
        //, _cAs(o._cAs)
        , _cAlpha(o._cAlpha)
        , _cSizeX(o._cSizeX)
        , _cSizeY(o._cSizeY)
        , _cScaleX(o._cScaleX)
        , _cScaleY(o._cScaleY)
        , _cSizeXVariation(o._cSizeXVariation)
        , _cSizeYVariation(o._cSizeYVariation)
        , _cLifeVariation(o._cLifeVariation)
        , _cLife(o._cLife)
        , _cAmount(o._cAmount)
        , _cAmountVariation(o._cAmountVariation)
        , _cEmissionAngle(o._cEmissionAngle)
        , _cEmissionRange(o._cEmissionRange)
        , _cGlobalVelocity(o._cGlobalVelocity)
        , _cDirection(o._cDirection)
        , _cDirectionVariation(o._cDirectionVariation)
        , _cDirectionVariationOT(o._cDirectionVariationOT)
        , _cFramerate(o._cFramerate)
        , _cStretch(o._cStretch)
        , _cSplatter(o._cSplatter)

        // copy automatically: base/entity
        // not copy: 
    {
        _dob = pm->GetCurrentTime();
        SetOKtoRender(false);

        _children.clear();
        for (auto it = o.GetEffects().begin(); it != o.GetEffects().end(); ++it)
        {
            AddEffect(new Effect(**it, pm));
        }
    }


    Emitter::~Emitter()
    {
        if (_arrayOwner)
        {
            delete _cR;
            delete _cG;
            delete _cB;
            delete _cBaseSpin;
            delete _cSpin;
            delete _cSpinVariation;
            delete _cVelocity;
            delete _cBaseWeight;
            delete _cWeight;
            delete _cWeightVariation;
            delete _cBaseSpeed;
            delete _cVelVariation;
            //delete _cAs;
            delete _cAlpha;
            delete _cSizeX;
            delete _cSizeY;
            delete _cScaleX;
            delete _cScaleY;
            delete _cSizeXVariation;
            delete _cSizeYVariation;
            delete _cLifeVariation;
            delete _cLife;
            delete _cAmount;
            delete _cAmountVariation;
            delete _cEmissionAngle;
            delete _cEmissionRange;
            delete _cGlobalVelocity;
            delete _cDirection;
            delete _cDirectionVariation;
            delete _cDirectionVariationOT;
            delete _cFramerate;
            delete _cStretch;
            delete _cSplatter;
        }
    }

    void Emitter::SortAll()
    {
        _cR->Sort();
        _cG->Sort();
        _cB->Sort();
        _cBaseSpin->Sort();
        _cSpin->Sort();
        _cSpinVariation->Sort();
        _cVelocity->Sort();
        _cBaseSpeed->Sort();
        _cVelVariation->Sort();
        //_cAs->Sort();
        _cAlpha->Sort();
        _cSizeX->Sort();
        _cSizeY->Sort();
        _cScaleX->Sort();
        _cScaleY->Sort();
        _cSizeXVariation->Sort();
        _cSizeYVariation->Sort();
        _cLifeVariation->Sort();
        _cLife->Sort();
        _cAmount->Sort();
        _cAmountVariation->Sort();
        _cEmissionAngle->Sort();
        _cEmissionRange->Sort();
        _cFramerate->Sort();
        _cStretch->Sort();
        _cGlobalVelocity->Sort();
    }

    void Emitter::ShowAll()
    {
        SetVisible(true);
        // Effect
        for (auto it = _effects.begin(); it != _effects.end(); ++it)
        {
            (*it)->ShowAll();
        }
    }

    void Emitter::HideAll()
    {
        SetVisible(false);
        // Effect
        for (auto it = _effects.begin(); it != _effects.end(); ++it)
        {
            (*it)->HideAll();
        }
    }

    AttributeNode* Emitter::AddScaleX( float f, float v )
    {
        return _cScaleX->Add(f, v);
    }

    AttributeNode* Emitter::AddScaleY( float f, float v )
    {
        return _cScaleY->Add(f, v);
    }

    AttributeNode* Emitter::AddSizeX( float f, float v )
    {
        return _cSizeX->Add(f, v);
    }

    AttributeNode* Emitter::AddSizeY( float f, float v )
    {
        return _cSizeY->Add(f, v);
    }

    AttributeNode* Emitter::AddSizeXVariation( float f, float v )
    {
        return _cSizeXVariation->Add(f, v);
    }

    AttributeNode* Emitter::AddSizeYVariation( float f, float v )
    {
        return _cSizeYVariation->Add(f, v);
    }

    AttributeNode* Emitter::AddBaseSpeed( float f, float v )
    {
        return _cBaseSpeed->Add(f, v);
    }

    AttributeNode* Emitter::AddVelocity( float f, float v )
    {
        return _cVelocity->Add(f, v);
    }

    AttributeNode* Emitter::AddBaseWeight( float f, float v )
    {
        return _cBaseWeight->Add(f, v);
    }

    AttributeNode* Emitter::AddWeightVariation( float f, float v )
    {
        return _cWeightVariation->Add(f, v);
    }

    AttributeNode* Emitter::AddWeight( float f, float v )
    {
        return _cWeight->Add(f, v);
    }

    AttributeNode* Emitter::AddVelVariation( float f, float v )
    {
        return _cVelVariation->Add(f, v);
    }

//     AttributeNode* Emitter::AddAS( float f, float v )
//     {
//         return _cAs->Add(f, v);
//     }

    AttributeNode* Emitter::AddAlpha( float f, float v )
    {
        return _cAlpha->Add(f, v);
    }

    AttributeNode* Emitter::AddSpin( float f, float v )
    {
        return _cSpin->Add(f, v);
    }

    AttributeNode* Emitter::AddBaseSpin( float f, float v )
    {
        return _cBaseSpin->Add(f, v);
    }

    AttributeNode* Emitter::AddSpinVariation( float f, float v )
    {
        return _cSpinVariation->Add(f, v);
    }

    AttributeNode* Emitter::AddR( float f, float v )
    {
        return _cR->Add(f, v);
    }

    AttributeNode* Emitter::AddG( float f, float v )
    {
        return _cG->Add(f, v);
    }

    AttributeNode* Emitter::AddB( float f, float v )
    {
        return _cB->Add(f, v);
    }

    AttributeNode* Emitter::AddLifeVariation( float f, float v )
    {
        return _cLifeVariation->Add(f, v);
    }

    AttributeNode* Emitter::AddLife( float f, float v )
    {
        return _cLife->Add(f, v);
    }

    AttributeNode* Emitter::AddAmount( float f, float v )
    {
        return _cAmount->Add(f, v);
    }

    AttributeNode* Emitter::AddAmountVariation( float f, float v )
    {
        return _cAmountVariation->Add(f, v);
    }

    AttributeNode* Emitter::AddEmissionAngle( float f, float v )
    {
        return _cEmissionAngle->Add(f, v);
    }

    AttributeNode* Emitter::AddEmissionRange( float f, float v )
    {
        return _cEmissionRange->Add(f, v);
    }

    AttributeNode* Emitter::AddGlobalVelocity( float f, float v )
    {
        return _cGlobalVelocity->Add(f, v);
    }

    AttributeNode* Emitter::AddDirection( float f, float v )
    {
        return _cDirection->Add(f, v);
    }

    AttributeNode* Emitter::AddDirectionVariation( float f, float v )
    {
        return _cDirectionVariation->Add(f, v);
    }

    AttributeNode* Emitter::AddDirectionVariationOT( float f, float v )
    {
        return _cDirectionVariationOT->Add(f, v);
    }

    AttributeNode* Emitter::AddFramerate( float f, float v )
    {
        return _cFramerate->Add(f, v);
    }

    AttributeNode* Emitter::AddStretch( float f, float v )
    {
        return _cStretch->Add(f, v);
    }

    AttributeNode* Emitter::AddSplatter( float f, float v )
    {
        return _cSplatter->Add(f, v);
    }

    void Emitter::AddEffect( Effect* effect )
    {
        _effects.push_back(effect);
    }

    void Emitter::SetParentEffect( Effect *parent )
    {
        _parentEffect = parent;
    }

    void Emitter::SetImage( AnimImage* image )
    {
        _image = image;
        _AABB_ParticleMaxWidth = image->GetWidth() * 0.5f;
        _AABB_ParticleMaxHeight = image->GetHeight() * 0.5f;
        _AABB_ParticleMinWidth = image->GetWidth() * (-0.5f);
        _AABB_ParticleMinHeight = image->GetHeight() * (-0.5f);
    }

    void Emitter::SetAngleOffset( int offset )
    {
        _angleOffset = offset;
    }

    void Emitter::SetUniform( bool value )
    {
        _uniform = value;
    }

    void Emitter::SetAngleType( Angle type )
    {
        _angleType = type;
    }

    void Emitter::SetAngleType( int type )
    {
        _angleType = AngAlign;
        switch (type)
        {
        case 0: break;              // nothing, already set by default
        case 1: _angleType = AngRandom; break;
        case 2: _angleType = AngSpecify; break;
        default:
            assert(false);
        }
    }

    void Emitter::SetUseEffectEmission( bool value )
    {
        _useEffectEmission = value;
    }

    void Emitter::SetVisible( bool value )
    {
        _visible = value;
    }

    void Emitter::SetSingleParticle( bool value )
    {
        _singleParticle = value;
    }

    void Emitter::SetRandomColor( bool value )
    {
        _randomColor = value;
    }

    void Emitter::SetZLayer( int zLayer )
    {
        _zLayer = zLayer;
    }

    void Emitter::SetAnimate( bool value )
    {
        _animate = value;
    }

    void Emitter::SetRandomStartFrame( bool value )
    {
        _randomStartFrame = value;
    }

    void Emitter::SetAnimationDirection( int direction )
    {
        _animationDirection = direction;
    }

    void Emitter::SetColorRepeat( int repeat )
    {
        _colorRepeat = repeat;
    }

    void Emitter::SetAlphaRepeat( int repeat )
    {
        _alphaRepeat = repeat;
    }

    void Emitter::SetOneShot( bool value )
    {
        _oneShot = value;
    }

    void Emitter::SetHandleCenter( bool value )
    {
        _handleCenter = value;
    }

    void Emitter::SetParticlesRelative( bool value )
    {
        _particlesRelative = value;
    }

    void Emitter::SetTweenSpawns( bool value )
    {
        _tweenSpawns = value;
    }

    void Emitter::SetLockAngle( bool value )
    {
        _lockedAngle = value;
    }

    void Emitter::SetAngleRelative( bool value )
    {
        _angleRelative = value;
    }

    void Emitter::SetOnce( bool value )
    {
        _once = value;
    }

    void Emitter::SetGroupParticles( bool value )
    {
        _groupParticles = value;
    }

    Effect* Emitter::GetParentEffect() const
    {
        return _parentEffect;
    }

    AnimImage* Emitter::GetImage() const
    {
        return _image;
    }

    int Emitter::GetAngleOffset() const
    {
        return _angleOffset;
    }

    bool Emitter::IsUniform() const
    {
        return _uniform;
    }

    Emitter::Angle Emitter::GetAngleType() const
    {
        return _angleType;
    }

    bool Emitter::IsUseEffectEmmision() const
    {
        return _useEffectEmission;
    }

    bool Emitter::IsVisible() const
    {
        return _visible;
    }

    bool Emitter::IsSingleParticle() const
    {
        return _singleParticle;
    }

    bool Emitter::IsRandomColor() const
    {
        return _randomColor;
    }

    int Emitter::GetZLayer() const
    {
        return _zLayer;
    }

    bool Emitter::IsAnimate() const
    {
        return _animate;
    }

    bool Emitter::IsRandomStartFrame() const
    {
        return _randomStartFrame;
    }

    int Emitter::GetAnimationDirection() const
    {
        return _animationDirection;
    }

    int Emitter::GetColorRepeat() const
    {
        return _colorRepeat;
    }

    int Emitter::GetAlphaRepeat() const
    {
        return _alphaRepeat;
    }

    bool Emitter::IsOneShot() const
    {
        return _oneShot;
    }

    bool Emitter::IsHandleCenter() const
    {
        return _handleCenter;
    }

    bool Emitter::IsParticlesRelative() const
    {
        return _particlesRelative;
    }

    bool Emitter::IsTweenSpawns() const
    {
        return _tweenSpawns;
    }

    bool Emitter::IsLockAngle() const
    {
        return _lockedAngle;
    }

    bool Emitter::IsAngleRelative() const
    {
        return _angleRelative;
    }

    bool Emitter::IsOnce() const
    {
        return _once;
    }

    bool Emitter::IsGroupParticles() const
    {
        return _groupParticles;
    }

    const char * Emitter::GetPath() const
    {
        return _path.c_str();
    }

    void Emitter::SetRadiusCalculate( bool value )
    {
        _radiusCalculate = value;
        // Entity
        for (auto it = _children.begin(); it != _children.end(); ++it)
        {
            (*it)->SetRadiusCalculate(value);
        }
        // Effect
        for (auto it = _effects.begin(); it != _effects.end(); ++it)
        {
            (*it)->SetRadiusCalculate(value);
        }
    }

    void Emitter::Destroy(bool releaseChildren)
    {
        _parentEffect = NULL;
        _image = NULL;
        // Effect
        for (auto it = _effects.begin(); it != _effects.end(); ++it)
        {
            (*it)->Destroy();
            delete *it;
        }
        _effects.clear();

        base::Destroy(false);
    }

    void Emitter::ChangeDoB( float dob )
    {
        _dob = dob;
        // Effect
        for (auto it = _effects.begin(); it != _effects.end(); ++it)
        {
            (*it)->ChangeDoB(dob);
        }
    }

    bool Emitter::Update()
    {
        Capture();

        _matrix.Set(cosf(_angle / 180.0f * (float)M_PI), sinf(_angle / 180.0f * (float)M_PI), -sinf(_angle / 180.0f * (float)M_PI), cosf(_angle / 180.0f * (float)M_PI));

        if (_parent && _relative)
        {
            SetZ(_parent->GetZ());
            _matrix = _matrix.Transform(_parent->GetMatrix());
            Vector2 rotvec = _parent->GetMatrix().TransformVector(Vector2(_x, _y));

            _wx = _parent->GetWX() + rotvec.x * _z;
            _wy = _parent->GetWY() + rotvec.y * _z;

            _relativeAngle = _parent->GetRelativeAngle() + _angle;
        }
        else
        {
            _wx = _x;
            _wy = _y;
        }

        if (!_tweenSpawns)
        {
            Capture();
            _tweenSpawns = true;
        }

        _dying = _parentEffect->IsDying();

        base::UpdateBoundingBox();

        if (_radiusCalculate)
            base::UpdateEntityRadius();

        UpdateChildren();

        if (!_dead && !_dying)
        {
            if (_visible &&_parentEffect->GetParticleManager()->IsSpawningAllowed())
                UpdateSpawns();
        }
        else
        {
            if (_children.empty())
            {
                Destroy();
                return false;
            }
            else
            {
                KillChildren();
            }
        }
        return true;
    }

    void Emitter::UpdateSpawns( Particle *eSingle /*= NULL*/ )
    {
        int intCounter;
        float qty;
        float er;
        Particle* e;
        float curFrame = _parentEffect->GetCurrentEffectFrame();
        ParticleManager* pm = _parentEffect->GetParticleManager();

        qty = ((GetEmitterAmount(curFrame) + Rnd(GetEmitterAmountVariation(curFrame))) * _parentEffect->GetCurrentAmount() * pm->GetGlobalAmountScale() * pm->GetLocalAmountScale()) / EffectsLibrary::GetUpdateFrequency();
        if (!_singleParticle)
            _counter += qty;
        intCounter = (int)_counter;
        if (intCounter >= 1 || (_singleParticle && !_startedSpawning))
        {
            TLFXLOG(PARTICLES, ("spawned: %d", intCounter));
            if (!_startedSpawning && _singleParticle)
            {
                switch (_parentEffect->GetClass())
                {
                case Effect::TypePoint: intCounter = 1; break;
                case Effect::TypeArea:  intCounter = _parentEffect->GetMGX() * _parentEffect->GetMGY(); break;
                case Effect::TypeLine:
                case Effect::TypeEllipse: intCounter = _parentEffect->GetMGX(); break;
                }
            }
            else if (_singleParticle && _startedSpawning)
            {
                intCounter = 0;
            }

            // preload attributes
            _currentLife = GetEmitterLife(curFrame) * _parentEffect->GetCurrentLife();
            if (!_bypassWeight)
            {
                _currentWeight = GetEmitterBaseWeight(curFrame);
                _currentWeightVariation = GetEmitterWeightVariation(curFrame);
            }

            if (!_bypassSpeed)
            {
                _currentSpeed = GetEmitterBaseSpeed(curFrame);
                _currentSpeedVariation = GetEmitterVelVariation(curFrame);
            }

            if (!_bypassSpin)
            {
                _currentSpin = GetEmitterBaseSpin(curFrame);
                _currentSpinVariation = GetEmitterSpinVariation(curFrame);
            }

            _currentDirectionVariation = GetEmitterDirectionVariation(curFrame);

            if (_useEffectEmission)
            {
                er = _parentEffect->GetCurrentEmissionRange();
                _currentEmissionAngle = _parentEffect->GetCurrentEmissionAngle();
            }
            else
            {
                er = GetEmitterEmissionRange(curFrame);
                _currentEmissionAngle = GetEmitterEmissionAngle(curFrame);
            }

            _currentLifeVariation = GetEmitterLifeVariation(curFrame);
            _currentSizeX = GetEmitterSizeX(curFrame);
            _currentSizeY = GetEmitterSizeY(curFrame);
            _currentSizeXVariation = GetEmitterSizeXVariation(curFrame);
            _currentSizeYVariation = GetEmitterSizeYVariation(curFrame);

            // ------------------------------
            for (int c = 1; c <= intCounter; ++c)
            {
                _startedSpawning = true;
                assert(pm);
                if (!eSingle)
                {
                    e = pm->GrabParticle(_parentEffect, _groupParticles, _zLayer);
                }
                else
                {
                    e = eSingle;
                }

                if (e)
                {
#ifdef _DEBUG
                    ++EffectsLibrary::particlesCreated;
#endif
                    // -----Link to its emitter and assign the control source (which is this emitter)----
					std::string particleName = "(particle)";
					particleName.append(GetName());
					e->SetName(particleName.c_str());
                    e->SetEmitter(this);
                    e->SetParent(this);
                    e->SetParticleManager(pm);
                    e->SetEffectLayer(_parentEffect->GetEffectLayer());
                    // ----------------------------------------------------
                    e->SetDoB(pm->GetCurrentTime());

                    if (_parentEffect->GetTraverseEdge() && _parentEffect->GetClass() == Effect::TypeLine)
                    {
                        _particlesRelative = true;
                    }
                    e->SetRelative(_particlesRelative);

                    switch (_parentEffect->GetClass())
                    {
                    case Effect::TypePoint:
                        if (e->IsRelative())
                        {
                            e->SetX((float)(0 - _parentEffect->GetHandleX()));
                            e->SetY((float)(0 - _parentEffect->GetHandleY()));
                        }
                        else
                        {
                            float tween = (float)c / intCounter;
                            if (_parentEffect->GetHandleCenter() || (_parentEffect->GetHandleX() + _parentEffect->GetHandleY() == 0))
                            {
                                // @dan already set? tween = (float)c / intCounter;
                                e->SetX(TweenValues(_oldWX, _wx, tween));
                                e->SetY(TweenValues(_oldWY, _wy, tween));
                                if (_z != 1)
                                {
                                    e->SetWX(e->GetX() - _parentEffect->GetHandleX() * _z);
                                    e->SetWY(e->GetY() - _parentEffect->GetHandleY() * _z);
                                }
                                else
                                {
                                    e->SetWX(e->GetX() - _parentEffect->GetHandleX());
                                    e->SetWY(e->GetY() - _parentEffect->GetHandleY());
                                }
                            }
                            else
                            {
                                e->SetX((float)(0 - _parentEffect->GetHandleX()));
                                e->SetY((float)(0 - _parentEffect->GetHandleY()));
                                Vector2 rotvec = _parent->GetMatrix().TransformVector(Vector2(e->GetX(), e->GetY()));
                                e->SetX(TweenValues(_oldWX, _wx, tween) + rotvec.x);
                                e->SetY(TweenValues(_oldWY, _wy, tween) + rotvec.y);
                                if (_z != 1)
                                {
                                    e->SetWX(e->GetX() * _z);
                                    e->SetWY(e->GetY() * _z);
                                }
                                else
                                {
                                    e->SetWX(e->GetX());
                                    e->SetWY(e->GetY());
                                }
                            }
                        }
                        break;

                    case Effect::TypeArea:
                        if (_parentEffect->GetEmitAtPoints())
                        {
                            if (_parentEffect->GetSpawnDirection() == -1)
                            {
                                _gx += _parentEffect->GetSpawnDirection();
                                if (_gx < 0)
                                {
                                    _gx = (float)(_parentEffect->GetMGX() - 1);
                                    _gy += _parentEffect->GetSpawnDirection();
                                    if (_gy < 0)
                                        _gy = (float)(_parentEffect->GetMGY() - 1);
                                }
                            }

                            if (_parentEffect->GetMGX() > 1)
                            {
                                e->SetX((_gx / (_parentEffect->GetMGX() - 1) * _parentEffect->GetCurrentWidth()) - _parentEffect->GetHandleX());
                            }
                            else
                            {
                                e->SetX((float)(-_parentEffect->GetHandleX()));
                            }

                            if (_parentEffect->GetMGY() > 1)
                            {
                                e->SetY((_gy / (_parentEffect->GetMGY() - 1) * _parentEffect->GetCurrentHeight()) - _parentEffect->GetHandleY());
                            }
                            else
                            {
                                e->SetY((float)(-_parentEffect->GetHandleY()));
                            }

                            if (_parentEffect->GetSpawnDirection() == 1)
                            {
                                _gx += _parentEffect->GetSpawnDirection();
                                if (_gx >= _parentEffect->GetMGX())
                                {
                                    _gx = 0;
                                    _gy += _parentEffect->GetSpawnDirection();
                                    if (_gy >= _parentEffect->GetMGY())
                                        _gy = 0;
                                }
                            }
                        }
                        else
                        {
                            e->SetX(Rnd(_parentEffect->GetCurrentWidth())  - _parentEffect->GetHandleX());
                            e->SetY(Rnd(_parentEffect->GetCurrentHeight()) - _parentEffect->GetHandleY());
                        }

                        if (!e->IsRelative())
                        {
                            Vector2 rotvec = _parent->GetMatrix().TransformVector(Vector2(e->GetX(), e->GetY()));
                            if (_z != 1)
                            {
                                e->SetX(_parent->GetWX() + rotvec.x * _z);
                                e->SetY(_parent->GetWY() + rotvec.y * _z);
                            }
                            else
                            {
                                e->SetX(_parent->GetWX() + rotvec.x);
                                e->SetY(_parent->GetWY() + rotvec.y);
                            }
                        }

                        break;

                    case Effect::TypeEllipse:
                        {
                            float tx = _parentEffect->GetCurrentWidth()  / 2.0f;
                            float ty = _parentEffect->GetCurrentHeight() / 2.0f;
                            float th = 0;

                            if (_parentEffect->GetEmitAtPoints())
                            {
                                if (_parentEffect->GetMGX() == 0)
                                    _parentEffect->SetMGX(1);

                                _gx += _parentEffect->GetSpawnDirection();
                                if (_gx >= _parentEffect->GetMGX())
                                {
                                    _gx = 0;
                                }
                                else if (_gx < 0)
                                {
                                    _gx = (float)(_parentEffect->GetMGX() - 1);
                                }

                                th = _gx * (_parentEffect->GetEllipseArc() / _parentEffect->GetMGX()) + _parentEffect->GetEllipseOffset();
                            }
                            else
                            {
                                th = Rnd(_parentEffect->GetEllipseArc()) + _parentEffect->GetEllipseOffset();
                            }
                            e->SetX( cosf(th / 180.0f * (float)M_PI) * tx - _parentEffect->GetHandleX() + tx);
                            e->SetY(-sinf(th / 180.0f * (float)M_PI) * ty - _parentEffect->GetHandleY() + ty);

                            if (!e->IsRelative())
                            {
                                Vector2 rotvec = _parent->GetMatrix().TransformVector(Vector2(e->GetX(), e->GetY()));
                                if (_z != 1)
                                {
                                    e->SetX(_parent->GetWX() + rotvec.x * _z);
                                    e->SetY(_parent->GetWY() + rotvec.y * _z);
                                }
                                else
                                {
                                    e->SetX(_parent->GetWX() + rotvec.x);
                                    e->SetY(_parent->GetWY() + rotvec.y);
                                }
                            }
                        }
                        break;

                    case Effect::TypeLine:
                        if (!_parentEffect->GetTraverseEdge())
                        {
                            if (_parentEffect->GetEmitAtPoints())
                            {
                                if (_parentEffect->GetSpawnDirection() == -1)
                                {
                                    _gx += _parentEffect->GetSpawnDirection();
                                    if (_gx < 0)
                                        _gx = (float)(_parentEffect->GetMGX() - 1);
                                }

                                if (_parentEffect->GetMGX() > 1)
                                {
                                    e->SetX((_gx / (_parentEffect->GetMGX() - 1) * _parentEffect->GetCurrentWidth()) - _parentEffect->GetHandleX());
                                }
                                else
                                {
                                    e->SetX((float)(-_parentEffect->GetHandleX()));
                                }
                                e->SetY((float)(-_parentEffect->GetHandleY()));

                                if (_parentEffect->GetSpawnDirection() == 1)
                                {
                                    _gx += _parentEffect->GetSpawnDirection();
                                    if (_gx >= _parentEffect->GetMGX())
                                        _gx = 0;
                                }
                            }
                            else
                            {
                                e->SetX(Rnd(_parentEffect->GetCurrentWidth()) - _parentEffect->GetHandleX());
                                e->SetY((float)(-_parentEffect->GetHandleY()));
                            }
                        }
                        else
                        {
                            if (_parentEffect->GetDistanceSetByLife())
                            {
                                e->SetX((float)(-_parentEffect->GetHandleX()));
                                e->SetY((float)(-_parentEffect->GetHandleY()));
                            }
                            else
                            {
                                if (_parentEffect->GetEmitAtPoints())
                                {
                                    if (_parentEffect->GetSpawnDirection() == -1)
                                    {
                                        _gx += _parentEffect->GetSpawnDirection();
                                        if (_gx < 0)
                                            _gx = (float)(_parentEffect->GetMGX() - 1);
                                    }

                                    if (_parentEffect->GetMGX() > 1)
                                    {
                                        e->SetX((_gx / (_parentEffect->GetMGX() - 1) * _parentEffect->GetCurrentWidth()) - _parentEffect->GetHandleX());
                                    }
                                    else
                                    {
                                        e->SetX((float)(-_parentEffect->GetHandleX()));
                                    }
                                    e->SetY((float)(-_parentEffect->GetHandleY()));

                                    if (_parentEffect->GetSpawnDirection() == 1)
                                    {
                                        _gx += _parentEffect->GetSpawnDirection();
                                        if (_gx >= _parentEffect->GetMGX())
                                            _gx = 0;
                                    }
                                }
                                else
                                {
                                    e->SetX(Rnd(_parentEffect->GetCurrentWidth()) - _parentEffect->GetHandleX());
                                    e->SetY((float)(-_parentEffect->GetHandleY()));
                                }
                            }
                        }

                        // rotate
                        if (!e->IsRelative())
                        {
                            Vector2 rotvec = _parent->GetMatrix().TransformVector(Vector2(e->GetX(), e->GetY()));
                            if (_z != 1)
                            {
                                e->SetX(_parent->GetWX() + rotvec.x * _z);
                                e->SetY(_parent->GetWY() + rotvec.y * _z);
                            }
                            else
                            {
                                e->SetX(_parent->GetWX() + rotvec.x);
                                e->SetY(_parent->GetWY() + rotvec.y);
                            }
                        }
                        break;
                    }

                    // set the zoom level
                    e->SetZ(_z);

                    // set up the image
                    e->SetAvatar(_image);
                    e->SetHandleX(_handleX);
                    e->SetHandleY(_handleY);
                    e->SetAutocenter(_handleCenter);

                    // set lifetime properties
                    e->SetLifeTime((int)(_currentLife + Rnd(-_currentLifeVariation, _currentLifeVariation) * _parentEffect->GetCurrentLife()));

                    // speed
                    e->SetSpeedVecX(0);
                    e->SetSpeedVecY(0);
                    if (!_bypassSpeed)
                    {
                        e->SetSpeed(_cVelocity->Get(0));
                        e->SetVelVariation(Rnd(-_currentSpeedVariation, _currentSpeedVariation));
                        e->SetBaseSpeed((_currentSpeed + e->GetVelVariation()) * _parentEffect->GetCurrentVelocity());
                        //e->_velSeed = Rnd(0, 1.0f);
                        e->SetSpeed(_cVelocity->Get(0) * e->GetBaseSpeed() * _cGlobalVelocity->Get(0));
                    }
                    else
                    {
                        e->SetSpeed(0);
                    }

                    // size
                    e->SetGSizeX(_parentEffect->GetCurrentSizeX());
                    e->SetGSizeY(_parentEffect->GetCurrentSizeY());

                    // width
                    float scaleTemp = _cScaleX->Get(0);
                    float sizeTemp = 0;
                    e->SetScaleVariationX(Rnd(_currentSizeXVariation));
                    e->SetWidth(e->GetScaleVariationX() + _currentSizeX);
                    if (scaleTemp != 0)
                    {
                        sizeTemp = (e->GetWidth() / _image->GetWidth()) * scaleTemp * e->GetGSizeX();
                    }
                    e->SetScaleX(sizeTemp);

                    if (_uniform)
                    {
                        // height
                        e->SetScaleY(sizeTemp);

                        if (!_bypassStretch)
                        {
                            e->SetScaleY((GetEmitterScaleX(0) * e->GetGSizeX() * (e->GetWidth() + (fabsf(e->GetSpeed()) * GetEmitterStretch(0) * _parentEffect->GetCurrentStretch()))) / _image->GetWidth());
                            if (e->GetScaleY() < e->GetScaleX())
                                e->SetScaleY(e->GetScaleX());
                        }

                        e->SetWidthHeightAABB(_AABB_ParticleMinWidth, _AABB_ParticleMaxWidth, _AABB_ParticleMinWidth, _AABB_ParticleMaxWidth);
                    }
                    else
                    {
                        // height
                        scaleTemp = GetEmitterScaleY(0);
                        sizeTemp = 0;
                        e->SetScaleVariationY(Rnd(_currentSizeYVariation));
                        e->SetHeight(e->GetScaleVariationY() + _currentSizeY);
                        if (scaleTemp != 0)
                        {
                            sizeTemp = (e->GetHeight() / _image->GetHeight()) * scaleTemp * e->GetGSizeY();
                        }
                        e->SetScaleY(sizeTemp);

                        if (!_bypassStretch && e->GetSpeed() != 0)
                        {
                            e->SetScaleY((GetEmitterScaleY(0) * e->GetGSizeY() * (e->GetHeight() + (fabsf(e->GetSpeed()) * GetEmitterStretch(0) * _parentEffect->GetCurrentStretch()))) / _image->GetHeight());
                            if (e->GetScaleY() < e->GetScaleX())
                                e->SetScaleY(e->GetScaleX());
                        }

                        e->SetWidthHeightAABB(_AABB_ParticleMinWidth, _AABB_ParticleMaxWidth, _AABB_ParticleMinHeight, _AABB_ParticleMaxHeight);
                    }

                    // splatter
                    if (!_bypassSplatter)
                    {
                        float splatterTemp = GetEmitterSplatter(curFrame);
                        float splatX = Rnd(-splatterTemp, splatterTemp);
                        float splatY = Rnd(-splatterTemp, splatterTemp);

                        while (Vector2::GetDistance(0, 0, splatX, splatY) >= splatterTemp && splatterTemp > 0)
                        {
                            splatX = Rnd(-splatterTemp, splatterTemp);
                            splatY = Rnd(-splatterTemp, splatterTemp);
                        }

                        if (_z == 1 || e->IsRelative())
                        {
                            e->Move(splatX, splatY);
                        }
                        else
                        {
                            e->Move(splatX * _z, splatY * _z);
                        }
                    }

                    // rotation and direction of travel settings
                    e->MiniUpdate();
                    if (_parentEffect->GetTraverseEdge() && _parentEffect->GetClass() == Effect::TypeLine)
                    {
                        e->SetDirectionLocked(true);
                        e->SetEntityDirection(90.0f);
                    }
                    else
                    {
                        if (_parentEffect->GetClass() != Effect::TypePoint)
                        {
                            if (!_bypassSpeed || _angleType == AngAlign)
                            {
                                e->SetEmissionAngle(_currentEmissionAngle + Rnd(-er, er));
                                switch (_parentEffect->GetEmissionType())
                                {
                                case Effect::EmInwards:
                                    if (e->IsRelative())
                                        e->SetEmissionAngle(e->GetEmissionAngle() + Vector2::GetDirection(e->GetX(), e->GetY(), 0, 0));
                                    else
                                        e->SetEmissionAngle(e->GetEmissionAngle() + Vector2::GetDirection(e->GetWX(), e->GetWY(), e->GetParent()->GetWX(), e->GetParent()->GetWY()));
                                    break;

                                case Effect::EmOutwards:
                                    if (e->IsRelative())
                                        e->SetEmissionAngle(e->GetEmissionAngle() + Vector2::GetDirection(0, 0, e->GetX(), e->GetY()));
                                    else
                                        e->SetEmissionAngle(e->GetEmissionAngle() + Vector2::GetDirection(e->GetParent()->GetWX(), e->GetParent()->GetWY(), e->GetWX(), e->GetWY()));
                                    break;

                                case Effect::EmInAndOut:
                                    if (_dirAlternater)
                                    {
                                        if (e->IsRelative())
                                            e->SetEmissionAngle(e->GetEmissionAngle() + Vector2::GetDirection(0, 0, e->GetX(), e->GetY()));
                                        else
                                            e->SetEmissionAngle(e->GetEmissionAngle() + Vector2::GetDirection(e->GetParent()->GetWX(), e->GetParent()->GetWY(), e->GetWX(), e->GetWY()));
                                    }
                                    else
                                    {
                                        if (e->IsRelative())
                                            e->SetEmissionAngle(e->GetEmissionAngle() + Vector2::GetDirection(e->GetX(), e->GetY(), 0, 0));
                                        else
                                            e->SetEmissionAngle(e->GetEmissionAngle() + Vector2::GetDirection(e->GetWX(), e->GetWY(), e->GetParent()->GetWX(), e->GetParent()->GetWY()));
                                    }
                                    _dirAlternater = !_dirAlternater;
                                    break;

                                case Effect::EmSpecified:
                                    // nothing
                                    break;
                                }
                            }
                        }
                        else
                        {
                            e->SetEmissionAngle(_currentEmissionAngle + Rnd(-er, er));
                        }

                        if (!_bypassDirectionvariation)
                        {
                            e->SetDirectionVairation(_currentDirectionVariation);
                            float dv = e->GetDirectionVariation() * GetEmitterDirectionVariationOT(0);
                            e->SetEntityDirection(e->GetEmissionAngle() + GetEmitterDirection(0) + Rnd(-dv, dv));
                        }
                        else
                        {
                            e->SetEntityDirection(e->GetEmissionAngle() + GetEmitterDirection(0));
                        }
                    }

                    // ------ e->_lockedAngle = _lockedAngle
                    if (!_bypassSpin)
                    {
                        e->SetSpinVariation(Rnd(-_currentSpinVariation, _currentSpinVariation) + _currentSpin);    // @todo dan currentSpin?
                    }

                    // weight
                    if (!_bypassWeight)
                    {
                        e->SetWeight(GetEmitterWeight(0));
                        e->SetWeightVariation(Rnd(-_currentWeightVariation, _currentWeightVariation));
                        e->SetBaseWeight((_currentWeight + e->GetWeightVariation()) * _parentEffect->GetCurrentWeight());
                    }

                    // -------------------
                    if (_lockedAngle)
                    {
                        if (!_bypassWeight && !_bypassSpeed && !_parentEffect->IsBypassWeight())
                        {
                            e->SetSpeedVecX(sinf(e->GetEntityDirection() / 180.0f * (float)M_PI));
                            e->SetSpeedVecY(cosf(e->GetEntityDirection() / 180.0f * (float)M_PI));
                            e->SetAngle(Vector2::GetDirection(0, 0, e->GetSpeedVecX(), -e->GetSpeedVecY()));
                        }
                        else
                        {
                            if (_parentEffect->GetTraverseEdge())
                            {
                                e->SetAngle(_parentEffect->GetAngle() + _angleOffset);
                            }
                            else
                            {
                                e->SetAngle(e->GetEntityDirection() + _angle + _angleOffset);
                            }
                        }
                    }
                    else
                    {
                        switch (_angleType)
                        {
                        case AngAlign:
                            if (_parentEffect->GetTraverseEdge())
                                e->SetAngle(_parentEffect->GetAngle() + _angleOffset);
                            else
                                e->SetAngle(e->GetEntityDirection() + _angleOffset);
                            break;

                        case AngRandom:
                            e->SetAngle(Rnd((float)_angleOffset));
                            break;

                        case AngSpecify:
                            e->SetAngle((float)_angleOffset);
                            break;
                        }
                    }

                    // color settings
                    if (_randomColor)
                    {
                        float randomAge = Rnd((float)_cR->GetLastFrame());
                        e->SetRed((unsigned char)RandomizeR(e, randomAge));
                        e->SetGreen((unsigned char)RandomizeG(e, randomAge));
                        e->SetBlue((unsigned char)RandomizeB(e, randomAge));
                    }
                    else
                    {
                        e->SetRed((unsigned char)GetEmitterR(0));
                        e->SetGreen((unsigned char)GetEmitterG(0));
                        e->SetBlue((unsigned char)GetEmitterB(0));
                    }
                    e->SetEntityAlpha(e->GetEmitter()->GetEmitterAlpha(e->GetAge(), (float)e->GetLifeTime()) * _parentEffect->GetCurrentAlpha());

                    // blend mode
                    e->_blendMode = _blendMode;

                    // animation and framerate
                    e->_animating = _animate;
                    e->_animateOnce = _once;
                    e->_framerate = GetEmitterFramerate(0);
                    if (_randomStartFrame)
                        e->_currentFrame = Rnd((float)e->_avatar->GetFramesCount());
                    else
                        e->_currentFrame = (float)_currentFrame;

                    // add any sub children
                    //e->_runChildren = false;
                    // Effect
                    for (auto it = _effects.begin(); it != _effects.end(); ++it)
                    {
                        Effect* newEffect = new Effect(*static_cast<Effect*>(*it), pm);
                        newEffect->SetParent(e);
                        newEffect->SetParentEmitter(this);
                        newEffect->SetEffectLayer(e->_effectLayer);
                    }
                    _parentEffect->SetParticlesCreated(true);

                    // get the relative angle
                    if (!e->_relative)
                    {  // @todo dan Set(cosf(_angle  ??
                        float angle = _angle / 180.0f * (float)M_PI;
                        e->_matrix.Set(cosf(angle), sinf(angle), -sinf(angle), cosf(angle));
                        e->_matrix = e->_matrix.Transform(_parent->GetMatrix());
                    }
                    e->_relativeAngle = _parent->GetRelativeAngle() + e->_angle;
                    e->UpdateEntityRadius();
                    e->UpdateBoundingBox();
                        
                    // capture old values for tweening
                    e->Capture();

                } // if (e)
            } // for
            _counter -= intCounter;
        }
    } // Emitter::UpdateSpawns()

    void Emitter::ControlParticle( Particle *e )
    {

        // alpha change
        if (_alphaRepeat > 1)
        {
            e->_rptAgeA += EffectsLibrary::GetCurrentUpdateTime() * _alphaRepeat;
            e->_alpha = GetEmitterAlpha(e->_rptAgeA, (float)e->_lifeTime) * _parentEffect->GetCurrentAlpha();
            if (e->_rptAgeA > e->_lifeTime && e->_aCycles < _alphaRepeat)
            {
                e->_rptAgeA -= e->_lifeTime;
                ++e->_aCycles;
            }
        }
        else
        {
            e->_alpha = GetEmitterAlpha(e->_age, (float)e->_lifeTime) * _parentEffect->GetCurrentAlpha();
        }

        // angle changes
        if (_lockedAngle && _angleType == AngAlign)
        {
            if (e->_directionLocked)
            {
                e->_angle = _parentEffect->GetAngle() + _angle + _angleOffset;
            }
            else
            {
                if (!_bypassWeight && (!_parentEffect->IsBypassWeight() || e->_direction))
                {
                    if (e->_oldWX != e->_wx && e->_oldWY != e->_wy)
                    {
                        if (e->_relative)
                            e->_angle = Vector2::GetDirection(e->_oldX, e->_oldY, e->_x, e->_y);
                        else
                            e->_angle = Vector2::GetDirection(e->_oldWX, e->_oldWY, e->_wx, e->_wy);

                        if (fabsf(e->_oldAngle - e->_angle) > 180)
                        {
                            if (e->_oldAngle > e->_angle)
                                e->_oldAngle -= 360;
                            else
                                e->_oldAngle += 360;
                        }
                    }
                }
                else
                {
                    e->_angle = e->_direction + _angle + _angleOffset;
                }
            }
        }
        else
        {
            if (!_bypassSpin)
                e->_angle += (GetEmitterSpin(e->_age, (float)e->_lifeTime) * e->_spinVariation * _parentEffect->GetCurrentSpin()) / EffectsLibrary::GetCurrentUpdateTime();
        }

        // direction changes and motion randomness
        if (e->_directionLocked)
        {
            e->_direction = 90;
            switch (_parentEffect->GetClass())
            {
            case Effect::TypeLine:
                if (_parentEffect->GetDistanceSetByLife())
                {
                    float life = e->_age / e->_lifeTime;
                    e->_x = (life * _parentEffect->GetCurrentWidth()) - _parentEffect->GetHandleX();
                }
                else
                {
                    switch (_parentEffect->GetEndBehavior())
                    {
                    case Effect::EndKill:
                        if (e->_x > _parentEffect->GetCurrentWidth() - _parentEffect->GetHandleX() || e->_x < 0 - _parentEffect->GetHandleX())
                            e->_dead = 2;
                        break;

                    case Effect::EndLoopAround:
                        if (e->_x > _parentEffect->GetCurrentWidth() - _parentEffect->GetHandleX())
                        {
                            e->_x = (float)(-_parentEffect->GetHandleX());
                            e->MiniUpdate();
                            e->_oldX = e->_x;
                            e->_oldWX = e->_wx;
                            e->_oldWY = e->_wy;
                        }
                        else if (e->_x < 0 - _parentEffect->GetHandleX())
                        {
                            e->_x = _parentEffect->GetCurrentWidth() - _parentEffect->GetHandleX();
                            e->MiniUpdate();
                            e->_oldX = e->_x;
                            e->_oldWX = e->_wx;
                            e->_oldWY = e->_wy;
                        }
                        break;
					case Effect::EndLetFree:
						break;
                    }
                }
				break;
			default:
				break;
            }
        }
        else
        {
            if (!_bypassDirectionvariation)
            {
                float dv = e->_directionVariation * GetEmitterDirectionVariationOT(e->_age, (float)e->_lifeTime);
                e->_timeTracker += (int)EffectsLibrary::GetUpdateTime();
                if (e->_timeTracker > EffectsLibrary::motionVariationInterval)
                {
                    e->_randomDirection += EffectsLibrary::maxDirectionVariation * Rnd(-dv, dv);
                    e->_randomSpeed += EffectsLibrary::maxVelocityVariation * Rnd(-dv, dv);
                    e->_timeTracker = 0;
                }
            }
            e->_direction = e->_emissionAngle + GetEmitterDirection(e->_age, (float)e->_lifeTime) + e->_randomDirection;
        }

        // size changes
        if (!_bypassScaleX)
        {
            e->_scaleX = (GetEmitterScaleX(e->_age, (float)e->_lifeTime) * e->_gSizeX * e->_width) / _image->GetWidth();
        }
        if (_uniform)
        {
            if (!_bypassScaleX)
                e->_scaleY = e->_scaleX;
        }
        else
        {
            if (!_bypassScaleY)
            {
                e->_scaleY = (GetEmitterScaleY(e->_age, (float)e->_lifeTime) * e->_gSizeY * e->_height) / _image->GetHeight();
            }
        }

        // color changes
        if (!_bypassColor)
        {
            if (!_randomColor)
            {
                if (_colorRepeat > 1)
                {
                    e->_rptAgeC += EffectsLibrary::GetCurrentUpdateTime() * _colorRepeat;
                    e->_red = (unsigned char)GetEmitterR(e->_rptAgeC, (float)e->_lifeTime);
                    e->_green = (unsigned char)GetEmitterG(e->_rptAgeC, (float)e->_lifeTime);
                    e->_blue = (unsigned char)GetEmitterB(e->_rptAgeC, (float)e->_lifeTime);
                    if (e->_rptAgeC > e->_lifeTime && e->_cCycles < _colorRepeat)
                    {
                        e->_rptAgeC -= e->_lifeTime;
                        ++e->_cCycles;
                    }
                }
                else
                {
                    e->_red = (unsigned char)GetEmitterR(e->_age, (float)e->_lifeTime);
                    e->_green = (unsigned char)GetEmitterG(e->_age, (float)e->_lifeTime);
                    e->_blue = (unsigned char)GetEmitterB(e->_age, (float)e->_lifeTime);
                }
            }
        }

        // animation
        if (!_bypassFramerate)
            e->_framerate = GetEmitterFramerate(e->_age, (float)e->_lifeTime) * _animationDirection;

        // speed changes
        if (!_bypassSpeed)
        {
            e->_speed = GetEmitterVelocity(e->_age, (float)e->_lifeTime) * e->_baseSpeed * GetEmitterGlobalVelocity(_parentEffect->GetCurrentEffectFrame());
            e->_speed += e->_randomSpeed;
        }
        else
        {
            e->_speed = e->_randomSpeed;
        }

        // stretch
        if (!_bypassStretch)
        {
            if (!_bypassWeight && !_parentEffect->IsBypassWeight())
            {
                if (e->_speed != 0)
                {
                    e->_speedVec.x = e->_speedVec.x / EffectsLibrary::GetCurrentUpdateTime();
                    e->_speedVec.y = e->_speedVec.y / EffectsLibrary::GetCurrentUpdateTime() - e->_gravity;
                }
                else
                {
                    e->_speedVec.x = 0;
                    e->_speedVec.y = -e->_gravity;
                }

                if (_uniform)
                    e->_scaleY = (GetEmitterScaleX(e->_age, (float)e->_lifeTime) * e->_gSizeX * (e->_width + (fabsf(e->_speed) * GetEmitterStretch(e->_age, (float)e->_lifeTime) * _parentEffect->GetCurrentStretch()))) / _image->GetWidth();
                else
                    e->_scaleY = (GetEmitterScaleY(e->_age, (float)e->_lifeTime) * e->_gSizeY * (e->_height + (fabsf(e->_speed) * GetEmitterStretch(e->_age, (float)e->_lifeTime) * _parentEffect->GetCurrentStretch()))) / _image->GetHeight();
            }
            else
            {
                if (_uniform)
                    e->_scaleY = (GetEmitterScaleX(e->_age, (float)e->_lifeTime) * e->_gSizeX * (e->_width + (fabsf(e->_speed) * GetEmitterStretch(e->_age, (float)e->_lifeTime) * _parentEffect->GetCurrentStretch()))) / _image->GetWidth();
                else
                    e->_scaleY = (GetEmitterScaleY(e->_age, (float)e->_lifeTime) * e->_gSizeY * (e->_height + (fabsf(e->_speed) * GetEmitterStretch(e->_age, (float)e->_lifeTime) * _parentEffect->GetCurrentStretch()))) / _image->GetHeight();
            }

            if (e->_scaleY < e->_scaleX)
                e->_scaleY = e->_scaleX;
        }

        // weight changes
        if (!_bypassWeight)
            e->_weight = GetEmitterWeight(e->_age, (float)e->_lifeTime) * e->_baseWeight;
    }

    float Emitter::RandomizeR( Particle *e, float randomAge )
    {
        return _cR->GetOT(randomAge, (float)e->GetLifeTime(), false);
    }

    float Emitter::RandomizeG( Particle *e, float randomAge )
    {
        return _cG->GetOT(randomAge, (float)e->GetLifeTime(), false);
    }

    float Emitter::RandomizeB( Particle *e, float randomAge )
    {
        return _cB->GetOT(randomAge, (float)e->GetLifeTime(), false);
    }

    void Emitter::DrawCurrentFrame( float x /*= 0*/, float y /*= 0*/, float w /*= 128.0f*/, float h /*= 128.0f*/ )
    {
        if (_image)
        {
            /*
            SetAlpha(1.0f);
            SetBlend(_blendMode);
            SetImageHandle(_image->GetImage(), 0, 0);
            SetColor(255, 255, 255);
            SetScale(w / _image->GetWidth(), _image->GetHeight());
            _image->Draw(x, y, _frame);
            */
        }
    }

    void Emitter::CompileAll()
    {
        // base
        _cLife->Compile();
        _cLifeVariation->Compile();
        _cAmount->Compile();
        _cSizeX->Compile();
        _cSizeY->Compile();
        _cBaseSpeed->Compile();
        _cBaseWeight->Compile();
        _cBaseSpin->Compile();
        _cEmissionAngle->Compile();
        _cEmissionRange->Compile();
        _cSplatter->Compile();
        _cVelVariation->Compile();
        _cWeightVariation->Compile();
        _cAmountVariation->Compile();
        _cSizeXVariation->Compile();
        _cSizeYVariation->Compile();
        _cSpinVariation->Compile();
        _cDirectionVariation->Compile();
        // over lifetime
        float longestLife = GetLongestLife();
        _cAlpha->CompileOT(longestLife);
        _cR->CompileOT(longestLife);
        _cG->CompileOT(longestLife);
        _cB->CompileOT(longestLife);
        _cScaleX->CompileOT(longestLife);
        _cScaleY->CompileOT(longestLife);
        _cSpin->CompileOT(longestLife);
        _cVelocity->CompileOT(longestLife);
        _cWeight->CompileOT(longestLife);
        _cDirection->CompileOT(longestLife);
        _cDirectionVariationOT->CompileOT(longestLife);
        _cFramerate->CompileOT(longestLife);
        _cStretch->CompileOT(longestLife);
        // global adjusters
        _cGlobalVelocity->Compile();

        // Effect
        for (auto it = _effects.begin(); it != _effects.end(); ++it)
        {
            (*it)->CompileAll();
        }

        AnalyseEmitter();
    }

    void Emitter::CompileQuick()
    {
        float longestLife = GetLongestLife();

        _cAlpha->Clear(1);
        _cAlpha->SetCompiled(0, GetEmitterAlpha(0, longestLife));

        _cR->Clear(1);
        _cG->Clear(1);
        _cB->Clear(1);
        _cR->SetCompiled(0, GetEmitterR(0, longestLife));
        _cG->SetCompiled(0, GetEmitterG(0, longestLife));
        _cB->SetCompiled(0, GetEmitterB(0, longestLife));

        _cScaleX->Clear(1);
        _cScaleY->Clear(1);
        _cScaleX->SetCompiled(0, GetEmitterScaleX(0, longestLife));
        _cScaleY->SetCompiled(0, GetEmitterScaleY(0, longestLife));

        _cVelocity->Clear(1);
        _cVelocity->SetCompiled(0, GetEmitterVelocity(0, longestLife));

        _cWeight->Clear(1);
        _cWeight->SetCompiled(0, GetEmitterWeight(0, longestLife));

        _cDirection->Clear(1);
        _cDirection->SetCompiled(0, GetEmitterDirection(0, longestLife));

        _cDirectionVariationOT->Clear(1);
        _cDirectionVariationOT->SetCompiled(0, GetEmitterDirectionVariationOT(0, longestLife));

        _cFramerate->Clear(1);
        _cFramerate->SetCompiled(0, GetEmitterFramerate(0, longestLife));

        _cStretch->Clear(1);
        _cStretch->SetCompiled(0, GetEmitterStretch(0, longestLife));

        _cSplatter->Clear(1);
        _cSplatter->SetCompiled(0, GetEmitterSplatter(0));
    }

    void Emitter::AnalyseEmitter()
    {
        ResetBypassers();

        if (!_cLifeVariation->GetLastFrame() && !GetEmitterLifeVariation(0))
            _bypassLifeVariation = true;

        if (!GetEmitterStretch(0, 1.0f))
            _bypassStretch = true;

        if (!_cFramerate->GetLastFrame() && !GetEmitterSplatter(0))
            _bypassFramerate = true;

        if (!_cSplatter->GetLastFrame() && !_cSplatter->Get(0))
            _bypassSplatter = true;

        if (!_cBaseWeight->GetLastFrame() && !_cWeightVariation->GetLastFrame() && !GetEmitterBaseWeight(0) && !GetEmitterWeightVariation(0))
            _bypassWeight = true;

        if (!_cWeight->GetLastFrame() && !_cWeight->Get(0))
            _bypassWeight = true;

        if (!_cBaseSpeed->GetLastFrame() && !_cVelVariation->GetLastFrame() && !GetEmitterBaseSpeed(0) && !GetEmitterVelVariation(0))
            _bypassSpeed = true;

        if (!_cBaseSpin->GetLastFrame() && !_cSpinVariation->GetLastFrame() && !GetEmitterBaseSpin(0) && !GetEmitterSpinVariation(0))
            _bypassSpin = true;

        if (!_cDirectionVariation->GetLastFrame() && !GetEmitterDirectionVariation(0))
            _bypassDirectionvariation = true;

        if (_cR->GetAttributesCount() <= 1)
        {
            _bRed = GetEmitterR(0, 1.0f) != 0;             // @todo dan ???
            _bGreen = GetEmitterG(0, 1.0f) != 0;
            _bBlue = GetEmitterB(0, 1.0f) != 0;
            _bypassColor = true;
        }

        if (_cScaleX->GetAttributesCount() <= 1)
            _bypassScaleX = true;

        if (_cScaleY->GetAttributesCount() <= 1)
            _bypassScaleY = true;
    }

    void Emitter::ResetBypassers()
    {
        _bypassWeight = false;
        _bypassSpeed = false;
        _bypassSpin = false;
        _bypassDirectionvariation = false;
        _bypassColor = false;
        _bRed = false;
        _bGreen = false;
        _bBlue = false;
        _bypassScaleX = false;
        _bypassScaleY = false;
        _bypassLifeVariation = false;
        _bypassFramerate = false;
        _bypassStretch = false;
        _bypassSplatter = false;
    }

    float Emitter::GetLongestLife() const
    {
        float longestLife = ( _cLifeVariation->GetMaxValue() + _cLife->GetMaxValue() ) * _parentEffect->GetLifeMaxValue();
        /*
        float longestLife = 0;

        if (_cLife.GetLastFrame() >= _cLifeVariation.GetLastFrame() && _cLife.GetLastFrame() >= _parentEffect->GetLifeLastFrame())
        {
            for (int frame = 0; frame <= (int)_cLife.GetLastFrame(); ++frame)
            {
                float tempLife = (GetEmitterLifeVariation((float)frame) + GetEmitterLife((float)frame)) * _parentEffect->GetLife((float)frame);
                if (tempLife > longestLife) longestLife = tempLife;
            }
        }

        if (_cLifeVariation.GetLastFrame() >= _cLife.GetLastFrame() && _cLifeVariation.GetLastFrame() >= _parentEffect->GetLifeLastFrame())
        {
            for (int frame = 0; frame <= (int)_cLifeVariation.GetLastFrame(); ++frame)
            {
                float tempLife = (GetEmitterLifeVariation((float)frame) + GetEmitterLife((float)frame)) * _parentEffect->GetLife((float)frame);
                if (tempLife > longestLife) longestLife = tempLife;
            }
        }

        if (_parentEffect->GetLifeLastFrame() >= _cLife.GetLastFrame() && _parentEffect->GetLifeLastFrame() >= _cLifeVariation.GetLastFrame())
        {
            for (int frame = 0; frame <= (int)_parentEffect->GetLifeLastFrame(); ++frame)
            {
                float tempLife = (GetEmitterLifeVariation((float)frame) + GetEmitterLife((float)frame)) * _parentEffect->GetLife((float)frame);
                if (tempLife > longestLife) longestLife = tempLife;
            }
        }
*/
        return longestLife;
    }

    float Emitter::GetEmitterLife( float frame ) const
    {
        return _cLife->Get(frame);
    }

    float Emitter::GetEmitterLifeVariation( float frame ) const
    {
        return _cLifeVariation->Get(frame);
    }

    float Emitter::GetEmitterAmount( float frame ) const
    {
        return _cAmount->Get(frame);
    }

    float Emitter::GetEmitterSizeX( float frame ) const
    {
        return _cSizeX->Get(frame);
    }

    float Emitter::GetEmitterSizeY( float frame ) const
    {
        return _cSizeY->Get(frame);
    }

    float Emitter::GetEmitterBaseSpeed( float frame ) const
    {
        return _cBaseSpeed->Get(frame);
    }

    float Emitter::GetEmitterBaseWeight( float frame ) const
    {
        return _cBaseWeight->Get(frame);
    }

    float Emitter::GetEmitterBaseSpin( float frame ) const
    {
        return _cBaseSpin->Get(frame);
    }

    float Emitter::GetEmitterEmissionAngle( float frame ) const
    {
        return _cEmissionAngle->Get(frame);
    }

    float Emitter::GetEmitterEmissionRange( float frame ) const
    {
        return _cEmissionRange->Get(frame);
    }

    float Emitter::GetEmitterSplatter( float frame ) const
    {
        return _cSplatter->Get(frame);
    }

    float Emitter::GetEmitterVelVariation( float frame ) const
    {
        return _cVelVariation->Get(frame);
    }

    float Emitter::GetEmitterWeightVariation( float frame ) const
    {
        return _cWeightVariation->Get(frame);
    }

    float Emitter::GetEmitterAmountVariation( float frame ) const
    {
        return _cAmountVariation->Get(frame);
    }

    float Emitter::GetEmitterSizeXVariation( float frame ) const
    {
        return _cSizeXVariation->Get(frame);
    }

    float Emitter::GetEmitterSizeYVariation( float frame ) const
    {
        return _cSizeYVariation->Get(frame);
    }

    float Emitter::GetEmitterSpinVariation( float frame ) const
    {
        return _cSpinVariation->Get(frame);
    }

    float Emitter::GetEmitterDirectionVariation( float frame ) const
    {
        return _cDirectionVariation->Get(frame);
    }

    float Emitter::GetEmitterAlpha( float age, float lifetime ) const
    {
        return _cAlpha->GetOT(age, lifetime);
    }

    float Emitter::GetEmitterR( float age, float lifetime ) const
    {
        return _cR->GetOT(age, lifetime);
    }

    float Emitter::GetEmitterG( float age, float lifetime ) const
    {
        return _cG->GetOT(age, lifetime);
    }

    float Emitter::GetEmitterB( float age, float lifetime ) const
    {
        return _cB->GetOT(age, lifetime);
    }

    float Emitter::GetEmitterScaleX( float age, float lifetime ) const
    {
        return _cScaleX->GetOT(age, lifetime);
    }

    float Emitter::GetEmitterScaleY( float age, float lifetime ) const
    {
        return _cScaleY->GetOT(age, lifetime);
    }

    float Emitter::GetEmitterSpin( float age, float lifetime ) const
    {
        return _cSpin->GetOT(age, lifetime);
    }

    float Emitter::GetEmitterVelocity( float age, float lifetime ) const
    {
        return _cVelocity->GetOT(age, lifetime);
    }

    float Emitter::GetEmitterWeight( float age, float lifetime ) const
    {
        return _cWeight->GetOT(age, lifetime);
    }

    float Emitter::GetEmitterDirection( float age, float lifetime ) const
    {
        return _cDirection->GetOT(age, lifetime);
    }

    float Emitter::GetEmitterDirectionVariationOT( float age, float lifetime ) const
    {
        return _cDirectionVariationOT->GetOT(age, lifetime);
    }

    float Emitter::GetEmitterFramerate( float age, float lifetime ) const
    {
        return _cFramerate->GetOT(age, lifetime);
    }

    float Emitter::GetEmitterStretch( float age, float lifetime ) const
    {
        return _cStretch->GetOT(age, lifetime);
    }

    float Emitter::GetEmitterGlobalVelocity( float frame )
    {
        return _cGlobalVelocity->Get(frame);
    }

    const std::list<Effect*>& Emitter::GetEffects() const
    {
        return _effects;
    }

    bool Emitter::IsDying() const
    {
        return _dying;
    }

    void Emitter::SetPath( const char *path )
    {
        _path = path;
    }

} // namespace TLFX

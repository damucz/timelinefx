#include "TLFXParticle.h"
#include "TLFXEmitter.h"
#include "TLFXParticleManager.h"
#include "TLFXEffect.h"
#include "TLFXEffectsLibrary.h"         // TLFXLOG

namespace TLFX
{

    Particle::Particle()
        : _emitter(NULL)

        , _weightVariation(0)
        , _scaleVariationX(0)
        , _scaleVariationY(0)
        , _gSizeX(0)
        , _gSizeY(0)

        , _velVariation(0)
        , _spinVariation(0)

        , _directionVariation(0)
        , _timeTracker(0)
        , _randomDirection(0)
        , _randomSpeed(0)
        , _emissionAngle(0)
        , _releaseSingleParticle(false)

        , _particleManager(NULL)
        , _layer(0)
        , _groupParticles(false)
        , _effectLayer(0)
    {

    }

    bool Particle::Update()
    {
        TLFXLOG(PARTICLES, ("particle #%p update", this));

        Capture();

        if (_emitter->IsDying() || _emitter->IsOneShot() || _dead)
            _releaseSingleParticle = true;

        if (_emitter->IsSingleParticle() && !_releaseSingleParticle)
        {
            _age = _particleManager->GetCurrentTime() - _dob;
            if (_age > _lifeTime)
            {
                _age = 0;
                _dob = _particleManager->GetCurrentTime();
            }
        }
        else
        {
            _age = _particleManager->GetCurrentTime() - _dob;
        }

        base::Update();

        if (_age > _lifeTime || _dead == 2)                 // if dead=2 then that means its reached the end of the line (in kill mode) for line traversal effects
        {
            _dead = 1;
            if (_children.empty())
            {
                _particleManager->ReleaseParticle(this);
                if (_emitter->IsGroupParticles())
                    _emitter->GetParentEffect()->RemoveInUse(_layer, this);

                Reset();
                return false;               // RemoveChild
            }
            else
            {
                _emitter->ControlParticle(this);
                KillChildren();
            }

            return true;
        }

        _emitter->ControlParticle(this);
        return true;
    }

    void Particle::Reset()
    {
        _age = 0;
        _wx = 0;
        _wy = 0;
        _z = 1.0f;
        _avatar = NULL;
        _dead = 0;
        ClearChildren();
        _directionVariation = 0;
        _direction = 0;
        _directionLocked = false;
        _randomSpeed = 0;
        _randomDirection = 0;
        _parent = NULL;
        _rootParent = NULL;
        _aCycles = 0;
        _cCycles = 0;
        _rptAgeA = 0;
        _rptAgeC = 0;
        _releaseSingleParticle = false;
        _gravity = 0;
        _weight = 0;
        _emitter = NULL;
    }

    void Particle::Destroy(bool releaseChildren)
    {
        _particleManager->ReleaseParticle(this);
        base::Destroy();
        Reset();
    }

    void Particle::SetX( float x )
    {
        if (_age > 0)
            _oldX = _x;
        else
            _oldX = x;
        _x = x;
    }

    void Particle::SetY( float y )
    {
        if (_age > 0)
            _oldY = _y;
        else
            _oldY = y;
        _y = y;
    }

    void Particle::SetZ( float z )
    {
        if (_age > 0)
            _oldZ = _z;
        else
            _oldZ = z;
        _z = z;
    }

    void Particle::SetGroupParticles( bool value )
    {
        _groupParticles = value;
    }

    bool Particle::IsGroupParticles() const
    {
        return _groupParticles;
    }

    int Particle::GetEffectLayer() const
    {
        return _effectLayer;
    }

    void Particle::SetLayer( int layer )
    {
        _layer = layer;
    }

    int Particle::GetLayer() const
    {
        return _layer;
    }

    Emitter* Particle::GetEmitter() const
    {
        return _emitter;
    }

    void Particle::SetReleaseSingleParticles( bool value )
    {
        _releaseSingleParticle = value;
    }

    void Particle::SetEmitter( Emitter *e )
    {
        _emitter = e;
    }

    void Particle::SetParticleManager( ParticleManager *pm )
    {
        _particleManager = pm;
    }

    void Particle::SetEffectLayer( int layer )
    {
        _effectLayer = layer;
    }

    void Particle::SetVelVariation( float velVariation )
    {
        _velVariation = velVariation;
    }

    float Particle::GetVelVariation() const
    {
        return _velVariation;
    }

    void Particle::SetGSizeX( float gSizeX )
    {
        _gSizeX = gSizeX;
    }

    void Particle::SetGSizeY( float gSizeY )
    {
        _gSizeY = gSizeY;
    }

    float Particle::GetGSizeX() const
    {
        return _gSizeX;
    }

    float Particle::GetGSizeY() const
    {
        return _gSizeY;
    }

    void Particle::SetScaleVariationX( float scaleVarX )
    {
        _scaleVariationX = scaleVarX;
    }

    float Particle::GetScaleVariationX() const
    {
        return _scaleVariationX;
    }

    void Particle::SetScaleVariationY( float scaleVarY )
    {
        _scaleVariationY = scaleVarY;
    }

    float Particle::GetScaleVariationY() const
    {
        return _scaleVariationY;
    }

    void Particle::SetEmissionAngle( float emissionAngle )
    {
        _emissionAngle = emissionAngle;
    }

    float Particle::GetEmissionAngle() const
    {
        return _emissionAngle;
    }

    void Particle::SetDirectionVairation( float dirVar )
    {
        _directionVariation = dirVar;
    }

    float Particle::GetDirectionVariation() const
    {
        return _directionVariation;
    }

    void Particle::SetSpinVariation( float spinVar )
    {
        _spinVariation = spinVar;
    }

    float Particle::GetSpinVariation() const
    {
        return _spinVariation;
    }

    void Particle::SetWeightVariation( float weightVar )
    {
        _weightVariation = weightVar;
    }

    float Particle::GetWeightVariation() const
    {
        return _weightVariation;
    }

} // namespace TLFX

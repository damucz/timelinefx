#include "TLFXEntity.h"
#include "TLFXEffectsLibrary.h"         // "globals"
#include "TLFXAnimImage.h"
#include "TLFXAttributeNode.h"

#include <cmath>
#include <cassert>

namespace TLFX
{

    Entity::Entity()
        : _x(0), _y(0)
        , _oldX(0), _oldY(0)
        , _wx(0), _wy(0)
        , _oldWX(0), _oldWY(0)
        , _z(1.0f)
        , _oldZ(1.0f)
        , _relative(true)

        , _r(0), _g(0), _b(0)
        , _red(255), _green(255), _blue(255)
        , _oldRed(255), _oldGreen(255), _oldBlue(255)


        , _width(0), _height(0)
        , _weight(0)
        , _gravity(0)
        , _baseWeight(0)
        , _oldWeight(0)
        , _scaleX(1.0f), _scaleY(1.0f)
        , _sizeX(1.0f), _sizeY(1.0f)
        , _oldScaleX(1.0f), _oldScaleY(1.0f)

        , _speed(0)
        , _baseSpeed(0)
        , _oldSpeed(0)
        , _updateSpeed(true)

        , _direction(0)
        , _directionLocked(false)
        , _angle(0)
        , _oldAngle(0)
        , _relativeAngle(0)
        , _oldRelativeAngle(0)

        , _avatar(NULL)
        , _frameOffset(0)
        , _framerate(1.0f)
        , _currentFrame(0)
        , _oldCurrentFrame(0)
        , _animating(false)
        , _animateOnce(false)
        , _animAction(0)
        , _handleX(0)
        , _handleY(0)
        , _autoCenter(true)
        , _okToRender(true)

        , _dob(0)
        , _age(0)
        , _rptAgeA(0)
        , _rptAgeC(0)
        , _aCycles(0)
        , _cCycles(0)
        , _oldAge(0)
        , _dead(0)
        , _destroyed(false)
        , _lifeTime(0)
        , _timediff(0)

        , _AABB_Calculate(true)
        , _collisionXMin(0)
        , _collisionYMin(0)
        , _collisionXMax(0)
        , _collisionYMax(0)
        , _AABB_XMin(0)
        , _AABB_YMin(0)
        , _AABB_XMax(0)
        , _AABB_YMax(0)
        , _AABB_MaxWidth(0)
        , _AABB_MaxHeight(0)
        , _AABB_MinWidth(0)
        , _AABB_MinHeight(0)
        , _radiusCalculate(true)
        , _imageRadius(0)
        , _entityRadius(0)
        , _imageDiameter(0)

        , _parent(NULL)
        , _rootParent(NULL)

        , _blendMode(BMAlphaBlend)

        , _alpha(1.0f)
        , _oldAlpha(0)

        , _runChildren(false)
        , _pixelsPerSecond(0)
    {

    }

    Entity::Entity( const Entity& o )
        : _x(o._x)
        , _y(o._y)
        , _oldX(o._oldX)
        , _oldY(o._oldY)
        , _wx(o._wx)
        , _wy(o._wy)
        , _oldWX(o._oldWX)
        , _oldWY(o._oldWY)
        , _z(o._z)
        , _oldZ(o._oldZ)
        , _relative(o._relative)

        , _matrix(o._matrix)
        , _spawnMatrix(o._spawnMatrix)
        , _rotVec(o._rotVec)
        , _speedVec(o._speedVec)
        , _gravVec(o._gravVec)

        , _name(o._name)

        , _r(o._r)
        , _g(o._g)
        , _b(o._b)
        , _red(o._red)
        , _green(o._green)
        , _blue(o._blue)
        , _oldRed(o._oldRed)
        , _oldGreen(o._oldGreen)
        , _oldBlue(o._oldBlue)

        , _width(o._width)
        , _height(o._height)
        , _weight(o._weight)
        , _gravity(o._gravity)
        , _baseWeight(o._baseWeight)
        , _oldWeight(o._oldWeight)
        , _scaleX(o._scaleX)
        , _scaleY(o._scaleY)
        , _sizeX(o._sizeX)
        , _sizeY(o._sizeY)
        , _oldScaleX(o._oldScaleX)
        , _oldScaleY(o._oldScaleY)

        , _speed(o._speed)
        , _baseSpeed(o._baseSpeed)
        , _oldSpeed(o._oldSpeed)
        , _updateSpeed(o._updateSpeed)

        , _direction(o._direction)
        , _directionLocked(o._directionLocked)
        , _angle(o._angle)
        , _oldAngle(o._oldAngle)
        , _relativeAngle(o._relativeAngle)
        , _oldRelativeAngle(o._oldRelativeAngle)

        , _avatar(o._avatar)
        , _frameOffset(o._frameOffset)
        , _framerate(o._framerate)
        , _currentFrame(o._currentFrame)
        , _oldCurrentFrame(o._oldCurrentFrame)
        , _animating(o._animating)
        , _animateOnce(o._animateOnce)
        , _animAction(o._animAction)
        , _handleX(o._handleX)
        , _handleY(o._handleY)
        , _autoCenter(o._autoCenter)
        , _okToRender(o._okToRender)

        , _dob(o._dob)
        , _age(o._age)
        , _rptAgeA(o._rptAgeA)
        , _rptAgeC(o._rptAgeC)
        , _aCycles(o._aCycles)
        , _cCycles(o._cCycles)
        , _oldAge(o._oldAge)
        , _dead(o._dead)
        , _destroyed(o._destroyed)
        , _lifeTime(o._lifeTime)
        , _timediff(o._timediff)

        , _AABB_Calculate(o._AABB_Calculate)
        , _collisionXMin(o._collisionXMin)
        , _collisionYMin(o._collisionYMin)
        , _collisionXMax(o._collisionXMax)
        , _collisionYMax(o._collisionYMax)
        , _AABB_XMin(o._AABB_XMin)
        , _AABB_YMin(o._AABB_YMin)
        , _AABB_XMax(o._AABB_XMax)
        , _AABB_YMax(o._AABB_YMax)
        , _AABB_MaxWidth(o._AABB_MaxWidth)
        , _AABB_MaxHeight(o._AABB_MaxHeight)
        , _AABB_MinWidth(o._AABB_MinWidth)
        , _AABB_MinHeight(o._AABB_MinHeight)
        , _radiusCalculate(o._radiusCalculate)
        , _imageRadius(o._imageRadius)
        , _entityRadius(o._entityRadius)
        , _imageDiameter(o._imageDiameter)

        , _parent(NULL)
        , _rootParent(NULL)

        , _blendMode(o._blendMode)

        , _alpha(o._alpha)
        , _oldAlpha(o._oldAlpha)

        , _runChildren(o._runChildren)

        , _pixelsPerSecond(o._pixelsPerSecond)
    {
        // do not copy children as we don't know their type
        // Emitter and Effect should take care about this
    }

    bool Entity::IsDestroyed() const
    {
        return _destroyed;
    }

    void Entity::SetName( const char *name )
    {
        _name = name;
    }

    const char * Entity::GetName() const
    {
        return _name.c_str();
    }

    bool Entity::Update()
    {
        float currentUpdateTime = EffectsLibrary::GetCurrentUpdateTime();

        // Update speed in pixels per second
        if (_updateSpeed && _speed)
        {
            _pixelsPerSecond = _speed / currentUpdateTime;
            _speedVec.x = sinf(_direction / 180.0f * (float)M_PI) * _pixelsPerSecond;
            _speedVec.y = cosf(_direction / 180.0f * (float)M_PI) * _pixelsPerSecond;

            _x += _speedVec.x * _z;
            _y -= _speedVec.y * _z;
        }

        // update the gravity
        if (_weight != 0)
        {
            _gravity += _weight / currentUpdateTime;
            _y += (_gravity / currentUpdateTime) * _z;
        }

        // set the matrix if it is relative to the parent
        if (_relative)
            _matrix.Set(cosf(_angle / 180.f * (float)M_PI), sinf(_angle / 180.0f * (float)M_PI), -sinf(_angle / 180.0f * (float)M_PI), cosf(_angle / 180.0f * (float)M_PI));

        // calculate where the entity is in the world
        if (_parent && _relative)
        {
            _z = _parent->_z;
            _matrix = _matrix.Transform(_parent->_matrix);
            Vector2 rotVec = _parent->_matrix.TransformVector(Vector2(_x, _y));
            if (_z != 1.0f)
            {
                _wx = _parent->_wx + rotVec.x * _z;
                _wy = _parent->_wy + rotVec.y * _z;
            }
            else
            {
                _wx = _parent->_wx + rotVec.x;
                _wy = _parent->_wy + rotVec.y;
            }
            _relativeAngle = _parent->_relativeAngle + _angle;
        }
        else
        {
            // If parent setz(parent.z)
            _wx = _x;
            _wy = _y;
        }

        if (!_parent)
            _relativeAngle = _angle;

        // update animation frame
        if (_avatar && _animating)
        {
            _currentFrame += _framerate / currentUpdateTime;
            if (_animateOnce)
            {
                if (_currentFrame > _avatar->GetFramesCount() - 1)
                {
                    _currentFrame = (float)(_avatar->GetFramesCount() - 1);
                }
                else if (_currentFrame <= 0)
                {
                    _currentFrame = 0;
                }
            }
        }

        // update the Axis Aligned Bounding Box
        if (_AABB_Calculate)
            UpdateBoundingBox();

        // update the radius of influence
        if (_radiusCalculate)
            UpdateEntityRadius();

        // update the children
        UpdateChildren();

        return true;
    }

    void Entity::SetX(float x)
    {
        _x = x;
    }

    float Entity::GetX() const
    {
        return _x;
    }

    void Entity::SetY( float y )
    {
        _y = y;
    }

    float Entity::GetY() const
    {
        return _y;
    }

    void Entity::SetZ( float z )
    {
        _z = z;
    }

    float Entity::GetZ() const
    {
        return _z;
    }

    const Matrix2& Entity::GetMatrix() const
    {
        return _matrix;
    }

    Matrix2& Entity::GetMatrix()
    {
        return _matrix;
    }

    void Entity::MiniUpdate()
    {
        _matrix.Set(cosf(_angle / 180.0f * (float)M_PI), sinf(_angle / 180.f * (float)M_PI), -sinf(_angle / 180.0f * (float)M_PI), cosf(_angle / 180.0f * (float)M_PI));

        if (_parent && _relative)
        {
            _z = _parent->_z;
            _matrix = _matrix.Transform(_parent->_matrix);
            Vector2 rotVec = _parent->_matrix.TransformVector(Vector2(_x, _y));
            if (_z != 1.0f)
            {
                _wx = _parent->_wx + rotVec.x * _z;
                _wy = _parent->_wy + rotVec.y * _z;
            }
            else
            {
                _wx = _parent->_wx + rotVec.x;
                _wy = _parent->_wy + rotVec.y;
            }
        }
        else
        {
            if (_parent)
                _z = _parent->_z;
            _wx = _x;
            _wy = _y;
        }
    }

    void Entity::UpdateChildren()
    {
        for (auto it = _children.begin(); it != _children.end(); )
        {
            if (!(*it)->Update())
                it = _children.erase(it);
            else
                ++it;
        }
    }

    void Entity::Capture()
    {
        _oldZ = _z;
        _oldWX = _wx;
        _oldWY = _wy;
        _oldX = _x;
        _oldY = _y;
        _oldAngle = _angle;
        _oldRelativeAngle = _relativeAngle;
        _oldScaleX = _scaleX;
        _oldScaleY = _scaleY;
        _oldCurrentFrame = _currentFrame;
    }

    void Entity::CaptureAll()
    {
        Capture();
        for (auto it = _children.begin(); it != _children.end(); ++it)
        {
            (*it)->Capture();
        }
    }

    void Entity::UpdateBoundingBox()
    {
        if (_z != 1.0f)
        {
            _collisionXMin = _AABB_MinWidth * _scaleX * _z;
            _collisionYMin = _AABB_MinHeight * _scaleY * _z;
            _collisionXMax = _AABB_MaxWidth * _scaleX * _z;
            _collisionYMax = _AABB_MaxHeight * _scaleY * _z;
        }
        else
        {
            _collisionXMin = _AABB_MinWidth * _scaleX;
            _collisionYMin = _AABB_MinHeight * _scaleY;
            _collisionXMax = _AABB_MaxWidth * _scaleX;
            _collisionYMax = _AABB_MaxHeight * _scaleY;
        }

        _AABB_XMin = _collisionXMin;
        _AABB_YMin = _collisionYMin;
        _AABB_XMax = _collisionXMax;
        _AABB_YMax = _collisionYMax;

        if (_children.empty())
            UpdateParentBoundingBox();
    }

    void Entity::UpdateEntityRadius()
    {
        if (_autoCenter)
        {
            if (_avatar)
            {
                float aMaxRadius = _avatar->GetMaxRadius();
                float aWidth = _avatar->GetWidth();
                float aHeight = _avatar->GetHeight();

                if (aMaxRadius != 0)
                    _imageRadius = std::max(aMaxRadius * _scaleX * _z, aMaxRadius * _scaleY * _z);
                else
                    _imageRadius = Vector2::GetDistance(aWidth / 2.0f * _scaleX * _z, aHeight / 2.0f * _scaleY * _z, aWidth * _scaleX * _z, aHeight * _scaleY * _z);
            }
            else
            {
                _imageRadius = 0;
            }
        }
        else
        {
            float aMaxRadius = _avatar->GetMaxRadius();
            float aWidth = _avatar->GetWidth();
            float aHeight = _avatar->GetHeight();

            if (aMaxRadius != 0)
                _imageRadius = Vector2::GetDistance(_handleX * _scaleX * _z, _handleY * _scaleY * _z, aWidth / 2.0f * _scaleX * _z, aHeight / 2.0f * _scaleY * _z)
                               + std::max(aMaxRadius * _scaleX * _z, aMaxRadius * _scaleY * _z);
            else
                _imageRadius = Vector2::GetDistance(_handleX * _scaleX * _z, _handleY * _scaleY * _z, aWidth * _scaleX * _z, aHeight * _scaleY * _z);
        }

        _entityRadius = _imageRadius;
        _imageDiameter = _imageRadius * 2.0f;

        if (_rootParent)
            UpdateRootParentEntityRadius();
    }

    void Entity::UpdateParentEntityRadius()
    {
        if (_parent)
        {
            if (!_children.empty())
                _parent->_entityRadius += std::max(0.0f, Vector2::GetDistance(_wx, _wy, _parent->_wx, _parent->_wy) + _entityRadius - _parent->_entityRadius);
            else
                _parent->_entityRadius += std::max(0.0f, Vector2::GetDistance(_wx, _wy, _parent->_wx, _parent->_wy) + _imageRadius - _parent->_entityRadius);
            // DebugLog name + " - Radius: " + entity_Radius + " | Distance to Parent: " + getdistance(wx, wy, parent.wx, parent.wy)
            _parent->UpdateParentEntityRadius();
        }
    }

    void Entity::UpdateRootParentEntityRadius()
    {
        if (_rootParent)
        {
            if (_alpha != 0)
                _rootParent->_entityRadius += std::max(0.0f, Vector2::GetDistance(_wx, _wy, _rootParent->_wx, _rootParent->_wy) + _imageRadius - _rootParent->_entityRadius);
            // DebugLog name + " - Radius: " + entity_Radius + " | Distance to Parent: " + getdistance(wx, wy, rootparent.wx, rootparent.wy)
        }
    }

    void Entity::UpdateParentBoundingBox()
    {
        if (_parent)
        {
            _parent->_AABB_XMax += std::max(0.0f, _wx - _parent->_wx + _AABB_XMax - _parent->_AABB_XMax);
            _parent->_AABB_YMax += std::max(0.0f, _wy - _parent->_wx + _AABB_YMax - _parent->_AABB_YMax);
            _parent->_AABB_XMin += std::max(0.0f, _wx - _parent->_wx + _AABB_XMin - _parent->_AABB_XMin);
            _parent->_AABB_YMin += std::max(0.0f, _wy - _parent->_wy + _AABB_YMin - _parent->_AABB_YMin);
        }
    }

    void Entity::AssignRootParent( Entity* e )
    {
        if (_parent)
            _parent->AssignRootParent(e);
        else
            e->_rootParent = this;
    }

    void Entity::DrawBoundingBox()
    {
        /*
        SetScale(1.0f, 1.0f);
        SetRotation(0);
        SetAlpha(0.5f);
        SetColor(255, 0, 255);
        DrawOval(_wx - _imageRadius, _wy - _imageRadius, _imageRadius * 2.0f, _imageRadius * 2.0f);
        */
    }

    void Entity::DrawEntityBoundary()
    {
        /*
        SetScale(1.0f, 1.0f);
        SetRotation(0);
        SetScale(0.5f);
        SetColor(255, 0, 255);
        DrawOval(_wx - _entityRadius, _wy - _entityRadius, _entityRadius * 2.0f, _entityRadius * 2.0f);
        */
    }

    void Entity::Zoom( float zoom )
    {
        _z += zoom;
        _oldZ = _z;
    }

    void Entity::AddChild( Entity *e )
    {
        _children.push_back(e);
        e->_parent = this;
        e->_radiusCalculate = _radiusCalculate;
        e->AssignRootParent(e);
    }

    void Entity::Destroy(bool releaseChildren)
    {
        _parent = NULL;
        _avatar = NULL;
        _rootParent = NULL;
        for (auto it = _children.begin(); it != _children.end(); ++it)
        {
            (*it)->Destroy(releaseChildren);
            if (releaseChildren) delete *it;
        }
        _children.clear();
        _destroyed = true;
    }

    void Entity::RemoveChild( Entity* e )
    {
        _children.remove(e);
        e->_parent = NULL;
    }

    void Entity::ClearChildren()
    {
        for (auto it = _children.begin(); it != _children.end(); ++it)
        {
            (*it)->Destroy();
            delete *it;
        }
        _children.clear();
    }

    void Entity::KillChildren()
    {
        for (auto it = _children.begin(); it != _children.end(); ++it)
        {
            (*it)->KillChildren();
            (*it)->_dead = 1;
        }
    }

    void Entity::Rotate( float degrees )
    {
        _angle += degrees;
    }

    void Entity::Move( float xamount, float yamount )
    {
        _x += xamount;
        _y += yamount;
    }

    int Entity::GetRed() const
    {
        return _red;
    }

    void Entity::SetRed( unsigned char r )
    {
        _red = r;
    }

    int Entity::GetGreen() const
    {
        return _green;
    }

    void Entity::SetGreen( unsigned char g )
    {
        _green = g;
    }

    int Entity::GetBlue() const
    {
        return _blue;
    }

    void Entity::SetBlue( unsigned char b )
    {
        _blue = b;
    }

    void Entity::SetEntityColor( unsigned char r, unsigned char g, unsigned char b )
    {
        _red = r;
        _green = g;
        _blue = b;
    }

    float Entity::GetEntityAlpha() const
    {
        return _alpha;
    }

    float Entity::GetImageRadius() const
    {
        return _imageRadius;
    }

    float Entity::GetEntityRadius() const
    {
        return _entityRadius;
    }

    void Entity::SetEntityAlpha( float alpha )
    {
        _alpha = alpha;
    }

    void Entity::SetPosition( float x, float y )
    {
        _x = x;
        _y = y;
    }

    void Entity::SetWX( float wx )
    {
        _wx = wx;
    }

    void Entity::SetWY( float wy )
    {
        _wy = wy;
    }

    void Entity::SetAutocenter( bool value )
    {
        _autoCenter = value;
    }

    void Entity::SetAngle( float degrees )
    {
        _angle = degrees;
    }

    void Entity::SetBlendMode( BlendMode mode )
    {
        _blendMode = mode;
    }

    void Entity::SetBlendMode( int mode )
    {
        _blendMode = BMAlphaBlend;
        switch (mode)
        {
        case 3: break;              // nothing, default is already set
        case 4: _blendMode = BMLightBlend; break;
        default:
            assert(false);              // not supported
        }
    }

    void Entity::SetHandleX( int x )
    {
        _handleX = x;
    }

    void Entity::SetHandleY( int y )
    {
        _handleY = y;
    }

    void Entity::SetParent( Entity* e )
    {
        e->AddChild(this);
    }

    void Entity::SetRelative( bool value )
    {
        _relative = value;
    }

    void Entity::SetEntityScale( float sx, float sy )
    {
        _scaleX = sx;
        _scaleY = sy;
    }

    void Entity::SetSpeed( float speed )
    {
        _speed = speed;
    }

    float Entity::GetSpeed() const
    {
        return _speed;
    }

    bool Entity::IsRadiusCalculate() const
    {
        return _radiusCalculate;
    }

    void Entity::SetRadiusCalculate( bool value )
    {
        _radiusCalculate = value;
        for (auto it = _children.begin(); it != _children.end(); ++it)
            (*it)->SetRadiusCalculate(value);
    }

    float Entity::GetFramerate() const
    {
        return _framerate;
    }

    void Entity::SetFramerate( float framerate )
    {
        _framerate = framerate;
    }

    bool Entity::IsAnimating() const
    {
        return _animating;
    }

    void Entity::SetAnimating( bool value )
    {
        _animating = value;
    }

    float Entity::GetCurrentFrame() const
    {
        return _currentFrame;
    }

    void Entity::SetCurrentFrame(float frame)
    {
        _currentFrame = frame;
    }

    void Entity::SetAvatar( AnimImage *avatar )
    {
        _avatar = avatar;
        _AABB_MaxWidth = _avatar->GetWidth() * 0.5f;
        _AABB_MaxHeight = _avatar->GetHeight() * 0.5f;
        _AABB_MinWidth = _avatar->GetWidth() * -0.5f;
        _AABB_MinHeight = _avatar->GetHeight() * -0.5f;
    }

    void Entity::SetAnimateOnce( bool value )
    {
        _animateOnce = value;
    }

    void Entity::SetUpdateSpeed( bool value )
    {
        _updateSpeed = value;
    }

    float Entity::GetAngle() const
    {
        return _angle;
    }

    int Entity::GetHandleX() const
    {
        return _handleX;
    }

    int Entity::GetHandleY() const
    {
        return _handleY;
    }

    Entity::BlendMode Entity::GetBlendMode() const
    {
        return _blendMode;
    }

    bool Entity::IsRelative() const
    {
        return _relative;
    }

    void Entity::GetEntityScale( float& sx, float& sy ) const
    {
        sx = _scaleX;
        sy = _scaleY;
    }

    AnimImage* Entity::GetAvatar() const
    {
        return _avatar;
    }

    Entity* Entity::GetParent() const
    {
        return _parent;
    }

    const std::list<Entity*>& Entity::GetChildren() const
    {
        return _children;
    }

    int Entity::GetLifeTime() const
    {
        return _lifeTime;
    }

    void Entity::SetLifeTime( int lifeTime )
    {
        _lifeTime = lifeTime;
    }

    float Entity::GetAge() const
    {
        return _age;
    }

    void Entity::SetAge( float age )
    {
        _age = age;
    }

    void Entity::Decay( float milliseconds )
    {
        _age += milliseconds;
    }

    float Entity::GetWX() const
    {
        return _wx;
    }

    float Entity::GetWY() const
    {
        return _wy;
    }

    float Entity::GetEntityDirection() const
    {
        return _direction;
    }

    void Entity::SetEntityDirection( float direction )
    {
        _direction = direction;
    }

    bool Entity::IsOKToRender() const
    {
        return _okToRender;
    }

    void Entity::SetOKtoRender( bool value )
    {
        _okToRender = value;
    }

    bool Entity::IsBoundingBox() const
    {
        return _AABB_Calculate;
    }

    void Entity::CalculateBoundingBox( bool value /*= true*/ )
    {
        _AABB_Calculate = value;
    }

    void Entity::Render( float tween )
    {
        /*
        if (_avatar && _okToRender)
        {
            if (_autoCenter)
            {
                if (_avatar->GetFramesCount() == 1)
                    MidHandleImage(_avatar->GetImage());
                else
                    SetImageHandle(_avatar->GetImage(), _avatar->GetWidth() / 2.0f, _avatar->GetHeight() / 2.0f);
            }
            else
            {
                SetImageHandle(_avatar->GetImage(), _handleX, _handleY);
            }

            SetBlend(_blendMode);
            
            float tv = TweenValues(_oldAngle, _angle, tween);
            SetRotation(tv);

            float tx = TweenValues(_oldScaleX, _scaleX, tween);
            float ty = TweenValues(_oldScaleY, _scaleY, tween);
            float tz = TweenValues(_oldZ, _z, tween);
            if (tz != 1.0f)
                SetScale(tx * tz, ty * tz);
            else
                SetScale(tx, ty);

            SetColor(_red, _green, _blue);
            SetAlpha(_alpha);

            if (_animating)
            {
                tv = TweenValues(_oldCurrentFrame, _currentFrame, tween) % _avatar->GetFramesCount();
                if (tv < 0)
                    tv = _avatar->GetFramesCount() - absf(tv);
            }
            else
            {
                tv = _currentFrame;
            }

            DrawSprite(_avatar, TweenValues(_oldWX, _wx, tween), TweenValues(_oldWY, _wy, tween), tv % _avatar->GetFramesCount());
        }

        for (auto it = _children.begin(); it != _children.end(); ++it)
        {
            (*it)->Render(tween);
        }
        */
    }

    float Entity::TweenValues( float oldValue, float value, float tween )
    {
        return oldValue + (value - oldValue) * tween;
    }

    int Entity::GetChildCount() const
    {
        return (int)_children.size();
    }

    float Entity::GetRelativeAngle() const
    {
        return _relativeAngle;
    }

    float Entity::Rnd( float range )
    {
        return range / RAND_MAX * rand();
    }

    float Entity::Rnd( float min, float max )
    {
        return (max - min) / RAND_MAX * rand() + min;
    }

    float Entity::GetOldWX() const
    {
        return _oldWX;
    }

    float Entity::GetOldWY() const
    {
        return _oldWY;
    }

    float Entity::GetImageDiameter() const
    {
        return _imageDiameter;
    }

    float Entity::GetOldAngle() const
    {
        return _oldAngle;
    }

    float Entity::GetOldRelativeAngle() const
    {
        return _oldRelativeAngle;
    }

    float Entity::GetScaleX() const
    {
        return _scaleX;
    }

    float Entity::GetScaleY() const
    {
        return _scaleY;
    }

    float Entity::GetOldScaleX() const
    {
        return _oldScaleX;
    }

    float Entity::GetOldScaleY() const
    {
        return _oldScaleY;
    }

    float Entity::GetOldZ() const
    {
        return _oldZ;
    }

    float Entity::GetOldCurrentFrame() const
    {
        return _oldCurrentFrame;
    }

    void Entity::SetDoB(float dob)
    {
        _dob = dob;
    }

    float Entity::GetDoB() const
    {
        return _dob;
    }

    void Entity::SetSpeedVecX( float x )
    {
        _speedVec.x = x;
    }

    void Entity::SetSpeedVecY( float y )
    {
        _speedVec.y = y;
    }

    void Entity::SetBaseSpeed( float speed )
    {
        _baseSpeed = speed;
    }

    float Entity::GetBaseSpeed() const
    {
        return _baseSpeed;
    }

    void Entity::SetWidth( float width )
    {
        _width = width;
    }

    float Entity::GetWidth() const
    {
        return _width;
    }

    void Entity::SetHeight( float height )
    {
        _height = height;
    }

    float Entity::GetHeight() const
    {
        return _height;
    }

    void Entity::SetScaleX( float scaleX )
    {
        _scaleX = scaleX;
    }

    void Entity::SetScaleY( float scaleY )
    {
        _scaleY = scaleY;
    }

    void Entity::SetWidthHeightAABB( float minWidth, float minHeight, float maxWidth, float maxHeight )
    {
        _AABB_MaxWidth = maxWidth;
        _AABB_MaxHeight = maxHeight;
        _AABB_MinWidth = minWidth;
        _AABB_MinHeight = minHeight;
    }

    void Entity::SetDirectionLocked( bool value )
    {
        _directionLocked = value;
    }

    bool Entity::IsDirectionLocked() const
    {
        return _directionLocked;
    }

    float Entity::GetSpeedVecX() const
    {
        return _speedVec.x;
    }

    float Entity::GetSpeedVecY() const
    {
        return _speedVec.y;
    }

    void Entity::SetWeight( float weight )
    {
        _weight = weight;
    }

    float Entity::GetWeight() const
    {
        return _weight;
    }

    void Entity::SetBaseWeight( float weight )
    {
        _baseWeight = weight;
    }

    float Entity::GetBaseWeight() const
    {
        return _weight;
    }

} // namespace TLFX

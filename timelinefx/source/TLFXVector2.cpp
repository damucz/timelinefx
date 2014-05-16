#include "TLFXVector2.h"

#include <cmath>

namespace TLFX
{
    Vector2::Vector2(float vx, float vy)
        : x(vx), y(vy)
    {

    }

    Vector2 Vector2::Create( float vx, float vy )
    {
        return Vector2(vx, vy);
    }

    void Vector2::Move( float distanceX, float distanceY )
    {
        x += distanceX;
        y += distanceY;
    }

    void Vector2::Move( const Vector2& distance )
    {
        x += distance.x;
        y += distance.y;
    }

    void Vector2::Set( float vx, float vy )
    {
        x = vx;
        y = vy;
    }

    void Vector2::Set( const Vector2& v )
    {
        x = v.x;
        y = v.y;
    }

    Vector2 Vector2::Subtract( const Vector2& v ) const
    {
        return Vector2(x - v.x, y - v.y);
    }

    Vector2 Vector2::Add( const Vector2& v ) const
    {
        return Vector2(x + v.x, y + v.y);
    }

    Vector2 Vector2::Multiply( const Vector2& v ) const
    {
        return Vector2(x * v.x, y * v.y);
    }

    Vector2 Vector2::Scale( float scale ) const
    {
        return Vector2(x * scale, y * scale);
    }

    float Vector2::Length() const
    {
        return sqrtf(x * x + y * y);
    }

    Vector2 Vector2::Unit() const
    {
        float length = Length();
        Vector2 v;

        if (length != 0)
        {
            v.x = x / length;
            v.y = y / length;
        }
        return v;
    }

    Vector2 Vector2::Normal() const
    {
        return Vector2(-y, x);
    }

    Vector2 Vector2::LeftNormal() const
    {
        return Vector2(y, -x);
    }

    void Vector2::Normalize()
    {
        float length = Length();
        if (length != 0)
        {
            x /= length;
            y /= length;
        }
    }

    float Vector2::DotProduct( const Vector2& v ) const
    {
        return x * v.x + y * v.y;
    }

    float Vector2::GetDistance( float fromx, float fromy, float tox, float toy, bool fast /*= false*/ )
    {
        float w = tox - fromx;
        float h = toy - fromy;

        if (fast)
            return w * w + h * h;
        else
            return sqrtf(w * w + h * h);
    }

    /**
     * Get the direction from 1 point to another
     * Thanks to "Snarkbait" for this little code snippit
     * @return Angle of difference
     */
    float Vector2::GetDirection( float fromx, float fromy, float tox, float toy )
    {
        // arcus tangens, convert to degrees, add 450 and normalize to 360.
        return fmodf((atan2f(toy - fromy, tox - fromx) / (float)M_PI * 180.0f + 450.0f), 360.0f);
    }

} // namespace TLFX

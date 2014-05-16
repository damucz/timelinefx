#include "TLFXMatrix2.h"
#include "TLFXVector2.h"

namespace TLFX
{

    Matrix2::Matrix2()
        : aa(0), ab(0)
        , ba(0), bb(0)
    {

    }

    TLFX::Matrix2 Matrix2::Create( float aa_ /*= 1.0f*/, float ab_ /*= 0*/, float ba_ /*= 0*/, float bb_ /*= 1.0f*/ )
    {
        Matrix2 m;
        m.aa = aa_;
        m.ab = ab_;
        m.ba = ba_;
        m.bb = bb_;
        return m;
    }

    void Matrix2::Set( float aa_ /*= 1.0f*/, float ab_ /*= 0*/, float ba_ /*= 0*/, float bb_ /*= 1.0f*/ )
    {
        aa = aa_;
        ab = ab_;
        ba = ba_;
        bb = bb_;
    }

    void Matrix2::Transpose()
    {
        float abt = ab;
        ab = ba;
        ba = abt;
    }

    void Matrix2::Scale( float s )
    {
        aa *= s;
        ab *= s;
        ba *= s;
        bb *= s;
    }

    TLFX::Matrix2 Matrix2::Transform( const Matrix2& m ) const
    {
        Matrix2 r;
        r.aa = aa * m.aa + ab * m.ba;
        r.ab = aa * m.ab + ab * m.bb;
        r.ba = ba * m.aa + bb * m.ba;
        r.bb = ba * m.ab + bb * m.bb;
        return r;
    }

    Vector2 Matrix2::TransformVector( const Vector2& v ) const
    {
        Vector2 tv;
        tv.x = v.x * aa + v.y * ba;
        tv.y = v.x * ab + v.y * bb;
        return tv;
    }

    void Matrix2::TransformPoint( float x, float y, float& tx, float& ty )
    {
        tx = x * aa + y * ba;
        ty = x * ab + y * bb;
    }

} // namespace TLFX

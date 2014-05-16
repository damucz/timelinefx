#include "TLFXAttributeNode.h"

namespace TLFX
{

    AttributeNode::AttributeNode()
        : frame(0)
        , value(0)
        , isCurve(false)
        , c0x(0)
        , c0y(0)
        , c1x(0)
        , c1y(0)
    {

    }

    bool AttributeNode::Compare( const AttributeNode& other ) const
    {
        return frame > other.frame;                // @todo dan sgn(frame - other.frame)
    }

    void AttributeNode::SetCurvePoints( float x0, float y0, float x1, float y1 )
    {
        c0x = x0;
        c0y = y0;
        c1x = x1;
        c1y = y1;
        isCurve = true;
    }

    void AttributeNode::ToggleCurve()
    {
        isCurve = !isCurve;
    }

    bool AttributeNode::operator<( const AttributeNode& other ) const
    {
        return Compare(other);
    }

} // namespace TLFX

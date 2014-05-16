#ifdef _MSC_VER
#pragma once
#endif

#ifndef _TLFX_VECTOR2_H
#define _TLFX_VECTOR2_H

namespace TLFX
{

    class Vector2
    {
    public:
        float x, y;

        Vector2(float vx = 0, float vy = 0);

        /**
         * Create a new vector with the given coordinates
         * @return New #Vector2
         */
        static Vector2 Create(float vx, float vy);

        /**
         * Move a vector but the given x and y amount
         */
        void Move(float distanceX, float distanceY);

        /**
         * Move a vector buy the given vector
         */
        void Move(const Vector2& distance);

        /**
         * Reposition the vector by the new x,y coordinates given
         */
        void Set(float vx, float vy);

        /**
         * Reposition the vector by the given vector
         */
        void Set(const Vector2& v);

        /**
         * Subtract this Vector2 vector by another and return the result in a new vector
         * @return A new #Vector2
         */
        Vector2 Subtract(const Vector2& v) const;

        /**
         * Add this Vector2 vector to another and return the result in a new vector
         * return A new #Vector2
         */
        Vector2 Add(const Vector2& v) const;

        /**
         * multiply this vector with another and return the result
         * @return New #Vector2
         */
        Vector2 Multiply(const Vector2& v) const;

        /**
         * Scale the vector by the given amount and return the result in a new vector
         * @return new scaled #Vector2
         */
        Vector2 Scale(float scale) const;

        /**
         * Get the length of the vector
         * @return The length or magnitude of the vector.
         */
        float Length() const;

        /**
         * Get the unit vector of the vector
         * @return New unit vector of this vector
         */
        Vector2 Unit() const;

        /**
         * get the normal of the vector
         * @return New #Vector2 normal of this vector
         */
        Vector2 Normal() const;
        Vector2 LeftNormal() const;

        /**
         * Normalise the vector
         */
        void Normalize();

        /**
         * Get the dot product of the vector
         * @return The dot product of the vector.
         */
        float DotProduct(const Vector2& v) const;

        static float GetDistance(float fromx, float fromy, float tox, float toy, bool fast = false);
        static float GetDirection(float fromx, float fromy, float tox, float toy);

    protected:
    };

} // namespace TLFX

#endif // _TLFX_VECTOR2_H

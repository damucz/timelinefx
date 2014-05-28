#ifdef _MSC_VER
#pragma once
#endif

#ifndef _TLFX_ENTITY_H
#define _TLFX_ENTITY_H

#include "TLFXMatrix2.h"
#include "TLFXVector2.h"

#include <list>
#include <string>

namespace TLFX
{

    class AnimImage;
    struct AttributeNode;

    /**
     * Entity type for basic object information
     * <p>This is the main type for storing entity information such as coordinates, color and other information. This type is designed to be a base
     * type that you can use to extend and create other types, for example tPlayer or tBullet. </p>
     * <p>Entities can be parented to other entities and maintain and update a list of children. These children can be relative to their parents therefore
     *  minimizing the work needed to calculate where entities should be drawn to the screen. If a parent rotates, then it's children will rotate with it and
     * likewise, if the parent moves then its children will move with it as well. Children don't have to be relative however, set relative to false using #setrelative
     * to make the children move independently, however they will still be updated by their parent</p>
     * <p>If you have an entity with children, and those children in turn have children, in order to update all of those entities only one call to the parent
     * #update method is required to see all of the children updated too. This also applies to rendering the entities on screen - by calling #render on the parent entity
     * all children entities will also be rendered. See the code below for an example</p>
     * <p>Entities draw to the screen using tAnimImage, a type that allows for single surface drawing from the singlesurface.mod. To set the image use #setavatar
     * and loadsprite() to set the tAnimImage. You can adjust the appearence of the entity such as colour and scale using commands such as #setentitycolor, #setentityalpha,
     * #setentityscale and #setangle</p>
     * <p>When entities are rendered they can be tweened so that their animation and movement on the screen is smoothed out using fixed rate timing. To do this you need to make a call
     * to #capture each time the entity is updated which stores the entities last position and other details. #Capture is not included in the #udpate method because it makes things
     * too inflexible. There are situations where you might want to specify when exactly you want to #capture the entity. This means that when you extend Entity it's a good idea to 
     * override the update method with your own and include a call to capture within it. Then you can make a call to super.update so that the base update method is still tun. Again, see 
     * the example to see how it can work.</p>
     */
    class Entity
    {
    public:
        enum BlendMode
        {
            BMAlphaBlend,
            BMLightBlend,
        };

        Entity();

        /**
         * Copy without children
         */
        Entity(const Entity& other);

        virtual ~Entity() {};

        /**
         * Update the entity
         * Updates its coordinates based on the current speed (cs), applies any gravity, updates the current frame of the image and also updates the world coordinates. World
         * coordinates (wx and wy) represent the location of the entity where it will be drawn on screen. This is calculated based on where the entity is in relation to
         * it's parent entities. Update also updates the entity's children so only a single call to the parent entity is required to see all the children updated.
         */
        virtual bool Update();

        /**
         * A mini update called when the entity is created
         * This is sometimes necessary to get the correct world coordinates for when new entities are spawned so that tweening is updated too. Otherwise
         * you might experience the entity shooting across the screen as it tweens between locations.
         */
        void MiniUpdate();

        /**
         * Update all children of this entity.
         */
        void UpdateChildren();

        /**
         * Capture world coordinates, entity angle and scale for tweening.
         * Tweening is used in applications that use fixed rate timing. This is where the logic routines of an application are updated a fixed
         * amount of times each frame, but the drawing routines are updated as many times as possible. Each time the entity is updated during a logic
         * update you can capture its coordinates, then, depending on how much time has passed since the last logic update, the entity can be interpolated
         * between the old coordinates and the new ones creating a nice smooth movement no matter the PC you're running it on. To simplify things you
         * can use the tweener.mod to implement fixed rate timing. See the tweener.mod for more info.
         */
        void Capture();

        /**
         * Capture all including all children
         */
        void CaptureAll();

        /**
         * Update the entities bounding box
         * This will update the entities bounding box, and if the entity has no children it will update its parent bounding box if it has one.
         */
        void UpdateBoundingBox();

        /**
         * Update the entity's radius of influence
         * The radius of influence is the area around the entity that could possibly be drawn to. This is used in the timelinefx editor where
         * it's used to autofit the effect to the animation frame
         */
        void UpdateEntityRadius();

        /**
         * Update the entity's parent radius of influence
         */
        void UpdateParentEntityRadius();

        /**
         * Update the entity's parent radius of influence
         */
        void UpdateRootParentEntityRadius();

        /**
         * Update the entity's parent bounding box
         */
        void UpdateParentBoundingBox();

        /**
         * Assign the root parent of the entity
         * This assigns the root parent of the entity which will be the highest level in the entity hierarchy. This method is generally only used
         * internally, when an entity is added as a child to another entity.
         */
        void AssignRootParent(Entity* entity);

        /**
         * draw the bounding box for debugging
         */
        void DrawBoundingBox();

        /**
         * Draw the whole boundary of the entity including children
         */
        void DrawEntityBoundary();

        /**
         * Change the level of zoom for the particle.
         */
        void Zoom(float zoom);

        /**
         * Add a new child entity to the entity
         * This will also automatically set the children parent.
         */
        void AddChild(Entity *entity);

        /**
         * Destroy the entity
         * This will destroy the entity and all it's children, ensuring all references are removed. Best to call this
         * when you're finished with the entity to avoid memory leaks.
         */
        virtual void Destroy(bool releaseMemory = true);

        /**
         * Remove a child entity from this entity's list of children
         */
        void RemoveChild(Entity* entity);

        /**
         * Clear all child entities from this list of children
         * This completely destroys them so the garbage collector can free the memory
         */
        void ClearChildren();

        /**
         * Recursively kills all child entities and any children within those too and so on.
         * This sets all the children's dead field to true so that you can tidy them later on however you need. If you just want to 
         * get rid of them completely use #ClearChildren.
         */
        void KillChildren();

        /**
         * Rotate the entity by the number of degrees you pass to it
         */
        void Rotate(float degrees);

        /**
         * Move the entity by the amount x and y that you pass to it
         */
        void Move(float xamount, float yamount);

        /**
         * Get the red value in this Entity object.
         */
        int GetRed() const;

        /**
         * Set the red value for this Entity object.
         */
        void SetRed(unsigned char r);

        /**
         * Get the green value in this Entity object.
         */
        int GetGreen() const;

        /**
         * Set the green value for this Entity object.
         */
        void SetGreen(unsigned char g);

        /**
         * Get the blue value in this Entity object.
         */
        int GetBlue() const;

        /**
         * Set the blue value for this Entity object.
         */
        void SetBlue(unsigned char b);

        /**
         * Set the color for the Entity object.
         */
        void SetEntityColor(unsigned char r, unsigned char g, unsigned char b);

        /**
         * Get the alpha value in this Entity object.
         */
        float GetEntityAlpha() const;

        /**
         * Get the Image Radius value in this Entity object.
         * The image radius is the area that the entity could possible be drawn to. This takes into account scale and more importantly, the handle
         * of the image. Radius_Calculate needs to be set to true for this value to be kept updated.
         */
        float GetImageRadius() const;

        /**
         * Get the Entity Radius value in this Entity object.
         * The entity radius is similar to the Image_Radius except that it also takes into account all the children of the entity as well.
         * Radius_Calculate needs to be set to true for this value to be kept updated.
         */
        float GetEntityRadius() const;

        /**
         * Set the alpha value for this Entity object.
         */
        void SetEntityAlpha(float alpha);

        /**
         * Set the current x coordinate of the entity
         * This will be relative to the parent if relative is set to true
         */
        void SetX(float x);

        /**
         * Get the current x coordinate of the entity
         * This will be relative to the parent if relative is set to true
         */
        float GetX() const;

        /**
         * Set the current y coordinate of the entity
         * This will be relative to the parent if relative is set to true
         */
        void SetY(float y);

        /**
         * Get the current y coordinate of the entity
         * This will be relative to the parent if relative is set to true
         */
        float GetY() const;

        /**
         * Set the current zoom level of the entity
         */
        void SetZ(float z);

        float GetZ() const;

        /**
         * The the x and y position of the entity
         * This will be relative to the parent if relative is set to true
         */
        void SetPosition(float x, float y);

        /**
         * Set the current world x coordinate of the entity
         */
        void SetWX(float wx);

        /**
         * Set the current world y coordinate of the entity
         */
        void SetWY(float wy);

        /**
         * Set to true to position the handle of the entity at the center
         */
        void SetAutocenter(bool value);

        /**
         * Set the current angle of rotation of the entity
         */
        void SetAngle(float degrees);

        /**
         * Set the current blendmode of the entity ie., ALPHABLEND/LIGHTBLEND
         */
        void SetBlendMode(BlendMode mode);
        void SetBlendMode(int mode);

        /**
         * Set the entities x handle
         * This will not apply if autocenter is set to true
         */
        void SetHandleX(int x);

        /**
         * Set the entities y handle
         * This will not apply if autocenter is set to true
         */
        void SetHandleY(int y);

        /**
         * Set the name of the entity
         */
        void SetName(const char *name);

        /**
         * Set the parent of the entity
         * Entities can have parents and children. Entities are drawn relative to their parents if the relative flag is set to true. 
         * Using this command and #AddChild you can create a hierarchy of entities. There's no need to call #AddChild as well as #SetParent
         * because both commands will automatically set both accordingly
         */
        void SetParent(Entity* entity);

        /**
         * Sets whether this entity remains relative to it's parent
         * Entities that are relative to their parent entity will position, rotate and scale with their parent.
         */
        void SetRelative(bool value);

        /**
         * Sets the scale of the entity.
         * This will set both the x and y scale of the entity based on the values you pass it.
         */
        void SetEntityScale(float sx, float sy);

        /**
         * Set the current speed of the entity
         * Sets the speed which is measured in pixels per second
         */
        void SetSpeed(float speed);

        /**
         * Get the current speed of the entity
         * Gets the speed which is measured in pixels per second
         */
        float GetSpeed() const;

        /**
         * Get the Radius Calculate value in this Entity object.
         * see #SetRadiusCalculate for more info
         */
        bool IsRadiusCalculate() const;

        /**
         * Set the Radius Calculate value for this Entity object.
         * Radius is the radius of the entity where it could possible be drawn to. This includes all of it's children as well. 
         * This will also propagate to all children, so it's best to set this to true before adding children to the entity, that way, the children will acquire
         * the same value as the parent. By default this is false. 
         */
        void SetRadiusCalculate(bool value);

        /**
         * Get the framerate value in this Entity object.
         * see #SetFrameRate for more info.
         */
        float GetFramerate() const;

        /**
         * Set the framerate value for this Entity object.
         * the frame rate dicates how fast the entity animates if it has more then 1 frame
         * of animation. The framerate is measured in frames per second.
         */
        void SetFramerate(float framerate);

        /**
         * Returns true if the entity is animating
         */
        bool IsAnimating() const;

        /**
         * Set to true to make the entity animate
         */
        void SetAnimating(bool value);

        /**
         * Get the currentframe of the entity avatar animation
         */
        float GetCurrentFrame() const;

        /**
         * Set the currentframe of the entity avatar animation
         */
        void SetCurrentFrame(float frame);

        /**
         * Set the avatar (AnimImage) that the entity uses when it draws to the screen
         * AnimImage is defined in singlesurface.mod, and is a type that draws animated images using a single surface for extra speed.
         */
        void SetAvatar(AnimImage *avatar);

        /**
         * Set to true to make the entity animate just once
         * Once the entity as reached the end of the animation cycle it will stop animating.
         */
        void SetAnimateOnce(bool value);

        /**
         * Set the UpdateSpeed value for this Entity object.
         * Set to true or false, default is true. Setting to false will make the update method
         * ignore any speed calculations. This is useful in situations where you want to extend Entity
         * and calculate speed in your own way.
         */
        void SetUpdateSpeed(bool value);

        /**
         * Get the current angle of rotation
         */
        float GetAngle() const;

        /**
         * Get the current entity handle x
         */
        int GetHandleX() const;

        /**
         * Get the current entity image handle y
         */
        int GetHandleY() const;

        /**
         * Get the current blendmode
         */
        BlendMode GetBlendMode() const;

        /**
         * Get whether this entity is relative to it's parent
         */
        bool IsRelative() const;

        /**
         * Get the name of the entity
         */
        const char *GetName() const;

        /**
         * Gets the x and y scale of the entity.
         */
        void GetEntityScale(float& sx, float& sy) const;

        /**
         * Get the current avatar (AnimImage) that the entity uses when it draws to the screen
         */
        AnimImage* GetAvatar() const;

        /**
         * Get the current parent of the entity
         * Entities can have parents and children. Entities are drawn relative to their parents if the relative flag is true. 
         * Using this command and #AddChild you can create a hierarchy of entities.
         */
        Entity* GetParent() const;

        /**
         * Get the children that this entity has
         * This will return a list of children that the entity currently has
         */
        const std::list<Entity*>& GetChildren() const;

        /**
         * Get the lifetime value in this Entity object.
         * See #SetLifeTime
         */
        int GetLifeTime() const;

        /**
         * Set the lifetime value for this Entity object.
         * LifeTime represents the length of time that the entity should "Live" for. This allows entities to decay and expire in a given time.
         * LifeTime is measured in milliseconds. See #SetAge and #Decay for adjusting the age of the entity.
         */
        void SetLifeTime(int lifeTime);

        /**
         * Get the age value in this Entity object.
         * See #SetAge and #Decay.
         */
        float GetAge() const;

        /**
         * Set the age value for this Entity object.
         * Setting the age of of the entity allows you to keep track of how old the entity so that something can happen after a given amount of time.
         * See #Decay to increase the age by a given amount.
         */
        void SetAge(float age);

        /**
         * Increases the age value by a given amount
         */
        void Decay(float milliseconds);

        /**
         * Get the wx value in this Entity object.
         * WX represents the current x world coordinate of the entity. This may differ to x, which will contain the x coordinate relative 
         * to the parent entity
         */
        float GetWX() const;

        /**
         * Get the wy value in this Entity object.
         * WY represents the current Y world coordinate of the entity. This may differ to y, which will contain the Y coordinate relative 
         * to the parent entity
         */
        float GetWY() const;

        /**
         * Get the direction value in this Entity object.
         * Get the current direction the entity is traveling in
         */
        float GetEntityDirection() const;

        /**
         * Set the direction value for this Entity object.
         * Set the current direction the entity is traveling in
         */
        void SetEntityDirection(float direction);

        /**
         * Get the oktorender value in this Entity object
         * see #SetOKToRender
         */
        bool IsOKToRender() const;

        /**
         * Set the oktorender value for this Entity object.
         * Sometimes you might not always want entities to be rendered. When the render method is called, it will always render the children as well,
         * but if some of those children are effects which are rendered by a particle manager, then you don't want them rendered twice, so you can set this
         * to false to avoid them being rendered.
         */
        void SetOKtoRender(bool value);

        /**
         * Returns true if the axis aligned bounding box is being calculated for this entity
         */
        bool IsBoundingBox() const;

        /**
         * Set the AABB Include value for this Entity object.
         */
        void CalculateBoundingBox(bool value = true);

        /**
         * Render the entity
         * This will Draw the entity onto the screen using the tween value you pass to it to interpolate between old and new positions when
         * using fixed rate timing.
         */
        void Render(float tween);

        /**
         * Interpolate between 2 values
         * This is the function used to achieve render tweening by taking the old and new values and interpolating between the 2
         */
        static float TweenValues(float oldValue, float value, float tween);

        const Matrix2& GetMatrix() const;
        Matrix2& GetMatrix();

        bool IsDestroyed() const;

        int GetChildCount() const;

        float GetRelativeAngle() const;

        float GetOldWX() const;
        float GetOldWY() const;

        float GetImageDiameter() const;

        float GetOldAngle() const;
        float GetOldRelativeAngle() const;

        float GetScaleX() const;
        float GetScaleY() const;
        float GetOldScaleX() const;
        float GetOldScaleY() const;
        void SetScaleX(float scaleX);
        void SetScaleY(float scaleY);

        float GetOldZ() const;

        float GetOldCurrentFrame() const;

        void SetDoB(float dob);
        float GetDoB() const;

        void SetSpeedVecX(float x);
        void SetSpeedVecY(float y);
        float GetSpeedVecX() const;
        float GetSpeedVecY() const;

        void SetBaseSpeed(float speed);
        float GetBaseSpeed() const;

        void SetWidth(float width);
        float GetWidth() const;
        void SetHeight(float height);
        float GetHeight() const;

        void SetWidthHeightAABB(float minWidth, float minHeight, float maxWidth, float maxHeight);

        void SetDirectionLocked(bool value);
        bool IsDirectionLocked() const;

        void SetWeight(float weight);
        float GetWeight() const;
        void SetBaseWeight(float weight);
        float GetBaseWeight() const;

        static float Rnd(float range);
        static float Rnd(float min, float max);

    protected:
        // coordinates
        float                           _x, _y;                     // x and y coords
        float                           _oldX, _oldY;               // old x and y coords for tweening
        float                           _wx, _wy;                   // World Coords
        float                           _oldWX, _oldWY;             // Old world coords for tweening
        float                           _z;                         // z height off ground
        float                           _oldZ;                      // old z coords for tweening
        bool                            _relative;                  // whether the entity remains relative to it's parent. Relative is the default.
        // ------------------------
        Matrix2                         _matrix;                    // A matrix to calculate entity rotation relative to the parent
        Matrix2                         _spawnMatrix;               // May be moved in the future to tlParticle!
        Vector2                         _rotVec;                    // Vector formed between the parent and the children
        Vector2                         _speedVec;                  // vector created by he speed and direction of the entity
        Vector2                         _gravVec;                   // vector created by the current down force of the entity
        // entity name
        std::string                     _name;                      // name
        // colors
        unsigned char                   _r, _g, _b;                 // Avatar color in editor
        unsigned char                   _red, _green, _blue;        // Tint Colors
        unsigned char                   _oldRed, _oldGreen, _oldBlue;
        // size attribute and weight
        float                           _width, _height;            // width and height
        float                           _weight;                    // current weight
        float                           _gravity;                   // current speed of the drop
        float                           _baseWeight;                // base weight
        float                           _oldWeight;                 // tween weight
        float                           _scaleX, _scaleY;           // scale
        float                           _sizeX, _sizeY;             // size
        float                           _oldScaleX, _oldScaleY;     // Tweening
        // speed settings and variables
        float                           _speed;                     // current speed
        float                           _baseSpeed;                 // base speed of entity
        float                           _oldSpeed;                  // Old speed for tweening           // @todo dan oldcs
        bool                            _updateSpeed;               // Set to false to make the update method avoid updating the speed and movement
        // direction and rotation
        float                           _direction;                 // current direction
        bool                            _directionLocked;           // Locks the direction to the edge of the effect, for edage traversal
        float                           _angle;                     // current rotation of the entity
        float                           _oldAngle;                  // Tweening angle
        float                           _relativeAngle;             // To store the angle imposed by the parent
        float                           _oldRelativeAngle;
        // image settings and animation
        AnimImage*                      _avatar;                    // link to the image that represents the entity
        float                           _frameOffset;               // animation offset
        float                           _framerate;
        float                           _currentFrame;              // current frame of animation
        float                           _oldCurrentFrame;
        bool                            _animating;                 // whether or not the entity should be animating
        bool                            _animateOnce;               // whether the entity should animate just the once
        int                             _animAction;                // how the entity should animate
        int                             _handleX;
        int                             _handleY;
        bool                            _autoCenter;                // True if the handle of the entity is at the center of the image
        bool                            _okToRender;                // Set to false if you don't want this to be rendered
        // life and age variables
        float                           _dob;
        float                           _age;
        float                           _rptAgeA;
        float                           _rptAgeC;
        int                             _aCycles;
        int                             _cCycles;
        float                           _oldAge;
        int                             _dead;
        bool                            _destroyed;
        int                             _lifeTime;
        float                           _timediff;
        // bounding box info
        bool                            _AABB_Calculate;
        float                           _collisionXMin;
        float                           _collisionYMin;
        float                           _collisionXMax;
        float                           _collisionYMax;
        float                           _AABB_XMin;
        float                           _AABB_YMin;
        float                           _AABB_XMax;
        float                           _AABB_YMax;
        float                           _AABB_MaxWidth;
        float                           _AABB_MaxHeight;
        float                           _AABB_MinWidth;
        float                           _AABB_MinHeight;
        bool                            _radiusCalculate;
        float                           _imageRadius;               // This is the radius of which the image can be drawn within
        float                           _entityRadius;              // This is the radius that encompasses the whole entity, including children
        float                           _imageDiameter;
        // ownership
        Entity*                         _parent;                    // parent of the entity, for example bullet fired by the entity
        Entity*                         _rootParent;                // The root parent of the entity
        // children
        std::list<Entity*>              _children;                  // list of child entities
        bool                            _childrenOwner;             // true if this parent is responsible for disposing their children
        BlendMode                       _blendMode;                 // blend mode of the entity
        // alpha settings
        float                           _alpha;                     // current alpha level of the entity
        float                           _oldAlpha;                  // Tweening alpha
        // flags
        bool                            _runChildren;               // When the entity is created, this is false to avoid running it's children on creation to avoid recursion
        // temps
        float                           _pixelsPerSecond;
    };

} // namespace TLFX

#endif // _TLFX_ENTITY_H

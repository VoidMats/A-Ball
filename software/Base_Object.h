#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include <SFML/Graphics.hpp>

/*!
 * \brief The Base_Object class
 * is used in the game for creating all objects in the window.
 */

class Base_Object
{
public:
    //! The Base_Object class contain all the data for a object which is not unique for that class.
    //! This include the position and size. If the object has a check of collision it's in the middle
    //! class Solid_Object.
    Base_Object(float x, float y, float width, float height);
    virtual ~Base_Object() = default;
    Base_Object(Base_Object const &other) = default;
    Base_Object & operator = (Base_Object const &other) = default;
    Base_Object(Base_Object &&other) = default;
    Base_Object & operator = (Base_Object &&other) = default;

    //! Each object must be possible to render.
    virtual void render(sf::RenderWindow *window) = 0;

    //! Return the x-position of the object
    float get_x();

    //! Return the y-position of the object
    float get_y();

    //! Return width of the object
    float get_width();

    //! Return height of the object
    float get_height();

    //! Set a new y-position of the object
    void set_y(float new_y);

protected:
    float x_pos;
    float y_pos;
    float width;
    float height;
};

#endif // BASE_OBJECT_H

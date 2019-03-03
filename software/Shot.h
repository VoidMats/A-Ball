#ifndef SHOT_H
#define SHOT_H
#include <SFML/Graphics.hpp>
#include "Solid_Object.h"
#include "Smart_Pointer.h"
#include "Textures.h"

#include <string>

/*!
\brief The Shot class
is used in the game for creating shot objects in the field.
*/

class Shot: public Solid_Object
{
public:
    Shot(float x, float y,
         Textures* tex,
         std::vector<Solid_Object*> & m_list);
    /*!
    Updates the position and checks collision with bricks and top.
    */
    void update(std::vector<Solid_Object*> & obstacles);
private:
    float speed{-2};
};

#endif

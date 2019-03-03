#ifndef BOX_H
#define BOX_H
#include <SFML/Graphics.hpp>
#include <string>
#include "Solid_Object.h"
#include "Smart_Pointer.h"

/*!
\brief The Box class
is used in the game for creating objects in the field. This could be walls, highscore board etc.
 */

class Box: public Solid_Object
{
public:
    Box(float x, float y, float width, float height,
         std::string name,
         Textures *tex,
         std::vector<Solid_Object*> & m_list);
};

#endif

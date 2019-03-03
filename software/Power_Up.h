#ifndef POWER_UP_H
#define POWER_UP_H
#include <SFML/Graphics.hpp>
#include <string>
#include "Solid_Object.h"
#include "Textures.h"
#include "Smart_Pointer.h"

/*!
 * \brief The Power_Up class
 * is used in the game for creating powerup objects in the field.
 */

class Power_Up: public Solid_Object
{
public:
    Power_Up(float x, float y,
          std::string name, Textures* tex,
          std::vector<Solid_Object*> & m_list,
          int type);
    /*!
    Updates position.
    Checks collision with player and bottom.
    */
    void update(std::vector<Solid_Object*> & obstacles);

private:
    float speed{1};
    int type;
};

#endif

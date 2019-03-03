#include <SFML/Graphics.hpp>
#include "Power_Up.h"
#include "Textures.h"
#include "Player.h"
#include <string>
#include <random>

Power_Up::Power_Up(float x, float y,
     std::string name, Textures* tex,
     std::vector<Solid_Object*> & m_list,
     int type)
     : Solid_Object{x, y, 15.0f, 10.0f, name, tex, m_list}, type{type}
{}

void Power_Up::update(std::vector<Solid_Object*> & obstacles)
{
    y_pos += speed;

    for ( int idx{0}; idx < static_cast<int>(obstacles.size()); idx++ )
    {
        if ( check_collision(obstacles[idx]) )
        {
            if ( obstacles[idx]->get_name() == "Player" )
            {
                dynamic_cast<Player*>(obstacles[idx])->add_effect(type);
                remove_obj(idx);
            }
            else if ( obstacles[idx]->get_name() == "Bottom" )
            {
                remove_obj(idx);
            }
        }
    }
}

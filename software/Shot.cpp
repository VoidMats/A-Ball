#include <SFML/Graphics.hpp>
#include "Shot.h"
#include "Textures.h"
#include <string>

Shot::Shot(float x, float y,
    Textures* tex,
    std::vector<Solid_Object*> & m_list)
    : Solid_Object{x, y, 4.0f, 16.0f, "Shot", tex, m_list}
{}

void Shot::update(std::vector<Solid_Object*> & obstacles)
{
    y_pos += speed;

    for ( int idx{0}; idx < obstacles.size(); idx++ )
    {
        if ( check_collision(obstacles[idx]) )
        {
            if ( obstacles[idx]->get_name() == "Brick1"
              || obstacles[idx]->get_name() == "Brick2"
              || obstacles[idx]->get_name() == "Brick3" )
            {
                obstacles[idx]->remove_obj(idx);
                remove_obj(idx);
                break;
            }
            else if ( obstacles[idx]->get_name() == "Top"
                   || obstacles[idx]->get_name() == "Brick4" )
            {
                remove_obj(idx);
                break;
            }

        }
    }
}

#include <SFML/Graphics.hpp>
#include "Brick.h"
#include "Textures.h"

Brick::Brick(float x, float y, float width, float height,
            std::string name,
            Textures *tex,
            std::vector<Solid_Object*> &m_list,
            s_Ptr<Score> score,
            int type)
     : Solid_Object{x, y, width, height, name, tex, m_list},
      score{score}, type{type}
{}

void Brick::remove_obj(int idx)
{
    if ( name == "Brick1" )
    {
        Solid_Object *ptr = member_list[idx];
        member_list.erase(begin(member_list)+idx);
        delete ptr;
    }
    else if ( name == "Brick2" )
    {
        name = "Brick1";
        shape.setSize(sf::Vector2f(width, height));
        auto i = texture_list->get_texture(name);
        shape.setTexture(i, true);
    }
    else
    {
        name = "Brick2";
        shape.setSize(sf::Vector2f(width, height));
        auto i = texture_list->get_texture(name);
        shape.setTexture(i, true);
    }
    score->add_score( 10 );
}

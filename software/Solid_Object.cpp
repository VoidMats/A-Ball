#include "Solid_Object.h"
#include "Textures.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

Solid_Object::Solid_Object(float x, float y, float width, float height,
                           std::string name,
                           Textures *tex,
                           std::vector<Solid_Object*> &m_list)
    : Base_Object{x, y, width, height},
    name{name}, texture_list{tex}, member_list{m_list}
{
    shape.setSize(sf::Vector2f(width, height));

    if( empty_texture() )
    {
        shape.setFillColor(sf::Color::Red);
    }
    else
    {
        auto i = texture_list->get_texture(name);
        shape.setTexture(i, true);
    }
}

void Solid_Object::render(sf::RenderWindow *window)
{
    shape.setPosition(x_pos, y_pos);
    window->draw(shape);
}

std::string Solid_Object::get_name() {
    return name;
}

void Solid_Object::update(std::vector<Solid_Object*> &obstacles)
{

}

void Solid_Object::update_player(std::vector<Solid_Object*> &walls,
    std::vector<Solid_Object*> &m_obj, sf::Vector2f dir)
{

}

bool Solid_Object::check_collision(Solid_Object *obstacle)
{
    return (
        obstacle->x_pos <= x_pos + width
     && obstacle->x_pos + obstacle->width >= x_pos )
     && (
        obstacle->y_pos <= y_pos + height
     && obstacle->y_pos + obstacle->height >= y_pos );
}

bool Solid_Object::empty_texture()
{
    return (texture_list == nullptr);
}

void Solid_Object::remove_obj(int idx)
{
    for ( int x{0}; x < member_list.size(); x++ )
    {
        if ( member_list[x]->get_name() == name )
        {
            Solid_Object *ptr{ member_list[x] };
            member_list.erase(begin(member_list)+x);
            delete ptr;
            break;
        }
    }
}

void Solid_Object::rem_effect()
{}

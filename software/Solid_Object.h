#ifndef SOLID_OBJECT_H
#define SOLID_OBJECT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Base_Object.h"
#include "Textures.h"
#include "Smart_Pointer.h"

/*!
 * \brief The Solid_Object class
 * is used in the game for creating all objects that might need
 * collision detection and/or textures.
 */

class Solid_Object: public Base_Object
{
public:
    Solid_Object(float x, float y, float width, float height,
                 std::string name,
                 Textures *tex,
                 std::vector<Solid_Object*> &m_list);
    ~Solid_Object() = default;
    Solid_Object(Solid_Object const &other) = default;
    Solid_Object & operator = (Solid_Object const &other) = default;
    void render(sf::RenderWindow *window) override;
    /*!
    Returns name as a string.
    */
    std::string get_name();
    /*!
    Removes current object from its member list.
    */
    virtual void remove_obj(int idx);
    virtual void rem_effect();
    virtual void update(std::vector<Solid_Object*> &obstacles);
    virtual void update_player(std::vector<Solid_Object*> &walls,
                          std::vector<Solid_Object*> &m_obj,
                          sf::Vector2f dir);

protected:
    /*!
    Returns true if current object intersects with obstacle.
    */
    bool check_collision(Solid_Object *obstacle);
    /*!
    Returns true if texture_list is empty.
    */
    bool empty_texture();

    Textures *texture_list;
    std::vector<Solid_Object*> &member_list;
    sf::RectangleShape shape;
    std::string name;
};

#endif

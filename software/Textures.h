#ifndef TEXTURES_H
#define TEXTURES_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "Smart_Pointer.h"

/*!
\brief The Textures class
is used to load and store all textures used in the game in a map.
*/

class Textures
{
public:
    Textures();
    ~Textures();
    /*!
    Loads all textures used in the game.
    */
    void read_textures();
    /*!
    Returns a pointer to a specific texture.
    */
    sf::Texture* get_texture(std::string name);
    /*!
    Finds and loads a specific texture.
    */
    void add_texture(std::string name);

private:
    std::map<std::string, sf::Texture*> textures;

};

#endif

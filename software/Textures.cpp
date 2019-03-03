#include <fstream>
#include <iostream>
#include "Textures.h"

Textures::Textures()
{
    read_textures();
}

Textures::~Textures()
{
    for( auto it : textures )
    {
        delete it.second;
    }

}

sf::Texture* Textures::get_texture(std::string name)
{
    auto i = textures.find(name);
    if ( i != textures.end() )
    {
        return i->second;
    }
}

void Textures::read_textures()
{
    std::cout<< "*** Reading textures ***" << std::endl;
    std::ifstream ifs{"textures.txt"};
    std::string file;
    while ( getline(ifs, file) )
    {
        add_texture(file);
    }
}

void Textures::add_texture(std::string name)
{
    sf::Texture* t{new sf::Texture};
    std::string file{"textures/" + name};
    t->loadFromFile(file);
    name.erase(begin(name) + name.find_first_of('.'), end(name));
    textures.insert(make_pair(name, t));
}

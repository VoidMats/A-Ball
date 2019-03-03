#include <SFML/Graphics.hpp>
#include "Box.h"
#include "Textures.h"

using namespace std;

Box::Box(float x, float y, float width, float height,
     std::string name,
     Textures *tex,
     std::vector<Solid_Object*> & m_list)
     : Solid_Object{x, y, width, height, name, tex, m_list}
{}

#ifndef BRICK_H
#define BRICK_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Solid_Object.h"
#include "Score.h"
#include "Textures.h"
#include "Smart_Pointer.h"

/*!
\brief The Brick class
is used in the game for creating brick objects in the field.
*/

class Brick: public Solid_Object
{
public:
    Brick(float x, float y, float width, float height,
          std::string name,
          Textures *tex,
          std::vector<Solid_Object*> &m_list,
          s_Ptr<Score> score, int type);
    ~Brick() = default;
    Brick(Brick const &other) = default;
    Brick & operator = (Brick const &other) = default;
    /*!
     * Updates or removes the brick at index idx.
     */
    void remove_obj(int idx) override;
private:
    s_Ptr<Score> score;
    int type;
};

#endif

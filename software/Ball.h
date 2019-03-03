#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Solid_Object.h"
#include "Score.h"
#include "Textures.h"
#include "Smart_Pointer.h"

/*!
 * \brief The Ball class
 * is used in the game for creating ball objects in the field.
 */

class Ball: public Solid_Object
{
public:
    Ball(float x, float y,
        std::string name,
        Textures *tex,
        std::vector<Solid_Object*> & m_list,
        s_Ptr<Score> score);
    ~Ball() = default;
    Ball(Ball const &other) = default;
    Ball & operator = (Ball const &other) = default;
    /*!
    Updates position and speed. Checks collision with bricks, player and walls.
    Handles spawning of powerups.
    */
    void update(std::vector<Solid_Object*> & obstacles) override;

private:
    void update_pos(Solid_Object* obstacle);

    s_Ptr<Score> score;
    float x_speed{1};
    float y_speed{-1};
    int* life;
};

#endif

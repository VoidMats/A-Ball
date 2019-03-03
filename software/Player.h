#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Solid_Object.h"
#include "Smart_Pointer.h"
#include "Textures.h"
#include "Score.h"
#include "Brick.h"
#include "Box.h"
#include "Shot.h"

/*!
 * \brief The Player class
 * is used in the game for creating the player object in the field.
 */

class Player: public Solid_Object
{
public:
    Player(float x, float y,
          Textures* tex,
          std::vector<Solid_Object*> & m_list,
          s_Ptr<Score> _p_score,
          std::vector<Solid_Object*> & b_list);
    /*!
    Adds a powerup-effect to the player.
    */
    void add_effect(int effect);
    /*!
    Handles all player updates.
    Updates position based on input.
    Checks for collision.
    Handles expiring powerup-effects.
    Pushes ball in case of overlap.
    */
<<<<<<< HEAD
    void update_player(std::vector<Solid_Object*> & walls,
      std::vector<Solid_Object*> & m_obj, sf::Vector2f dir) override;
    /*!
    Removes any powerup-effect from the player.
    */
    void rem_effect();
private:
    float x_sp{5};
    float y_sp{2.5};
    int type_effect{0};
=======
    void update_player(std::vector<Solid_Object*> &walls,
                       std::vector<Solid_Object*> &m_obj,
                       sf::Vector2f dir) override;
private:
    void rem_effect();

>>>>>>> d39218ac81597930da142d4c4a7666acaf7b2e92
    const float w_w{660};
    const float w_h{800};
    const float s_h{100};
    const float p_h{(w_h-s_h)/4};

    s_Ptr<Score> p_score;
    float x_sp{5};
    float y_sp{2.5};
    int type_effect{0};

    std::vector<Solid_Object*> &bricks_other_player;
    sf::Time time_effect{};
    sf::Clock effect_timer{};
    sf::Clock shot_timer{};
};

#endif //PLAYER_H

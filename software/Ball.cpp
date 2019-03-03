#include "Ball.h"
#include "Textures.h"
#include "Power_Up.h"
#include "Solid_Object.h"
#include <string>
#include <vector>
#include <random>

Ball::Ball(float x, float y,
    std::string name,
    Textures *tex,
    std::vector<Solid_Object*> & m_list,
    s_Ptr<Score> score)
        : Solid_Object{x, y, 8.0f, 8.0f, name, tex, m_list},
        score{score}, life{nullptr}
{}

void Ball::update_pos(Solid_Object* obstacle)
{
    float obs_l{obstacle->get_x()};
    float obs_r{obs_l + obstacle->get_width()};
    float obs_u{obstacle->get_y()};
    float obs_d{obs_u + obstacle->get_height()};
    float old_x{x_pos - x_speed};
    float old_y{y_pos - y_speed};

    //Upper-left corner
    if ( x_pos <= obs_l && y_pos <= obs_u )
    {
        if ( x_speed > 0 && y_speed > 0 ) //Coming from above-left
        {
            if ( (y_pos + height)-(obs_u) > (x_pos + width)-(obs_l) )
            {
                x_speed = -x_speed;
            }
            else
            {
                y_speed = -y_speed;
            }
        }
        else if ( x_speed > 0 && y_speed < 0 ) //Coming from below-left
        {
            x_speed = -x_speed;
        }
        else if ( x_speed < 0 && y_speed > 0 ) //Coming from above-right
        {
            y_speed = -y_speed;
        }
    }
    //Lower-left corner
    else if ( x_pos <= obs_l && y_pos + height >= obs_d )
    {
        if ( x_speed > 0 && y_speed < 0 ) //Coming from below-left
        {
            if ( obs_d - y_pos > (x_pos + width)-(obs_l) )
            {
                x_speed = -x_speed;
            }
            else
            {
                y_speed = -y_speed;
            }
        }
        else if ( x_speed > 0 && y_speed > 0 ) //Coming from above-left
        {
            x_speed = -x_speed;
        }
        else if ( x_speed < 0 && y_speed < 0 ) //Coming from below-right
        {
            y_speed = -y_speed;
        }
    }
    //Lower-right corner
    else if ( x_pos + width >= obs_r && y_pos + height >= obs_d )
    {
        if ( x_speed < 0 && y_speed < 0 ) //Coming from below-right
        {
            if ( obs_d - y_pos > obs_r - x_pos )
            {
                x_speed = -x_speed;
            }
            else
            {
                y_speed = -y_speed;
            }
        }
        else if ( x_speed < 0 && y_speed > 0 ) //Coming from above-right
        {
            x_speed = -x_speed;
        }
        else if ( x_speed > 0 && y_speed < 0 ) //Coming from below-left
        {
            y_speed = -y_speed;
        }
    }
    //Upper-right corner
    else if ( x_pos + width >= obs_r && y_pos <= obs_u )
    {
        if ( x_speed < 0 && y_speed > 0 ) //Coming from above-right
        {
            if ( y_pos - obs_u > obs_r - x_pos )
            {
                x_speed = -x_speed;
            }
            else
            {
                y_speed = -y_speed;
            }
        }
        else if ( x_speed < 0 && y_speed < 0 ) //Coming from below-right
        {
            x_speed = -x_speed;
        }
        else if ( x_speed > 0 && y_speed > 0 ) //Coming from above-left
        {
            y_speed = -y_speed;
        }
    }
    //Left or right side
    else if ( x_pos < obs_l || x_pos + width > obs_r )
    {
        x_speed = -x_speed;
    }
    //Top or bottom side
    else if ( y_pos < obs_u || y_pos + height > obs_d )
    {
        y_speed = -y_speed;
    }

    x_pos = old_x;
    y_pos = old_y;
}

void Ball::update(std::vector<Solid_Object*> & obstacles)
{
    x_pos += x_speed;
    y_pos += y_speed;

    for ( unsigned int idx{0}; idx < obstacles.size(); idx++ )
    {
        if ( check_collision(obstacles[idx]) )
        {
            if ( obstacles[idx]->get_name() == "Player" )
            {
                update_pos(obstacles[idx]);
                score->reset_hit();
                break;
            }
            else if ( obstacles[idx]->get_name() == "Top" )
            {
                y_speed = -y_speed;
                y_pos += y_speed;
                break;
            }
            else if ( obstacles[idx]->get_name() == "Left"
                   || obstacles[idx]->get_name() == "Right" )
            {
                x_speed = -x_speed;
                x_pos += x_speed;
                break;
            }
            else if ( obstacles[idx]->get_name() == "Bottom" )
            {
                score->reset_hit();
                score->lose_life();
                remove_obj(idx);
                break;
            }
            else if ( obstacles[idx]->get_name() == "Brick1"
                   || obstacles[idx]->get_name() == "Brick2"
                   || obstacles[idx]->get_name() == "Brick3" )
            {
                update_pos(obstacles[idx]);

                std::random_device rd;
<<<<<<< HEAD
                std::uniform_int_distribution<int> chance(1, 10);
=======
                std::uniform_int_distribution<int> chance(1, 5);
>>>>>>> d39218ac81597930da142d4c4a7666acaf7b2e92
                int spawn_pu{chance(rd)};
                std::uniform_int_distribution<int> type(1, 5);
                int pu_type{type(rd)};

                if ( spawn_pu == 1)
                {
                    Solid_Object* pu{ new Power_Up{
                        obstacles[idx]->get_x() + 15,
                        obstacles[idx]->get_y() + 5,
                        "PowerUp" + std::to_string(pu_type),
                        texture_list,
                        member_list,
                        pu_type} };
                    member_list.push_back(pu);
                }
                score->add_hit();

                if ( obstacles[idx]->get_name() == "Brick1" )
                {
                    obstacles[idx]->remove_obj(idx);
                    --idx;
                }
                else
                {
                    obstacles[idx]->remove_obj(idx);
                }
                break;

            }
            else if ( obstacles[idx]->get_name() == "Brick4" )
            {
                update_pos(obstacles[idx]);
                break;
            }

        }
    }
}

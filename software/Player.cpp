#include <SFML/Graphics.hpp>
#include "Player.h"

//#include <iostream>>

Player::Player(float x, float y,
     Textures* tex,
     std::vector<Solid_Object*> & m_list,
     s_Ptr<Score> _p_score,
     std::vector<Solid_Object*> &b_list)
     : Solid_Object{x, y, 80.0f, 10.0f, "Player", tex, m_list},
       p_score{ _p_score }, bricks_other_player{ b_list } {}

void Player::add_effect(int effect)
{
    rem_effect();
    effect_timer.restart();
    type_effect = effect;
    if( type_effect == 1 )
    {
        x_pos = x_pos + width/4;
        width = width/2;
        shape.setSize(sf::Vector2f(width, height));
    }
    else if( type_effect == 2 )
    {
        x_pos = x_pos - width/2;
        width = width*2;
        shape.setSize(sf::Vector2f(width, height));
    }
    else if( type_effect == 3 )
    {
        shot_timer.restart();
    }
    else if( type_effect == 4 )
    {
        p_score->add_score( 2000 );
    }
    else if( type_effect == 5 )
    {
        if( p_score->get_nr_players() == 2)
        {
            float pos_x;
            float pos_y;
            if( p_score->get_player_nr() == 2 )
            {
                pos_x = p_score->get_nr_added_bricks()*40.0f+10.0f;
                pos_y = 17*20;
            }
            else
            {
                pos_x = p_score->get_nr_added_bricks()*40.0f+670.0f;
                pos_y = 17*20;
            }
            Solid_Object* brick{ new Brick{pos_x, pos_y, 40, 20,
                            "Brick4", texture_list, bricks_other_player,
                            p_score, 4} };
            bricks_other_player.push_back(brick);
            p_score->add_brick( false );
        }
        else
        {
            int limit{0};
            if( bricks_other_player.size() > 3)
                limit = 3;
            else
                limit = static_cast<int>( bricks_other_player.size() );
            for( int i; i<limit; ++i)
            {
                Solid_Object *ptr{ bricks_other_player[i] };
                bricks_other_player.erase( begin(bricks_other_player)+i );
                delete ptr;
            }
        }
    }
}

void Player::update_player(std::vector<Solid_Object*>& walls, std::vector<Solid_Object*>& m_obj, sf::Vector2f dir)
{
    y_pos += dir.y*y_sp;
    x_pos += dir.x*x_sp;

    if ( type_effect != 0 && effect_timer.getElapsedTime().asSeconds() >= 10 )
    {
        rem_effect();
    }
    else if ( type_effect == 3 && shot_timer.getElapsedTime().asSeconds() >= 0.95 )
    {
        shot_timer.restart();
        float pos_x{x_pos+width/2-1};
        float pos_y{y_pos-9};
        Solid_Object* shot{ new Shot{pos_x, pos_y, texture_list, m_obj} };
        m_obj.push_back(shot);
    }

    for ( unsigned int idx{0}; idx < walls.size(); idx++ )
    {
        if ( check_collision(walls[idx]) )
        {
            if ( walls[idx]->get_name() == "Left" )
            {
                x_pos = walls[idx]->get_x() + walls[idx]->get_width();
            }
            else if ( walls[idx]->get_name() == "Right" )
            {
                x_pos = walls[idx]->get_x() - width;
            }
            else if ( walls[idx]->get_name() == "Bottom" )
            {
                y_pos = w_h - s_h - height - walls[idx]->get_height();
            }
            else if ( walls[idx]->get_name() == "Divider" )
            {
                y_pos = w_h-p_h-s_h;
            }
        }
    }

    for ( unsigned int idx{0}; idx < m_obj.size(); idx++ )
    {
        if ( check_collision(m_obj[idx]) && m_obj[idx]->get_name() == "Ball" )
        {
            if ( m_obj[idx]->get_y() + m_obj[idx]->get_height()/2
               <= y_pos + height/2 )
            {
                m_obj[idx]->set_y(y_pos - m_obj[idx]->get_height());
            }
            else
            {
                m_obj[idx]->set_y(y_pos + height);
            }
        }
    }
}

void Player::rem_effect()
{
    if ( type_effect == 1 )
    {
        width = width*2;
        x_pos = x_pos - width/4;
        shape.setSize(sf::Vector2f(width, height));
    }
    else if ( type_effect == 2 )
    {
        width = width/2;
        x_pos = x_pos + width/2;
        shape.setSize(sf::Vector2f(width, height));
    }
    type_effect = 0;
}

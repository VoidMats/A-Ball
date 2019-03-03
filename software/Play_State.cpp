#include <iostream>
#include "Play_State.h"

using namespace std;
using namespace sf;

Play_State::Play_State(RenderWindow *window, Textures *texture, vector<vector<string>> *vec)
    :Key_Input{window, texture}, vec_level{vec}, p_score_class{nullptr}
{
    p_score_class = make_shared<Score>();
    p_score_class->add_nr_players(1);
    p_score_class->add_player_nr(1);
}

Play_State::~Play_State()
{
    clear_board(false);

    if(p_score_class.unique())
        p_score_class.reset();
}


int Play_State::run()
{
    initiate();

    bool quit{false};
    bool new_level{false};
    level = 0;
    while( !quit )
    {
        initiate_level( new_level );
        while ( !quit && !new_level )
        {
            Keyboard::Key key = check_keys(quit);
            if( key == Keyboard::Key::Space )
            {
                // Check if there is a ball on the field
                bool bExist{false};
                for( auto it : moving_objects )
                {
                    if(it->get_name() == "Ball")
                        bExist = true;
                }
                if( !bExist )
                {
                    auto p_obj{player.at(0)};
                    float pos_x{p_obj->get_x()+p_obj->get_width()/2-2.5f};
                    float pos_y{p_obj->get_y()-8};
                    Solid_Object* ball{ new Ball{pos_x, pos_y, "Ball", texture,
                                    moving_objects, p_score_class} };
                    moving_objects.push_back(ball);
                }
            }
            else if( key == Keyboard::Key::Escape )
            {
                quit = true;
                return -2;
            }
            window->clear();
            update_render_game();
            window->display();
            // Check if the level is finished
            if(bricks.size() == nr_bricks_type_4)
            {
                clear_board(true);
                ++level;
                // Next level if there is any
                if( level < vec_level->size() )
                {
                    string txt_level{ "Level " + to_string(level) };
                    create_text( w_win/2-85, h_win/2-h_scoreboard, txt_level );
                    text.back().setCharacterSize(30);
                    string txt_comp{ "Completed" };
                    create_text( w_win/2-115, h_win/2-h_scoreboard+50, txt_comp );
                    text.back().setCharacterSize(30);
                    window->clear();
                    update_render_game();
                    window->display();
                    new_level = true;
                    this_thread::sleep_for( chrono::milliseconds(3000) );
                    text.pop_back();
                    text.pop_back();
                }
                // No more levels - Game Over
                else
                {
                    string txt_level{ "Level " + to_string(level) };
                    create_text( w_win/2-85, h_win/2-h_scoreboard, txt_level );
                    text.back().setCharacterSize(30);
                    string txt_comp{ "Game Over" };
                    create_text( w_win/2-115, h_win/2-h_scoreboard+50, txt_comp );
                    text.back().setCharacterSize(30);
                    window->clear();
                    update_render_game();
                    window->display();
                    this_thread::sleep_for( chrono::milliseconds(3000 ));
                    text.pop_back();
                    text.pop_back();
                    quit = true;
                    return p_score_class->get_score();

                }
            }
            // No more life -> Game Over
            if(p_score_class->get_life() <= 0)
            {
                this_thread::sleep_for( chrono::milliseconds(3000 ));
                return p_score_class->get_score();
            }
        }
    }
    return -1;
}

void Play_State::initiate()
{
    clear_board(false);
    p_score_class->reset_life();
    level = 0;

    cout << "*** Create gameboard *** " << endl;

    // Create static objects for container boxes
    Solid_Object* divider{ new Box{0, h_win-h_scoreboard-((h_win-h_scoreboard)/4), w_win,1,
                    "Divider", texture, boxes} };
    boxes.push_back(divider);
    Solid_Object* background{ new Box{0, 0, w_win, h_win-h_scoreboard,
                    "Background", texture, boxes} };
    boxes.push_back(background);
    Solid_Object* top{ new Box{0, 0, w_win, w_frame,
                    "Top", texture, boxes} };
    boxes.push_back(top);
    Solid_Object* left{ new Box{0, 0, w_frame, h_win-h_scoreboard,
                    "Left", texture, boxes} };
    boxes.push_back(left);
    Solid_Object* right{ new Box{w_win-w_frame, 0, w_frame, h_win-h_scoreboard,
                    "Right", texture, boxes} };
    boxes.push_back(right);
    Solid_Object* bottom{ new Box{0, h_win-h_scoreboard-1, w_win, 1,
                    "Bottom", texture, boxes} };
    boxes.push_back(bottom);
    Solid_Object* scoreboard{ new Box{0, h_win-h_scoreboard, w_win, h_scoreboard,
                    "Scoreboard", texture, boxes} };
    boxes.push_back(scoreboard);

    // Create player object for container player
    Solid_Object* Play{ new Player{300, 600, texture, player,
                    p_score_class, bricks} };
    player.push_back(Play);

    // Create textboxes for the scoreboard
    create_text( w_frame+20, h_win-h_scoreboard/2+w_frame, "Score: " );
    create_text( w_frame+20, h_win-h_scoreboard+w_frame+10, "Player One" );
    create_text( w_frame+10+w_win/2, h_win-h_scoreboard/2+w_frame, "Multiplier: " );
    create_text( w_frame+10+w_win/2, h_win-h_scoreboard+w_frame+10, "Level: " );

    // Create life objects for the screen -> show how many life the player has.
    for( int i{0}; i<3; ++i )
    {
        RectangleShape rec;
        rec.setSize(Vector2f(30,5));
        rec.setTexture( texture->get_texture("Player") );
        rec.setRotation(-45);
        rec.setPosition(w_frame+30*i+10, h_win-h_scoreboard-30);
        life.push_back(rec);
    }
}

void Play_State::initiate_level( bool &_new_level )
{
    nr_bricks_type_4 = 0;
    p_score_class->add_brick( true );

    for( auto it : player )
    {
        it->rem_effect();
    }

    if( !vec_level->empty() ) {
        cout << "*** Reading level from memory ***" << endl;
        for( int rows{0}; rows<max_rows; ++rows )
        {
            for( int col{0}; col<max_bricks; ++col) {
                vector<string> vec{ vec_level->at(level) };
                char c{ vec.at(rows).at(col) };

                if ( c == '1' || c == '2' || c == '3' || c == '4' )
                {
                    if ( c == '4' )
                    {
                        ++nr_bricks_type_4;
                    }
                    string name{"Brick"};
                    string type{c};
                    name.append(type);
                    float pos_x{col*w_brick+w_frame};
                    float pos_y{rows*h_brick+w_frame};
                    Solid_Object* brick{ new Brick{pos_x, pos_y, w_brick, h_brick,
                                    name, texture, bricks, p_score_class, int(c)} };
                    bricks.push_back(brick);
                }
            }
        }
        _new_level = false;
    }
}

void Play_State::update_render_game()
{

    text[0].setString( "Score: " + to_string(p_score_class->get_score()) );
    text[2].setString( "Multiplier: x" + to_string(p_score_class->get_multi()) );
    text[3].setString( "Level: " + to_string(level+1));  // move this to when the level actually change

    for( auto it : boxes )
    {
        it->render(window);
    }
    for( auto it : bricks )
    {
        it->render(window);
    }
    for( auto it : moving_objects )
    {
        it->update(boxes);
    }
<<<<<<< HEAD

=======
>>>>>>> d39218ac81597930da142d4c4a7666acaf7b2e92
    for( auto it : moving_objects )
    {
        it->update(player);
    }
<<<<<<< HEAD

=======
>>>>>>> d39218ac81597930da142d4c4a7666acaf7b2e92
    for( auto it : moving_objects )
    {
        it->update(bricks);
    }
<<<<<<< HEAD

=======
>>>>>>> d39218ac81597930da142d4c4a7666acaf7b2e92
    for( auto it : moving_objects )
    {
        it->render(window);
    }
    for( auto it : player )
    {
        it->update_player(boxes, moving_objects, dir_1);
        it->render(window);
    }
    for( auto it : text )
    {
        window->draw(it);
    }
    if( static_cast<unsigned int>(p_score_class->get_life()) < life.size())
    {
        life.pop_back();
    }
    for( auto it : life )
    {
        window->draw(it);
    }
}

void Play_State::clear_board(bool _level)
{
    for( auto it : moving_objects )
    {
        delete it;
    }

    for( auto it : bricks )
    {
        delete it;
    }

    moving_objects.clear();
    bricks.clear();

    // Objects which need to be cleared when there is a new game.
    if( !_level )
    {
        for( auto it : boxes )
        {
            delete it;
        }

        for( auto it : player )
        {
            delete it;
        }
        boxes.clear();
        player.clear();
        life.clear();
        p_score_class->reset_score();
    }
}

void Play_State::create_text(float pos_x, float pos_y, string _text)
{
    Text txt( _text, font );
    txt.setPosition( pos_x, pos_y );
    txt.setCharacterSize( 20 );
    txt.setColor(Color::White);
    text.push_back(txt);
}

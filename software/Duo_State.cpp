#include "Duo_State.h"

using namespace std;
using namespace sf;


Duo_State::Duo_State(RenderWindow *window, Textures *texture, vector<vector<string> > *vec)
    :Key_Input{window, texture}, vec_level{vec}, p_score_player_1{nullptr}, p_score_player_2{nullptr}
{
    p_score_player_1 = make_shared<Score>();
    p_score_player_2 = make_shared<Score>();
    p_score_player_1->add_nr_players(2);
    p_score_player_2->add_nr_players(2);
    p_score_player_1->add_player_nr(1);
    p_score_player_2->add_player_nr(2);

    initiate();
}

Duo_State::~Duo_State()
{
    clear_board(false);

    if(p_score_player_1.unique())
        p_score_player_1.reset();
    if(p_score_player_2.unique())
        p_score_player_2.reset();
}

int Duo_State::run()
{
    // Set position of window and make it widther
    set_window(true);

    bool quit{false};
    bool new_level{false};

    p_score_player_1->reset_life();
    p_score_player_2->reset_life();
    level = 0;
    while( !quit )
    {
        initiate_level( new_level, true );
        initiate_level( new_level, false );
        while ( !quit && !new_level )
        {
            Keyboard::Key key = check_keys(quit);
            if( key == Keyboard::Key::LControl )
            {
                // Check if there is a ball on the field one
                check_ball( true );
            }
            else if( key == Keyboard::Key::RControl)
            {
                // Check if there is a ball on the field two
                check_ball( false );
            }
            else if( key == Keyboard::Key::Escape )
            {
                quit = true;
                set_window(false);
                return 0;
            }
            window->clear();
            update_render_game();
            window->display();
            // Check if the level is finished
            if( bricks_player_1.size() == nr_bricks_type_4 ||
                bricks_player_2.size() == nr_bricks_type_4 )
            {
                ++level;
                if( level < vec_level->size() )
                {
                    string txt_level{ "Level " + to_string(level) };
                    string txt_comp{ "Completed" };
                    if( bricks_player_1.size() == nr_bricks_type_4 )
                    {
                        std::cout << "player one next level" << std::endl;
                        create_text( w_win/2-85, h_win/2-h_scoreboard, txt_level );
                        text.back().setCharacterSize(30);
                        create_text( w_win/2-115, h_win/2-h_scoreboard+50, txt_comp );
                        text.back().setCharacterSize(30);
                    }
                    else
                    {
                        std::cout << "player two next level" << std::endl;
                        create_text( w_win+w_win/2-85, h_win/2-h_scoreboard, txt_level );
                        text.back().setCharacterSize(30);
                        create_text( w_win+w_win/2-115, h_win/2-h_scoreboard+50, txt_comp );
                        text.back().setCharacterSize(30);
                    }
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
                    string txt_comp{ "Game Over" };
                    if( bricks_player_1.size() == nr_bricks_type_4 )
                    {
                        create_text( w_win/2-85, h_win/2-h_scoreboard, txt_level );
                        text.back().setCharacterSize(30);
                        create_text( w_win/2-115, h_win/2-h_scoreboard+50, txt_comp );
                        text.back().setCharacterSize(30);
                    }
                    else
                    {
                        create_text( w_win+w_win/2-85, h_win/2-h_scoreboard, txt_level );
                        text.back().setCharacterSize(30);
                        create_text( w_win+w_win/2-115, h_win/2-h_scoreboard+50, txt_comp );
                        text.back().setCharacterSize(30);
                    }
                    window->clear();
                    update_render_game();
                    window->display();
                    this_thread::sleep_for( chrono::milliseconds(3000 ));
                    text.pop_back();
                    text.pop_back();
                    quit = true;
                    clear_board(true);
                    set_window(false);
                    // Check which score is highest
                    return p_score_player_1->get_score();

                }
                clear_board(true);

            }
            // No more life -> Game Over
            if( p_score_player_1->get_life() <= 0 ||
                p_score_player_2->get_life() <= 0 )
            {
                this_thread::sleep_for( chrono::milliseconds(3000 ));
                set_window(false);
                if( p_score_player_1->get_score() > p_score_player_2->get_score() )
                    return p_score_player_1->get_score();
                else
                    return p_score_player_2->get_score();
            }
        }
    }
    return -1;
}

void Duo_State::initiate()
{

    cout << "*** Create gameboard one *** " << endl;

    // Create static objects for container boxes
    Solid_Object* divider{ new Box{0, h_win-h_scoreboard-((h_win-h_scoreboard)/4), w_win,1,
                    "Divider", texture, boxes_player_1} };
    boxes_player_1.push_back(divider);
    Solid_Object* background{ new Box{0, 0, w_win, h_win-h_scoreboard,
                    "Background", texture, boxes_player_1} };
    boxes_player_1.push_back(background);
    Solid_Object* top{ new Box{0, 0, w_win, w_frame,
                    "Top", texture, boxes_player_1} };
    boxes_player_1.push_back(top);
    Solid_Object* left{ new Box{0, 0, w_frame, h_win-h_scoreboard,
                    "Left", texture, boxes_player_1} };
    boxes_player_1.push_back(left);
    Solid_Object* right{ new Box{w_win-w_frame, 0, w_frame, h_win-h_scoreboard,
                    "Right", texture, boxes_player_1} };
    boxes_player_1.push_back(right);
    Solid_Object* bottom{ new Box{0, h_win-h_scoreboard-1, w_win, 1,
                    "Bottom", texture, boxes_player_1} };
    boxes_player_1.push_back(bottom);
    Solid_Object* scoreboard{ new Box{0, h_win-h_scoreboard, w_win, h_scoreboard,
                    "Scoreboard", texture, boxes_player_1} };
    boxes_player_1.push_back(scoreboard);

    // Create player object for container player
    Solid_Object* p_player_1{ new Player{ 300, 600, texture, player_1,
                    p_score_player_1, bricks_player_2 }};
    player_1.push_back( p_player_1 );

    cout << "*** Create gameboard two ***" << endl;

    // Create static objects for container boxes
    Solid_Object* divider_2{ new Box{w_win, h_win-h_scoreboard-((h_win-h_scoreboard)/4), w_win,1,
                    "Divider", texture, boxes_player_2} };
    boxes_player_2.push_back(divider_2);
    Solid_Object* background_2{ new Box{w_win, 0, w_win, h_win-h_scoreboard,
                    "Background", texture, boxes_player_2} };
    boxes_player_2.push_back(background_2);
    Solid_Object* top_2{ new Box{w_win, 0, w_win, w_frame,
                    "Top", texture, boxes_player_2} };
    boxes_player_2.push_back(top_2);
    Solid_Object* left_2{ new Box{w_win, 0, w_frame, h_win-h_scoreboard,
                    "Left", texture, boxes_player_2} };
    boxes_player_2.push_back(left_2);
    Solid_Object* right_2{ new Box{w_win*2-w_frame, 0, w_frame, h_win-h_scoreboard,
                    "Right", texture, boxes_player_2} };
    boxes_player_2.push_back(right_2);
    Solid_Object* bottom_2{ new Box{w_win, h_win-h_scoreboard-1, w_win, 1,
                    "Bottom", texture, boxes_player_2} };
    boxes_player_2.push_back(bottom_2);
    Solid_Object* scoreboard_2{ new Box{w_win, h_win-h_scoreboard, w_win, h_scoreboard,
                    "Scoreboard", texture, boxes_player_2} };
    boxes_player_2.push_back(scoreboard_2);

    // Create player object for gameboard two
    Solid_Object* p_player_2{ new Player{ w_win+300, 600, texture, player_2,
                    p_score_player_2, bricks_player_1 }};
    player_2.push_back( p_player_2 );

    // Create textboxes for the scoreboard player one
    create_text( w_frame+20, h_win-h_scoreboard/2+w_frame, "Score: " );
    create_text( w_frame+20, h_win-h_scoreboard+w_frame+10, "Player One" );
    create_text( w_frame+10+w_win/2, h_win-h_scoreboard/2+w_frame, "Multiplier: " );
    create_text( w_frame+10+w_win/2, h_win-h_scoreboard+w_frame+10, "Level: " );

    // Create textboxes for the scoreboard player two
    create_text( w_win + w_frame+20, h_win-h_scoreboard/2+w_frame, "Score: " );
    create_text( w_win + w_frame+20, h_win-h_scoreboard+w_frame+10, "Player Two" );
    create_text( w_win + w_frame+10+w_win/2, h_win-h_scoreboard/2+w_frame, "Multiplier: " );
    create_text( w_win + w_frame+10+w_win/2, h_win-h_scoreboard+w_frame+10, "Level: " );

    // Create life objects for the screen -> show how many life the player one has.
    for( int i{0}; i<3; ++i )
    {
        RectangleShape rec;
        rec.setSize(Vector2f(30,5));
        rec.setTexture( texture->get_texture("Player") );
        rec.setRotation(-45);
        rec.setPosition(w_frame+30*i+10, h_win-h_scoreboard-30);
        life_player_1.push_back(rec);
    }

    // Create life objects for the screen -> show how many life the player one has.
    for( int i{0}; i<3; ++i )
    {
        RectangleShape rec;
        rec.setSize(Vector2f(30,5));
        rec.setTexture( texture->get_texture("Player") );
        rec.setRotation(-45);
        rec.setPosition(w_win+w_frame+30*i+10, h_win-h_scoreboard-30);
        life_player_2.push_back(rec);
    }
}

void Duo_State::initiate_level( bool &_new_level, bool player_one )
{
    nr_bricks_type_4 = 0;
    p_score_player_1->add_brick( true );
    p_score_player_2->add_brick( true );


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
                    float pos_x;
                    float pos_y;
                    if( player_one )
                    {
                        pos_x = col*w_brick+w_frame;
                        pos_y = rows*h_brick+w_frame;
                        Solid_Object* brick{ new Brick{pos_x, pos_y, w_brick, h_brick,
                                        name, texture, bricks_player_1, p_score_player_1, int(c)} };
                        bricks_player_1.push_back(brick);
                    }
                    else
                    {
                        pos_x = col*w_brick+w_frame+w_win;
                        pos_y = rows*h_brick+w_frame;
                        Solid_Object* brick_2{ new Brick{pos_x, pos_y, w_brick, h_brick,
                                        name, texture, bricks_player_2, p_score_player_2, int(c)} };
                        bricks_player_2.push_back(brick_2);
                    }
                }
            }
        }
        _new_level = false;
    }
}

void Duo_State::update_render_game()
{
    text[0].setString( "Score: " + to_string(p_score_player_1->get_score()) );
    text[2].setString( "Multiplier: x" + to_string(p_score_player_1->get_multi()) );
    text[3].setString( "Level: " + to_string(level+1));
    text[4].setString( "Score: " + to_string(p_score_player_2->get_score()) );
    text[6].setString( "Multiplier: x" + to_string(p_score_player_2->get_multi()) );
    text[7].setString( "Level: " + to_string(level+1));

    // TODO -- Too many loops
    for( auto it : boxes_player_1 )
    {
        it->render(window);
    }
    for( auto it : boxes_player_2 )
    {
        it->render(window);
    }
    for( auto it : bricks_player_1 )
    {
        it->render(window);
    }
    for( auto it : bricks_player_2 )
    {
        it->render(window);
    }
    for( auto it : moving_objects_player_1 )
    {
        it->update( boxes_player_1 );
    }
    for( auto it : moving_objects_player_2 )
    {
        it->update( boxes_player_2 );
    }
    for( auto it : moving_objects_player_1 )
    {
        it->update( player_1 );
    }
    for( auto it : moving_objects_player_2 )
    {
        it->update( player_2 );
    }
    for( auto it : moving_objects_player_1 )
    {
        it->update( bricks_player_1 );
    }
    for( auto it : moving_objects_player_2 )
    {
        it->update( bricks_player_2 );
    }
    for( auto it : moving_objects_player_1 )
    {
        it->render(window);
    }
    for( auto it : moving_objects_player_2 )
    {
        it->render(window);
    }
    for( auto it : player_1 )
    {
        it->update_player(boxes_player_1, moving_objects_player_1, dir_1);
        it->render(window);
    }
    for( auto it : player_2 )
    {
        it->update_player(boxes_player_2, moving_objects_player_2, dir_2);
        it->render(window);
    }
    for( auto it : text )
    {
        window->draw(it);
    }
    if( static_cast<unsigned int>( p_score_player_1->get_life()) < life_player_1.size())
    {
        life_player_1.pop_back();
    }
    if( static_cast<unsigned int>( p_score_player_2->get_life()) < life_player_2.size())
    {
        life_player_2.pop_back();
    }
    for( auto it : life_player_1 )
    {
        window->draw( it );
    }
    for( auto it : life_player_2 )
    {
        window->draw( it );
    }
}

void Duo_State::clear_board(bool _level)
{
    for( auto it : moving_objects_player_1 )
    {
        delete it;
    }
    for( auto it : moving_objects_player_2 )
    {
        delete it;
    }
    for( auto it : bricks_player_1 )
    {
        delete it;
    }
    for( auto it : bricks_player_2 )
    {
        delete it;
    }
    moving_objects_player_1.clear();
    moving_objects_player_2.clear();
    bricks_player_1.clear();
    bricks_player_2.clear();

    // Objects which need to be cleared when there is a new game.
    if( !_level )
    {
        for( auto it : boxes_player_1 )
        {
            delete it;
        }
        for( auto it : boxes_player_2 )
        {
            delete it;
        }
        for( auto it : player_1 )
        {
            delete it;
        }
        for( auto it : player_2 )
        {
            delete it;
        }
        player_1.clear();
        player_2.clear();
        boxes_player_1.clear();
        boxes_player_2.clear();
        life_player_1.clear();
        life_player_2.clear();
        p_score_player_1->reset_score();
        p_score_player_2->reset_score();
    }
}

void Duo_State::create_text(float pos_x, float pos_y, string _text)
{
    Text txt( _text, font );
    txt.setPosition( pos_x, pos_y );
    txt.setCharacterSize( 20 );
    txt.setColor(Color::White);
    text.push_back(txt);
}

void Duo_State::set_window( bool _widthscreen )
{
    Vector2i pos{ window->getPosition() };
    Vector2u size;
    Vector2f center{ window->getView().getCenter() };
    View new_view;
    if( _widthscreen )
    {
        pos.x = pos.x - w_win/2;
        size.x = static_cast<unsigned int>(w_win)*2;
        size.y = static_cast<unsigned int>(h_win);
        new_view.setSize( w_win*2, h_win );
        center.x += w_win/2;
        new_view.setCenter( center );
    }
    else
    {
        pos.x = pos.x + w_win/2;
        size.x = static_cast<unsigned int>(w_win);
        size.y = static_cast<unsigned int>(h_win);
        new_view.setSize( w_win, h_win );
        center.x -= w_win/2;
        new_view.setCenter(center);
    }
    window->setPosition(pos);
    window->setSize(size);
    window->setView(new_view);
}

void Duo_State::check_ball( bool _bPlayer_1 )
{
    bool bExist{false};
    if( _bPlayer_1 )
    {
        for( auto it : moving_objects_player_1 )
        {
            if(it->get_name() == "Ball")
            {
                bExist = true;
            }
        }
        if( !bExist )
        {
            auto p_obj{ player_1.at(0) };
            float pos_x{p_obj->get_x()+p_obj->get_width()/2-2.5f};
            float pos_y{p_obj->get_y()-8};
            Solid_Object* ball{ new Ball{pos_x, pos_y, "Ball", texture,
                            moving_objects_player_1, p_score_player_1} };
            moving_objects_player_1.push_back(ball);
        }
    }
    else
    {
        for( auto it : moving_objects_player_2 )
        {
            if(it->get_name() == "Ball")
            {
                bExist = true;
            }
        }
        if( !bExist )
        {
            auto p_obj{ player_2.at(0) };
            float pos_x{p_obj->get_x()+p_obj->get_width()/2-2.5f};
            float pos_y{p_obj->get_y()-8};
            Solid_Object* ball{ new Ball{pos_x, pos_y, "Ball", texture,
                            moving_objects_player_2, p_score_player_2} };
            moving_objects_player_2.push_back(ball);
        }
    }
}

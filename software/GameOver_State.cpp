#include "GameOver_State.h"

using namespace std;
using namespace sf;

GameOver_State::GameOver_State(RenderWindow *window,
                               Textures *texture,
                               std::vector<std::pair<int, string> > *_score,
                               int *_player_score)
    :Key_Input{window, texture}, list_score{_score}, player_score{_player_score}
{
    // All field objects for the GameOver_State is done here
    initiate();
}

GameOver_State::~GameOver_State()
{
    if( !boxes.empty() )
    {
        for( auto it : boxes )
        {
            delete it;
        }
    }
    boxes.clear();

    if( !texts.empty() )
    {
        for( auto it: texts )
        {
            delete it;
        }
    }

    texts.clear();
}

int GameOver_State::run()
{
    bool quit{false};
    initiate_game();
    check_score();
    Event event;
    while(!quit)
    {
        window->clear();
        update_render_game();
        window->display();
        if( enter_name )
        {
            while ( window->pollEvent(event) )
            {
                if( event.type == event.TextEntered )
                {
                    if( event.text.unicode < 128
                            && event.text.unicode != 8
                            && event.text.unicode != 13)
                    {
                        if( name.size() < 10 )
                            name += (static_cast<char>(event.text.unicode));
                        window->clear();
                        update_render_game();
                        window->display();
                    }
                    if( event.text.unicode == 8 )
                    {
                        if( name.size() > 0 )
                        {
                            name.pop_back();
                        }
                        window->clear();
                        update_render_game();
                        window->display();
                    }
                    if( event.text.unicode == 13 )
                    {
                        write_score_to_memory();
                        enter_name = false;
                        window->clear();
                        update_render_game();
                        window->display();
                        break;
                    }
                }
            }
         }
        else
        {
            Keyboard::Key key{check_keys(quit)};
            if( key == Keyboard::Key::Escape )
                return 0;
            if( key == Keyboard::Key::Return )
                return 2;
            if( key == Keyboard::Key::Space )
                return 2;
        }
    }
    return -1;
}

void GameOver_State::initiate()
{
    vector<pair<string,int>> vec_txt
    {
        {"Game Over",40},
        {"Score: ",20},
        {"Please enter name: ",20},
        {"",20},
        {"Enter return to menu",20}
    };
    vector<pair<float,float>> vec_pos{
        {190,150},
        {220,235},
        {195,300},
        {240,350},
        {170,550}
    };

    for( int i{0}; i<vec_txt.size(); ++i )
    {
        Text *txt{ new Text{} };
        txt->setString(vec_txt.at(i).first);
        txt->setFont(font);
        txt->setCharacterSize(vec_txt.at(i).second);
        txt->setColor(Color::White);
        txt->setPosition(vec_pos.at(i).first,vec_pos.at(i).second);
        texts.push_back(txt);
    }

    // Create static objects
    Solid_Object* background{ new Box{0, 0, w_win, h_win, "Background", texture, boxes} };
    boxes.push_back(background);
    Solid_Object* top{ new Box{0, 0, w_win, w_frame, "Top", texture, boxes} };
    boxes.push_back(top);
    Solid_Object* left{ new Box{0, 0, w_frame, h_win, "Left", texture, boxes} };
    boxes.push_back(left);
    Solid_Object* right{ new Box{w_win-w_frame, 0, w_frame, h_win, "Right", texture, boxes} };
    boxes.push_back(right);
    Solid_Object* bottom{ new Box{0, h_win-w_frame, w_win, w_frame, "Bottom", texture, boxes} };
    boxes.push_back(bottom);
    Solid_Object* banner{ new Box{100,100,460,500, "Banner", texture, boxes} };
    boxes.push_back(banner);

}

void GameOver_State::initiate_game()
{
    string txt_score{ "Score: " + to_string(*player_score) };
    texts.at(1)->setString( txt_score );

    place = -1;
    name = "";
    texts.at(3)->setString( "" );
}

void GameOver_State::update_render_game()
{

    for( auto it : boxes ) {
        it->render( window );
    }

    if( enter_name ) {
        texts.at(3)->setString( name );
        window->draw( *texts.at(0) );
        window->draw( *texts.at(1) );
        window->draw( *texts.at(2) );
        window->draw( *texts.at(3) );
    }
    else
    {
        window->draw( *texts.at(0) );
        window->draw( *texts.at(1) );
        window->draw( *texts.at(3) );
        window->draw( *texts.at(4) );
    }

}

void GameOver_State::check_score()
{
    if( !list_score->empty() )
    {
        for(unsigned int i{0}; i<list_score->size(); ++i)
        {
            int value{ list_score->at(i).first };
            if( *player_score > value ) {
                enter_name = true;
                place = i;
                break;
            }
        }
    }
}

void GameOver_State::write_score_to_memory()
{
    list_score->insert( list_score->begin()+place, make_pair(*player_score,name) );
    list_score->pop_back();
}

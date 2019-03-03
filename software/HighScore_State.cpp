#include "HighScore_State.h"
#include <string>

using namespace std;
using namespace sf;

HighScore_State::HighScore_State(sf::RenderWindow *window, Textures *texture,
                std::vector<std::pair<int, std::string>> &score_list)
    :Key_Input{window, texture}, score_list{score_list}
{
    initiate();
}

HighScore_State::~HighScore_State()
{
    if( !boxes.empty() )
    {
        for ( auto it : boxes )
            delete it;
    }
    boxes.clear();

    if( !texts.empty() )
    {
        for ( auto it : texts )
            delete it;
    }
    texts.clear();
}

int HighScore_State::run()
{
    initiate_game();
    window->clear();
    update_render_game();
    window->display();

    bool quit{false};
    while(!quit)
    {
        Keyboard::Key key{ check_keys(quit) };
        if ( key == Keyboard::Key::Return
          || key == Keyboard::Key::Escape )
        {
            return 0;
            quit = true;
        }
    }
    return -1;
}

void HighScore_State::initiate()
{
    // Create text
    Text *entry{ new Text{}};
    entry->setString("Highscore");
    entry->setFont(font);
    entry->setCharacterSize(40);
    entry->setColor(Color::White);
    entry->setPosition(190, 150);
    texts.push_back(entry);

    for ( int i{0}; i < 5; ++i )
    {
        Text *entry{ new Text{}};
        entry->setString(
            score_list[i].second + ": " + to_string(score_list[i].first));
        entry->setFont(font);
        entry->setCharacterSize(30);
        entry->setColor(Color::White);
        entry->setPosition(200, 300+i*40);
        texts.push_back(entry);
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
    Solid_Object* bottom{ new Box{0, h_win-w_frame, w_win, w_frame, "Top", texture, boxes} };
    boxes.push_back(bottom);
    Solid_Object* banner{ new Box{100,100,460,500, "Banner", texture, boxes} };
    boxes.push_back(banner);
}

void HighScore_State::initiate_game()
{
    for( int i{0}; i<5; ++i )
    {
        texts.at(i+1)->setString( score_list[i].second + ": " + to_string(score_list[i].first) );
    }
}

void HighScore_State::update_render_game()
{
    for( auto it : boxes )
    {
        it->render(window);
    }

    for ( auto it : texts )
    {
        window->draw(*it);
    }
}

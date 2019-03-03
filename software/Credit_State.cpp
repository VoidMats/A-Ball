#include "Credit_State.h"
#include <string>

using namespace std;
using namespace sf;

Credit_State::Credit_State(RenderWindow *window, Textures *texture)
    :Key_Input{window, texture}
{
    initiate();
}

Credit_State::~Credit_State()
{
    if(!boxes.empty())
    {
        for( auto it : boxes )
            delete it;
    }
    if(!texts.empty())
    {
        for( auto it : texts )
            delete it;
    }
}

int Credit_State::run()
{
    window->clear();
    draw_game();
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

void Credit_State::initiate()
{

    vector<pair<string,int>> vec_txt
    {
        {"Credits",40},
        {"Programmers",30},
        {"Mats Eriksson",20},
        {"Joakim Westerberg",20}
    };

    vector<pair<float,float>> vec_pos{
        {170,100},
        {180,200},
        {180,260},
        {180,310}
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
    Solid_Object* background{
        new Box{0, 0, w_win, h_win, "Background", texture, boxes} };
    boxes.push_back(background);
    Solid_Object* top{
        new Box{0, 0, w_win, w_frame, "Top", texture, boxes} };
    boxes.push_back(top);
    Solid_Object* left{
        new Box{0, 0, w_frame, h_win, "Left", texture, boxes} };
    boxes.push_back(left);
    Solid_Object* right{
        new Box{w_win-w_frame, 0, w_frame, h_win, "Right", texture, boxes} };
    boxes.push_back(right);
    Solid_Object* bottom{
        new Box{0, h_win-w_frame, w_win, w_frame, "Top", texture, boxes} };
    boxes.push_back(bottom);
}

void Credit_State::draw_game()
{
    for( auto it : boxes ) {
        it->render(window);
    }
    for ( auto it : texts )
    {
        window->draw(*it);
    }
}

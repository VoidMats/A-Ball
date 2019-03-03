#include "Menu_State.h"

using namespace std;
using namespace sf;

Menu_State::Menu_State(RenderWindow *window, Textures *texture)
    :Key_Input{window, texture}
{}

Menu_State::~Menu_State()
{
    if( !boxes.empty() )
    {
        for( auto it : boxes )
            delete it;
    }
    if( !texts.empty() )
    {
        for( auto it : texts )
            delete it;
    }
}

int Menu_State::run()
{

    bool quit{false};
    initiate();
    while( !quit )
    {
        window->clear();
        update_render_game();
        window->display();
        Keyboard::Key key{ check_keys(quit) };
        if(key == Keyboard::Key::Up)
        {
            --select;
            if( select < 1 )
                select = max_nr_select;
        }
        if(key == Keyboard::Key::Down)
        {
            ++select;
            if( select > max_nr_select )
                select = 1;
        }
        if(key == Keyboard::Key::Return)
        {
            return select;
        }
        if(key == Keyboard::Key::Escape)
        {
            quit = true;
        }
    }
    return -1;
}

void Menu_State::initiate()
{

    select = 1;

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

    vector<string> button_names
    {
        {"Single Player"},
        {"Duo Player"},
        {"Highscore"},
        {"Credits"},
        {"Quit"}
    };

    for ( unsigned int i{0}; i<max_nr_select; i++ )
    {
        Text *entry{ new Text{}};
        entry->setString(button_names[i]);
        entry->setFont(font);
        entry->setCharacterSize(20);
        entry->setColor(Color::White);
        entry->setPosition(240, 255+i*50);
        texts.push_back(entry);
        float y_value{ 250+static_cast<float>(i)*50 };
        Solid_Object* button{
            new Box{220, y_value, 240, 40, "Banner", texture, boxes} };
        boxes.push_back(button);
    }

    float r{10};
    ball.setRadius(r);
    ball.setTexture(texture->get_texture("Ball"));
    ball.setPosition(Vector2f(160,250));
}

void Menu_State::update_render_game()
{

    ball.setPosition(180, 210 + select*50);

    for( auto it : boxes ) {
        it->render(window);
    }
    for ( auto it : texts )
    {
        window->draw(*it);
    }
    window->draw(ball);
}

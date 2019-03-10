#include "Key_Input.h"

Key_Input::Key_Input(sf::RenderWindow *window, Textures *texture)
    :window{window}, texture{texture}
{
    if( !font.loadFromFile("ka1.ttf") ) {
        std::cout << "Fail to load font from file " << std::endl;
    }
}

int Key_Input::run()
{
    return 0;
}

sf::Keyboard::Key Key_Input::check_keys(bool &quit)
{
    sf::Keyboard::Key key{ sf::Keyboard::Key::Unknown };
    sf::Event event;
    while ( window->pollEvent(event) )
    {
        switch ( event.type )
        {
            case sf::Event::Closed:
                quit = true;
                break;
            case sf::Event::KeyPressed:
                key = event.key.code;
                on_key_use( true, key );
                break;
            case sf::Event::KeyReleased:
                on_key_use( false, event.key.code );
                break;
            default:
                break;
        }
    }
    return key;
}

void Key_Input::on_key_use(bool pressed, sf::Keyboard::Key key)
{
    switch ( key )
    {
        // Player two
        case sf::Keyboard::Key::Up:
            keys2.up = pressed;
            direction( false );
            break;
        case sf::Keyboard::Key::Down:
            keys2.down = pressed;
            direction( false );
            break;
        case sf::Keyboard::Key::Left:
            keys2.left = pressed;
            direction( false );
            break;
        case sf::Keyboard::Key::Right:
            keys2.right = pressed;
            direction( false );
            break;
        // Player one
        case sf::Keyboard::Key::W:
            keys1.up = pressed;
            direction( true );
            break;
        case sf::Keyboard::Key::S:
            keys1.down = pressed;
            direction( true );
            break;
        case sf::Keyboard::Key::A:
            keys1.left = pressed;
            direction( true );
            break;
        case sf::Keyboard::Key::D:
            keys1.right = pressed;
            direction( true );
            break;
        default:
            break;
    }
}
void Key_Input::direction( bool player_one )
{
    float y{0};
    float x{0};
    if( player_one )
    {
        if ( keys1.up )
            y -= 1.0f;
        if ( keys1.down )
            y += 1.0f;
        if ( keys1.left )
            x -= 1.0f;
        if ( keys1.right )
            x += 1.0f;
        dir_1.x = x;
        dir_1.y = y;
    }
    else
    {
        if ( keys2.up )
            y -= 1.0f;
        if ( keys2.down )
            y += 1.0f;
        if ( keys2.left )
            x -= 1.0f;
        if ( keys2.right )
            x += 1.0f;
        dir_2.x = x;
        dir_2.y = y;
    }

}

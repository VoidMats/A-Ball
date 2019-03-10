#ifndef KEY_INPUT_H
#define KEY_INPUT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Textures.h"
#include "Smart_Pointer.h"

//! The Key_Input class handle the keyboard input of the game.

class Key_Input
{
public:
    Key_Input(sf::RenderWindow *window, Textures *texture);
    virtual ~Key_Input() = default;
    Key_Input(Key_Input const &copy) = default;
    Key_Input &operator = (Key_Input const &copy) = default;

    //! Abstract function run() which are used for all State classes to be executed.
    virtual int run() = 0;
protected:
    //! Struct to name each direction.
    struct Keys
    {
        bool up{false};
        bool down{false};
        bool left{false};
        bool right{false};
    };

    //! Function will check the keys on the active window and will revert back the key that was pressed.
    //! If no key is pressed the returned value will be unknown. The function also set the direction
    //! on the player.
    sf::Keyboard::Key check_keys(bool &quit);

    const float w_win{660};     //! Width of the render window
    const float h_win{800};     //! Height of the render window
    const float w_frame{10};    //! Width of the frame

    sf::RenderWindow *window;
    Textures *texture;
    sf::Vector2f dir_1{0.0f, 0.0f};
    sf::Vector2f dir_2{0.0f, 0.0f};
    Keys keys1{};
    Keys keys2{};
    sf::Font font{};

private:

    //! Function will check which key was pressed and add correction value to the direction of the
    //! player.
    void on_key_use(bool pressed, sf::Keyboard::Key key);

    //! If correct key is pressed function will add correct value to the direction variable.
    void direction(bool player_one);
};

#endif

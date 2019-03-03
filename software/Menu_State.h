#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Key_Input.h"
#include "Smart_Pointer.h"
#include "Textures.h"
#include "Box.h"

/*!
 * \brief The Menu_State class handle the menu of the game.
 */

class Menu_State : public Key_Input
{
    //! The Menu_State class handle the menu of the game. This class should be called in the beginning of
    //! the game. The class will render a menu of five chooses - Single Player, Duo Player, Highscore, Credits
    //! and Quit. The class need a sf::RenderWindow and textures to render the window propelery.
    //! When a selection is made an int value is returned to teh game engine.
public:
    Menu_State(sf::RenderWindow *window, Textures *texture);
    ~Menu_State();
    Menu_State(Menu_State const &other) = default;
    Menu_State & operator = (Menu_State const &other) = default;

    //! The virtual public run() function keep the main loop of the menu system.
    //! Selection is made by using the up/down keys on the keyboard and select
    //! with return. The pressed key is recived by the Key_Input class, check_keys(bool).
    int run() override;
private:

    //! Initiate create all objects which will be shown on the gamefield. Only the ball
    //! will be moving showing which selection will be selected when pressing enter.
    void initiate();

    //! The update_render_game() function will execute the movement of the ball and
    //! the rendering of the gamefield.
    void update_render_game();

    const unsigned int max_nr_select{5};    //! Variable which set how many states there is in the game

    unsigned int select{};
    std::vector<Solid_Object*> boxes{};
    std::vector<sf::Text*> texts{};
    sf::Text txt{};
    sf::CircleShape ball{};
};

#endif

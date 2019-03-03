#ifndef HIGHSCORE_STATE_H
#define HIGHSCORE_STATE_H

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Key_Input.h"
#include "Smart_Pointer.h"
#include "Textures.h"
#include "Box.h"

/*!
 * \brief Highscore class handle the highscore list of the game.
 */

class HighScore_State: public Key_Input
{
    //! Highscore class handle the highscore list of the game. The class will
    //! create a view with textboxes. All data is collected from the Game_Engine class
    //! and show on the window.
public:
    HighScore_State(sf::RenderWindow *window, Textures *texture,
    std::vector<std::pair<int, std::string>> &score_list);
    ~HighScore_State();
    HighScore_State(HighScore_State const &other) = default;
    HighScore_State & operator = (HighScore_State const &other) = default;

    //! The run() function will execute the highscore of the game. The view is shown
    //! on the gamefield.
    int run() override;
private:

    //! Initiate() will create all objects which is shown on the highscore list
    void initiate();

    //! Initiate_game() will reset the text of the text boxes.
    void initiate_game();

    //! Render the highscore. There is no position update in this function
    void update_render_game();

    std::vector<std::pair<int, std::string>> &score_list;
    std::vector<Solid_Object*> boxes{};
    std::vector<sf::Text*> texts{};
};

#endif //HIGHSCORE_STATE_H

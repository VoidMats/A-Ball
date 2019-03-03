#ifndef GAMEOVER_STATE_H
#define GAMEOVER_STATE_H

#include <SFML/Graphics.hpp>
#include <utility>
#include <string>
#include <iostream>
#include "Key_Input.h"
#include "Textures.h"
#include "Box.h"
#include "Smart_Pointer.h"

/*!
 * \brief The GameOver_State class handle the end-game. Including enter name, show score.
 */

class GameOver_State : public Key_Input
{
    //! The GameOver_State class handle everything that has to be done when the game is over.
    //! The score is check against the highscore list. If the player do have a score which will
    //! break into the list, the player has to enter its name. The name is then saved into the list.
public:
    GameOver_State(sf::RenderWindow *window,
                   Textures *texture,
                   std::vector<std::pair<int, std::string>> *_score,
                   int *_player_score);
    ~GameOver_State();
    GameOver_State(GameOver_State const &other) = default;
    GameOver_State & operator = (GameOver_State const &other) = default;

    //! The run() function will execute all function for the GameOver_State
    int run() override;
private:

    //! Initiate function is called in the constructor of the class. Initiate will create all
    //! graphical objects in the field. For repeated finished game the function initiate_game()
    //! has to be called to clean text etc.
    void initiate();

    //! Initiate_game() function is called in the beginning of the run() function. This will clear
    //! any text which is left behind from last game.
    void initiate_game();

    //! Function will update any text and render the screen
    void update_render_game();

    //! Check_score() function will compare the score fom the player with the highscore list.
    //! If the player do get into the list the bool enter_name will be triggered and it will
    //! be possible to enter the name.
    void check_score();

    //! Save the score into the highscore list
    void write_score_to_memory();

    int *player_score{nullptr};
    int place{-1};
    bool enter_name{false};
    std::string name{""};
    std::vector<Solid_Object*> boxes{};
    std::vector<sf::Text*> texts{};
    std::vector<std::pair<int, std::string>> *list_score;
};

#endif //GAMEOVER_STATE_H

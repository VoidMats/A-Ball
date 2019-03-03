#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <vector>
#include <utility>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Key_Input.h"
#include "Menu_State.h"
#include "Play_State.h"
#include "Duo_State.h"
#include "GameOver_State.h"
#include "HighScore_State.h"
#include "Credit_State.h"
#include "Textures.h"
#include "Smart_Pointer.h"

<<<<<<< HEAD
/*!
 * \brief Class Game_Engine will create all necessary states and load/save all data connected to the game.
 */
=======
>>>>>>> d39218ac81597930da142d4c4a7666acaf7b2e92

class Game_Engine
{
    //! Game_Engine() will create the game and read all the data necessary for the game.
    //! Game_Engine does not need any input data to be created.

public:
    Game_Engine();
    ~Game_Engine();
    Game_Engine(Game_Engine const &other) = default;
    Game_Engine & operator = (Game_Engine const &other) = default;
    Game_Engine(Game_Engine &&other) = default;
    Game_Engine & operator = (Game_Engine &&other) = default;

    //! Function run() execute the class which is also the game. The highscore and level is imported from
    //! each file. All states is created
    void run();
private:

    //! Read the level from the file. The file has to be .txt or similar. Each line is collected this string
    //! is stored into a vector. The reading stop at max_rows (16) and this will submit a level in the game.
    //! If the word "level" is enter before max_rows the vector will be flled with empty rows.
    bool read_level_file( std::string filename );

    //! Read the highscore from the file.
    void read_score( std::string filename );

    //! Store the high score back into the file. The file is trunked before saving the new list.
    void store_score( std::string filename );

    //! Function will create all states in the game.
    void initiate();

    const unsigned int w_win{660};      //! Width of the render window
    const unsigned int h_win{800};      //! Height of the render window
    const int max_rows{16};             //! Maximum number rows with bricks
    const int max_bricks{16};           //! Maximum number bricks in one row

    unsigned int selected_menu;
    Textures *texture;
    int score;
    int *p_player_score{};

    sf::RenderWindow window{sf::VideoMode{w_win, h_win}, "A Ball"};
    sf::RenderWindow *p_win{};
    std::vector<std::vector<std::string>> vec_level{};
    std::vector<std::vector<std::string>> *p_level{};
    std::vector<std::pair<int,std::string>> score_list;
    std::vector<std::pair<int,std::string>> *p_list_score{};
    std::vector<Key_Input*> states{};

};

#endif // GAME_ENGINE_H

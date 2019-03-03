#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <thread>
#include "Key_Input.h"
#include "Base_Object.h"
#include "Solid_Object.h"
#include "Ball.h"
#include "Player.h"
#include "Brick.h"
#include "Box.h"
#include "Power_Up.h"
#include "Textures.h"
#include "Score.h"
#include "Smart_Pointer.h"

<<<<<<< HEAD
/*!
 * \brief The Play_State class handle the game
 */
=======
//! The Play_State class handle the game, where the main task is to operate the movement
//! and the rendering of all the objects in the gamefield. This class also recive the
//! important information which is shown to the user. The public virtual function run
//! will execute the game. When game is finished the score is sent back to the game
//! engine with return.
>>>>>>> d39218ac81597930da142d4c4a7666acaf7b2e92

class Play_State: public Key_Input
{
    //! The Play_State class handle the game, where the main task is to operate the movement
    //! and the rendering of all the objects in the gamefield. This class also recive the
    //! important information which is shown to the user. The public virtual function run
    //! will execute the game. When game is finished the score is sent back to the game
    //! engine.

public:
    Play_State(sf::RenderWindow *window, Textures *texture, std::vector<std::vector<std::string>> *vec);
    ~Play_State();
    Play_State(Play_State const &other) = default;
    Play_State & operator = (Play_State const &other) = default;

    //! Run function is the main loop for the game. The function take care of update, drawing and which level
    //! to execute. Important data are recived from the score class, so it could be shown for the user.
    //! The run function does not take care of the actual movement (calculation of position, direction etc).
    //! This is done by each solid_object by the update() function.
    int run() override;
private:

    //! Initiate function is called in the begining of the run() function to setup the field with correct objects.
    //! Bricks are excluded because they are created in the initiate_level() function. The ball is created
    //! in the while-loop of the run() function.
    void initiate();

    //! Function which create all objects for the next level. This is mainly the bricks which are
    //! pushed to the vector bricks.
    void initiate_level( bool &_new_level );

    //! This function update the position, text etc and render all objects on the screen. Update_render_game()
    //! has to be executed before the sf::RenderWindow.diplay() or the movement will not be registered.
    void update_render_game();

    //! Function clear the containers moving_objects, boxes, bricks, player and life from objects
    //! before starting new game. This due to any redundant objects on the field when starting
    //! new game or changing level. If bool _level is set to true only level objects will be removed.
    void clear_board(bool _level);

    //! Create a text box on the field. Textbox is added to the container text and will be render in the
    //! update_render_game().
    void create_text(float pos_x, float pos_y, std::string _text);

    const float h_player_area{175};             //! Set the height of the player moving area
    const float h_scoreboard{100};              //! Set the height of the scoreboard
    const float w_brick{40};                    //! Set the width of the brick
    const float h_brick{20};                    //! Set the height of the brick
    const int max_rows{16};                     //! Maximum number of rows with bricks
    const int max_bricks{16};                   //! Maximum number of bricks in one row

    std::vector<std::vector<std::string>> *vec_level;
    s_Ptr<Score> p_score_class;                 //! Pointer to the score class
    unsigned int nr_bricks_type_4{0};           //! Number of brick 4 in this level
    int level{0};                               //! Counter of the level running
    std::vector<sf::Text> text{};
    std::vector<sf::RectangleShape> life{};
    std::vector<Solid_Object*> moving_objects{};
    std::vector<Solid_Object*> boxes{};
    std::vector<Solid_Object*> bricks{};
    std::vector<Solid_Object*> player{};
};

#endif //PLAY_STATE_H

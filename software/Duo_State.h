#ifndef DUO_STATE_H
#define DUO_STATE_H

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


class Duo_State: public Key_Input
{
public:
    Duo_State(sf::RenderWindow *window, Textures *texture, std::vector<std::vector<std::string>> *vec);
    ~Duo_State();
    Duo_State(Duo_State const &other) = default;
    Duo_State & operator = (Duo_State const &other) = default;

    int run() override;
private:
    void initiate();
    void initiate_level(bool &_new_level , bool player_one);
    void update_render_game();
    void clear_board(bool _level);
    void create_text(float pos_x, float pos_y, std::string _text);
    void set_window(bool _widthscreen);
    void check_ball(bool _bPlayer_2);

    const float h_player_area{175}; //! Set the height of the player moving area
    const float h_scoreboard{100};  //! Set the height of the scoreboard
    const float w_brick{40};        //! Set the width of the brick
    const float h_brick{20};        //! Set the height of the brick
    const int max_rows{16};         //! Maximum number of rows with bricks
    const int max_bricks{16};       //! Maximum number of bricks in one row

    std::vector<std::vector<std::string>>* vec_level;
    s_Ptr<Score> p_score_player_1;
    s_Ptr<Score> p_score_player_2;
    unsigned int nr_bricks_type_4{0};
    int level{0};
    std::vector<sf::Text> text{};
    std::vector<sf::RectangleShape> life_player_1{};
    std::vector<sf::RectangleShape> life_player_2{};
    std::vector<Solid_Object*> moving_objects_player_1{};
    std::vector<Solid_Object*> moving_objects_player_2{};
    std::vector<Solid_Object*> boxes_player_1{};
    std::vector<Solid_Object*> boxes_player_2{};
    std::vector<Solid_Object*> bricks_player_1{};
    std::vector<Solid_Object*> bricks_player_2{};
    std::vector<Solid_Object*> player_1{};
    std::vector<Solid_Object*> player_2{};

};

#endif //DUO_STATE_H

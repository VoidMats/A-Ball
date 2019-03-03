#include "Game_Engine.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
using namespace sf;

Game_Engine::Game_Engine()
    :selected_menu{0}, texture{nullptr}
{

}

Game_Engine::~Game_Engine()
{
    for( auto it : states ) {
        delete it;
    }
    delete texture;
}

void Game_Engine::run()
{
    initiate();

    bool quit{false};
    while( !quit )
    {
        switch(selected_menu)
        {
            case 0: // Menu state
            {
                Key_Input *menu_state{new Menu_State{p_win, texture}};
                int ret = menu_state->run();
                if( ret == -1 )
                    quit = true;
                else
                    selected_menu = ret;
                delete menu_state;
                break;
            }
            case 1: // One player state
            {
                Key_Input *play_state{new Play_State{p_win, texture, p_level}};
                int ret = play_state->run();
                if( ret == -1 )
                    quit = true;
                else if ( ret == -2 )
                    selected_menu = 0;
                else if( ret >= 0 ) {
                    selected_menu = 6;
                    score = ret;
                }
                else{
                    quit = true;
                }
                delete play_state;
                break;
            }
            case 2: // Two player state
            {
                Key_Input *duo_state{new Duo_State{p_win, texture, p_level}};
                int ret = duo_state->run();
                if( ret == -1 )
                    quit = true;
                else if ( ret == 0 )
                    selected_menu = 0;
                else if( ret > 0 ) {
                    selected_menu = 6;
                    score = ret;
                }
                else{
                    quit = true;
                }
                delete duo_state;
                break;
            }
            case 3: // Highscore state
            {
                Key_Input *high_state{new HighScore_State{p_win, texture, score_list}};
                int ret = high_state->run();
                if( ret == -1 )
                    quit = true;
                else
                    selected_menu = 0;
                delete high_state;
                break;
            }
            case 4: // Credit state
            {
                Key_Input *credit_state{new Credit_State{p_win, texture}};
                int ret = credit_state->run();
                if( ret == -1 )
                    quit = true;
                else
                    selected_menu = 0;
                delete credit_state;
                break;
            }
            case 6: // Gameover state
            {
                Key_Input *over_state{new GameOver_State{p_win, texture, p_list_score, p_player_score }};
                int ret = over_state->run();
                if( ret == -1 )
                    quit = true;
                else
                {
                    selected_menu = ret;
                }
                delete over_state;
                break;
            }
            default:
            {
                quit = true;
                break;
            }
        }
    }
    store_score("highscore.txt");
}

bool Game_Engine::read_level_file(string filename)
{
    ifstream in_file{filename};
    cout << "*** Reading levels from " << filename << " ***" << endl;
    if( in_file.fail() ) {
        cout << "Fail to read text file: " << filename << endl;
        return false;
    }

    bool bEnd{false};
    unsigned int counter{1};
    while( !in_file.eof() )
    {
        vector<string> level;
        for(int i{0}; i<max_rows; ++i)
        {
            string line{""};
            if( !bEnd )
            {
                getline(in_file, line);
            }
            if( line.find("level") != line.npos )
            {
                bEnd = true;
            }
            if( bEnd )
            {
                line = "0000000000000000";
            }
            if( line.size() < max_bricks )
            {
                for(long unsigned int i{line.size()}; i<max_bricks; ++i )
                    line.push_back('0');
            }
            level.push_back( line );
        }
        vec_level.push_back( level );
        cout << "Insert level " << counter << " into memory" << endl;
        bEnd = false;
        in_file.peek();
        ++counter;
    }
    in_file.close();
    return true;
}

void Game_Engine::read_score(std::string filename)
{
    int _score;
    string name;
    ifstream ifs{filename};
    cout << "*** Reading highscore from " << filename << " ***" << endl;
    if( ifs.fail() ) {
        cout << "Failure to read file: " << filename << endl;
        return;
    }
    while( ifs >> _score >> name )
    {
        score_list.push_back(make_pair(_score, name));
    }
}

void Game_Engine::store_score(std::string filename)
{
    ofstream ofs{filename, ios::trunc};
    for ( auto it : score_list )
    {
        ofs << it.first << " " << it.second << endl;
    }
}

void Game_Engine::initiate()
{
    read_score("highscore.txt");
    read_level_file("level.txt");

    texture = new Textures;
    selected_menu = 0;
    p_win = &window;
    p_level = &vec_level;
    p_list_score = &score_list;
    p_player_score = &score;

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

}

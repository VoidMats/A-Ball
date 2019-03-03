#include "Score.h"

Score::Score(){}

void Score::add_nr_players(int _players)
{
    nr_players = _players;
}

void Score::add_player_nr(int _player)
{
    player_nr = _player;
}

void Score::add_brick( bool reset )
{
    if( reset)
        nr_added_bricks = 0;
    else
        nr_added_bricks += 1;
}

void Score::add_hit() {
    ++hits;
    if ( hits >= 8 ) {
        hits = 0;
        ++multi;
    }
}

void Score::add_score( int _number )
{
    score_point += (_number * multi);
}

void Score::reset_hit()
{
    hits = 0;
    multi = 1;
}

void Score::reset_score()
{
    score_point = 0;
}

void Score::reset_life()
{
    life = 3;
}

void Score::lose_life()
{
    --life;
}

int Score::get_score()
{
    return score_point;
}

int Score::get_multi()
{
    return multi;
}

int Score::get_life()
{
    return life;
}

int Score::get_nr_players()
{
    return nr_players;
}

int Score::get_player_nr()
{
    return player_nr;
}

int Score::get_nr_added_bricks()
{
    return nr_added_bricks;
}

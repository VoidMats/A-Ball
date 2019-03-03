#ifndef SCORE_H
#define SCORE_H

/*!
 * \brief The Score class
 * Is used to keep track of data needed by several classes in the game.
 * Tracks: Number of consecutive hits, score multiplier,
 * current score, lifes remaining.
 */

class Score
{
public:
    Score();
    void add_nr_players( int _players );
    void add_player_nr( int _player );
    void add_brick(bool reset);
    //! Adds 1 to hits.
    void add_hit();
    //! Adds 100 * multi to score_point.
    void add_score(int _number);
    //! Sets hits to 0.
    void reset_hit();
    //! Sets score_point to 0.
    void reset_score();
    //! Sets life to 3.
    void reset_life();
    //! Subtracts 1 from life.
    void lose_life();
    //! Returns current score as int.
    int get_score();
    //! Returns current multiplier as int.
    int get_multi();
    //! Returns current life as int.
    int get_life();
    //! Return nr players
    int get_nr_players();
    int get_player_nr();
    int get_nr_added_bricks();

private:
    int score_point{0};
    int hits{0};
    int multi{1};
    int life{3};
    int nr_players{1};
    int player_nr{0};
    int nr_added_bricks{0};
};

#endif

#ifndef CREDIT_STATE_H
#define CREDIT_STATE_H

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Key_Input.h"
#include "Smart_Pointer.h"
#include "Textures.h"
#include "Box.h"

/*!
 * \brief Class create a view which show some textboxes with info.
 */

class Credit_State: public Key_Input
{
    //! Credits class will only create a view and show some textboxes with info. Using the enter
    //! button will return to the Menu_State. The text is hardcoded and can only be edied in the
    //! source code. Run will execute the credit class.
public:
    Credit_State(sf::RenderWindow *window, Textures *texture);
    ~Credit_State();

    //! Run function will execute the class. It will show the class objects on the screen. If the
    //! Return or the Escape button is pressed the user will reverted back to the menu. If anything
    //! wrong run function will return -1. However, this is not likelly it will happened.
    int run() override;
private:

    //! The inititate() function will create all objects that will be shown on the screen. The
    //! function is called in the constructor of the class. Inititate_level() which are used
    //! in othwer classes is not necessary here because there is no moving objects.
    void initiate();

    //! This function will print all class objects into the screen.
    void draw_game();

    std::vector<Solid_Object*> boxes{};
    std::vector<sf::Text*> texts{};
};
#endif

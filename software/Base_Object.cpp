#include <SFML/Graphics.hpp>
#include "Base_Object.h"

Base_Object::Base_Object(float x, float y, float width, float height)
: x_pos{x}, y_pos{y}, width{width}, height{height} {}

float Base_Object::get_x() {
    return x_pos;
}

float Base_Object::get_y() {
    return y_pos;
}

float Base_Object::get_width() {
    return width;
}

float Base_Object::get_height() {
    return height;
}

void Base_Object::set_y(float new_y) {
    y_pos = new_y;
}

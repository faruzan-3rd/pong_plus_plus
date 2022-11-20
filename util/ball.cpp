#include "ball.h"
#include "util.h"


Ball::Ball(const sf::Vector2f pos, const float radius, const float thickness, const sf::Vector2f default_dir, const float default_speed):
        image(sf::CircleShape(radius)), position(pos), direction(default_dir), speed(default_speed)
{

    // image.setFillColor(sf::Color::Transparent);
    image.setFillColor(sf::Color::White);
    image.setOutlineThickness(thickness);
    image.setOutlineColor(sf::Color::White);
}


void Ball::draw(sf::RenderWindow& window){
    image.setPosition(sf::Vector2f(position.x - image.getRadius() / 2, position.y - image.getRadius() / 2));
    window.draw(image);
}


void Ball::move(const float delta){
    
    position += direction * speed * delta;
}


const sf::Vector2f& Ball::get_position() const{
    return position;
}


void Ball::reverse_y_velocity(const float reset_y1, const float reset_y2){
    direction.y *= -1;

    if(abs(reset_y1 - position.y) < abs(reset_y2 - position.y)){
        position.y = reset_y1;
    }else{
        position.y = reset_y2;
    }
}


void Ball::collide_with_player(const float player_y, const float player_height, const float reset_x){
    direction = utl::get_new_vector(player_y, player_height, position.y, direction);

    position.x = reset_x;
}

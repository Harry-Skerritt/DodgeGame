//
// Created by Harry on 13/07/2025.
//

#ifndef GLOWSPRITE_H
#define GLOWSPRITE_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

class GlowSprite : public sf::Drawable, public sf::Transformable {
  public:
    GlowSprite();
    ~GlowSprite();

    bool init(sf::Vector2f size, sf::Color glow_color, sf::Color core_color, float glow_size);
    void overrideShader(std::string shader_path);

  protected:
     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:
    sf::RectangleShape m_shape;
    sf::RenderTexture m_rt;
    sf::Shader m_shader;

    std::string m_shader_path = "../Data/Shaders/shader.frag";

    sf::Vector2f m_size;
    float m_glow_size;
    sf::Vector2f m_glow_padding;



};



#endif //GLOWSPRITE_H

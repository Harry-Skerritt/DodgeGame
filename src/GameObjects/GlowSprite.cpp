//
// Created by Harry on 13/07/2025.
//

#include "GlowSprite.h"

GlowSprite::GlowSprite() {};
GlowSprite::~GlowSprite() = default;

bool GlowSprite::init(sf::Vector2f size, sf::Color glow_color, sf::Color core_color, float glow_size)
{
    m_size = size;
    m_glow_size = glow_size;
    m_glow_padding = { glow_size * 2, glow_size * 2 };

    m_rt.create(m_size.x + m_glow_padding.x, m_size.y + m_glow_padding.y);
    m_rt.clear(sf::Color::Transparent);

    m_shape.setSize(m_size);
    m_shape.setFillColor(core_color);
    m_shape.setPosition(m_glow_size, m_glow_size);

    m_rt.draw(m_shape);
    m_rt.display();

    if (!m_shader.loadFromFile(m_shader_path, sf::Shader::Fragment)) {
        std::cerr << "Failed to load fragment shader" << std::endl;
        return false;
    }

    m_shader.setUniform("iResolution", sf::Vector2f(m_rt.getSize()));
    m_shader.setUniform("glowColor", sf::Glsl::Vec4(glow_color.r, glow_color.g, glow_color.b, 1.0f));
    m_shader.setUniform("coreColor", sf::Glsl::Vec4(core_color.r, core_color.g, core_color.b, 1.f));
    m_shader.setUniform("glowSize", m_glow_size);

    return true;
}

void GlowSprite::overrideShader(std::string shader_path)
{
  m_shader_path = shader_path;
}

void GlowSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite glow_sprite(m_rt.getTexture());
    glow_sprite.setPosition(200, 200);

    states.shader = &m_shader;
    states.blendMode = sf::BlendAlpha;
    target.draw(glow_sprite, states);
}
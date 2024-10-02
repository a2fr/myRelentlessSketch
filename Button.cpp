#include "Button.h"

void Button::Draw()
{
    // Draw the start button
    if (m_isHovering) {
        ofSetColor(150, 150, 150); // Hover color
    }
    else {
        ofSetColor(100, 100, 100); // Normal color
    }
    ofDrawRectangle(m_button);
    ofSetColor(0);
    m_buttonFont.drawString(m_name, m_button.x + m_button.width / 2 - m_buttonFont.stringWidth(m_name) / 2, m_button.y + m_button.height / 2 + m_buttonFont.stringHeight(m_name) / 4);
}

bool Button::isHover(int x, int y)
{
    m_isHovering = m_button.inside(x, y);
    return m_isHovering;
}

void Button::setPosition(ofRectangle rectangle)
{
    m_button = rectangle;
}

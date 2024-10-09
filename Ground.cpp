#include "Ground.h"

void Ground::Draw()
{
	ofSetColor(m_color);
	ofDrawRectangle(m_position.x, m_position.y, m_width, m_height);
}

void Ground::resize()
{
	m_width = ofGetWidth();
	m_position.y = ofGetHeight() - m_height;
}

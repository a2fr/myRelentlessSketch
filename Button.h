#pragma once
#ifndef Button_h
#define Button_h

#include "ofMain.h"

class Button
{
public:
	string m_name;
	ofRectangle m_button;
	ofTrueTypeFont m_titleFont;
	ofTrueTypeFont m_buttonFont;
	bool m_isHovering;

public:
	Button(string name, ofRectangle const& rectangle, bool isHovering = false) :m_name(name), m_button(rectangle), m_isHovering(isHovering) {
		//// Load custom fonts
		m_titleFont.load("goodtimesrg.otf", 55);
		m_buttonFont.load("goodtimesrg.otf", 12);
	}

	void Draw();
	bool isHover(int x, int y);
	void setPosition(ofRectangle rectangle);

};

#endif


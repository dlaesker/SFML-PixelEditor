#include <SFML/Graphics.hpp>
#include <stdio.h>

/* ********************** *
 * Author: Denis Laesker  *
 ************************ */

/* Description: This file implements a simple pixel grid that can be edited with various colors. Feel free to modify it. 
 */

// Window Size
#define WH 600
#define WW 600

// Cell Size
#define CS 10

/* Grid Size: For a Wn X Wm window size and cell size CS, there will be a total of (Wn / CS) x (Wn / CS) cells in the grid. */

#define GH (WH / CS)
#define GW (WW / CS)

// To keep track of
sf::RectangleShape rects[GH][GW];

#define NCOLORS 4
sf::Color Colors[NCOLORS] = {
	sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Black
};

int main(){
	sf::RenderWindow window(sf::VideoMode(WH, WW), "GRID");
	
	/* Initialize Grid */
	// No nested for loops on my watch.
	for(int k = 0; k < GH * GW; k += 1){
		int i = k / GW;
		int j = k % GW;
			
		rects[i][j].setSize({CS,CS});	// 10 x 10 rectangle (aka a square)
		
		rects[i][j].setOutlineColor(sf::Color::Black);
		rects[i][j].setOutlineThickness(1);
		
		rects[i][j].setPosition(CS*i,CS*j); // Offset by cell size
	}
		
	
	int INIT = 1, current_color = 0;
	sf::Event ev;
	while(window.isOpen()){
		while(window.pollEvent(ev)){
			if(ev.type == sf::Event::Closed){
				window.clear(sf::Color::White);
				window.close();
			}
			
			if(ev.type == sf::Event::KeyPressed &&
				 ev.key.code == sf::Keyboard::Space){
				current_color = (current_color + 1) % NCOLORS;
			}
		}
		
		// First time rendering :)
		if(INIT){
			window.clear(sf::Color::White);
			for(int k = 0; k < GH * GW; k += 1){
				int i = k / GW;
				int j = k % GW;
				window.draw(rects[i][j]);
			}
			window.display();
			INIT = 0;
		}
		
		// No need to redraw the entire grid all the time. Just when the mouse is pressed.
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
			
			// Retrieve the mouse position
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			// If mouse is within the window
			if((mousePos.x <= WW && mousePos.y <= WH) &&
				 (mousePos.x >= 0  && mousePos.y >= 0)){
				
				window.clear(sf::Color::White);
				
				// Retrieve the positions within the bounding box (cell)
				int _x = mousePos.x / CS;
				int _y = mousePos.y / CS;
			
				if(_x < WH && _y < WW){ // One can never be too safe ;)
					rects[_x][_y].setFillColor(Colors[current_color]);
				}
			}
			
			// Redraw the updated grid
			for(int k = 0; k < GH * GW; k += 1){
				int i = k / GW;
				int j = k % GW;
				window.draw(rects[i][j]);
			}
			window.display();
		}
	}
	return 0;
}

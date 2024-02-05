#pragma once

namespace sf {
    class RenderWindow;
    class Event;
}



struct Render {
    sf::RenderWindow* pWindow;
    sf::Event* pEvent;
    int iWidth;
    int iHeight;
    void Update(); // Update SFML Render
};




#include <SFML/Graphics.hpp>
#include <array>

void draw_board(sf::RenderWindow &window);

int main()
{
    //the sf::Titlebar | sf::Style::Close prevents resizing of the window
    sf::RenderWindow window(sf::VideoMode(600, 600), "Tic Tac Toe", sf::Style::Titlebar | sf::Style::Close);
    
    int turn = 1; //1 for O, 2 for X
    
    //the initial board
    std::array<std::array<int, 3>, 3> board{
        {{0,0,0},
         {0,0,0},
         {0,0,0}}
    };
    
    //main game loop
    while (window.isOpen())
    {
        //handle event
        sf::Event event;
        while (window.pollEvent(event))
        {
            //close window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //draw the board
        draw_board(window);
    }
    
    return 0;
}

//draw the # board with lines
void draw_board(sf::RenderWindow &window)
{
    //clear the window to black
    window.clear(sf::Color::Black);
    
    //draw horizontal lines
    sf::RectangleShape line1(sf::Vector2f(600, 5));
    line1.setFillColor(sf::Color::White);
    line1.setPosition(0, 200);
    
    sf::RectangleShape line2 = line1;
    line2.setPosition(0, 400);
    
    //draw vertical lines;
    sf::RectangleShape line3(sf::Vector2f(5, 600));
    line3.setFillColor(sf::Color::White);
    line3.setPosition(200, 0);
    
    sf::RectangleShape line4 = line3;
    line4.setPosition(400, 0);
    
    //draw to the window
    window.draw(line1);
    window.draw(line2);
    window.draw(line3);
    window.draw(line4);
    
    window.display();
}
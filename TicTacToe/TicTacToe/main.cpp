#include <SFML/Graphics.hpp>
#include <vector>

#include <iostream>

void draw_board(sf::RenderWindow &window);
void draw_slot(sf::RenderWindow &window, int symbol ,int x_pos, int y_pos);
bool check_win(std::vector<std::vector<int>> &board, int side);

int main()
{
    //the sf::Titlebar | sf::Style::Close prevents resizing of the window
    sf::RenderWindow window(sf::VideoMode(600, 600), "Tic Tac Toe", sf::Style::Titlebar | sf::Style::Close);
    
    int turn = 1; //1 for O, 2 for X
    
    //the initial board
    std::vector<std::vector<int>> board{
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
        
        //draw the slots
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                draw_slot(window, board[i][j], i, j);
                
        window.display();
    }
    
    return 0;
}

//draw the # board with lines
void draw_board(sf::RenderWindow &window)
{
    //clear the window to black
    window.clear(sf::Color::Black);
    
    //draw horizontal lines
    sf::RectangleShape line1(sf::Vector2f(600, 2));
    line1.setFillColor(sf::Color::White);
    line1.setPosition(0, 200);
    
    sf::RectangleShape line2 = line1;
    line2.setPosition(0, 400);
    
    //draw vertical lines;
    sf::RectangleShape line3(sf::Vector2f(2, 600));
    line3.setFillColor(sf::Color::White);
    line3.setPosition(200, 0);
    
    sf::RectangleShape line4 = line3;
    line4.setPosition(400, 0);
    
    
    //draw to the window
    window.draw(line1);
    window.draw(line2);
    window.draw(line3);
    window.draw(line4);
}

//draw each slot with X or O
void draw_slot(sf::RenderWindow &window, int symbol, int x_pos, int y_pos)
{

    if (symbol == 1)      //O
    {
        sf::CircleShape shape(90); //radius of 100
        shape.setFillColor(sf::Color::Transparent);   //the inner loop of O
        shape.setOutlineThickness(5);
        shape.setOutlineColor(sf::Color::White);
        shape.setPosition(5 + (205 * x_pos), 5 + (205 * y_pos));
        
        window.draw(shape);
    }
    else if (symbol == 2) //X
    {
        //the \ cross
        sf::RectangleShape cross1(sf::Vector2f(200, 5));
        cross1.setPosition(25 + (210 * x_pos), 20 + (210 * y_pos));
        cross1.rotate(45);
        cross1.setFillColor(sf::Color::White);
        
        //the / cross
        sf::RectangleShape cross2(sf::Vector2f(200,5));
        cross2.setPosition(25 + (210 * x_pos), 165 + (205 * y_pos));
        cross2.rotate(-45);
        cross2.setFillColor(sf::Color::White);
        
        window.draw(cross1);
        window.draw(cross2);
    }
}

bool check_win(std::vector<std::vector<int>> &board, int side)
{
    int count;
    
    //check horizontally
    for (int i = 0; i < 3; ++i)
    {
        //each row
        count = 0;
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == side)
                ++count;
        }
        
        if (count == 3)
        {
            return true;
        }
    }
    
    //check vertically
    for (int j = 0; j < 3; ++j)
    {
        //each column
        count = 0;
        for (int i = 0; i < 3; ++i)
        {
            if (board[i][j] == side)
                ++count;
        }
        
        if (count == 3)
        {
            return true;
        }
    }
    
    //check diagonally
    count = 0;
    for (int i,j = 0; i < 3; ++i, ++j)
    {
        if (board[i][j] == side)
            ++count;
    }
    
    if (count == 3)
    {
        return true;
    }
    
    count = 0;
    for (int i = 0, j = 2; i < 3; ++i, --j)
    {
        if (board[i][j] == side)
            ++count;
    }
    
    if (count == 3)
    {
        return true;
    }
    
    return false;
}
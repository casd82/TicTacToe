#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "ResourcePath.hpp"

void draw_board(sf::RenderWindow &window);
void draw_slot(sf::RenderWindow &window, int symbol ,int x_pos, int y_pos);
bool check_win(std::vector<std::vector<int>> &board, int side);
bool handle_click(std::vector<std::vector<int>> &board, int side, int x, int y);
void draw_win_scene(sf::RenderWindow &window, int side);

int main()
{
    //the sf::Titlebar | sf::Style::Close prevents resizing of the window
    sf::RenderWindow window(sf::VideoMode(600, 600), "Tic Tac Toe", sf::Style::Titlebar | sf::Style::Close);
    
    int turn = 1; //1 for O, 2 for X
    bool win = false;
    
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
            
            //handle click
            if (!win && event.type == sf::Event::MouseButtonPressed)
            {
                if(handle_click(board, turn, event.mouseButton.x, event.mouseButton.y))
                {
                    //check if win
                    win = check_win(board, turn);
                    
                    //change turn
                    if (!win)
                    {
                        if (turn == 1)
                        {
                            turn = 2;
                        }
                        else
                        {
                            turn = 1;
                        }
                    }
                }
            }
        }
        
        //draw the board
        draw_board(window);
        
        //draw the slots
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                draw_slot(window, board[i][j], i, j);
        
        if (win)
        {
            draw_win_scene(window, turn);
        }
            
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
    for (int i = 0, j = 0; i < 3; ++i, ++j)
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

bool handle_click(std::vector<std::vector<int>> &board, int side, int io, int jo)
{
    //locate which slot is clicked
    int i, j;
    
    //y for i
    if (io < 200)
    {
        i = 0;
    }
    else if (io < 400)
    {
        i = 1;
    }
    else
    {
        i = 2;
    }
    
    //x for j
    if (jo < 200)
    {
        j = 0;
    }
    else if (jo < 400)
    {
        j = 1;
    }
    else
    {
        j = 2;
    }
    
    if (board[i][j] == 0)   //if the slot is empty
    {
        board[i][j] = side;
        return true;
    }
    
    return false;
}

void draw_win_scene(sf::RenderWindow &window, int side)
{
    sf::Text text;
    sf::Font font;
    font.loadFromFile(resourcePath() + "Cut the crap.ttf");
    text.setFont(font);
    text.setCharacterSize(80);
    text.setColor(sf::Color::Yellow);
    text.setPosition(175, 250);
    
    if (side == 1)
    {
        text.setString("O wins");
    }
    else
    {
        text.setString("X wins");
    }
    
    window.draw(text);
}
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <string>
#include <ctime>   
#include <fstream>
#include <cstdio>
#include <cstdlib>
using namespace sf;
int trapRecord1 = 0, trapRecord2 = 0, trapRecord3 = 0;
void openrecord();
const int M = 25;
const int N = 40;

int grid[M][N] = { 0 };
int ts = 18; //tile size

struct Enemy
{
    int x, y, dx, dy;

    Enemy()
    {
        x = 300;
        y = 300;
        dx = 4 - rand() % 8;
        dy = 4 - rand() % 8;
    }

    void move()
    {
        x += dx; if (grid[y / ts][x / ts] == 1) { dx = -dx; x += dx; }
        y += dy; if (grid[y / ts][x / ts] == 1) { dy = -dy; y += dy; }
    }
};

void drop(int y, int x)
{
    if (grid[y][x] == 0) grid[y][x] = -1;
    if (grid[y - 1][x] == 0) drop(y - 1, x);
    if (grid[y + 1][x] == 0) drop(y + 1, x);
    if (grid[y][x - 1] == 0) drop(y, x - 1);
    if (grid[y][x + 1] == 0) drop(y, x + 1);
}

int main()
{
    srand(time(0));
    openrecord();

    RenderWindow window(VideoMode(N * ts, M * ts * 1.08), "Trap the Flys");
    window.setFramerateLimit(60);

    Texture t1, t2, t3, t4;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/fly-3-removebg-preview.png");
    t4.loadFromFile("images/background.jpg");

    Sprite sTile(t1), sGameover(t2), sEnemy(t3), background(t4);
    sGameover.setPosition(100, 100);
    sEnemy.setOrigin(20, 20);
    background.setPosition(0, 36);

    int enemyCount = 4;
    Enemy a[10];

    bool Game = true;
    int x = 0, y = 2, dx = 0, dy = 0;
    float timer = 0, delay = 0.07;
    Clock clock;

    for (int i = 0; i < M + 2; i++)
        for (int j = 0; j < N; j++)
            if (i == 2 || j == 0 || i == M + 1 || j == N - 1)  grid[i][j] = 1;

    int oldScore = 9, score = 0;
    while (window.isOpen())
    {



        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            //std::cout << "in";
            /*if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::Escape)
                {
                    for (int i = 1; i < M - 1; i++)
                        for (int j = 1; j < N - 1; j++)
                            grid[i][j] = 0;

                    x = 10; y = 0;
                    Game = true;
                }*/
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) { dx = -1; dy = 0; };
        if (Keyboard::isKeyPressed(Keyboard::Right)) { dx = 1; dy = 0; };
        if (Keyboard::isKeyPressed(Keyboard::Up)) { dx = 0; dy = -1; };
        if (Keyboard::isKeyPressed(Keyboard::Down)) { dx = 0; dy = 1; };

        if (!Game)
        {
            if (score > trapRecord3)
            {
                if (score > trapRecord2)
                {
                    if (score > trapRecord1)
                    {
                        trapRecord3 = trapRecord2;
                        trapRecord2 = trapRecord1;
                        trapRecord1 = score;
                        score = 0;
                    }
                    else
                    {
                        trapRecord3 = trapRecord2;
                        trapRecord2 = score;
                        score = 0;
                    }
                }
                else
                {
                    trapRecord3 = score;
                    score = 0;
                }
            }
            std::ofstream recordfile;
            recordfile.open("images/trapRecord.txt");

            recordfile << trapRecord1 << "\n" << trapRecord2 << "\n" << trapRecord3;
            recordfile.close();
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                window.clear();
                oldScore = 9;
                score = 0;
                dx = dy = 0;
                x = 0;
                y = 2;
                for (int i = 2; i < M + 2; i++)
                    for (int j = 0; j < N; j++)
                        if (i == 2 || j == 0 || i == M + 1 || j == N - 1)  grid[i][j] = 1;
                        else grid[i][j] = 0;
                /*for (int i = 2; i < M + 2; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        std::cout << grid[i][j];
                    }
                    std::cout << "\n";
                }*/



                Game = true;
            }

        }

        if (!Game) continue;
        score = 0;
        for (int i = 3; i < M + 1; i++)
        {
            for (int j = 1; j < N - 1; j++)
            {
                if (grid[i][j] == 1)
                {
                    score += 1;
                }
            }
        }
        if (score != oldScore)
        {
            oldScore = score;
            //std::cout << "score:" <<score << "\n";

        }
        if (timer > delay)
            if (dy != 0 or dx != 0)
            {
                if (grid[y][x] == 2 && grid[y + dy][x + dx] == 2) Game = false;
                x += dx;
                y += dy;
                dy = 0;
                dx = 0;

                if (x < 0) x = 0; if (x > N - 1) x = N - 1;
                if (y < 2) y = 2; if (y > M + 1) y = M + 1;

                //if (grid[y][x]==2 ) Game=false;
                if (grid[y][x] == 0) grid[y][x] = 2;
                timer = 0;
            }

        for (int i = 0; i < enemyCount; i++) a[i].move();



        if (grid[y][x] == 1)
        {
            //if (dx != 0 or dy != 0)
            {
                dx = dy = 0;

                for (int i = 0; i < enemyCount; i++)
                    drop(a[i].y / ts, a[i].x / ts);
                for (int i = 0; i < M + 2; i++)
                    for (int j = 0; j < N; j++)
                        if (grid[i][j] == -1) grid[i][j] = 0;
                        else grid[i][j] = 1;
            }
        }

        for (int i = 0; i < enemyCount; i++)
            if (grid[a[i].y / ts][a[i].x / ts] == 2) Game = false;


        /////////draw//////////
        window.clear();
        window.draw(background);
        for (int i = 2; i < M + 2; i++)
            for (int j = 0; j < N; j++)
            {
                if (grid[i][j] == 0) continue;
                if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts));
                if (grid[i][j] == 2) sTile.setTextureRect(IntRect(54, 0, ts, ts));
                sTile.setPosition(j * ts, i * ts);
                window.draw(sTile);
            }
        sTile.setTextureRect(IntRect(36, 0, ts, ts));
        sTile.setPosition(x * ts, y * ts);
        window.draw(sTile);

        sEnemy.rotate(10);
        for (int i = 0; i < enemyCount; i++)
        {
            sEnemy.setPosition(a[i].x, a[i].y);
            window.draw(sEnemy);
        }
        //int score = 0;
        std::string str1 = "SCORE:";
        std::string str2 = std::to_string(score);
        std::string str = str1 + str2;
        Text text, title;
        Font font;
        font.loadFromFile("images/Metropolitan.ttf");
        text.setFont(font);
        text.setPosition(0, 0);
        if (score > trapRecord1)
        {
            text.setFillColor(sf::Color::Red);
        }
        else
        {
            text.setFillColor(sf::Color::White);
        }
        text.setCharacterSize(30);
        text.setString(str);
        window.draw(text);
        title.setFont(font);
        title.setPosition(270, 0);
        title.setFillColor(sf::Color::White);
        title.setCharacterSize(30);
        title.setString("Trap the Flys");
        window.draw(title);

        if (!Game)
        {
            window.draw(sGameover);
            Text text3;
            text3.setFont(font);
            text3.setPosition(178, 415);
            text3.setFillColor(sf::Color::White);
            text3.setCharacterSize(30);
            text3.setString("press Enter to start again");
            window.draw(text3);
            if (score > trapRecord1)
            {
                Text text2;
                text2.setFont(font);
                text2.setPosition(200, 230);
                text2.setFillColor(sf::Color::Red);
                text2.setCharacterSize(50);
                text2.setString("New Record!!!");
                window.draw(text2);

            }
        }
        /*while (!Game)
        {
            //std::cout << "Enter";
            if (Keyboard::isKeyPressed(Keyboard::Enter)) std::cout << "Enter";
            //std::cout << "Enter";
            Event f;
            /*while (window.pollEvent(f))
            {

                if (f.type == Event::Closed)
                    window.close();
                std::cout << "in";
                if (f.type == Event::KeyPressed)
                {
                    if (f.key.code == Keyboard::Enter)
                    {
                        std::cout << "true";
                        //window.close();
                    }
                }

            }
        }*/
        window.display();
    }
    /*if (score > record3)
    {
        if (score > record2)
        {
            if (score > record1)
            {
                record3 = record2;
                record2 = record1;
                record1 = score;
            }
            else
            {
                record3 = record2;
                record2 = score;
            }
        }
        else
        {
            record3 = score;
        }
    }
    std::ofstream recordfile;
    recordfile.open("images/trapRecord.txt");
    recordfile << trapRecord1 << "\n" << trapRecord2 << "\n" << trapRecord3;
    recordfile.close();*/

    return 0;
}

void openrecord() {
    std::fstream  file;
    char score[20] = { 0 };
    file.open("images/trapRecord.txt", std::ios::in);
    srand(time(0));
    char score2[20] = { 0 };
    char score3[20] = { 0 };
    file.getline(score, 20);
    file.getline(score2, 20);
    file.getline(score3, 20);
    int len0 = strlen(score);
    trapRecord1 = atoi(score);
    trapRecord2 = atoi(score2);
    trapRecord3 = atoi(score3);
    for (int i = 0; i < 20; i++) {
        //cout << score[i]<<score2[i];
    }
    //std::cout << record1 << ',' << record2 << ',' << record3;
    file.close();
}

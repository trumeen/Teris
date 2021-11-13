#include "SNAKE.hpp"

SNAKE::SNAKE(/* args */)
{
}

SNAKE::~SNAKE()
{
}

bool SNAKE::move()
{
    switch (currentDirection)
    {
    case DIRECTION_DOWN:
        down();
        break;
    case DIRECTION_UP:
        up();
        break;
    case DIRECTION_LEFT:
        left();
        break;
    case DIRECTION_RIGHT:
        right();
        break;
    default:
        break;
    }
}

bool SNAKE::left()
{
    currentDirection = DIRECTION_LEFT;
    if (isOver(currentDirection))
    {
        return false;
    }
    else
    {
        if (target[POSITION_X] == dots[0][POSITION_X] - 1 && target[POSITION_Y] == dots[0][POSITION_Y])
        {
            add2Head();
        }
        else
        {
            for (int i = length; i >= 0; i--)
            {
                if (i == 0)
                {
                    dots[i][POSITION_X] = dots[i][POSITION_X] - 1;
                    dots[i][POSITION_Y] = dots[i][POSITION_Y];
                }
                else
                {
                    dots[i][POSITION_X] = dots[i - 1][POSITION_X];
                    dots[i][POSITION_Y] = dots[i - 1][POSITION_Y];
                }
            }
            show();
        }
        return true;
    }
}

bool SNAKE::right()
{
    currentDirection = DIRECTION_RIGHT;
    if (isOver(currentDirection))
    {
        return false;
    }
    else
    {
        if (target[POSITION_X] == dots[0][POSITION_X] + 1 && target[POSITION_Y] == dots[0][POSITION_Y])
        {
            add2Head();
        }
        else
        {
            for (int i = length; i >= 0; i--)
            {
                if (i == 0)
                {
                    dots[i][POSITION_X] = dots[i][POSITION_X] + 1;
                    dots[i][POSITION_Y] = dots[i][POSITION_Y];
                }
                else
                {
                    dots[i][POSITION_X] = dots[i - 1][POSITION_X];
                    dots[i][POSITION_Y] = dots[i - 1][POSITION_Y];
                }
            }
            show();
        }

        return true;
    }
}

bool SNAKE::up()
{
    currentDirection = DIRECTION_UP;
    if (isOver(currentDirection))
    {
        return false;
    }
    else
    {
        if (target[POSITION_X] == dots[0][POSITION_X] && target[POSITION_Y] == dots[0][POSITION_Y] - 1)
        {
            add2Head();
        }
        else
        {
            for (int i = length; i >= 0; i--)
            {
                if (i == 0)
                {
                    dots[i][POSITION_X] = dots[i][POSITION_X];
                    dots[i][POSITION_Y] = dots[i][POSITION_Y] - 1;
                }
                else
                {
                    dots[i][POSITION_X] = dots[i - 1][POSITION_X];
                    dots[i][POSITION_Y] = dots[i - 1][POSITION_Y];
                }
            }
            show();
        }
        return true;
    }
}

bool SNAKE::down()
{
    currentDirection = DIRECTION_DOWN;
    if (isOver(currentDirection))
    {
        return false;
    }
    else
    {
        if (target[POSITION_X] == dots[0][POSITION_X] && target[POSITION_Y] == dots[0][POSITION_Y] + 1)
        {
            add2Head();
        }
        else
        {
            for (int i = length; i >= 0; i--)
            {
                if (i == 0)
                {
                    dots[i][POSITION_X] = dots[i][POSITION_X];
                    dots[i][POSITION_Y] = dots[i][POSITION_Y] + 1;
                }
                else
                {
                    dots[i][POSITION_X] = dots[i - 1][POSITION_X];
                    dots[i][POSITION_Y] = dots[i - 1][POSITION_Y];
                }
            }
            show();
        }
        return true;
    }
}

void SNAKE::start()
{
    length = 1;
    dots[0][POSITION_X] = COLS / 2;
    dots[0][POSITION_Y] = ROWS / 2;
    add();
    show();
}

void SNAKE::add2Head()
{
    length++;
    for (int i = length - 1; i >= 0; i--)
    {
        if (i == 0)
        {
            dots[i][POSITION_X] = target[POSITION_X];
            dots[i][POSITION_Y] = target[POSITION_Y];
        }
        else
        {
            dots[i][POSITION_X] = dots[i - 1][POSITION_X];
            dots[i][POSITION_Y] = dots[i - 1][POSITION_Y];
        }
        Serial.print(dots[i][POSITION_X]);
        Serial.print("######");
        Serial.println(dots[i][POSITION_Y]);
    }
    show();
    add();
    show();
    callback(10);
}

bool SNAKE::isOver(int direction)
{
    switch (direction)
    {
    case DIRECTION_LEFT:
        if (dots[0][POSITION_X] - 1 < 0 || contains(dots[0][POSITION_X] - 1, dots[0][POSITION_Y]))
        {
            return true;
        }
        break;

    case DIRECTION_RIGHT:
        if (dots[0][POSITION_X] + 1 >= COLS || contains(dots[0][POSITION_X] + 1, dots[0][POSITION_Y]))
        {
            return true;
        }
        break;

    case DIRECTION_DOWN:
        if (dots[0][POSITION_Y] + 1 >= ROWS || contains(dots[0][POSITION_X], dots[0][POSITION_Y] + 1))
        {
            return true;
        }
        break;

    case DIRECTION_UP:
        if (dots[0][POSITION_Y] - 1 < 0 || contains(dots[0][POSITION_X], dots[0][POSITION_Y] - 1))
        {
            return true;
        }
        break;

    default:
        break;
    }
}

bool SNAKE::contains(int x, int y)
{
    for (int i = 0; i < length; i++)
    {
        if (dots[i][POSITION_X] == x && dots[i][POSITION_Y] == y)
        {
            return true;
        }
    }
    return false;
}

void SNAKE::add()
{
    int count = 0;
    int space[200][2];
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            if (!contains(i, j))
            {
                space[count][POSITION_X] = i;
                space[count][POSITION_Y] = j;
                count++;
            }
        }
    }

    int pos = rand() % (count - 1);
    Serial.print(count);
    Serial.print("***********");
    Serial.println(pos);
    target[POSITION_X] = space[pos][POSITION_X];
    target[POSITION_Y] = space[pos][POSITION_Y];
}

void SNAKE::show()
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            myCanvas[i][j] = 0;
        }
    }

    Serial.println(length);
    myCanvas[target[POSITION_X]][target[POSITION_Y]] = 0x00ff00;
    for (int i = 0; i < length; i++)
    {
        Serial.print(dots[i][POSITION_X]);
        Serial.print("-----");
        Serial.println(dots[i][POSITION_Y]);
        myCanvas[dots[i][POSITION_X]][dots[i][POSITION_Y]] = 0xFF0000;
    }
}

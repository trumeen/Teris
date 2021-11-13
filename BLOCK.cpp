#include "BLOCK.hpp"

#define DOTS_CNT 4
Block::Block()
{
}

Block::~Block()
{
}

void Block::show()
{
    int color = 0;
    switch (myType)
    {
    case TERIS_TYPE_O:
        color = 0xFFEB3B;
        break;
    case TERIS_TYPE_I:
        color = 0x2196F3;
        break;
    case TERIS_TYPE_S:
        color = 0xF44336;
        break;
    case TERIS_TYPE_Z:
        color = 0x4CAF50;
        break;

    case TERIS_TYPE_L:
        color = 0xFF9800;
        break;

    case TERIS_TYPE_J:
        color = 0xE91E63;
        break;

    case TERIS_TYPE_T:
        color = 0x673AB7;
        break;
    default:
        break;
    }
    //更新本次的位置
    for (int i = 0; i < DOTS_CNT; i++)
    {
        myCanvas[dots[i][POSITION_X]][dots[i][POSITION_Y]] = color;
    }
}

void Block::clear()
{
    //清理位置
    for (int i = 0; i < DOTS_CNT; i++)
    {
        myCanvas[dots[i][POSITION_X]][dots[i][POSITION_Y]] = 0;
    }
}

void Block::newBolck(int type)
{
    currentAngle = 0;
    myType = type;
    switch (myType)
    {
    case TERIS_TYPE_O:
        dots[0][POSITION_X] = 4;
        dots[0][POSITION_Y] = 0;

        dots[1][POSITION_X] = 4;
        dots[1][POSITION_Y] = 1;

        dots[2][POSITION_X] = 5;
        dots[2][POSITION_Y] = 0;

        dots[3][POSITION_X] = 5;
        dots[3][POSITION_Y] = 1;
        break;

    case TERIS_TYPE_I:
        dots[0][POSITION_X] = 4;
        dots[0][POSITION_Y] = 0;

        dots[1][POSITION_X] = 4;
        dots[1][POSITION_Y] = 1;

        dots[2][POSITION_X] = 4;
        dots[2][POSITION_Y] = 2;

        dots[3][POSITION_X] = 4;
        dots[3][POSITION_Y] = 3;
        break;

    case TERIS_TYPE_L:
        dots[0][POSITION_X] = 4;
        dots[0][POSITION_Y] = 0;

        dots[1][POSITION_X] = 4;
        dots[1][POSITION_Y] = 1;

        dots[2][POSITION_X] = 4;
        dots[2][POSITION_Y] = 2;

        dots[3][POSITION_X] = 5;
        dots[3][POSITION_Y] = 2;
        break;

    case TERIS_TYPE_J:
        dots[0][POSITION_X] = 4;
        dots[0][POSITION_Y] = 0;

        dots[1][POSITION_X] = 4;
        dots[1][POSITION_Y] = 1;

        dots[2][POSITION_X] = 4;
        dots[2][POSITION_Y] = 2;

        dots[3][POSITION_X] = 3;
        dots[3][POSITION_Y] = 2;
        break;
    case TERIS_TYPE_S:
        dots[0][POSITION_X] = 3;
        dots[0][POSITION_Y] = 1;

        dots[1][POSITION_X] = 4;
        dots[1][POSITION_Y] = 1;

        dots[2][POSITION_X] = 4;
        dots[2][POSITION_Y] = 0;

        dots[3][POSITION_X] = 5;
        dots[3][POSITION_Y] = 0;
        break;

    case TERIS_TYPE_Z:
        dots[0][POSITION_X] = 3;
        dots[0][POSITION_Y] = 0;

        dots[1][POSITION_X] = 4;
        dots[1][POSITION_Y] = 0;

        dots[2][POSITION_X] = 4;
        dots[2][POSITION_Y] = 1;

        dots[3][POSITION_X] = 5;
        dots[3][POSITION_Y] = 1;
        break;

    case TERIS_TYPE_T:
        dots[0][POSITION_X] = 4;
        dots[0][POSITION_Y] = 0;

        dots[1][POSITION_X] = 3;
        dots[1][POSITION_Y] = 1;

        dots[2][POSITION_X] = 4;
        dots[2][POSITION_Y] = 1;

        dots[3][POSITION_X] = 5;
        dots[3][POSITION_Y] = 1;
        break;

    default:
        break;
    }
}

bool Block::down(int speed)
{
    clear();
    //判断对应的四个点是否已经到达边界
    for (int i = 0; i < DOTS_CNT; i++)
    {
        //如果下方有了方块则不移动
        if (myCanvas[dots[i][POSITION_X]][dots[i][POSITION_Y] + 1] != 0)
        {
            show();
            return false;
        }
        //如果已经达到边框
        if (dots[i][POSITION_Y] >= 19)
        {
            show();
            return false;
        }
    }
    //判断对应的四个点是否已经到达边界
    for (int i = 0; i < DOTS_CNT; i++)
    {
        dots[i][POSITION_Y]++;
    }
    show();
    return true;
}

bool Block::left()
{
    clear();
    //判断对应的四个点是否已经到达边界
    for (int i = 0; i < DOTS_CNT; i++)
    {

        //如果已经达到边框
        if (dots[i][POSITION_X] == 0)
        {
            show();
            return false;
        }
        //如果左方有了方块则不移动
        if (myCanvas[dots[i][POSITION_X] - 1][dots[i][POSITION_Y]] != 0)
        {
            show();
            return false;
        }
    }
    //判断对应的四个点是否已经到达边界
    for (int i = 0; i < DOTS_CNT; i++)
    {
        dots[i][POSITION_X]--;
    }
    show();
    return true;
}

bool Block::right()
{
    clear();
    //判断对应的四个点是否已经到达边界
    for (int i = 0; i < DOTS_CNT; i++)
    {

        //如果已经达到边框
        if (dots[i][POSITION_X] == COLS - 1)
        {
            show();
            return false;
        }
        //如果右方有了方块则不移动
        if (myCanvas[dots[i][POSITION_X] + 1][dots[i][POSITION_Y]] != 0)
        {
            show();
            return false;
        }
    }
    //判断对应的四个点是否已经到达边界
    for (int i = 0; i < DOTS_CNT; i++)
    {
        dots[i][POSITION_X]++;
    }
    show();
    return true;
}

bool Block::up()
{
    clear();

    switch (myType)
    {
    case TERIS_TYPE_O:
        show();
        return false;
        break;

    case TERIS_TYPE_I:
        if (currentAngle == 0)
        {
            //从竖直变成横向时判断，1、第二个左边一格没有；2、第二个右边一格没有；3、第二个右边两格没有
            if (myCanvas[dots[1][POSITION_X] - 1][dots[1][POSITION_Y]] == 0 && myCanvas[dots[1][POSITION_X] + 1][dots[1][POSITION_Y]] == 0 && myCanvas[dots[1][POSITION_X] + 2][dots[1][POSITION_Y]] == 0)
            {
                //可以变换
                dots[0][POSITION_X] = dots[1][POSITION_X] - 1;
                dots[0][POSITION_Y] = dots[1][POSITION_Y];

                dots[2][POSITION_X] = dots[1][POSITION_X] + 1;
                dots[2][POSITION_Y] = dots[1][POSITION_Y];

                dots[3][POSITION_X] = dots[1][POSITION_X] + 2;
                dots[3][POSITION_Y] = dots[1][POSITION_Y];
                currentAngle = 90;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        else
        {
            //从横向变成竖直的判断，
            if (myCanvas[dots[1][POSITION_X]][dots[1][POSITION_Y] - 1] == 0 && myCanvas[dots[1][POSITION_X]][dots[1][POSITION_Y] + 1] == 0 && myCanvas[dots[1][POSITION_X]][dots[1][POSITION_Y] + 2] == 0)
            {
                //可以变换
                dots[0][POSITION_X] = dots[1][POSITION_X];
                dots[0][POSITION_Y] = dots[1][POSITION_Y] - 1;

                dots[2][POSITION_X] = dots[1][POSITION_X];
                dots[2][POSITION_Y] = dots[1][POSITION_Y] + 1;

                dots[3][POSITION_X] = dots[1][POSITION_X];
                dots[3][POSITION_Y] = dots[1][POSITION_Y] + 2;
                currentAngle = 0;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        break;

    case TERIS_TYPE_L:
        if (currentAngle == 0)
        {
            //第二个方格，1、左边第一个无；2、左边一个下一个无；3、右边第一个无
            if (myCanvas[dots[1][POSITION_X] - 1][dots[1][POSITION_Y]] == 0 && myCanvas[dots[1][POSITION_X] - 1][dots[1][POSITION_Y] + 1] == 0 && myCanvas[dots[1][POSITION_X] + 1][dots[1][POSITION_Y]] == 0)
            {
                //可以变化
                //可以变换
                dots[0][POSITION_X] = dots[1][POSITION_X] - 1;
                dots[0][POSITION_Y] = dots[1][POSITION_Y] + 1;

                dots[2][POSITION_X] = dots[1][POSITION_X];
                dots[2][POSITION_Y] = dots[1][POSITION_Y];

                dots[3][POSITION_X] = dots[1][POSITION_X] + 1;
                dots[3][POSITION_Y] = dots[1][POSITION_Y];

                dots[1][POSITION_X] = dots[1][POSITION_X] - 1;
                dots[1][POSITION_Y] = dots[1][POSITION_Y];
                currentAngle = 90;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        else if (currentAngle == 90)
        {
            //第三个方格，1、左边第一个无；2、左边一个下一个无；3、右边第一个无
            if (myCanvas[dots[2][POSITION_X] - 1][dots[2][POSITION_Y] - 1] == 0 && myCanvas[dots[2][POSITION_X]][dots[2][POSITION_Y] - 1] == 0 && myCanvas[dots[2][POSITION_X]][dots[2][POSITION_Y] + 1] == 0)
            {
                //可以变换
                dots[0][POSITION_X] = dots[2][POSITION_X] - 1;
                dots[0][POSITION_Y] = dots[2][POSITION_Y] - 1;

                dots[1][POSITION_X] = dots[2][POSITION_X];
                dots[1][POSITION_Y] = dots[2][POSITION_Y] - 1;

                dots[3][POSITION_X] = dots[2][POSITION_X];
                dots[3][POSITION_Y] = dots[2][POSITION_Y] + 1;

                currentAngle = 180;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        else if (currentAngle == 180)
        {
            if (myCanvas[dots[2][POSITION_X] + 1][dots[2][POSITION_Y] - 1] == 0 && myCanvas[dots[2][POSITION_X] - 1][dots[2][POSITION_Y]] == 0 && myCanvas[dots[2][POSITION_X] + 1][dots[2][POSITION_Y]] == 0)
            {
                //可以变换
                dots[0][POSITION_X] = dots[2][POSITION_X] - 1;
                dots[0][POSITION_Y] = dots[2][POSITION_Y];

                dots[1][POSITION_X] = dots[2][POSITION_X];
                dots[1][POSITION_Y] = dots[2][POSITION_Y];

                dots[3][POSITION_X] = dots[2][POSITION_X] + 1;
                dots[3][POSITION_Y] = dots[2][POSITION_Y] - 1;

                dots[2][POSITION_X] = dots[2][POSITION_X] + 1;
                dots[2][POSITION_Y] = dots[2][POSITION_Y];

                currentAngle = 270;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        else
        {
            if (myCanvas[dots[1][POSITION_X]][dots[1][POSITION_Y] - 1] == 0 && myCanvas[dots[1][POSITION_X]][dots[1][POSITION_Y] + 1] == 0 && myCanvas[dots[1][POSITION_X] + 1][dots[1][POSITION_Y] + 1] == 0)
            {
                //可以变换
                dots[0][POSITION_X] = dots[1][POSITION_X];
                dots[0][POSITION_Y] = dots[1][POSITION_Y] - 1;

                dots[2][POSITION_X] = dots[1][POSITION_X];
                dots[2][POSITION_Y] = dots[1][POSITION_Y] + 1;

                dots[3][POSITION_X] = dots[1][POSITION_X] + 1;
                dots[3][POSITION_Y] = dots[1][POSITION_Y] + 1;

                currentAngle = 0;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        break;

    case TERIS_TYPE_J:
        if (currentAngle == 0)
        {
            //第二个方格，1、左边第一个无；2、左边一个下一个无；3、右边第一个无
            if (myCanvas[dots[1][POSITION_X] - 1][dots[1][POSITION_Y]] == 0 && myCanvas[dots[1][POSITION_X] - 1][dots[1][POSITION_Y] - 1] == 0 && myCanvas[dots[1][POSITION_X] + 1][dots[1][POSITION_Y]] == 0)
            {
                //可以变化
                //可以变换
                dots[0][POSITION_X] = dots[1][POSITION_X] - 1;
                dots[0][POSITION_Y] = dots[1][POSITION_Y] - 1;

                dots[2][POSITION_X] = dots[1][POSITION_X];
                dots[2][POSITION_Y] = dots[1][POSITION_Y];

                dots[3][POSITION_X] = dots[1][POSITION_X] + 1;
                dots[3][POSITION_Y] = dots[1][POSITION_Y];

                dots[1][POSITION_X] = dots[1][POSITION_X] - 1;
                dots[1][POSITION_Y] = dots[1][POSITION_Y];
                currentAngle = 90;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        else if (currentAngle == 90)
        {
            //第三个方格，1、左边第一个无；2、左边一个下一个无；3、右边第一个无
            if (myCanvas[dots[2][POSITION_X]][dots[2][POSITION_Y] - 1] == 0 && myCanvas[dots[2][POSITION_X] + 1][dots[2][POSITION_Y] - 1] == 0 && myCanvas[dots[2][POSITION_X]][dots[2][POSITION_Y] + 1] == 0)
            {
                //可以变换
                dots[0][POSITION_X] = dots[2][POSITION_X] + 1;
                dots[0][POSITION_Y] = dots[2][POSITION_Y] - 1;

                dots[1][POSITION_X] = dots[2][POSITION_X];
                dots[1][POSITION_Y] = dots[2][POSITION_Y] - 1;

                dots[3][POSITION_X] = dots[2][POSITION_X];
                dots[3][POSITION_Y] = dots[2][POSITION_Y] + 1;

                currentAngle = 180;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        else if (currentAngle == 180)
        {
            if (myCanvas[dots[2][POSITION_X] - 1][dots[2][POSITION_Y]] == 0 && myCanvas[dots[2][POSITION_X] + 1][dots[2][POSITION_Y]] == 0 && myCanvas[dots[2][POSITION_X] + 1][dots[2][POSITION_Y] + 1] == 0)
            {
                //可以变换
                dots[0][POSITION_X] = dots[2][POSITION_X] - 1;
                dots[0][POSITION_Y] = dots[2][POSITION_Y];

                dots[1][POSITION_X] = dots[2][POSITION_X];
                dots[1][POSITION_Y] = dots[2][POSITION_Y];

                dots[3][POSITION_X] = dots[1][POSITION_X] + 1;
                dots[3][POSITION_Y] = dots[1][POSITION_Y] + 1;

                dots[2][POSITION_X] = dots[2][POSITION_X] + 1;
                dots[2][POSITION_Y] = dots[2][POSITION_Y];

                currentAngle = 270;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        else
        {
            if (myCanvas[dots[1][POSITION_X]][dots[1][POSITION_Y] - 2] == 0 && myCanvas[dots[1][POSITION_X]][dots[1][POSITION_Y] - 1] == 0)
            {
                //可以变换
                dots[0][POSITION_X] = dots[1][POSITION_X];
                dots[0][POSITION_Y] = dots[1][POSITION_Y] - 1;

                dots[2][POSITION_X] = dots[1][POSITION_X];
                dots[2][POSITION_Y] = dots[1][POSITION_Y] + 1;

                dots[3][POSITION_X] = dots[1][POSITION_X] - 1;
                dots[3][POSITION_Y] = dots[1][POSITION_Y] + 1;

                currentAngle = 0;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        break;
    case TERIS_TYPE_S:
        if (currentAngle == 0)
        {
            if (myCanvas[dots[1][POSITION_X] + 1][dots[1][POSITION_Y]] == 0 && myCanvas[dots[1][POSITION_X] + 1][dots[1][POSITION_Y] + 1] == 0)
            {
                //可以变换
                dots[0][POSITION_X] = dots[1][POSITION_X];
                dots[0][POSITION_Y] = dots[1][POSITION_Y] - 1;

                dots[2][POSITION_X] = dots[1][POSITION_X] + 1;
                dots[2][POSITION_Y] = dots[1][POSITION_Y];

                dots[3][POSITION_X] = dots[1][POSITION_X] + 1;
                dots[3][POSITION_Y] = dots[1][POSITION_Y] + 1;

                currentAngle = 90;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        else
        {
            if (myCanvas[dots[2][POSITION_X]][dots[2][POSITION_Y] - 1] == 0 && myCanvas[dots[2][POSITION_X] + 1][dots[2][POSITION_Y] - 1] == 0)
            {
                //可以变换
                dots[0][POSITION_X] = dots[2][POSITION_X] - 1;
                dots[0][POSITION_Y] = dots[2][POSITION_Y];

                dots[1][POSITION_X] = dots[2][POSITION_X];
                dots[1][POSITION_Y] = dots[2][POSITION_Y];

                dots[3][POSITION_X] = dots[2][POSITION_X] + 1;
                dots[3][POSITION_Y] = dots[2][POSITION_Y] - 1;

                dots[2][POSITION_X] = dots[2][POSITION_X];
                dots[2][POSITION_Y] = dots[2][POSITION_Y] - 1;
                currentAngle = 0;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        break;

    case TERIS_TYPE_Z:
        if (currentAngle == 0)
        {
            if (myCanvas[dots[2][POSITION_X] + 1][dots[2][POSITION_Y] - 1] == 0 && myCanvas[dots[2][POSITION_X] + 1][dots[2][POSITION_Y]] == 0 && myCanvas[dots[2][POSITION_X]][dots[1][POSITION_Y] + 1] == 0)
            {
                //可以变换
                dots[0][POSITION_X] = dots[2][POSITION_X] + 1;
                dots[0][POSITION_Y] = dots[2][POSITION_Y] - 1;

                dots[1][POSITION_X] = dots[2][POSITION_X] + 1;
                dots[1][POSITION_Y] = dots[2][POSITION_Y];

                dots[3][POSITION_X] = dots[2][POSITION_X];
                dots[3][POSITION_Y] = dots[2][POSITION_Y] + 1;

                currentAngle = 90;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        else
        {
            if (myCanvas[dots[2][POSITION_X] - 1][dots[2][POSITION_Y]] == 0 && myCanvas[dots[2][POSITION_X] + 1][dots[2][POSITION_Y] + 1] == 0)
            {
                //可以变换
                dots[0][POSITION_X] = dots[2][POSITION_X] - 1;
                dots[0][POSITION_Y] = dots[2][POSITION_Y];

                dots[1][POSITION_X] = dots[2][POSITION_X];
                dots[1][POSITION_Y] = dots[2][POSITION_Y];

                dots[3][POSITION_X] = dots[2][POSITION_X] + 1;
                dots[3][POSITION_Y] = dots[2][POSITION_Y] + 1;

                dots[2][POSITION_X] = dots[2][POSITION_X];
                dots[2][POSITION_Y] = dots[2][POSITION_Y] + 1;
                currentAngle = 0;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        break;

    case TERIS_TYPE_T:
        if (currentAngle == 0)
        {
            //第二个方格，1、左边第一个无；2、左边一个下一个无；3、右边第一个无
            if (myCanvas[dots[1][POSITION_X]][dots[1][POSITION_Y] + 1] == 0)
            {
                //可以变化

                dots[1][POSITION_X] = dots[2][POSITION_X];
                dots[1][POSITION_Y] = dots[2][POSITION_Y];

                dots[2][POSITION_X] = dots[1][POSITION_X];
                dots[2][POSITION_Y] = dots[1][POSITION_Y] + 1;

                currentAngle = 90;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        else if (currentAngle == 90)
        {
            //第三个方格，1、左边第一个无；2、左边一个下一个无；3、右边第一个无
            if (myCanvas[dots[1][POSITION_X] - 1][dots[1][POSITION_Y]] == 0)
            {
                //可以变换
                dots[0][POSITION_X] = dots[2][POSITION_X] - 1;
                dots[0][POSITION_Y] = dots[2][POSITION_Y];

                dots[2][POSITION_X] = dots[3][POSITION_X];
                dots[2][POSITION_Y] = dots[3][POSITION_Y];

                dots[3][POSITION_X] = dots[1][POSITION_X];
                dots[3][POSITION_Y] = dots[1][POSITION_Y] + 1;

                currentAngle = 180;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        else if (currentAngle == 180)
        {
            if (myCanvas[dots[1][POSITION_X]][dots[2][POSITION_Y] - 1] == 0)
            {

                dots[2][POSITION_X] = dots[1][POSITION_X];
                dots[2][POSITION_Y] = dots[1][POSITION_Y];

                dots[1][POSITION_X] = dots[2][POSITION_X] - 1;
                dots[1][POSITION_Y] = dots[2][POSITION_Y];

                currentAngle = 270;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        else
        {
            if (myCanvas[dots[2][POSITION_X] + 1][dots[1][POSITION_Y]] == 0)
            {
                //可以变换
                dots[0][POSITION_X] = dots[1][POSITION_X];
                dots[0][POSITION_Y] = dots[1][POSITION_Y];

                dots[1][POSITION_X] = dots[2][POSITION_X] - 1;
                dots[1][POSITION_Y] = dots[2][POSITION_Y];

                dots[3][POSITION_X] = dots[2][POSITION_X] + 1;
                dots[3][POSITION_Y] = dots[2][POSITION_Y];

                currentAngle = 0;
                show();
                return true;
            }
            else
            {
                show();
                return false;
            }
        }
        break;

    default:
        break;
    }
}
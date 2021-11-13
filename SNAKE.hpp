#ifndef _SNAKE_H
#define _SNAKE_H

#include "BLOCK.hpp"
#include <stdlib.h>
#include <HardwareSerial.h>

#define DIRECTION_LEFT 1
#define DIRECTION_RIGHT 2
#define DIRECTION_DOWN 3
#define DIRECTION_UP 4

#define CALLBACK_SIGNATURE void (*callback)(int)
// #define COLS 10
// #define ROWS 20

// #define POSITION_X 0
// #define POSITION_Y 1

class SNAKE
{
private:
    int currentDirection = DIRECTION_LEFT;
    int dots[COLS * ROWS][2];
    int length = 0;
    int **myCanvas;
    int target[2];
    void (*callback)(int);

    /* data */
public:
    SNAKE(/* args */);

    /**
     * @brief 贪吃蛇移动
     * 
     * @return true 
     * @return false 
     */
    bool move();

    /**
    * @brief 贪吃蛇向上
    * 
    * @return true 
    * @return false 
    */
    bool up();

    /**
     * @brief 贪吃蛇向下
     * 
     * @return true 
     * @return false 
     */
    bool down();

    /**
     * @brief 贪吃蛇向左
     * 
     * @return true 
     * @return false 
     */
    bool left();

    /**
     * @brief 贪吃蛇向右
     * 
     * @return true 
     * @return false 
     */
    bool right();

    /**
     * @brief 添加新模块
     * 
     */
    void add();

    /**
     * @brief 开始游戏
     * 
     */
    void start();

    /**
     * @brief 显示到画布上
     * 
     */
    void show();

    /**
     * @brief 吃掉添加的模块
     * 
     */
    void add2Head();

    /**
     * @brief 设置分数更新回调
     * 
     */
    void setScoreCallback(CALLBACK_SIGNATURE)
    {
        this->callback = callback;
    }

    /**
     * @brief 获取当前方向
     * 
     * @return int 
     */
    int getCurrentDirection()
    {
        return currentDirection;
    }

    /**
     * @brief 设置画布
     * 
     * @param canvas 
     */
    void setCanvas(int **canvas)
    {
        myCanvas = canvas;
    }

    /**
     * @brief 游戏是否结束
     * 
     * @param direction 
     * @return true 
     * @return false 
     */
    bool isOver(int direction);

    /**
     * @brief 是否包含对应的模块
     * 
     * @param x 横坐标
     * @param y 纵坐标
     * @return true 
     * @return false 
     */
    bool contains(int x, int y);
    
    ~SNAKE();
};

#endif
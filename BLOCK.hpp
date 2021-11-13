#ifndef _BLOCK_h
#define _BLOCK_h

#define POSITION_X  0
#define POSITION_Y  1

#define COLS 10
#define ROWS 20
/**
 * 1 3
 * 2 4
 * */
#define TERIS_TYPE_O 0 //田
#define TERIS_TYPE_I 1 //数直线

/**
 *   口口
 * 口口
 * */
#define TERIS_TYPE_S 2 

/**
 * 口口
 *   口口
 * */
#define TERIS_TYPE_Z 3 

/**
 * 口
 * 口
 * 口口
 * */
#define TERIS_TYPE_L 4

/**
 *    口
 *    口
 *  口口
 * */
#define TERIS_TYPE_J 5

/**
 *  口口口
 *    口
 * */
#define TERIS_TYPE_T 6

class Block
{
typedef int DOTS[4][2] ;
// typedef int CANVANS ** ;
private:
    /* data */
    int myType;
    int ** myCanvas; 
    DOTS dots;
    int currentAngle;

public:
    Block();

    bool up();

    bool down(int speed);

    bool left();

    bool right();


    void setCanvas(int ** canvas){
        myCanvas = canvas;
    }

    void show();

    void clear();

    void newBolck(int type);

    ~Block();
    

};


#endif

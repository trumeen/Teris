#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include "BLOCK.hpp"
#include "BOOTSCREEN.hpp"
#include "SNAKE.hpp"

//定义WS2812B 控制引脚
#define PIN 0
//定义灯珠数量
#define NUMPIXELS 200

#define MAX_LEVEL 20

#define KEY_UP 1
#define KEY_DOWN 0
#define KEY_LEFT 2
#define KEY_RIGHT 3
#define KEY_START 4
#define KEY_PAUSE 5
#define KEY_GAME_MODE_SNAKE 6
#define KEY_GAME_MODE_TETRIS 7

#define GAME_STATE_IDLE 0
#define GAME_STATE_START 1
#define GAME_STATE_PAUSE 2
#define GAME_STATE_END 3
#define GAME_STATE_INIT 4

#define GAME_TYPE_SNAKE 1
#define GAME_TYPE_TERIS 2

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Ticker flipper; //实例化定时器对象

#define DELAYVAL 500

//Wi-Fi 名称
const char *ssid = "Cheery";

//Wi-Fi密码
const char *password = "111222aa";

//mqtt 服务器地址
const char *mqtt_server = "192.168.71.165";

WiFiClient espClient;
PubSubClient client(espClient);

StaticJsonDocument<100> doc;

String lastState = "";

Block block;

SNAKE snake;

int **current;

int level = 5; //游戏等级

int tempLevel = 0;

int score = 0; //游戏得分

int gameType = GAME_TYPE_SNAKE;

int gameState = GAME_STATE_INIT; //游戏状态 0-等待开始 1-游戏中 2-游戏暂停 3-游戏结束

int timeCount = 0; //定时器计数器
/**
   配置WIFI
*/
void setup_wifi()
{
  delay(10);
  WiFi.begin(ssid, password);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    // pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    // pixels.show();
    // i++;
    // if (i == pixels.numPixels())
    // {
    //   pixels.clear();
    //   i == 0;
    // }
    delay(DELAYVAL);
  }
  randomSeed(micros());
}

/**
   MQTT 消息回调
   @topic 消息主题
   @payload 信息内容
   @length 数据长度
*/

String acionTopic = "trumeen/home/game/action";

void callback(char *topic, byte *payload, unsigned int length)
{
  if (acionTopic.equals(topic))
  {
    switch (int(payload[0]))
    {
    case KEY_DOWN:
      if (gameType == GAME_TYPE_TERIS)
      {
        while (block.down(1))
        {
          showBlock();
        }
      }
      else if (gameType == GAME_TYPE_SNAKE)
      {
        if (snake.getCurrentDirection() != DIRECTION_DOWN && snake.getCurrentDirection() != DIRECTION_UP)
        {
          snake.down();
          showBlock();
        }
      }

      break;

    case KEY_UP:
      if (gameState == GAME_STATE_START)
      {
        if (gameType == GAME_TYPE_TERIS)
        {
          block.up();
          showBlock();
        }
        else if (gameType == GAME_TYPE_SNAKE)
        {
          if (snake.getCurrentDirection() != DIRECTION_DOWN && snake.getCurrentDirection() != DIRECTION_UP)
          {
            snake.up();
            showBlock();
          }
        }
      }
      break;
    case KEY_LEFT:
      if (gameState == GAME_STATE_START)
      {
        if (gameType == GAME_TYPE_TERIS)
        {
          block.left();
          showBlock();
        }
        else if (gameType == GAME_TYPE_SNAKE)
        {
          if (snake.getCurrentDirection() != DIRECTION_LEFT && snake.getCurrentDirection() != DIRECTION_RIGHT)
          {
            snake.left();
            showBlock();
          }
        }
      }

      break;
    case KEY_RIGHT:
      if (gameState == GAME_STATE_START)
      {
        if (gameType == GAME_TYPE_TERIS)
        {
          block.right();
          showBlock();
        }
        else if (gameType == GAME_TYPE_SNAKE)
        {
          if (snake.getCurrentDirection() != DIRECTION_LEFT && snake.getCurrentDirection() != DIRECTION_RIGHT)
          {
            snake.right();
            showBlock();
          }
        }
      }
      break;
    case KEY_START:
      if (gameState != GAME_STATE_START)
      {
        timeCount = 0;
        gameState = GAME_STATE_START;
        updateLevel();
      }
      break;

    case KEY_PAUSE:
      if (gameState == GAME_STATE_PAUSE)
      {
        gameState = GAME_STATE_START;
      }
      else
      {
        gameState = GAME_STATE_PAUSE;
      }
      break;

    case KEY_GAME_MODE_SNAKE:
      gameState = GAME_STATE_INIT;
      gameType = GAME_TYPE_SNAKE;
      break;

    case KEY_GAME_MODE_TETRIS:
      gameState = GAME_STATE_INIT;
      gameType = GAME_TYPE_TERIS;
      break;

    default:
      break;
    }
  }
  else
  {
    DeserializationError error = deserializeJson(doc, payload);
    // Test if parsing succeeds.
    if (error)
    {
      Serial.println(error.f_str());
      return;
    }

    //解析JSON数据
    const char *state = doc["state"];
    int brightness = doc["brightness"];
    int r = doc["color"]["r"];
    int g = doc["color"]["g"];
    int b = doc["color"]["b"];

    //设置开关状态
    if (lastState != state)
    {
      // changeState(((String)"ON").compareTo((String)state) == 0);
      lastState = state;
    }
    //设置亮度信息
    if (brightness && brightness != pixels.getBrightness())
    {
      pixels.setBrightness(brightness);
      pixels.show();
    }
    //设置颜色
    if (r || g || b)
    {
      for (int i = 0; i < pixels.numPixels(); i++)
      {
        pixels.setPixelColor(i, pixels.Color(r, g, b));
      }
      pixels.show();
    }
  }
}

bool isBooting = false;

int indexOffset = 0;

int length = sizeof(BOOT_SCREEN) / sizeof(BOOT_SCREEN[0]);

int screenCount = 0;

/**
 * 
 * 显示待机画面
 */
void showBootScreen()
{
  //3个时间周期做一次更新 3*50ms
  if (timeCount % 3 == 0)
  {
    //刚开机时滚动显示逻辑，从最下面开始滚动
    if (screenCount < length)
    {
      if (screenCount < ROWS)
      {
        for (int count = 0; count < screenCount + 1; count++)
        {
          for (int i = 0; i < COLS; i++)
          {
            int color = BOOT_SCREEN[screenCount - count][i];
            pixels.setPixelColor(getPosition(i, ROWS - 1 - count), pixels.Color(color >> 16 & 0xff, color >> 8 & 0xff, color & 0xff));
          }
        }
        pixels.show();
      }
      else
      {
        for (int count = 0; count < ROWS; count++)
        {
          for (int i = 0; i < COLS; i++)
          {
            int color = BOOT_SCREEN[screenCount - count][i];
            pixels.setPixelColor(getPosition(i, ROWS - 1 - count), pixels.Color(color >> 16 & 0xff, color >> 8 & 0xff, color & 0xff));
          }
        }
        pixels.show();
      }
    }
    else
    {
      //第一屏滚动显示完后的显示逻辑
      int index;
      for (int count = 0; count < ROWS; count++)
      {
        if (count > screenCount % length)
        {
          if (index < ROWS)
          {
            index = length - 1;
          }
          else
          {
            index--;
          }
        }
        else
        {
          index = (screenCount % length) - count;
        }
        for (int i = 0; i < COLS; i++)
        {
          int color = BOOT_SCREEN[index][i];
          pixels.setPixelColor(getPosition(i, ROWS - 1 - count), pixels.Color(color >> 16 & 0xff, color >> 8 & 0xff, color & 0xff));
        }
      }
      pixels.show();
      if (screenCount >= length + ROWS)
      {
        pixels.clear();
        screenCount = ROWS - 1;
        timeCount = 0;
      }
    }
    screenCount++;
  }
}

void flip()
{
  // Serial.print("定时器运行");
  // Serial.println(timeCount);
  switch (gameState)
  {
  case GAME_STATE_INIT:
    timeCount++;
    showBootScreen();
    break;
  case GAME_STATE_IDLE:
    timeCount = 0;
    break;

  case GAME_STATE_END:
    timeCount = 0;
    break;

  case GAME_STATE_START:

    pixels.clear();
    if (timeCount == 0)
    {
      score = 0;
      clearCanvas();
      Serial.print("第一次运行");
      if (gameType == GAME_TYPE_TERIS)
      {
        addBlock();
      }
      else
      {
        snake.setCanvas(current);
        snake.start();
        Serial.print("贪吃蛇");
      }

      showBlock();
    }
    else if (timeCount % (MAX_LEVEL - level) == 0)
    {
      if (gameType == GAME_TYPE_TERIS)
      {
        terisRun();
      }
      else if (gameType == GAME_TYPE_SNAKE)
      {
        snake.move();
        showBlock();
        Serial.println("后续运行");
      }
    }
    timeCount++;
    break;

  default:
    break;
  }
}

/**
 * 
 * 贪吃蛇运行逻辑
 */
void terisRun()
{
  Serial.println("后续运行");
  //执行游戏逻辑
  if (block.down(1))
  {
    Serial.println("模块下移");
    showBlock();
  }
  else
  {
    Serial.print("无法下移");
    //判断是否有消除的行，如果有消除的行，这消除行
    if (removeFullRow())
    {
      //消除行
      Serial.println("消除行");
      sendSoundMsg("D");
    }
    if (gameIsOver())
    {
      //游戏已经结束
      sendSoundMsg("O");
      Serial.println("游戏结束");
      gameState = GAME_STATE_END;
    }
    else
    {
      addBlock();
    }
  }
}

String clientId = "HomeGame";
/*
   重连连接
*/
void reconnect()
{
  //连接成功
  if (client.connect(clientId.c_str()))
  {
    //订阅按键消息
    client.subscribe("trumeen/home/game/action");
    // 连接成功发送主题和消息
    client.publish("trumeen/home/game", "ONLINE");
  }
  else
  {
    // Wait 5 seconds before retrying
    delay(5000);
  }
}

void setup()
{
  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(20);
  pixels.clear();
  flipper.attach(0.05, flip);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  initGame();
}

/**
 * @brief 更新分数
 * @param addScore 增加的分数
 */
void updateScore(int addScore)
{
  score += addScore;
  char content[10];
  itoa(score, content, 10);
  client.publish("trumeen/home/game/score", content);
}

/**
 * @brief  更新游戏等级
 * 
 */
void updateLevel()
{
  char content[10];
  itoa(level, content, 10);
  client.publish("trumeen/home/game/level", content);
}

/**
 * @brief 初始化游戏
 * 
 */
void initGame()
{
  Serial.println("初始化游戏");
  current = new int *[COLS];
  for (int i = 0; i < COLS; i++)
  {
    current[i] = new int[ROWS];
  }
  snake.setScoreCallback(scoreCallback);
}

/**
 * @brief 贪吃蛇游戏分数更新回调
 * 
 * @param snackScore 更新分数
 */
void scoreCallback(int snackScore)
{
  updateScore(snackScore);
}

/**
 * @brief 清除显示
 * 
 */
void clearCanvas()
{
  for (int i = 0; i < COLS; i++)
  {
    for (int j = 0; j < ROWS; j++)
    {
      current[i][j] = 0;
    }
  }
}

/**
 * @brief 转换XY坐标系到WS2812B显示位置
 * 
 * @param x 横坐标
 * @param y 纵坐标
 * @return int 对应WS2812B 位置
 */
int getPosition(int x, int y)
{
  // Serial.print("获取坐标:");
  // Serial.print(x);
  // Serial.print("---");
  // Serial.println(y);
  int position = 0;
  if (x % 2 == 1)
  {
    position = x * ROWS + (ROWS - 1 - y);
  }
  else
  {
    position = x * ROWS + y;
  }
  return position;
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}

/**
 * @brief 显出整行
 * 
 * @return true 存在消除
 * @return false 不存在消除
 */
bool removeFullRow()
{
  bool result = false;
  int rowsNeedRemove[4];
  int cnt = 0;
  int temp = 0;
  for (int i = 0; i < ROWS; i++)
  {
    temp = 0;
    for (int j = 0; j < COLS; j++)
    {
      if (current[j][i] == 0)
      {
        break;
      }
      else
      {
        temp++;
      }
    }
    if (temp == COLS)
    {
      rowsNeedRemove[cnt] = i;
      cnt++;
    }
  }
  if (cnt > 0)
  {
    for (int cntIndex = 0; cntIndex < cnt; cntIndex++)
    {
      for (int colIndex = 0; colIndex < COLS; colIndex++)
      {
        for (int j = 0; j < rowsNeedRemove[cntIndex]; j++)
        {
          current[colIndex][rowsNeedRemove[cntIndex] - j] = current[colIndex][rowsNeedRemove[cntIndex] - j - 1];
        }
      }
      for (int index = 0; index < COLS; index++)
      {
        current[index][0] = 0;
      }
    }
    showBlock();
    updateScore(cnt * 100);
    result = true;
  }

  return result;
}

/**
 * @brief 游戏是否结束
 * 
 * @return true 
 * @return false 
 */
bool gameIsOver()
{
  for (int i = 0; i < COLS; i++)
  {
    if (current[i][0] > 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * @brief 显示模块
 * 
 */
void showBlock()
{
  for (int i = 0; i < COLS; i++)
  {
    for (int j = 0; j < ROWS; j++)
    {
      int color = current[i][j];
      if (color > 0)
      {
        pixels.setPixelColor(getPosition(i, j), pixels.Color(color >> 16 & 0xFF, color >> 8 & 0xFF, color & 0xFF));
      }
      else
      {
        pixels.setPixelColor(getPosition(i, j), pixels.Color(0, 0, 0));
      }
    }
  }
  pixels.show();
}

/**
 * @brief 俄罗斯方块添加新的模块
 * 
 */
void addBlock()
{
  int type = rand() % 6;
  Serial.print("创建新模块");
  Serial.println(type);
  block.newBolck(type);
  block.setCanvas(current);
  block.show();
  updateScore(10);
}

/**
 * @brief 发送声音消息
 * 
 * @param msg 声音模式
 */
void sendSoundMsg(char *msg)
{
  client.publish("trumeen/home/game/sound", msg);
}

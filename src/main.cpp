#include <Arduino.h>
#include "device.h"

// 定义当前页面
int currentPage = 1;

// 显示当前页面
void showCurrentPage(int Page1)
{
  if (Page1 == 1)
  {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(5);
    tft.setCursor(1, 1);
    tft.print("Page1");
    Serial.println("showPage1_OK");
  }
  else if (Page1 == 2)
  {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(5);
    tft.setCursor(1, 1);
    tft.print("Page2");
    Serial.println("showPage2_OK");
  }
  else if (Page1 == 3)
  {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(5);
    tft.setCursor(1, 1);
    tft.print("Page3");
    Serial.println("showPage3_OK");
  }
  else if (Page1 == 4)
  {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(5);
    tft.setCursor(1, 1);
    tft.print("Page4");
    Serial.println("showPage4_OK");
  }
  else if (Page1 == 5)
  {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(5);
    tft.setCursor(1, 1);
    tft.print("Page5");
    Serial.println("showPage5_OK");
  }
}

void setup()
{
  Serial.begin(115200);

  tft.init();                           // 初始化屏幕
  tft.setRotation(3);                   // 设置屏幕旋转方向
  tft.fillScreen(TFT_BLACK);            // 填充屏幕为黑色
  tft.setCursor(0, 0);                  // 设置光标位置
  tft.setTextColor(TFT_RED, TFT_BLACK); // 设置文本颜色,背景颜色
  drawKeyboardPage(1);                  // 绘制第一页的键盘

  // 设置引脚模式
  pinMode(Btn_up, INPUT_PULLUP);
  pinMode(Btn_down, OUTPUT);
  digitalWrite(Btn_down, HIGH); // Btn_down引脚同时是LED5引脚，使用弱上拉输入拉不起来，需要强上拉，注意按键不要按太久
  pinMode(Btn_left, INPUT_PULLUP);
  pinMode(Btn_right, INPUT_PULLUP);
  pinMode(Btn_middle, INPUT_PULLUP);

  // 设置引脚消抖
  debouncer_Btn_up.attach(Btn_up);
  debouncer_Btn_down.attach(Btn_down);
  debouncer_Btn_left.attach(Btn_left);
  debouncer_Btn_right.attach(Btn_right);
  debouncer_Btn_middle.attach(Btn_middle);

  // 设置引脚消抖时间（默认10ms）
  debouncer_Btn_up.interval(5);     // 5ms 消抖时间
  debouncer_Btn_down.interval(5);   // 5ms 消抖时间
  debouncer_Btn_left.interval(5);   // 5ms 消抖时间
  debouncer_Btn_right.interval(5);  // 5ms 消抖时间
  debouncer_Btn_middle.interval(5); // 5ms 消抖时间
}

void loop()
{
  // 更新按键状态（在每次循环都需要引用）
  debouncer_Btn_up.update();
  debouncer_Btn_down.update();
  debouncer_Btn_left.update();
  debouncer_Btn_right.update();
  debouncer_Btn_middle.update();

  // 执行按键函数
  if (debouncer_Btn_up.fell())
  {
    selectedKey -= 26;
    if (selectedKey < 0)
    {
      selectedKey = 25; // 回滚到最后一个
    }
    drawKeyboardPage(page); // 根据页码重绘键盘
  }

  if (debouncer_Btn_down.fell())
  {
    selectedKey = selectedKey + 26;
    if (selectedKey > 89)
    {
      selectedKey = 89 - selectedKey; // 回滚到上一个
    }
    drawKeyboardPage(page); // 根据页码重绘键盘
  }

  if (debouncer_Btn_left.fell())
  {
    selectedKey--;
    if (selectedKey < 0)
    {
      selectedKey = 89;
    }
    drawKeyboardPage(page); // 根据页码重绘键盘
  }

  if (debouncer_Btn_right.fell())
  {
    selectedKey++;
    if (selectedKey > 25)
    {
      selectedKey = 0;
    }
    drawKeyboardPage(page); // 根据页码重绘键盘
  }

  if (debouncer_Btn_middle.fell())
  {
    tft.fillCircle(92, 40, 7, TFT_YELLOW); // 在屏幕中央显示黄色圆圈
    delay(500);                            // 延时500毫秒
    tft.fillCircle(92, 40, 7, TFT_BLACK);  // 取消圆圈
    char key;                              // 字符数组指针
    if (page == 1)
      key = Alphabet[selectedKey];
    else if (page == 2)
      key = alphabet[selectedKey];
    else if (page == 3)
      key = punctuation[selectedKey];
    Serial.println(String(key)); // 输出调试信息
    drawKeyboardPage(page);      // 根据页码重绘键盘
  }
  // 绘制选中的键盘按钮的边框
  // int row = selectedKey / 8;
  // int col = selectedKey % 8;
  // int x = 20 + col * 18;
  // int y = 10 + row * 18;
  // tft.drawRect(x - 3, y - 3, 16, 16, TFT_RED);
}

#ifndef _deviceh_
#define _deviceh_

#include <Arduino.h>
#include <Adafruit_GFX.h> //屏幕
#include <TFT_eSPI.h>     //屏幕
#include <Bounce2.h>      //消抖

// 定义按键引脚
#define Btn_up 8
#define Btn_down 13
#define Btn_left 5
#define Btn_right 9
#define Btn_middle 4

// 实例化屏幕对象
TFT_eSPI tft = TFT_eSPI(80, 160);

// 实例化按键消抖
Bounce debouncer_Btn_up = Bounce();
Bounce debouncer_Btn_down = Bounce();
Bounce debouncer_Btn_left = Bounce();
Bounce debouncer_Btn_right = Bounce();
Bounce debouncer_Btn_middle = Bounce();

int page = 0;        // 当前所在的页码
int selectedKey = 0; // 当前选中的键盘按钮

char Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()_+={}[]\\|;:'\",.?1234567890"; // 字母数组
char alphabet[] = "abcdefghijklmnopqrstuvwxyz";                                                                    // 字母数组
char punctuation[] = "!@#$%^&*()_+={}[]\\|;:'\",.<>?/";                                                            // 标点符号数组

void drawKeyboardPage(int page)
{
    tft.fillScreen(TFT_BLACK);  // 清空屏幕
    tft.setTextDatum(MC_DATUM); // 设置文本居中对齐

    char *keys; // 字符数组指针

    if (page == 0)
        keys = Alphabet; // 根据页码决定显示字母还是标点符号
    else if (page == 1)
        keys = alphabet;
    else if (page == 2)
        keys = punctuation;

    tft.setCursor(0, 45); // 设置光标位置
    for (int i = 0; i < 89; i++)
    { // 遍历所有键盘按钮并绘制
        // int row = i / 8;
        // int col = i % 8;
        // int x = 20 + col * 9;
        // int y = 10 + row * 9;
        // // tft.drawRect(x - 3, y - 3, 16, 16, TFT_WHITE); // 绘制按钮边框
        // // tft.drawRect(x-9, y-9, 9, 9, TFT_WHITE); // 绘制按钮边框
        // tft.setTextFont(1);                            // 设置字体大小为2

        // tft.drawString(String(keys[i]), x, y); // 在按钮上打印字符
        if(selectedKey == i){
           tft.setTextColor(TFT_RED, TFT_WHITE); // 设置文本颜色,背景颜色
           tft.print(Alphabet[i]);
           tft.setTextColor(TFT_RED, TFT_BLACK); // 设置文本颜色,背景颜色
        }
        else{
            tft.print(Alphabet[i]);
        }
        // Serial.print("X:");
        // Serial.print(tft.getCursorX());
        // Serial.print("Y:");
         Serial.println(selectedKey);
    }
}

#endif // !_device_H_
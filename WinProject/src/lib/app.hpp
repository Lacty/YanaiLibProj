
#pragma once

#include <iostream>
#include <Eigen/Core>
#include "color.hpp"
#include "graphic.hpp"
#include "key.hpp"
#include "mouse.hpp"
#include "font.hpp"
#include "random.hpp"
#include "clock.hpp"


struct GLFWwindow;

class App {
private:
  GLFWwindow* window_;

  // 背景色
  Color clear_color_;

  // windowのサイズ
  int window_w_;
  int window_h_;
  
  Key key_;
  Mouse mouse_;
  
  // CallBack関数
  static void mouseButtomCallback(GLFWwindow* window, int button, int action, int mods);
  static void mousePosCallBack(GLFWwindow* window, double xpos, double ypos);
  static void windowSizeCallBack(GLFWwindow* window, int width, int height);
  static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
  
  void setCallBackFunc();
  
  // 指定した位置にマウスを移動させる
  void setMousePos(const Vec2d& pos);
  
  // 描画開始
  void begin();
  
  // 描画終了
  void end();

public:
  // width : 画面の横幅
  // height : 画面の縦幅
  // title : タイトル
  explicit App(int width, int height, const char* title);
  App(const App& src) = delete;
  ~App();
  
  // windowが開いているかどうか
  // 開いている場合trueを返す
  bool isOpen();
  
  // 描画開始する前に実行する関数
  // begin() end()を実行
  void letsStart();
  
  // 背景色の色を設定する
  void setClearColor(float r, float g, float b);
  void setClearColor(const Color& color);
  
  // Key Events
  // キーが押された瞬間の判定
  bool isPushKey(int key);

  // キーが離された瞬間の判定
  bool isPullKey(int key);
  
  // キーが押されている間の判定
  bool isPressKey(int key);
  
  // Mouse Events
  // ボタンが押された瞬間の判定
  bool isPushMouse(int buttom);

  // ボタンが離された瞬間の判定
  bool isPullMouse(int buttom);

  // ボタンが押されている間の判定
  bool isPressMouse(int buttom);
  
  // 画面の中央を原点とする座標系で
  // マウスの位置を取得
  Vec2d mousePos() const;
};
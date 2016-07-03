
#pragma once

// STATICライブラリを読み込む
#define FTGL_LIBRARY_STATIC

#include <FTGL/ftgl.h>
#include <string>


// 文字を描画する機能を持つクラス
class Font {
private:
  FTPixmapFont font_;

public:
  Font() = delete;
  Font(const std::string& path);

  // 文字を描画する
  // str : 描画する文字列
  // x y : 位置
  // size : 文字のサイズ
  // 注意 : 左下が原点となる座標系である
  void draw(const std::string& str, const float x, const float y, const int size);
  void draw(const wchar_t* str, const float x, const float y, const int size);
  void drawCenter(const std::string& str, const float x, const float y, const int size);
  void drawCenter(const wchar_t* str, const float x, const float y, const int size);
};

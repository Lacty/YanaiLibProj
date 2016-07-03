
#pragma once


class Color {
public:
  float r; // 赤
  float g; // 緑
  float b; // 青
  
  Color() = default;
  Color(const Color& src) :r(src.r), g(src.g), b(src.b) {}
  Color(float r, float g, float b) :r(r), g(g), b(b) {}
  
  // 色を返す関数群
  // 適当に使いそうな色を用意
  static Color red()   { return Color(1, 0, 0); }
  static Color green() { return Color(0, 1, 0); }
  static Color blue()  { return Color(0, 0, 1); }
  static Color gray()  { return Color(0.3f, 0.3f, 0.3f); }
  static Color white() { return Color(1, 1, 1); }
};
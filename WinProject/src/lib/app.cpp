
#ifdef _WINDOWS
  // 競合がおきるのでmsvcrt.libを除外
#pragma comment(linker, "/NODEFAULTLIB:\"msvcrt.lib\"")
#endif

#include "app.hpp"

#include <cassert>

#include <GLFW/glfw3.h>


App::App(int width, int height, const char* title) :
  window_w_(width),
  window_h_(height)
{
  // GLFWの初期化
  assert(glfwInit());

  // windowを作成
  window_ = glfwCreateWindow(window_w_, window_h_, title, NULL, NULL);
  if (!window_) {
    glfwTerminate();
    assert(!"windowが作成できなかった");
  }

  // GLFWに自分を登録
  glfwSetWindowUserPointer(window_, this);

  // コンテキストを作成
  glfwMakeContextCurrent(window_);

  // callback関数を設定
  setCallBackFunc();

  // fpsを指定(1秒60フレーム
  glfwSwapInterval(1);

  // 座標系の設定
  // 画面中心が(0, 0)
  glViewport(0, 0, window_w_, window_h_);
  glOrtho(-window_w_ * 0.5f, window_w_ * 0.5f, -window_h_ * 0.5f, window_h_ * 0.5f, -0.0f, 1.0f);
}

App::~App() {
  // GLFWの後始末
  glfwTerminate();
}

void App::mouseButtomCallback(GLFWwindow* window, int button, int action, int mods) {
  auto app = static_cast<App*>(glfwGetWindowUserPointer(window));

  if (action == GLFW_PRESS) {
    app->mouse_.setButtonPush(button);
    app->mouse_.setButtonPress(button);
  }
  if (action == GLFW_RELEASE) {
    app->mouse_.setButtonPull(button);
    app->mouse_.popButtonPress(button);
  }
}

void App::mousePosCallBack(GLFWwindow* window, double xpos, double ypos) {
  auto app = static_cast<App*>(glfwGetWindowUserPointer(window));

  app->mouse_.setPos(xpos - app->window_w_ * 0.5f, -1 * (ypos - app->window_h_ * 0.5f));
}

void App::windowSizeCallBack(GLFWwindow* window, int width, int height) {
  auto app = static_cast<App*>(glfwGetWindowUserPointer(window));

  glViewport(0, 0, width, height);
  glLoadIdentity();
  glOrtho(-width * 0.5f, width * 0.5f, -height * 0.5f, height * 0.5f, -0.0f, 1.0f);

  app->window_w_ = width;
  app->window_h_ = height;
}

void App::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
  auto app = static_cast<App*>(glfwGetWindowUserPointer(window));

  if (action == GLFW_PRESS) {
    app->key_.setKeyPush(key);
    app->key_.setKeyPress(key);
  }
  if (action == GLFW_RELEASE) {
    app->key_.setKeyPull(key);
    app->key_.popKeyPress(key);
  }
}

void App::setCallBackFunc() {
  glfwSetMouseButtonCallback(window_, mouseButtomCallback);
  glfwSetCursorPosCallback(window_, mousePosCallBack);
  glfwSetWindowSizeCallback(window_, windowSizeCallBack);
  glfwSetKeyCallback(window_, keyCallBack);
}

bool App::isOpen() {
  return !glfwWindowShouldClose(window_);
}

void App::letsStart() {
  end();
  begin();
}

void App::begin() {
  glClearColor(clear_color_.r, clear_color_.g, clear_color_.b, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);

  glColor4f(1, 1, 1, 1);
}

void App::end() {
  key_.frashInput();
  mouse_.frashInput();

  glfwSwapBuffers(window_);

  glfwPollEvents();
}

void App::setClearColor(float r, float g, float b) {
  clear_color_ = Color(r, g, b);
}

void App::setClearColor(const Color &color) {
  clear_color_ = color;
}

// Key Events
bool App::isPushKey(int key) { return key_.isPush(key); }
bool App::isPullKey(int key) { return key_.isPull(key); }
bool App::isPressKey(int key) { return key_.isPress(key); }

// Mouse Events
bool App::isPushMouse(int buttom) { return mouse_.isPush(buttom); }
bool App::isPullMouse(int buttom) { return mouse_.isPull(buttom); }
bool App::isPressMouse(int buttom) { return mouse_.isPress(buttom); }

Vec2d App::mousePos() const { return mouse_.pos(); }

void App::setMousePos(const Vec2d& pos) {
  glfwSetCursorPos(window_, pos.x(), pos.y());
  mouse_.setPos(pos.x(), pos.y());
}
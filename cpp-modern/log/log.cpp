#include "log.h"

#include <cstdio>
#include <ctime>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>

namespace log {

static bool enabled_ = LOG_ENABLE;
static std::mutex enabled_mutex_;

static level level_ = static_cast<level>(LOG_LEVEL);
static std::mutex level_mutex_;

static std::map<std::string, bool> ls_;
static std::mutex ls_mutex_;

//light bg colors
static const char* red     = "\e[101m\e[97m"; //white on red
static const char* yellow  = "\e[103m\e[30m"; //black on yellow
static const char* green   = "\e[102m\e[30m"; //black on green
static const char* blue    = "\e[104m\e[97m"; //white on blue
static const char* reset_terminal_attributes = "\e[0m";

bool add(const char* category) {
  std::lock_guard<std::mutex> lock(ls_mutex_);
  return ls_.insert(std::make_pair(category, false)).second;
}

void block(const char* category) {
  std::lock_guard<std::mutex> lock(ls_mutex_);
  if (category == std::string{"*"}) {
    //special case where category is "*"
    for (auto& x : ls_) x.second = false;
  } else {
    ls_.at(category) = false;
  }
}

bool blocked(const char* category) {
  std::lock_guard<std::mutex> lock(ls_mutex_);
  return !ls_.at(category);
}

bool enabled() {
  std::lock_guard<std::mutex> lock(enabled_mutex_);
  return enabled_;
}

std::map<std::string, bool> ls() {
  std::lock_guard<std::mutex> lock(ls_mutex_);
  return ls_;
}

void reset() {
  {
    std::lock_guard<std::mutex> lock(enabled_mutex_);
    enabled_ = LOG_ENABLE;
  }
  {
    std::lock_guard<std::mutex> lock(level_mutex_);
    level_ = static_cast<level>(LOG_LEVEL);
  }
  {
    std::lock_guard<std::mutex> lock(ls_mutex_);
    ls_.clear();
  }
}

void enable(bool value) {
  std::lock_guard<std::mutex> lock(enabled_mutex_);
  enabled_ = value;
}

void set_level(level value) {
  std::lock_guard<std::mutex> lock(level_mutex_);
  level_ = value;
}

std::string to_color(level lvl) {
  static const char* level_colors[] = { red, yellow, green, blue };
  int i = static_cast<int>(lvl);
  i = 0 <= i && i <= LOG_LEVEL ? i : LOG_LEVEL;
  return level_colors[i];
}

std::string to_string(level lvl) {
  static const char* level_names[] = { "E", "W", "I", "D" };
  int i = static_cast<int>(lvl);
  i = 0 <= i && i <= LOG_LEVEL ? i : LOG_LEVEL;
  return level_names[i];
}

void unblock(const char* category) {
  std::lock_guard<std::mutex> lock(ls_mutex_);
  if (category == std::string{"*"}) {
    //special case where category is "*"
    for (auto& x : ls_) x.second = true;
  } else {
    ls_.at(category) = true;
  }
}

bool can_log(level lvl) {
  return lvl <= level_;
}

log::~log() {
  std::cout << os_.str();
}

std::ostringstream& log::stream(level lvl, const char* category) {
  os_ << to_color(lvl) << " " << to_string(lvl) << " " << reset_terminal_attributes << " [" << category << "] ";
  os_.clear(); //reset error flags
  return os_;
}

//TODO
std::string current_time() {
//  std::time_t t = std::time(nullptr);
//  std::tm* tm = std::localtime(&t);
//  static auto start = std::chrono::high_resolution_clock::now();
//  auto now = std::chrono::high_resolution_clock::now();
//  auto ellapsed = std::chrono::duration<double, std::milli>(now - start).count();
//  std::time_t now_c = std::chrono::system_clock::to_time_t(ellapsed);
//  std::cout << "* *" << ellapsed << "* *"; 
//  auto x =std::chrono::steady_clock::now();
//  static auto start = std::chrono::steady_clock::now();
//  auto now = std::chrono::steady_clock::now();
  char str[] = "00:00:00.000";
  int h = 0;
  int m = 0;
  int s = 0;
  int ms = 0;
  std::sprintf(str, "%02d:%02d:%02d.%03d", h, m, s, ms);
  return str;
}

std::string current_thread() {
  std::string id{"?"};
  std::stringstream ss;
  ss << std::this_thread::get_id();
  return ss.str();
}

}

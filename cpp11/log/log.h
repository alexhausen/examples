#pragma once

#include <map>
#include <sstream>
#include <string>

//compile with -DNLOG to disable LOG completely
#if defined(NLOG)
  #define LOG_ENABLE 0
  
#else
  #define LOG_ENABLE 1
#endif

#if !defined(LOG_LEVEL)
  #define LOG_LEVEL 3
#elif LOG_LEVEL > 3
  #define LOG_LEVEL 3
#endif

namespace log {

enum class level { error, warning, info, debug };

class log {
  log(const log&) = delete;
  log& operator=(const log&) = delete;
 public:
  log() = default;
  ~log();
  std::ostringstream& stream(level lvl, const char* category);
 private:
  std::ostringstream os_;
};

bool add(const char* category);
void block(const char* category);
void unblock(const char* category);
bool blocked(const char* category);
void enable(bool);
bool enabled();
std::map<std::string, bool> ls();
void reset();
void set_level(level lvl);
bool can_log(level lvl);
std::string to_color(level lvl);
std::string to_string(level lvl);
std::string current_time();
std::string current_thread();

}

#define LOG_BASIC(level, category) \
if (LOG_ENABLE) \
  if (log::enabled() && !log::blocked(category) &&log::can_log(level)) \
    log::log().stream(level, category)

#define LOG_(level, category) LOG_BASIC(level, category) << log::current_time() << " [" << log::current_thread() << "] " << __FILE__ << ":" << __LINE__ << " - "

#define LOG_D(category) LOG_(log::level::debug, category)
#define LOG_I(category) LOG_(log::level::info, category)
#define LOG_W(category) LOG_(log::level::warning, category)
#define LOG_E(category) LOG_(log::level::error, category)

#pragma once
#include <memory>
#include <vector>

#include "nvserv/components/component_base.h"
#include "nvserv/logs/declare.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/dist_sink.h"
#include "spdlog/sinks/sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

/**
 * TODO:
 * 1. Support custom logger
 * 2. Tidy up the code
 * Right now only support console & file logger, just snapin to make logger work
 */

NVREST_BEGIN_NAMESPACE(logs)

class Logging : public components::ComponentBase {
 public:
  Logging(components::ComponentLocator& locator,
          const components::ComponentConfig& config, bool is_monitor = false);

  virtual ~Logging();

  Logging& AddDefaultConsoleLogger(LogLevel level);

  Logging& AddFileLogger(LogLevel level, const std::string& filename);

  void Build(LogLevel level);

  void Log(LogLevel level, const std::string& message) const;

 private:
  std::vector<std::shared_ptr<spdlog::logger>> loggers_;
  std::shared_ptr<spdlog::sinks::dist_sink_mt> composite_sink_;
  std::shared_ptr<spdlog::logger> composite_logger_;

  void RegisterLogger(const std::string& name,
                      std::shared_ptr<spdlog::sinks::sink> sink,
                      spdlog::level::level_enum log_level);
};

NVREST_END_NAMESPACE
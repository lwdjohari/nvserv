#include "nvserv/logs/log.h"

NVREST_BEGIN_NAMESPACE(logs)

Logging::Logging(components::ComponentLocator& locator,
          const components::ComponentConfig& config, bool is_monitor)
                  : components::ComponentBase(
                        locator, config, components::ComponentType::kLogging),
                    loggers_(),
                    composite_sink_(
                        std::make_shared<spdlog::sinks::dist_sink_mt>()),
                    composite_logger_(std::make_shared<spdlog::logger>(
                        "nvserv_logger", composite_sink_)) {}

   Logging::~Logging() {}

  

  Logging& Logging::AddDefaultConsoleLogger(LogLevel level) {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    RegisterLogger(
        "nvserv::console_log", console_sink,
        static_cast<spdlog::level::level_enum>(static_cast<int32_t>(level)));

    return *this;
  }

  Logging& Logging::AddFileLogger(LogLevel level, const std::string& filename) {
    auto file_sink =
        std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, false);
    RegisterLogger(
        "nvserv::file_log", file_sink,
        static_cast<spdlog::level::level_enum>(static_cast<int32_t>(level)));
    return *this;
  }

  

  void Logging::Build(LogLevel level) {
    // Register the composite logger
    spdlog::register_logger(composite_logger_);

    // Set the logger as the default logger
    spdlog::set_default_logger(composite_logger_);

    // Set the global log level
    spdlog::set_level(
        static_cast<spdlog::level::level_enum>(static_cast<int32_t>(level)));
  }

  void Logging::Log(LogLevel level, const std::string& message) const {
    switch (level) {
      case LogLevel::Trace:
        spdlog::trace(message);
        break;
      case LogLevel::Debug:
        spdlog::debug(message);
        break;
      case LogLevel::Info:
        spdlog::info(message);
        break;
      case LogLevel::Warning:
        spdlog::warn(message);
        break;
      case LogLevel::Error:
        spdlog::error(message);
        break;
      case LogLevel::Critical:
        spdlog::critical(message);
        break;
      default:
        break;
    }
  }

  void Logging::RegisterLogger(const std::string& name,
                      std::shared_ptr<spdlog::sinks::sink> sink,
                      spdlog::level::level_enum log_level) {
    auto logger = std::make_shared<spdlog::logger>(name, sink);
    logger->set_level(log_level);
    loggers_.push_back(logger);
    composite_sink_->add_sink(sink);
  }

NVREST_END_NAMESPACE
#include "nvserv/logs/log.h"

// cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(logs)

Logging::Logging(components::ComponentLocator& locator,
                 const components::ComponentConfig& config, bool is_monitor)
                : components::ComponentBase(
                      locator, config, components::ComponentType::kLogging),
                  loggers_(),
                  composite_sink_(
                      std::make_shared<spdlog::sinks::dist_sink_mt>()),
                  composite_logger_(nullptr) {}

Logging::~Logging() {}

Logging& Logging::Initialize(const std::string& log_name) {
  composite_logger_ =
      std::make_shared<spdlog::logger>(log_name, composite_sink_);

  return *this;
}

Logging& Logging::AddDefaultConsoleLogger(LogLevel level) {
  if (!composite_logger_)
    throw NullReferenceException(
        "Call Logging::Initialize() before add logger.");

  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  RegisterLogger(
      "nvserv::console_log", console_sink,
      static_cast<spdlog::level::level_enum>(static_cast<int32_t>(level)));

  return *this;
}

Logging& Logging::AddFileLogger(LogLevel level, const std::string& filename) {
  if (!composite_logger_)
    throw NullReferenceException(
        "Call Logging::Initialize() before add logger.");

  auto file_sink =
      std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, false);
  RegisterLogger(
      "nvserv::file_log", file_sink,
      static_cast<spdlog::level::level_enum>(static_cast<int32_t>(level)));
  return *this;
}

void Logging::RegisterAll(bool set_global_level, LogLevel level) {
  if (!composite_logger_)
    throw NullReferenceException(
        "Call Logging::Initialize() before build logger.");

  // Register the composite logger
  spdlog::register_logger(composite_logger_);

  // Set the logger as the default logger
  spdlog::set_default_logger(composite_logger_);

  // Set the global log level
  if (set_global_level) {
    spdlog::set_level(
        static_cast<spdlog::level::level_enum>(static_cast<int32_t>(level)));
  }
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

void Logging::LogTrace(const std::string& message) const {
  Log(LogLevel::Trace, message);
}

void Logging::LogDebug(const std::string& message) const {
  Log(LogLevel::Debug, message);
}

void Logging::LogInfo(const std::string& message) const {
  Log(LogLevel::Info, message);
}

void Logging::LogWarning(const std::string& message) const {
  Log(LogLevel::Warning, message);
}

void Logging::LogError(const std::string& message) const {
  Log(LogLevel::Error, message);
}

void Logging::LogCritical(const std::string& message) const {
  Log(LogLevel::Critical, message);
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
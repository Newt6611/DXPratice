#pragma once

#include <memory>
#include "spdlog/spdlog.h"

class Log
{
public:
	static void Init();
	static inline std::shared_ptr<spdlog::logger>& GetLogger() { return m_Logger; }

private:
	static std::shared_ptr<spdlog::logger> m_Logger;
};

#define LogInfo(...) Log::GetLogger()->trace(__VA_ARGS__)
#define LogWarn(...) Log::GetLogger()->warn(__VA_ARGS__)
#define LogError(...) Log::GetLogger()->error(__VA_ARGS__)
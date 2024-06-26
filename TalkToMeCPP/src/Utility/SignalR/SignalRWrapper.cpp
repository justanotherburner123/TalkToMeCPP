// Copyright(c) 2024 grrimgrriefer & DZnnah, see LICENSE for details.

#pragma once
#include "../Logging/HubConnectionLogger.h"
#include "../Logging/LoggerInterface.h"
#include "SignalRWrapper.h"
#include <exception>
#include <format>
#include <functional>
#include <memory>
#include <signalrclient/hub_connection.h>
#include <signalrclient/hub_connection_builder.h>
#include <signalrclient/signalr_value.h>
#include <signalrclient/trace_level.h>
#include <string>
#include <vector>

namespace Utility::SignalR
{
	SignalRWrapper::SignalRWrapper(std::string_view address,
			int port,
			Logging::LoggerInterface& logger) :
		m_connection(std::make_unique<signalr::hub_connection>(signalr::hub_connection_builder::create(
			std::format("http://{}:{}/hub", address, std::to_string(port)))
			.with_logging(std::make_shared<Logging::HubConnectionLogger>(logger),
			signalr::trace_level::verbose).build()))
	{
	}

	void SignalRWrapper::Start(const std::function<void(std::exception_ptr)>& callback) noexcept
	{
		m_connection->start(callback);
	}

	void SignalRWrapper::Stop(const std::function<void(std::exception_ptr)>& callback) noexcept
	{
		m_connection->stop(callback);
	}

	void SignalRWrapper::On(const std::string& event_name,
		const std::function<void(const std::vector<signalr::value>&)>& handler)
	{
		m_connection->on(event_name.data(), handler);
	}

	void SignalRWrapper::Invoke(const std::string& method_name,
		const std::vector<signalr::value>& arguments,
		const std::function<void(const signalr::value&, std::exception_ptr)>& callback) noexcept
	{
		m_connection->invoke(method_name.data(), arguments, callback);
	}
}
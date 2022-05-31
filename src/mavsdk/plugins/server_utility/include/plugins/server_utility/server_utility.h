// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see
// https://github.com/mavlink/MAVSDK-Proto/blob/main/protos/server_utility/server_utility.proto)

#pragma once

#include <array>
#include <cmath>
#include <functional>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "mavsdk/plugin_base.h"

#include "mavsdk/callback_list.h"

namespace mavsdk {

class System;
class ServerUtilityImpl;

/**
 * @brief Utility for onboard MAVSDK instances for common "server" tasks.
 */
class ServerUtility : public PluginBase {
public:
    /**
     * @brief Constructor. Creates the plugin for a specific System.
     *
     * The plugin is typically created as shown below:
     *
     *     ```cpp
     *     auto server_utility = ServerUtility(system);
     *     ```
     *
     * @param system The specific system associated with this plugin.
     */
    explicit ServerUtility(System& system); // deprecated

    /**
     * @brief Constructor. Creates the plugin for a specific System.
     *
     * The plugin is typically created as shown below:
     *
     *     ```cpp
     *     auto server_utility = ServerUtility(system);
     *     ```
     *
     * @param system The specific system associated with this plugin.
     */
    explicit ServerUtility(std::shared_ptr<System> system); // new

    /**
     * @brief Destructor (internal use only).
     */
    ~ServerUtility() override;

    /**
     * @brief Status types.
     */
    enum class StatusTextType {
        Debug, /**< @brief Debug. */
        Info, /**< @brief Information. */
        Notice, /**< @brief Notice. */
        Warning, /**< @brief Warning. */
        Error, /**< @brief Error. */
        Critical, /**< @brief Critical. */
        Alert, /**< @brief Alert. */
        Emergency, /**< @brief Emergency. */
    };

    /**
     * @brief Stream operator to print information about a `ServerUtility::StatusTextType`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream&
    operator<<(std::ostream& str, ServerUtility::StatusTextType const& status_text_type);

    /**
     * @brief Possible results returned for server utility requests.
     */
    enum class Result {
        Unknown, /**< @brief Unknown result. */
        Success, /**< @brief Request succeeded. */
        NoSystem, /**< @brief No system is connected. */
        ConnectionError, /**< @brief Connection error. */
        InvalidArgument, /**< @brief Invalid argument. */
    };

    /**
     * @brief Stream operator to print information about a `ServerUtility::Result`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, ServerUtility::Result const& result);

    /**
     * @brief Callback type for asynchronous ServerUtility calls.
     */
    using ResultCallback = std::function<void(Result)>;

    /**
     * @brief Sends a statustext.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    Result send_status_text(StatusTextType type, std::string text) const;

    /**
     * @brief Copy constructor.
     */
    ServerUtility(const ServerUtility& other);

    /**
     * @brief Equality operator (object is not copyable).
     */
    const ServerUtility& operator=(const ServerUtility&) = delete;

private:
    /** @private Underlying implementation, set at instantiation */
    std::unique_ptr<ServerUtilityImpl> _impl;
};

} // namespace mavsdk
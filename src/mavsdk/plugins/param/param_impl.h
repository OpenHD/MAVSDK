#pragma once

#include <mutex>

#include "mavlink_include.h"
#include "plugins/param/param.h"
#include "plugin_impl_base.h"

namespace mavsdk {

class ParamImpl : public PluginImplBase {
public:
    explicit ParamImpl(System& system,uint8_t target_component_id,bool use_extended);
    explicit ParamImpl(std::shared_ptr<System> system,uint8_t target_component_id,bool use_extended);
    ~ParamImpl() override;

    void init() override;
    void deinit() override;

    void enable() override;
    void disable() override;

    std::pair<Param::Result, int32_t> get_param_int(const std::string& name);

    Param::Result set_param_int(const std::string& name, int32_t value);

    std::pair<Param::Result, float> get_param_float(const std::string& name);

    Param::Result set_param_float(const std::string& name, float value);

    std::pair<Param::Result, std::string> get_param_custom(const std::string& name);

    Param::Result set_param_custom(const std::string& name, const std::string& value);

    Param::AllParams get_all_params(bool clear_cache);

    void set_n_retransmissions(int n_retransmissions);

    void set_timeout(double timeout_s);

private:
    const uint8_t _target_component_id;
    const bool _use_extended;
    static Param::Result
    result_from_mavlink_parameter_sender_result(MavlinkParameterSender::Result result);
};

} // namespace mavsdk

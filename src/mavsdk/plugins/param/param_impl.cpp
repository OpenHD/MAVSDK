#include <functional>
#include "param_impl.h"
#include "system.h"

namespace mavsdk {

ParamImpl::ParamImpl(System& system,uint8_t target_component_id,bool use_extended) : PluginImplBase(system),
    _target_component_id(target_component_id),
    _use_extended(use_extended)
{
    _parent->register_plugin(this);
}

ParamImpl::ParamImpl(std::shared_ptr<System> system,uint8_t target_component_id,bool use_extended) : PluginImplBase(std::move(system)),
    _target_component_id(target_component_id),
    _use_extended(use_extended)
{
    _parent->register_plugin(this);
}

ParamImpl::~ParamImpl()
{
    _parent->unregister_plugin(this);
}

void ParamImpl::init() {}

void ParamImpl::deinit() {}

void ParamImpl::enable() {}

void ParamImpl::disable() {}

std::pair<Param::Result, int32_t> ParamImpl::get_param_int(const std::string& name)
{
    auto param_server=_parent->get_param_sender(_target_component_id,_use_extended);
    std::pair<MavlinkParameterSender::Result, int32_t> result = param_server->get_param_int(name);
    return std::make_pair<>(
        result_from_mavlink_parameter_sender_result(result.first), result.second);
}

Param::Result ParamImpl::set_param_int(const std::string& name, int32_t value)
{
    auto param_server=_parent->get_param_sender(_target_component_id,_use_extended);
    MavlinkParameterSender::Result result = param_server->set_param_int(name, value);
    return result_from_mavlink_parameter_sender_result(result);
}

std::pair<Param::Result, float> ParamImpl::get_param_float(const std::string& name)
{
    auto param_server=_parent->get_param_sender(_target_component_id,_use_extended);
    std::pair<MavlinkParameterSender::Result, float> result = param_server->get_param_float(name);
    return std::make_pair<>(
        result_from_mavlink_parameter_sender_result(result.first), result.second);
}

Param::Result ParamImpl::set_param_float(const std::string& name, float value)
{
    auto param_server=_parent->get_param_sender(_target_component_id,_use_extended);
    MavlinkParameterSender::Result result = param_server->set_param_float(name, value);
    return result_from_mavlink_parameter_sender_result(result);
}

std::pair<Param::Result, std::string> ParamImpl::get_param_custom(const std::string& name)
{
    auto param_server=_parent->get_param_sender(_target_component_id,_use_extended);
    auto result = param_server->get_param_custom(name);
    return std::make_pair<>(
        result_from_mavlink_parameter_sender_result(result.first), result.second);
}

Param::Result ParamImpl::set_param_custom(const std::string& name, const std::string& value)
{
    auto param_server=_parent->get_param_sender(_target_component_id,_use_extended);
    auto result = param_server->set_param_custom(name, value);
    return result_from_mavlink_parameter_sender_result(result);
}

Param::AllParams ParamImpl::get_all_params(bool clear_cache)
{
    auto param_server=_parent->get_param_sender(_target_component_id,_use_extended);
    auto tmp = param_server->get_all_params(clear_cache);

    Param::AllParams res{};
    for (auto const& param_pair : tmp) {
        if (param_pair.second.is<float>()) {
            Param::FloatParam tmp_param;
            tmp_param.name = param_pair.first;
            tmp_param.value = param_pair.second.get<float>();
            res.float_params.push_back(tmp_param);
        } else if (param_pair.second.is<int32_t>()) {
            Param::IntParam tmp_param;
            tmp_param.name = param_pair.first;
            tmp_param.value = param_pair.second.get<int32_t>();
            res.int_params.push_back(tmp_param);
        } else if (param_pair.second.is<int16_t>()) {
            Param::IntParam tmp_param;
            tmp_param.name = param_pair.first;
            tmp_param.value = param_pair.second.get<int16_t>();
            res.int_params.push_back(tmp_param);
        } else if (param_pair.second.is<int8_t>()) {
            Param::IntParam tmp_param;
            tmp_param.name = param_pair.first;
            tmp_param.value = param_pair.second.get<int8_t>();
            res.int_params.push_back(tmp_param);
        }else if (param_pair.second.is<std::string>()) {
            Param::CustomParam tmp_param;
            tmp_param.name = param_pair.first;
            tmp_param.value = param_pair.second.get<std::string>();
            res.custom_params.push_back(tmp_param);
        }
    }

    return res;
}

Param::Result
ParamImpl::result_from_mavlink_parameter_sender_result(MavlinkParameterSender::Result result)
{
    switch (result) {
        case MavlinkParameterSender::Result::Success:
            return Param::Result::Success;
        case MavlinkParameterSender::Result::Timeout:
            return Param::Result::Timeout;
        case MavlinkParameterSender::Result::ParamNameTooLong:
            return Param::Result::ParamNameTooLong;
        case MavlinkParameterSender::Result::WrongType:
            return Param::Result::WrongType;
        case MavlinkParameterSender::Result::ConnectionError:
            return Param::Result::ConnectionError;
        case MavlinkParameterSender::Result::ParamValueTooLong:
            return Param::Result::ParamValueTooLong;
        case MavlinkParameterSender::Result::ValueUnsupported:
            return Param::Result::ValueUnsupported;
        default:
            LogErr() << "Unknown param error";
            return Param::Result::Unknown;
    }
}

void ParamImpl::set_n_retransmissions(int n_retransmissions){
    auto param_server=_parent->get_param_sender(_target_component_id,_use_extended);
    param_server->set_n_retransmissions(n_retransmissions);
}

void ParamImpl::set_timeout(double timeout_s){
    auto param_server=_parent->get_param_sender(_target_component_id,_use_extended);
    param_server->set_timeout_seconds(timeout_s);
}

} // namespace mavsdk

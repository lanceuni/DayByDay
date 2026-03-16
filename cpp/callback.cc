// g++ -std=c++11 -Wall -Wextra -pthread callback.cc -o callback
#include <iostream>
#include <functional>
#include <string>
#include <thread>
#include <chrono>

// 模拟数据结构
struct SensorData {
    int id;
    double value;
    std::string timestamp;
};

// 定义回调函数类型
using SsiCallback = std::function<void(const std::string&, const SensorData&)>;

// ************* Proxy 类 *************
// 负责接收数据并触发回调
class Proxy {
public:
    Proxy() : callback_(nullptr) {
        std::cout << "[Proxy] 构造完成。\n";
    }

    // 设置回调函数
    void SetSsiCallback(SsiCallback callback) {
        callback_ = std::move(callback);
        std::cout << "[Proxy] 回调函数已设置。\n";
    }

    // 模拟接收数据并触发回调 (OnRun 时执行)
    void OnRun() {
        std::cout << "[Proxy] 开始运行并模拟接收数据...\n";
        // 模拟一些延迟，代表等待数据
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // 模拟接收到数据
        SensorData data{101, 25.6, "2023-10-27 10:00:00"};
        std::string error_status = "OK"; // 或者 "ERROR"

        std::cout << "[Proxy] 接收到数据: ID=" << data.id << ", Value=" << data.value << "\n";

        // 触发回调
        if (callback_) {
            std::cout << "[Proxy] 触发注册的回调函数...\n";
            callback_(error_status, data);
        } else {
            std::cout << "[Proxy] 警告：未设置回调函数！\n";
        }
        std::cout << "[Proxy] OnRun end\n";
    }

private:
    SsiCallback callback_;
};

// ************* Mapping 类 *************
// 负责初始化、注册回调、处理数据
class Mapping {
public:
    Mapping(Proxy& proxy) : proxy_(proxy) {
        std::cout << "[Mapping] 构造函数执行。\n";
        // 在构造函数中注册回调
        RegisterCallback();
    }

    // 注册回调函数到 Proxy
    void RegisterCallback() {
        // 使用 Lambda 表达式作为回调
        auto lambda_callback = [this](const std::string& e2e_error, const SensorData& data) {
            std::cout << "[Mapping] 回调被触发！\n";
            this->HandleSsiData(e2e_error, data);
        };

        std::cout << "[Mapping] 向 Proxy 注册回调函数...\n";
        proxy_.SetSsiCallback(lambda_callback);
    }

    // 回调函数实际调用的方法 - 处理数据
    void HandleSsiData(const std::string& e2e_error, const SensorData& data) {
        std::cout << "[Mapping::HandleSsiData] 开始处理数据...\n";
        if (e2e_error != "OK") {
            std::cout << "[Mapping::HandleSsiData] 错误: " << e2e_error << "\n";
            return;
        }
        std::cout << "[Mapping::HandleSsiData] 数据校验通过。\n";
        UpdateSensServiceAdas6(data);
    }

    // 更新服务数据
    void UpdateSensServiceAdas6(const SensorData& data) {
        std::cout << "[Mapping::UpdateSensServiceAdas6] 使用数据更新服务...\n";
        std::cout << "  -> 更新传感器 ID: " << data.id << "\n";
        std::cout << "  -> 更新值: " << data.value << "\n";
        std::cout << "  -> 时间戳: " << data.timestamp << "\n";
        std::cout << "[Mapping::UpdateSensServiceAdas6] 服务更新完成。\n";
    }


private:
    Proxy& proxy_; // 与 Proxy 的关联
};


// ************* 主函数 *************
int main() {
    std::cout << "--- 初始化阶段 ---\n";
    // 1. 创建 Proxy 实例
    Proxy my_proxy;

    // 2. 创建 Mapping 实例，并在构造时注册回调
    Mapping my_mapping(my_proxy);

    std::cout << "\n--- 运行时阶段 (OnRun) ---\n";
    // 3. 模拟 OnRun 过程，Proxy 接收数据并触发回调
    my_proxy.OnRun();

    std::cout << "\n--- 程序结束 ---\n";
    return 0;
}




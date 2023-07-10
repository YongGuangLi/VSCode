
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

// 获取本地网卡MAC地址
std::vector<std::string> getMacAddresses() {
    std::vector<std::string> macAddresses;
    std::ifstream file("/sys/class/net/eth0/address");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            macAddresses.push_back(line);
        }
        file.close();
    }
    return macAddresses;
}

// 验证授权
bool validateLicense(const std::string& licenseKey) {
    // 获取本地网卡MAC地址
    std::vector<std::string> macAddresses = getMacAddresses();

    // 检查授权码是否与任意一个网卡的MAC地址匹配
    for (const std::string& macAddress : macAddresses) {
        if (licenseKey == macAddress) {
            return true;
        }
    }

    return false;
}

int main() {
    // 输入授权码
    std::cout << "请输入授权码：";
    std::string licenseKey;
    std::cin >> licenseKey;

    // 验证授权
    if (validateLicense(licenseKey)) {
        std::cout << "授权成功！" << std::endl;
    } else {
        std::cout << "授权失败！" << std::endl;
    }

    return 0;
}

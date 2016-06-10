#pragma once

#include <string>

namespace ssodc {
namespace utils {

class ClasterState {
private:
    int m_id;
    std::string m_macaddress;
    int m_cpufreq;
    double m_cpuworkload;
    int m_ram;
    double m_ramworkload;
    int m_romfreespace;

public:
    ClasterState();
    ClasterState(int, std::string, int, double, int, double, int);

    int GetId();
    std::string GetMacAddress();
    int GetCpuFreq();
    double GetCpuWorkload();
    int GetRam();
    double GetRamWorkload();
    int GetRomFreespace();

    void SetId(int);
    void SetMacAddress(std::string);
    void SetCpuFreq(int);
    void SetCpuWorkload(double);
    void SetRam(int);
    void SetRamWorkload(double);
    void SetRomFreespace(int);

    ~ClasterState();
};

}     /* namespace utils */
}     /* namespace ssodc */

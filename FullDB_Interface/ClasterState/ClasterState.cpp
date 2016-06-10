#include "ClasterState.hpp"

namespace ssodc {
namespace utils {

ClasterState::ClasterState() : m_id(0), m_macaddress(""), m_cpufreq(0),
    m_cpuworkload(0.0), m_ram(0), m_ramworkload(0.0), m_romfreespace(0)
{
}

ClasterState::ClasterState(int id, std::string macaddress, int cpufreq, double cpuworkload,
                   int ram, double ramworkload, int romfreespace) : m_id(id),
    m_macaddress(macaddress), m_cpufreq(cpufreq), m_cpuworkload(cpuworkload),
    m_ram(ram), m_ramworkload(ramworkload) , m_romfreespace(romfreespace)
{
}

int ClasterState::GetId()
{
    return m_id;
}
std::string ClasterState::GetMacAddress()
{
    return m_macaddress;
}
int ClasterState::GetCpuFreq()
{
    return m_cpufreq;
}
double ClasterState::GetCpuWorkload()
{
    return m_cpuworkload;
}
int ClasterState::GetRam()
{
    return m_ram;
}
double ClasterState::GetRamWorkload()
{
    return m_ramworkload;
}
int ClasterState::GetRomFreespace()
{
    return m_romfreespace;
}

void ClasterState::SetId(int id)
{
    m_id = id;
}
void ClasterState::SetMacAddress(std::string macaddress)
{
    m_macaddress = macaddress;
}
void ClasterState::SetCpuFreq(int cpufreq)
{
    m_cpufreq = cpufreq;
}
void ClasterState::SetCpuWorkload(double cpuworkload)
{
    m_cpuworkload = cpuworkload;
}
void ClasterState::SetRam(int ram) 
{
    m_ram = ram;
}
void ClasterState::SetRamWorkload(double ramworkload)
{
    m_ramworkload = m_ramworkload;
}
void ClasterState::SetRomFreespace(int romfreespace)
{
    m_romfreespace = romfreespace;
}
ClasterState::~ClasterState() 
{
}

}     /* namespace utils */
}     /* namespace ssodc */

#include <iostream>
#include <string>
#include <fstream>

class Appliance
{
private:
    std::string i_name;
public:
    explicit Appliance(std::string& name) : i_name(name) {}

    void Poll()
    {
        std::cout << i_name << "\n";
        //какая-то реализация
    }
};

class Electricity_Meter : public Appliance
{
public:
    explicit Electricity_Meter(std::string& name) : Appliance(name) {}
};

class Input_Descrete_Signal : public Appliance
{
public:
    explicit Input_Descrete_Signal(std::string& name) : Appliance(name) {}
};

class Heating_Control : public Appliance
{
public:
    explicit Heating_Control(std::string& name) : Appliance(name) {}
};

std::string electricity_meter[] = { "Меркурий 230", "Нева МТ314", "Энергомера CE308" };

std::string input_descrete_signal[] = { "Reallab NL-16HV", "Приборэлектро PRE - 16", "Энергосервис ЭНМВ-1-24" };

std::string heating_control[] = { "Ouman S203", "Овен ТРМ232" };

struct
{
    Electricity_Meter* meter = nullptr;
    Input_Descrete_Signal* device = nullptr;
    Heating_Control* heat = nullptr;
} config ;

int main()
{
    setlocale(LC_ALL, "ru");
    std::ifstream cfg("..\cfg.txt");
    std::string tmp;

    while (getline(cfg, tmp))
    {
        int n = sizeof(electricity_meter) / sizeof(std::string);
        for (int i = 0; i < n; ++i)
        {
            if (electricity_meter[i] == tmp)
            {
                config.meter = new Electricity_Meter(tmp);
                break;
            }
        }

        n = sizeof(input_descrete_signal) / sizeof(std::string);
        for (int i = 0; i < n; ++i)
        {
            if (input_descrete_signal[i] == tmp)
            {
                config.device = new Input_Descrete_Signal(tmp);
                break;
            }
        }

        n = sizeof(heating_control) / sizeof(std::string);
        for (int i = 0; i < n; ++i)
        {
            if (heating_control[i] == tmp)
            {
                config.heat = new Heating_Control(tmp);
                break;
            }
        }
    }
}


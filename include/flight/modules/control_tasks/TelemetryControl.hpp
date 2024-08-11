#ifndef FLIGHT_TELEMETRYCONTROL_HPP
#define FLIGHT_TELEMETRYCONTROL_HPP

#include <flight/modules/control_tasks/Control.hpp>
#include <flight/modules/mcl/Registry.hpp>
#include <flight/modules/mcl/Flag.hpp>
#include <flight/modules/lib/Log.hpp>
#include <flight/modules/lib/Util.hpp>
#include <string>

class TelemetryControl : public Control {

typedef void (TelemetryControl::*functionType)(const vector<string>&);

private:
    unordered_map<string, functionType> functions;
    const unordered_map<string, vector<string>> arguments {
        {"HRT", {}},
        {"SAB", {}},
        {"UAB", {}},
        {"SAC", {"valve_location", "actuation_type", "priority"}},
        {"SRQ", {"sensor_type", "sensor_location"}},
        {"VRQ", {"valve_type", "valve_location"}},
        {"SGP", {}},
        {"INF", {}}
    };

    unordered_map<string, string> sensor_type_inverse_map {
        {"0", "thermocouple"},
        {"1", "pressure"},
        {"2", "load_cell"}
    };
    
    unordered_map<string, string> sensor_location_inverse_map {
        {"1", "PT-1"},
        {"2", "PT-2"},
        {"3", "PT-3"},
        {"4", "PT-4"},
        {"5", "TC-1"},
        {"6", "LC-1"},
        {"7", "LC-2"},
        {"8", "LC-3"}
    };

    std::unordered_map<std::string, std::string> valve_type_inverse_map {
        {"0", "solenoid"}
    };
    
    std::unordered_map<std::string, std::string> valve_location_inverse_map {
        {"1", "ethanol_ground_vent"},
        {"2", "nitrous_vent"},
        {"3", "ethanol_pressurization"},
        {"4", "nitrous_pressurization"},
        {"5", "ethanol_flight_vent"},
        {"6", "nitrous_flight_vent"},
        {"7", "ethanol_drain"},
        {"8", "nitrous_drain"},
        {"9", "ethanol_mpv"},
        {"A", "nitrous_mpv"},
        {"B", "nitrous_isolation"}
    };

    void ingest(const Log& log);

    void heartbeat(const vector<string>& args);
    void soft_abort(const vector<string>& args);
    void undo_soft_abort(const vector<string>& args);
    void solenoid_actuate(const vector<string>& args);
    void sensor_request(const vector<string>& args);
    void valve_request(const vector<string>& args);
    void stage_progression(const vector<string>& args);
    void info(const vector<string>& args);
    void make_functions();

public:
    TelemetryControl();
    void begin() override;
    void execute() override;
};
#endif //FLIGHT_TELEMETRYCONTROL_HPP

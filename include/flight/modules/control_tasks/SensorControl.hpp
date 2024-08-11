//
// Created by Srikar on 4/15/2020.
//

#ifndef FLIGHT_SENSORCONTROL_HPP
#define FLIGHT_SENSORCONTROL_HPP

#include <flight/modules/mcl/Registry.hpp>
#include <flight/modules/mcl/Flag.hpp>
#include <flight/modules/control_tasks/Control.hpp>
#include <flight/modules/lib/Kalman.hpp>
#include <vector>
#include <map>

class SensorControl : public Control {
    private:
        long double last_send_time;
        long send_interval;
        std::map<string, std::map<string, Kalman>> kalman_filters;
        unordered_map<string, string> sensor_type_map {
            {"thermocouple", "0"},
            {"pressure", "1"},
            {"load_cell", "2"}
        };
        
        unordered_map<string, string> sensor_location_map {
            {"PT-1", "1"},
            {"PT-2", "2"},
            {"PT-3", "3"},
            {"PT-4", "4"},
            {"TC-1", "5"},
            {"LC-1", "6"},
            {"LC-2", "7"},
            {"LC-3", "8"}
        };

        void boundary_check();
        void send_sensor_data();

    public:
        SensorControl();
        void begin() override;
        void execute() override;
};
#endif //FLIGHT_SENSORCONTROL_HPP

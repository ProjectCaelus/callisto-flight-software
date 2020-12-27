//
// Created by myfatemi04 on 12/27/2020.
//

#ifndef FLIGHT_CONFIG_HPP
#define FLIGHT_CONFIG_HPP

typedef struct {
    double lower, upper
} BoundaryConfig;

struct ConfigSensorInfo {
    struct kalman_args {
        double process_variance, measurement_variance, kalman_value;
    };
    struct boundaries {
        BoundaryConfig safe, warn;
    };
    int pin;
};

struct ConfigValveInfo {
    int pin;
    string natural_state;
    bool special;
};

class Config {
public:
    struct {
        string GS_IP;
        int GS_PORT;

        string SOCKETIO_HOST;
        int SOCKETIO_PORT;

        double DELAY;
    } telemetry;

    struct {
        map<string, map<string, ConfigSensorInfo>> list;
        string address;
        int baud;
        double send_interval;
    } sensors;

    struct {
        map<string, map<string, ConfigValveInfo>> list;
        string address;
        int baud;
        double send_interval;
    } valves;

    struct {
        vector<string> list;
        double request_interval;
        double send_interval;
    } stages;

    struct {
        double delay;
    } timer;

    struct {
        vector<string> active_stages;
    } pressure_control;

    string arduino_type;
};

Config global_config;

#endif //FLIGHT_CONFIG_HPP

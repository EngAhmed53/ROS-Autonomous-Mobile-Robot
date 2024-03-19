#ifndef ARDUINO_COMMS_HPP
#define ARDUINO_COMMS_HPP

#include <sstream>
#include <libserial/SerialPort.h>
#include <iostream>

class ArduinoComms
{
public:
    ArduinoComms();

    void connect(const std::string &serial_device, int32_t baud_rate, int32_t timeout_ms);
    void disconnect();
    bool connected() const;
    std::string send_msg(const std::string &msg_to_send, bool print_output = true);
    void send_empty_msg();
    void read_encoder_values(long &val_1, long &val_2);
    void set_motor_values(int val_1, int val_2);
    void set_pid_values(int k_p, int k_d, int k_i, int k_o);

private:
    LibSerial::BaudRate convert_baud_rate(int baud_rate);
    LibSerial::SerialPort serial_conn_;
    int timeout_ms_;
};

#endif // ARDUINO_COMMS_HPP
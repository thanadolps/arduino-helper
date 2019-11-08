#ifndef THANADOL_HELPER_SERIAL_IO_H
#define THANADOL_HELPER_SERIAL_IO_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class SerialIO {
public:
    
    static void wait_for_bytes(Stream* serial, int n_byte, int re_recieve_interval) {
        while(serial->available() < n_byte) {
            delay(re_recieve_interval);
        }
    }

    static void read_signed_bytes(Stream* serial, int8_t* buffer, size_t n)
    {
        size_t i = 0;
        int c;
        while (i < n)
        {
            c = serial->read();
            if (c < 0) break;
            *buffer++ = (int8_t) c;
            i++;
        }
    }

    static int8_t read_i8(Stream* serial) {
        byte byte_buffer[1];
        serial->readBytes(byte_buffer, 1);
        return byte_buffer[0];
    }

    static int16_t read_i16(Stream* serial)
    {
        int8_t buffer[2];
        read_signed_bytes(serial, buffer, 2);
        return (((int16_t) buffer[0]) & 0xff) | (((int16_t) buffer[1]) << 8 & 0xff00);
    }

    static int8_t wait_to_read_i8(Stream* serial, int re_recieve_interval) {
        wait_for_bytes(serial, 1, re_recieve_interval);
        return read_i8(serial);
    }

    static int16_t wait_to_read_i16(Stream* serial, int re_recieve_interval) {
        wait_for_bytes(serial, 2, re_recieve_interval);
        return read_i16(serial);
    }

};


#endif
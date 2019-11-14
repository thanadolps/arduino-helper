#ifndef THANADOL_HELPER_SERIAL_IO_H
#define THANADOL_HELPER_SERIAL_IO_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class SerialIO {
private:
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
public:
    
    static void wait_for_bytes(Stream* serial, int n_byte, int re_recieve_interval) {
        while(serial->available() < n_byte) {
            delay(re_recieve_interval);
        }
    }

    /**
     * read bytes from serial and return it as i8
     * can fail if serial don't contains enough byte
    */
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

    /**
     * simiar to read_i8 but wait for serial to contain enough byte first.
     * 
     * @param re_recieve_interval interval (in ms) between checking if serial contain enought byte
    */
    static int8_t wait_to_read_i8(Stream* serial, int re_recieve_interval) {
        wait_for_bytes(serial, 1, re_recieve_interval);
        return read_i8(serial);
    }

    static int16_t wait_to_read_i16(Stream* serial, int re_recieve_interval) {
        wait_for_bytes(serial, 2, re_recieve_interval);
        return read_i16(serial);
    }


    // Print Helper

    template<typename T>
    static void print_to(Stream* serial, T out) {
        serial->print(out);
    }

    template<typename T, typename... Args>
    static void print_to(Stream* serial, T out, Args... args) {
        serial->print(out);
        serial->print(' ');
        print_to(serial, args...);
    }

    template<typename T>
    static void println_to(Stream* serial, T out) {
        serial->println(out);
    }

    template<typename T, typename... Args>
    static void println_to(Stream* serial, T out, Args... args) {
        print_to(serial, out, args...);
        serial->println();
    }


    template<typename T>
    static void print(T out) {
        print_to(&Serial, out);
    }

    template<typename T, typename... Args>
    static void print(T out, Args... args) {
        print_to(&Serial, out, args...);
    }

    template<typename T>
    static void println(T out) {
        println_to(&Serial, out);
    }

    template<typename T, typename... Args>
    static void println(T out, Args... args) {
        println_to(&Serial, out, args...);
    }

};


#endif
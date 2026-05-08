#pragma once
#include <SFML/Graphics.hpp>

inline void int_to_char(int val, char* buf)
{
    if (val == 0) { buf[0] = '0'; buf[1] = '\0'; return; }
    char tmp[32]; int ti = 0;
    bool neg = val < 0;
    if (neg) val = -val;
    while (val > 0) { tmp[ti++] = '0' + val % 10; val /= 10; }
    int pos = 0;
    if (neg) buf[pos++] = '-';
    while (ti > 0) buf[pos++] = tmp[--ti];
    buf[pos] = '\0';
}
 
inline void double_to_char(double val, char* buf, int decimal_places = 2)
{
    if (val < 0) { buf[0] = '-'; val = -val; buf++; }
 
    // Use long long to handle large values without overflow
    long long int_part = (long long)val;
    int dec_part = (int)((val - (double)int_part) * 100.0 + 0.5); // +0.5 for rounding
 
    // If rounding pushed dec_part to 100, carry over
    if (dec_part >= 100) { int_part++; dec_part = 0; }
 
    // Write integer part manually
    char tmp[32]; int ti = 0;
    if (int_part == 0) { tmp[ti++] = '0'; }
    else {
        long long n = int_part;
        char r[32]; int ri = 0;
        while (n > 0) { r[ri++] = '0' + n % 10; n /= 10; }
        while (ri > 0) tmp[ti++] = r[--ri];
    }
 
    int pos = 0;
    for (int i = 0; i < ti; i++) buf[pos++] = tmp[i];
    buf[pos++] = '.';
 
    // Write decimal part (always 2 digits)
    if (dec_part < 10) buf[pos++] = '0';
    int_to_char(dec_part, tmp);
    for (int i = 0; tmp[i] != '\0'; i++) buf[pos++] = tmp[i];
    buf[pos] = '\0';
}
 
inline void sf_string_to_char(const sf::String& s, char* buf, std::size_t max)
{
    std::size_t len = s.getSize() < max - 1 ? s.getSize() : max - 1;
    for (std::size_t i = 0; i < len; ++i) buf[i] = (char)s[i];
    buf[len] = '\0';
}
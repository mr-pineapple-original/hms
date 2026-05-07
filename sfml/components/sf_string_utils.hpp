#pragma once
#include <SFML/Graphics.hpp>

inline void sf_string_to_char(const sf::String& str, char* buf, int max_size)
{
    int len = (int)str.getSize();
    if (len >= max_size) len = max_size - 1;
    for (int i = 0; i < len; i++)
        buf[i] = static_cast<char>(str[i]);
    buf[len] = '\0';
}

inline void int_to_char(int val, char* buf)
{
    if (val == 0) { buf[0] = '0'; buf[1] = '\0'; return; }
    char temp[16]; int d = 0, pos = 0;
    while (val > 0) { temp[d++] = '0' + (val % 10); val /= 10; }
    while (d > 0) buf[pos++] = temp[--d];
    buf[pos] = '\0';
}

inline void double_to_char(double val, char* buf, int decimal_places = 2)
{
    int int_part = (int)val;
    int dec_part = (int)((val - int_part) * 100);
    if (dec_part < 0) dec_part = -dec_part;

    char tmp[32];
    int pos = 0;

    int_to_char(int_part, tmp);
    for (int i = 0; tmp[i] != '\0'; i++) buf[pos++] = tmp[i];
    buf[pos++] = '.';

    if (dec_part < 10) buf[pos++] = '0';
    int_to_char(dec_part, tmp);
    for (int i = 0; tmp[i] != '\0'; i++) buf[pos++] = tmp[i];
    buf[pos] = '\0';
}
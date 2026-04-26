#pragma once

// Static utility class
class Parser
{
public:
    static void parse_int(const char* line, int& i, int& value);
    static void parse_float(const char* line, int& i, float& value);
    static void parse_double(const char* line, int& i, double& value);
    static void parse_char(const char* line, int& i, char& character);
    static void parse_string(const char* line, int& i, char* &output);
    static void skip_comma(const char* line, int& i);
};
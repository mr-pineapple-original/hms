#include"parser.hpp"
#include"char_array_functions.hpp"

void Parser::parse_int(const char* line, int& i, int& value)
{
    value = 0;

    while (line[i] != ',' && line[i] != '\0')
    {
        value = value * 10 + (line[i] - '0');
        i++;
    }
}

void Parser::skip_comma(const char* line, int& i)
{
    if (line[i] == ',')
        i++;
}

void Parser::parse_string(const char* line, int& i, char* &output)
{
    int size = DEFAULT_SIZE_CHAR_ARRAY;
    output = new char[size];

    int j = 0;

    while (line[i] != ',' && line[i] != '\0')
    {
        if (j >= size - 1)
        {
            resize_array(output, size, size * 2);
            size *= 2;
        }

        output[j++] = line[i++];
    }

    output[j] = '\0';
}

void Parser::parse_float(const char* line, int& i, float& value)
{
    value = 0;
    float factor = 1.0f;

    while (line[i] != ',' && line[i] != '\0')
    {
        if (line[i] == '.')
        {
            factor = 0.1f;
            i++;
            continue;
        }

        if (factor == 1.0f)
        {
            value = value * 10 + (line[i] - '0');
        }
        else
        {
            value += (line[i] - '0') * factor;
            factor *= 0.1f;
        }

        i++;
    }
}

void Parser::parse_char(const char* line, int& i, char& character)
{
    if (line[i] != '\0')
    {
        character = line[i];
    }
    else
    {
        character = '\0'; // fallback safety
    }
    i++;
}

void Parser::parse_double(const char* line, int& i, double& value)
{
    value = 0.0;
    double factor = 1.00;

    while (line[i] != ',' && line[i] != '\0')
    {
        if (line[i] == '.')
        {
            factor = 0.1;
            i++;
            continue;
        }

        if (factor == 1.0)
        {
            value = value * 10 + (line[i] - '0');
        }
        else
        {
            value += (line[i] - '0') * factor;
            factor *= 0.1;
        }

        i++;
    }
}
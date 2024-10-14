/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#include "Rotation.h"

Rotation::Rotation()
{
    raw_value = 0.0f;
}

Rotation::Rotation(float value)
{
    raw_value = PIBound(value);
}

float Rotation::GetRawValue()
{
    return raw_value;
}
Rotation Rotation::operator+(const Rotation &r) const
{
    return Rotation(PIBound(raw_value + r.raw_value));
}

Rotation Rotation::operator+(const float &r) const
{
    return Rotation(PIBound(raw_value + r));
}

Rotation Rotation::operator-(const Rotation &r) const
{
    return Rotation(PIBound(raw_value - r.raw_value));
}

Rotation Rotation::operator-(const float &r) const
{
    return Rotation(PIBound(raw_value - r));
}

Rotation &Rotation::operator=(const Rotation &r)
{
    raw_value = r.raw_value;
    return *this;
}

Rotation &Rotation::operator=(const float &r)
{
    raw_value = PIBound(r);
    return *this;
}

float Rotation::PIBound(float value)
{
    if (value > 0)
    {
        // calculate the division
        float division_result = value / 6.283185307f;
        // calculate how many times the value was fully divided by the base
        int complete_multiples = (int)(division_result);
        // return the decimal modulo
        return value - 6.283185307f * (float)complete_multiples;
    }
    else
    {
        // calculate the division
        float division_result = value / 6.283185307f;
        // calculate how many times the value was fully divided by the base
        int complete_multiples = 1 + (int)(division_result);
        // return the decimal modulo
        return value - 6.283185307f * (float)complete_multiples;
    }
}

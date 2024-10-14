/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#pragma once

/**
 * rotation class is a float that wraps around after 2pi
 */
class Rotation
{
private:
    // the raw rotation value
    float raw_value = 0.f;

public:
    Rotation();
    Rotation(float value);
    float GetRawValue();

    Rotation operator+(const Rotation &r) const;
    Rotation operator+(const float &r) const;
    Rotation operator-(const Rotation &r) const;
    Rotation operator-(const float &r) const;
    Rotation &operator=(const Rotation &r);
    Rotation &operator=(const float &r);

private:
    /**
     * ensures that value is between 0 and 2pi
     * @param value: the value to wrap
     * @return: the wraped value
     */
    static float PIBound(float value);
};

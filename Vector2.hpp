#ifndef VECTOR2_HPP
#define VECTOR2_HPP
#include <iostream>
#include <cmath>

template<typename T>
class Vector2
{
public:
    //Set the default value of a vector to 0
    Vector2() : x(0),y(0) {}
    //Initialise vector with given values
    Vector2(T x, T y) : x(x), y(y) {};
    //copy constructor for the vector
    Vector2(const Vector2& other) : x(other.x), y(other.y) {}
    //vector destructor
    ~Vector2() {}

    //X and Y values with a template type
    T x,y;

    //Get the magnitude (Length) of a vector
    float Magnitude()
    {
        return std::sqrt((x * x) + (y * y));
    }
    //Normalise the vector using its own magnitude
    void Normalise()
    {
        x/Magnitude();
        y/Magnitude();
    }

    //Add a vector to the current vector
    Vector2& operator+=(const Vector2& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    //subtract a vector to the current vector
    Vector2& operator-=(const Vector2& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    //Set a vector value to the current vector
    Vector2& operator=(Vector2 rhs)
    {
        std::swap(x, rhs.x);
        std::swap(y, rhs.y);
        return *this;
    }

    //output the vector to OS stream
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec)
    {
        return os << "(x=" << vec.x << " y=" << vec.y << ")";
    }

};

//Add two vectors together
template<typename T>
inline Vector2<T> operator+(Vector2<T> lhs, const Vector2<T>& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}
//Subtract two vectors together
template<typename T>
inline Vector2<T> operator-(Vector2<T> lhs, const Vector2<T>& rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

//Multiply a vector by a scalar value
template<typename T>
inline Vector2<T> operator*(Vector2<T> lhs, T rhs)
{
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
}

//Divide a vector by a scalar value
template<typename T>
inline Vector2<T> operator/(Vector2<T> lhs, T rhs)
{
    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;
}

//Check if two vectors are equal
template<typename T>
inline bool operator==(const Vector2<T>& lhs,const Vector2<T>& rhs)
{
    if(lhs.x == rhs.x && lhs.y == rhs.y)
        return true;
    return false;
}
//Check if two vectors are NOT equal
template<typename T>
inline bool operator!=(const Vector2<T>& lhs,const Vector2<T>& rhs)
{
    if(lhs.x != rhs.x && lhs.y != rhs.y)
        return true;
    return false;
}
//Get the inverted value of a vector
template<typename T>
inline Vector2<T> operator-(Vector2<T>& rhs)
{
    return {-rhs.x,-rhs.y};
}

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;

#endif // VECTOR2_HPP

#ifndef VECTOR_H_
#define VECTOR_H_

template <typename T>
class vector3
{
public:
	vector3();
	vector3(T X, T Y, T Z);

	template <typename U>
	explicit vector3(const vector3<U> &vector);

	T x;
	T y;
	T z;
};

template <typename T>
vector3<T> operator -(const vector3<T> &left);

template <typename T>
vector3<T> &operator +=(vector3<T> &left, const vector3<T> &right);

template <typename T>
vector3<T> &operator -=(vector3<T> &left, const vector3<T> &right);

template <typename T>
vector3<T> operator +(const vector3<T> &left, const vector3<T> &right);

template <typename T>
vector3<T> operator -(const vector3<T> &left, const vector3<T> &right);

template <typename T>
vector3<T> operator *(const vector3<T> &left, T right);

template <typename T>
vector3<T> operator *(T left, const vector3<T> &right);

template <typename T>
vector3<T> &operator *=(vector3<T> &left, T right);

template <typename T>
vector3<T> operator /(const vector3<T> &left, T right);

template <typename T>
vector3<T> &operator /=(vector3<T> &left, T right);

template <typename T>
bool operator ==(const vector3<T> &left, const vector3<T> &right);

template <typename T>
bool operator !=(const vector3<T> &left, const vector3<T> &right);

template <typename T>
class vector2
{
public:
	vector2();
	vector2(T X, T Y);

	template <typename U>
	explicit vector2(const vector2<U> &vector);

	T x;
	T y;
};

template <typename T>
vector2<T> operator -(const vector2<T> &right);

template <typename T>
vector2<T> &operator +=(vector2<T> &left, const vector2<T> &right);

template <typename T>
vector2<T> &operator -=(vector2<T> &left, const vector2<T> &right);

template <typename T>
vector2<T> operator +(const vector2<T> &left, const vector2<T> &right);

template <typename T>
vector2<T> operator -(const vector2<T> &left, const vector2<T> &right);

template <typename T>
vector2<T> operator *(const vector2<T> &left, T right);

template <typename T>
vector2<T> operator *(T left, const vector2<T> &right);

template <typename T>
vector2<T> &operator *=(vector2<T> &left, T right);

template <typename T>
vector2<T> operator /(const vector2<T> &left, T right);

template <typename T>
vector2<T> &operator /=(vector2<T> &left, T right);

template <typename T>
bool operator ==(const vector2<T> &left, const vector2<T> &right);

template <typename T>
bool operator !=(const vector2<T> &left, const vector2<T> &right);

#include "Vector.inl"

typedef vector3<int>	vector3i;
typedef vector3<float>	vector3f;
typedef vector2<int>          vector2i;
typedef vector2<unsigned int> vector2u;
typedef vector2<float>        vector2f;

#endif /* !VECTOR_H_ */

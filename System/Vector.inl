template <typename T>
inline vector3<T>::vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}


template <typename T>
inline vector3<T>::vector3(T X, T Y, T Z)
{
	this->x = X;
	this->y = Y;
	this->z = Z;
}


template <typename T>
template <typename U>
inline vector3<T>::vector3(const vector3<U> &vector)
{
	this->x = static_cast<T>(vector.x);
	this->y = static_cast<T>(vector.y);
	this->z = static_cast<T>(vector.z);
}


template <typename T>
inline vector3<T> operator -(const vector3<T> &left)
{
	return (vector3<T>(-left.x, -left.y, -left.z));
}


template <typename T>
inline vector3<T> &operator +=(vector3<T> &left, const vector3<T> &right)
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;

	return (left);
}


template <typename T>
inline vector3<T> &operator -=(vector3<T> &left, const vector3<T> &right)
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;

	return (left);
}


template <typename T>
inline vector3<T> operator +(const vector3<T> &left, const vector3<T> &right)
{
	return (vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z));
}


template <typename T>
inline vector3<T> operator -(const vector3<T> &left, const vector3<T> &right)
{
	return (vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z));
}


template <typename T>
inline vector3<T> operator *(const vector3<T> &left, T right)
{
	return (vector3<T>(left.x * right, left.y * right, left.z * right));
}


template <typename T>
inline vector3<T> operator *(T left, const vector3<T> &right)
{
	return (vector3<T>(right.x * left, right.y * left, right.z * left));
}


template <typename T>
inline vector3<T> &operator *=(vector3<T> &left, T right)
{
	left.x *= right;
	left.y *= right;
	left.z *= right;

	return (left);
}


template <typename T>
inline vector3<T> operator /(const vector3<T> &left, T right)
{
	return (vector3<T>(left.x / right, left.y / right, left.z / right));
}


template <typename T>
inline vector3<T> &operator /=(vector3<T> &left, T right)
{
	left.x /= right;
	left.y /= right;
	left.z /= right;

	return (left);
}


template <typename T>
inline bool operator ==(const vector3<T> &left, const vector3<T> &right)
{
	return ((left.x == right.x) && (left.y == right.y) && (left.z == right.z));
}


template <typename T>
inline bool operator !=(const vector3<T> &left, const vector3<T> &right)
{
	return ((left.x != right.x) || (left.y != right.y) || (left.z != right.z));
}

template <typename T>
inline vector2<T>::vector2()
{
	this->x = 0;
	this->y = 0;
}

template <typename T>
inline vector2<T>::vector2(T X, T Y)
{
	this->x = X;
	this->y = Y;
}

template <typename T>
template <typename U>
inline vector2<T>::vector2(const vector2<U> &vector) :
x(static_cast<T>(vector.x)),
y(static_cast<T>(vector.y))
{
	this->x = static_cast<T>(vector.x);
	this->Y = static_cast<T>(vector.y);
}

template <typename T>
inline vector2<T> operator -(const vector2<T> &right)
{
	return (vector2<T>(-right.x, -right.y));
}

template <typename T>
inline vector2<T> &operator +=(vector2<T> &left, const vector2<T> &right)
{
	left.x += right.x;
	left.y += right.y;

	return (left);
}

template <typename T>
inline vector2<T> &operator -=(vector2<T> &left, const vector2<T> &right)
{
	left.x -= right.x;
	left.y -= right.y;

	return (left);
}

template <typename T>
inline vector2<T> operator +(const vector2<T> &left, const vector2<T> &right)
{
	return (vector2<T>(left.x + right.x, left.y + right.y));
}

template <typename T>
inline vector2<T> operator -(const vector2<T> &left, const vector2<T> &right)
{
	return (vector2<T>(left.x - right.x, left.y - right.y));
}

template <typename T>
inline vector2<T> operator *(const vector2<T> &left, T right)
{
	return (vector2<T>(left.x * right, left.y * right));
}

template <typename T>
inline vector2<T> operator *(T left, const vector2<T> &right)
{
	return (vector2<T>(right.x * left, right.y * left));
}

template <typename T>
inline vector2<T> &operator *=(vector2<T> &left, T right)
{
	left.x *= right;
	left.y *= right;

	return (left);
}

template <typename T>
inline vector2<T> operator /(const vector2<T> &left, T right)
{
	return (vector2<T>(left.x / right, left.y / right));
}

template <typename T>
inline vector2<T> &operator /=(vector2<T> &left, T right)
{
	left.x /= right;
	left.y /= right;

	return (left);
}

template <typename T>
inline bool operator ==(const vector2<T> &left, const vector2<T> &right)
{
	return ((left.x == right.x) && (left.y == right.y));
}

template <typename T>
inline bool operator !=(const vector2<T> &left, const vector2<T> &right)
{
	return ((left.x != right.x) || (left.y != right.y));
}
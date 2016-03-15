#ifndef Vector2D_H
#define Vector2D_H
#include <math.h>

namespace gameEngine {

	struct Vector2D {
	public:
		Vector2D();
		Vector2D(float xx, float yy);
		float x, y;

		inline Vector2D &operator /=(const float Scalar) { x /= Scalar; y /= Scalar;		return *this; }

		inline Vector2D &operator *=(const float Scalar) { x *= Scalar; y *= Scalar;		return *this; }

		inline Vector2D &operator +=(const Vector2D &Other) { x += Other.x;	y += Other.y;	return *this; }

		inline Vector2D &operator -=(const Vector2D &Other) { x -= Other.x;	y -= Other.y;	return *this; }

		inline float operator ^ (const Vector2D &V)	const { return (x * V.y) - (y * V.x); } // cross product

		inline float operator * (const Vector2D &V)	const { return (x*V.x) + (y*V.y); } // dot product

		inline Vector2D operator * (float  s)			const { return Vector2D(x*s, y*s); }

		inline Vector2D operator / (float  s)			const { return Vector2D(x / s, y / s); }

		inline Vector2D operator + (const Vector2D &V)	const { return Vector2D(x + V.x, y + V.y); }

		inline Vector2D operator - (const Vector2D &V)	const { return Vector2D(x - V.x, y - V.y); }

		friend Vector2D operator * (float k, const Vector2D& V) { return Vector2D(V.x*k, V.y*k); }


		inline Vector2D operator -(void) const { return Vector2D(-x, -y); }

		inline float Length(void) const { return (float)sqrt(x*x + y*y); }

		float Normalise(void)
		{
			float fLength = Length();

			if (fLength == 0.0f)
				return 0.0f;

			(*this) *= (1.0f / fLength);

			return fLength;
		}

		Vector2D Direction(void) const
		{
			Vector2D Temp(*this);

			Temp.Normalise();

			return Temp;
		}

		float Angle(const Vector2D& xE)
		{
			float dot = (*this) * xE;
			float cross = (*this) ^ xE;

			// angle between segments
			float angle = (float)atan2(cross, dot);

			return angle;
		}

		Vector2D& Rotate(float angle)
		{
			float tx = x;
			x = x * cos(angle) - y * sin(angle);
			y = tx * sin(angle) + y * cos(angle);

			return *this;
		}

		Vector2D& Rotate(const Vector2D& xCentre, float fAngle)
		{
			Vector2D D = *this - xCentre;
			D.Rotate(fAngle);

			*this = xCentre + D;

			return *this;
		}

		void Clamp(const Vector2D& min, const Vector2D& max)
		{
			x = (x < min.x) ? min.x : (x > max.x) ? max.x : x;
			y = (y < min.y) ? min.y : (y > max.y) ? max.y : y;
		}
	};
}

#endif
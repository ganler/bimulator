#ifndef H_RAY_TRACING_TOOLS_AMP
#define H_RAY_TRACING_TOOLS_AMP
#include <amp_graphics.h>
#include <amp_math.h>

using namespace concurrency;
using namespace concurrency::fast_math;
using namespace concurrency::graphics;

inline float_3 cross(const float_3& A, const float_3& B) restrict(amp) {
	return float_3(A.y * B.z - A.z * B.y,
		A.z * B.x - A.x * B.z,
		A.x * B.y - A.y * B.x);
}

inline float dot(const float_3& A, const float_3& B) restrict(amp) {
	return A.x * B.x + A.y * B.y + A.z * B.z;
}

inline float length(const float_3& A) restrict(amp) {
	return sqrtf(A.x * A.x + A.y * A.y + A.z * A.z);
}

inline float_3 normalize(const float_3& A) restrict(amp) {
	return A / length(A);
}


inline float_3 cross(const float_3& A, const float_3& B) {
	return float_3(A.y * B.z - A.z * B.y,
		A.z * B.x - A.x * B.z,
		A.x * B.y - A.y * B.x);
}

inline float dot(const float_3& A, const float_3& B) {
	return A.x * B.x + A.y * B.y + A.z * B.z;
}

inline float length(const float_3& A) {
	return sqrtf(A.x * A.x + A.y * A.y + A.z * A.z);
}

inline float_3 normalize(const float_3& A) {
	return A / length(A);
}


#endif
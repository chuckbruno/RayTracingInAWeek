#include "vec3.h"

std::istream& operator>>(std::istream &is, vec3 &t) {
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

std::ostream& operator<<(std::ostream &os, const vec3 &t) {
	os << t.e[0] << " "  << t.e[1] << " " << t.e[2];
	return os;
}

void vec3::make_unit_vector() {
	float k = 1.0f / vec3::length();
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
}

vec3& vec3::operator+=(const vec3 &v) {
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

#pragma once
#ifndef _RANDOM_H
#define _RANDOM_H

#include <cstdlib>

inline double random_double() {
	return rand() / (RAND_MAX + 1.0);
}
#endif // !_RANDOM_H

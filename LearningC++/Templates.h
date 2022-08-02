#ifndef TEMPLATES_H
#define TEMPLATES_H

template <typename T, typename U>
auto max(const T x, const U y)
{
	return (x > y) ? x : y;
}

#endif
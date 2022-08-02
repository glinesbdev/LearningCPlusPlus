#pragma once

template <typename T>
struct Triad
{
	T first{};
	T second{};
	T third{};
};

// Not required in C++20
template <typename T>
Triad(T, T, T)->Triad<T>;

template <typename T>
void print(const Triad<T>& t)
{
	std::cout << '[' << t.first << ", " << t.second << ", " << t.third << ']';
}

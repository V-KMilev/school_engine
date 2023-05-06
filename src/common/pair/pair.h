#pragma once

template<typename T1, typename T2>

class Pair {
	public:
		T1 first;
		T2 second;

		Pair() : first(), second() {}

		Pair(const T1& f, const T2& s) : first(f), second(s) {}

		bool operator == (const Pair& other) const {
			return first == other.first && second == other.second;
		}

		bool operator != (const Pair& other) const {
			return !(*this == other);
		}

		bool operator < (const Pair& other) const {
			return first < other.first || (first == other.first && second < other.second);
		}

		bool operator > (const Pair& other) const {
			return other < *this;
		}

		bool operator <= (const Pair& other) const {
			return !(other < *this);
		}

		bool operator>=(const Pair& other) const {
			return !(*this < other);
		}
};

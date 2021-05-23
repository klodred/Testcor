#pragma once
#include <chrono>


class Timer {
private:

	std::chrono::system_clock::time_point start;
	std::chrono::milliseconds duration;
	int dur_in_int;

public:

	const int INF = INT_MAX;
	Timer(int dur) : duration(dur) { dur_in_int = dur; }

	void on() {

		start = std::chrono::system_clock::now();

	}

	void set_time(int t) {

		dur_in_int = t;
		auto fs = std::chrono::milliseconds(t);
		duration = fs;

	}

	bool is_ready() {

		auto cur_time = std::chrono::system_clock::now();
		auto elapse = std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - start);
		return dur_in_int != INF ? elapse > duration : false;

	}

};

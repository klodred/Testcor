#pragma once
#include <chrono>


class Timer {
private:

	std::chrono::system_clock::time_point start;
	std::chrono::milliseconds duration;

public:

	Timer(int dur) : duration(dur) { }

	void on() {

		start = std::chrono::system_clock::now();

	}

	bool is_ready() {

		auto cur_time = std::chrono::system_clock::now();
		auto elapse = std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - start);
		return elapse > duration;

	}

};

#include "interval.h"

const Interval& Interval::empty() {
	static const Interval instance;
	return instance;
}

const Interval& Interval::universe() {
	static const Interval instance(-INF, INF);
	return instance;
}

#include "PID.h"
#include <cmath>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;

	p_error = 0;
	i_error = 0;
	d_error = 0;
}

void PID::UpdateError(double cte) {
	d_error = 0.95 * (cte - p_error - d_error) + (d_error);

	p_error = cte;
	i_error += cte;
	
	if ( std::abs(Ki * i_error) > 10 * M_PI / 180 )
		i_error = std::copysign(1.0, i_error) * ( 10 * M_PI / 180 ) / Ki;
}

double PID::TotalError() {
	return -Kp * p_error - Ki * i_error - Kd * d_error;
}


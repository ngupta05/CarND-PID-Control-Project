#include "PID.h"

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
	this->i_error = this->d_error = this->t_error = 0;
	this->n = 0;
}

void PID::UpdateError(double cte) {
	d_error = cte - p_error;
	i_error += cte;
	p_error = cte;
	t_error = cte * cte;
	n += 1;
}

double PID::TotalError() {
	return t_error / n;
}


#ifndef TWIDDLE_H
#define TWIDDLE_H

class Twiddle {
private:
	double d[3];
	double k[3];
	double best_error;
	int idx;
	int lc;
public:
	Twiddle() {
		idx = 0;
		k[0] = k[1] = k[2] = 0;
		d[0] = d[1] = d[2] = 1;
		lc = 1;
		k[idx] += d[idx];
		best_error = 1000000;
	}

	void updateError(double error) {
		if (error < best_error) {
				best_error = error;
				d[idx] *= 1.1;
				idx = (idx + 1) % 3;
				k[idx] += d[idx];
				lc = 1;
		} else {
			if (lc > 0) {
				k[idx] -= 2 * d[idx];
				lc = -1;
			} else {
				k[idx] += d[idx];
				d[idx] *= 0.9;
				idx = (idx + 1) % 3;
				k[idx] += d[idx];
				lc = 1;
			}
		}
	}

	double getKp() { return k[0]; }
	double getKi() { return k[1]; }
	double getKd() { return k[2]; }
};

#endif

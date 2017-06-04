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
		// 0.142113,0.331,0
		k[0] = k[1] = k[2] = 0;
		k[0] = 0.142113;
		k[1] = 0.331;
		k[2] = 0.0;
		// 0.0163453,0.0199776,0.0109419
		d[0] = d[1] = d[2] = 0.1;
		d[0] = 0.0163453;
		d[1] = 0.0199776;
		d[2] = 0.0109419;
		lc = -1;
		k[idx] += d[idx];
		best_error = 1000000;
	}

	void updateError(double error) {
		std::cout << "New error: " << error << std::endl;
		if ((d[0] + d[1] + d[2]) < 0.001)
			return;
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
		std::cout << "New dp params: " << d[0] << "," << d[1] << ","
				<< d[2] << std::endl;
	}

	double getKp() { return k[0]; }
	double getKi() { return k[2]; }
	double getKd() { return k[1]; }
};

#endif

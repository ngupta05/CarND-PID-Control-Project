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
		// 0.101121,0.336078,0
		// Resetting Params: 0.106499,0.341613,0.00107753
		k[0] = k[1] = k[2] = 0;
		k[0] = 0.106499;
		k[1] = 0.341563;
		k[2] = 0.00107753;
		// 0.0163453,0.0199776,0.0109419
		// 0.00834428,0.00507804,0.00278128
		// New dp params: 0.0106686,0.00395114,0.00107753

		d[0] = d[1] = d[2] = 0.1;
		d[0] = 0.0106686;
		d[1] = 0.00395114;
		d[2] = 0.00118528;
		lc = 1;
		// TODO: This line needs to be uncommented in training mode.
		// k[idx] += d[idx];
		best_error = 3.6864E-7;
	}

	void updateError(double error) {
		std::cout << "New error: " << error << std::endl;
		std::cout << "Previous best: " << best_error << std::endl;
		if ((d[0] + d[1] + d[2]) < 0.001)
			return;
		if (error < best_error) {
			std::cout << "Case 1" << std::endl;
			best_error = error;
			d[idx] *= 1.1;
			idx = (idx + 1) % 3;
			k[idx] += d[idx];
			lc = 1;
		} else {
			if (lc > 0) {
				std::cout << "Case 2" << std::endl;
				k[idx] -= 2 * d[idx];
				lc = -1;
			} else {
				std::cout << "Case 3" << std::endl;
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

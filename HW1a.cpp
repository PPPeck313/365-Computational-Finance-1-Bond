//Preston Peck
//CS 365
//September 8, 2017
//HW1

#include <iostream>
#include <cmath>
using namespace std;

double future_value(double F0, double t0, double t1, double r);
int df_and_r(double F0, double F1, double t0, double t1, double df, double r);
double price_from_yield(double F, double c, double y, int n, double B);
int yield_from_price(double F, double c, int n, double B_market, double tol, int max_iter, double y);

int main() {
    double F0, F1, t0, t1, r, df = 0.0;
    cout << "ENTER VALUES" <<endl;
    cout << "Initial Value: $";
    cin >> F0;
    cout << "Initial Time: ";
    cin >> t0;
    cout << "Final Time: ";
    cin >> t1;
    cout << "Interest Rate: ";
    cin >> r;
    cout<< endl;

    F1 = future_value(F0, t0, t1, r);
    cout << endl;
    df_and_r(F0, F1, t0, t1, df, r);
    cout << endl;

    double F, c, y, B, B_market = 0.0;
    int n = 0;
    cout << "Face Value: $";
    cin >> F;
    cout << "Coupon Payment: $";
    cin >> c;
    cout << "Yield Rate: ";
    cin >> y; 
    cout << "Payments: ";
    cin >> n;
    cout << endl;

    B_market = price_from_yield(F, c, y, n, B);
    cout << endl;

    double tol = 0.0;
    int max_iter = 0;
    cout << "Tolerance: ";
    cin >> tol;
    cout << "Max Iteration: ";
    cin >> max_iter;
    cout << endl;

    yield_from_price(F, c, n, B_market, tol, max_iter, y);
}

double future_value(double F0, double t0, double t1, double r) {
	double r_decimal = 0.01 * r;
	double F1 = F0 * exp(r_decimal * (t1 - t0));
	cout << "Final Value: $" << F1 << endl;
	return F1;
}

int df_and_r(double F0, double F1, double t0, double t1, double df, double r) {
	if (t1 - t0 == 0.0) {
		df = 0;
		r = 0;
		return -1;
	}
	
	if ((F0 <= 0.0) || (F1 <= 0.0)) {
		df = 0;
		r = 0;
		return -2;
	}
	
	double t = t1 - t0;
	r = log(F1 / F0) / t;
	df = F0/F1;
	
	cout << "Discount Factor: " << df << endl;
	cout << "Interest Rate: " << r * 100 << "%" << endl;
	
	return 0;
}

double price_from_yield(double F, double c, double y, int n, double B) {
	double y_decimal = .01 * y;
    double B = 0.0;
	
	for (int i = 1; i <= n; i++) {
		if (i < n) {
			B += (.5 * c) / pow(1 + (.5 * y_decimal), i);
		}
		
		else {
			B += (F + (.5 * c)) / pow(1 + (.5 * y_decimal), n);
		}
	}
	
	cout << "Maturity Value: $" << B << endl;
	return B;
}

int yield_from_price(double F, double c, int n, double B_market, double tol, int max_iter, double y) {	
    double y_low = 0.0;
    double By_low = 0.0;
    cout << "LOW ";
    By_low = price_from_yield(F, c, y_low, n, By_low);
	
	if (abs(By_low - B_market) <= tol) {
		y = y_low;
		cout << endl << "Yield Rate: " << y << "%" << endl << endl;
		return 0;
	}
	
	if (By_low < B_market) {
		y = 0;
		cout << endl << "Yield Rate: " << y << "%" << endl << endl;
		return 1;
	}
	
    double y_high = 100.0;
    double By_high = 0.0;
    cout << "HIGH ";
	By_high = price_from_yield(F, c, y_high, n, By_high);
	
	if (abs(By_high - B_market) <= tol) {
		y = y_high;
		cout << endl << "Yield Rate: " << y << "%" << endl;
		return 0;
	}
	
	if (By_high > B_market) {
		y = 0;
		cout << endl << "Yield Rate: " << y << "%" << endl << endl;
		return 1;
    }
	
	for (int i = 0; i < max_iter; ++i) {
        double B = 0.0;
        
		y = (y_low + y_high) / 2.0;
        B = price_from_yield(F, c, y, n, B);
		
		if (abs(B - B_market) <= tol || y_high - y_low <= tol) {
			cout << endl << "Yield Rate: " << y << "%" << endl << endl;
			return 0;
		}
		
		else if (B > B_market) {
            cout << "New LOWER Limit: " << y << '%' << endl;
			y_low = y;
		}
		
		else {
            cout << "New UPPER Limit: " << y << '%' << endl;
			y_high = y;
		}
	}
	
    y = 0;
	cout << endl << "Yield Rate: " << y << "%" << endl << endl;
	return 1;
}

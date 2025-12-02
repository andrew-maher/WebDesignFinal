#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;
double calculateCompoundInterest(double principal, double rate,
                                 int timesCompounded, int years) {
  return principal * pow((1 + rate / timesCompounded), timesCompounded * years);
}

int main() {
  double principal;
  int timesCompounded;

  cout << "Enter the principal amount: ";
  cin >> principal;
  cout << "Enter the number of times the interest is compounded per year: ";
  cin >> timesCompounded;

  double interestRates[] = {0.03, 0.05, 0.07, 0.1};
  int yearsArray[] = {1, 5, 10, 20};

  cout << "\nPrincipal: $" << principal << endl;
  cout << "Times Compounded: " << timesCompounded << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  cout << setw(12) << "Years/Rate";
  for (double rate : interestRates) {
    cout << setw(12) << rate * 100 << "%";
  }
  cout << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;

  for (int years : yearsArray) {
    cout << setw(12) << years;
    for (double rate : interestRates) {
      double amount =
          calculateCompoundInterest(principal, rate, timesCompounded, years);
      cout << setw(14) << fixed << setprecision(2) << amount;
    }
    cout << endl;
  }
}

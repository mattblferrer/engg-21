/**
 * main.cpp
 *
 * FERRER, Matt Brycen L.
 * ENGG 21 - B
 * Project 1 Basic Statistical Measures and the
 * Linear and Gaussian Random Variables
*/

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <random>

using namespace std;

/**
 * computes the minimum, maximum, range, average, population
 * variance, and population standard deviation of the
 * data set
 */
void computeStats(double * data, int N, double minValue,
                  double maxValue, double range, double aveValue,
                  double popVariance, double popStdDev)
{
  // calculate minimum value
  minValue = data[0];
  for (int i=0; i<N; i++)
  {
    if (data[i] < minValue)
    {
      minValue = data[i];
    }
  }

  // calculate maximum value
  maxValue = data[0];
  for (int i=0; i<N; i++)
  {
    if (data[i] > maxValue)
    {
      maxValue = data[i];
    }
  }

  // calculate range
  range = maxValue - minValue;

  // calculate average value
  double sum = 0;
  for (int i=0; i<N; i++)
  {
    sum += data[i];
  }
  aveValue = sum / N;

  // calculate population variance
  double sum_differences = 0;  // sum of all (x_i - mu)^2
  for (int i=0; i<N; i++)
  {
    sum_differences += pow(data[i] - aveValue, 2);
  }
  popVariance = sum_differences / N;

  // calculate population standard deviation
  popStdDev = pow(popVariance, 0.5);  // take sqrt of variance

  // print calculated values to console
  cout << "Minimum value: " << minValue << endl;
  cout << "Maximum value: " << maxValue << endl;
  cout << "Range: " << range << endl;
  cout << "Average Value: " << aveValue << endl;
  cout << "Population Variance: " << popVariance << endl;
  cout << "Population Standard Deviation: " << popStdDev <<
    "\n" << endl;
}

void scale_and_translate(double * source, double * dest, int n,
                         double scaling, double translate)
{
  for (int i=0; i<n; i++)
  {
    dest[i] = (source[i] * scaling) + translate;
  }
}

void uniform_to_gaussian(double * xin, double * b,
                         double * yout, int n, double sigma)
{
  double pi = 4.0*atan(1.0);
  double r;

  // Gaussian random variable algorithm shown in Figure A.6
  for (int i=0; i<n; i++)
  {
    b[i] = 2.0*pi*b[i];
    r = pow(2.0*pow(sigma, 2) * log(1.0/(1.0-xin[i])), 0.5);
    yout[i] = r*cos(b[i]);
  }
}


int main()
{
  int N = 5000;  // size of each data set
  int prec = 15;  // decimal digits of random numbers
  double minValue;
  double maxValue;
  double range;
  double aveValue;
  double popVariance;
  double popStdDev;

  // set seed for random number generator
  unsigned int seed = time(0);
  mt19937_64 e(seed);  // initialize 64-bit Mersenne twister
  uniform_real_distribution<double> randreal(0,1);

  // Set A
  ofstream f;
  cout << setprecision(prec);
  f.open("set_A.csv");
  double * setA = new double[N];

  for (int i=0; i<N; i++)
  {
    setA[i] = randreal(e);
    f << setprecision(prec) << setA[i] << endl; // append to csv file
  }

  cout << "Set A" << endl;
  computeStats(setA, N, minValue, maxValue, range, aveValue,
    popVariance, popStdDev);

  f.close();

  // Set B
  f.open("set_B.csv");
  double * setB = new double[N];

  for (int i=0; i<N; i++)
  {
    setB[i] = randreal(e);
    f << setprecision(prec) << setB[i] << endl; // append to csv file
  }

  cout << "Set B" << endl;
  computeStats(setB, N, minValue, maxValue, range, aveValue,
    popVariance, popStdDev);

  f.close();

  // Set C
  double * setC = new double[N];
  scale_and_translate(setA, setC, N, 10, -5);

  cout << "Set C" << endl;
  computeStats(setC, N, minValue, maxValue, range, aveValue,
    popVariance, popStdDev);

  // Set D
  double * setD = new double[N];
  scale_and_translate(setB, setD, N, 50, 50);

  cout << "Set D" << endl;
  computeStats(setD, N, minValue, maxValue, range, aveValue,
    popVariance, popStdDev);

  // Set E
  double * setE = new double[N];
  uniform_to_gaussian(setA, setB, setE, N, 1);

  cout << "Set E" << endl;
  computeStats(setE, N, minValue, maxValue, range, aveValue,
    popVariance, popStdDev);

  // Set F
  double * setF = new double[N];
  scale_and_translate(setE, setF, N, 5, 75);

  cout << "Set F" << endl;
  computeStats(setF, N, minValue, maxValue, range, aveValue,
    popVariance, popStdDev);

  return 0;
}

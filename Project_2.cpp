/**
 * main.cpp
 *
 * FERRER, Matt Brycen L.
 * ENGG 21 - B
 * Data Clusters Simulation and Classification Game
*/

#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>

using namespace std;

/**
 * Scales and translates a variable
*/
double scale_and_translate_var(double source, double scaling, 
                               double translate)
{
  return (source * scaling) + translate;
}

/**
 * Converts two uniform random variables to a 
 * Gaussian random distributed variable and returns it
*/
double uniform_to_gaussian_var(double xin, double b, double sigma)
{
  double pi = 4.0*atan(1.0);
  double r;

  // Gaussian random variable algorithm shown in Figure A.6
  b = 2.0*pi*b;
  r = pow(2.0*pow(sigma, 2) * log(1.0/(1.0-xin)), 0.5);
  return r*cos(b);
}

/**
 * Generates a Gaussian random variable with
 * given mean, and sigma, and returns it
*/
double generate_gaussian(double mean, double sigma, mt19937_64& e)
{
  // generate random numbers according to uniform distribution
  uniform_real_distribution<double> randreal(0,1);
  double uniform_1 = randreal(e);
  double uniform_2 = randreal(e);

  // scale and translate resulting Gaussian and return
  double gaussian;
  gaussian = uniform_to_gaussian_var(uniform_1, uniform_2, 1);
  return scale_and_translate_var(gaussian, sigma, mean);
}

/**
 * Validates the program mode (has to be either 0 or 1)
*/
int validate_program_mode()
{
  // take input from user
  string input;
  double program_mode;
  getline(cin, input);

  // validate input mode
  while(true)
  {
    stringstream stream(input);

    // input is not number
    if(!(stream >> program_mode))
    {
      cin.clear();
      cout << "Invalid input. Please enter either 1 or 2. ";
      getline(cin, input);
    }

    // input is number, but not 1 or 2
    else if (program_mode < 1 || program_mode > 2 ||
      (int)program_mode != program_mode)
    {
      cin.clear();
      cout << "Number entered is invalid. Please enter either " << 
        "1 or 2. ";
      getline(cin, input);
    }

    else {
      // check if there are characters past the number
      char test;
      if(stream >> test)
      {
        cin.clear();
        cout << "Number entered is invalid. Please do not enter " << 
          "characters after the number. ";
        getline(cin, input);
      }

      // valid input
      else
      {
        break;
      }
    }
  }

  return program_mode;
}

/**
 * Validates the number of occurrences, N (has to be integer > 0)
*/
int validate_occurrences()
{
  // take input from user
  string N_input;
  double N_double;
  getline(cin, N_input);

  // validate input N
  while(true)
  {
    stringstream stream(N_input);

    // input is not double
    if(!(stream >> N_double))
    {
      cin.clear();
      cout << "Invalid input. Please enter an integer > 0.";
      getline(cin, N_input);
    }

    // input is double with decimal digits or is less than 1
    else if(N_double < 1 || (int)N_double != N_double)
    {
      cin.clear();
      cout << "Invalid input. Please enter an integer > 0. ";
      getline(cin, N_input);
    }

    else
    {
      // check if there are characters past the number
      char test;
      if(stream >> test)
      {
        cin.clear();
        cout << "Number entered is invalid. Please do not enter " << 
          "characters after the number. ";
        getline(cin, N_input);
      }

      // valid input
      else
      {
        break;
      }
    }
  }
  return (int)N_double;  // cast N to integer
}

/**
 * Validates the mean (has to be floating-point number)
*/
double validate_mean()
{
  // take input from user
  string input;
  double mean;
  getline(cin, input);

  // validate input N
  while(true)
  {
    stringstream stream(input);

    // input is not double
    if(!(stream >> mean))
    {
      cin.clear();
      cout << "Invalid input. Please enter a number.";
      getline(cin, input);
    }

    // input is double
    else
    {
      // check if there are characters past the number
      char test;
      if(stream >> test)
      {
        cin.clear();
        cout << "Number entered is invalid. Please do not enter " << 
          "characters after the number. ";
        getline(cin, input);
      }

      // valid input
      else
      {
        break;
      }
    }
  }
  return mean;  // cast N to integer
}

/**
 * Validates the relative frequency and sigma (standard deviation)
 * (Has to be positive floating-point number)
*/
double validate_freq_sigma()
{
  // take input from user
  string input;
  double freq_sigma;
  getline(cin, input);

  // validate input N
  while(true)
  {
    stringstream stream(input);

    // input is not double
    if(!(stream >> freq_sigma))
    {
      cin.clear();
      cout << "Invalid input. Please enter a number > 0.";
      getline(cin, input);
    }

    // input is double, but not positive
    else if(freq_sigma < 0)
    {
      cin.clear();
      cout << "Invalid input. Please enter a number > 0. ";
      getline(cin, input);
    }

    else
    {
      // check if there are characters past the number
      char test;
      if(stream >> test)
      {
        cin.clear();
        cout << "Number entered is invalid. Please do not enter " << 
          "characters after the number. ";
        getline(cin, input);
      }

      // valid input
      else
      {
        break;
      }
    }
  }
  return freq_sigma;
}

/**
 * Validates data type entered in game mode (Has to be a
 * character, either A, B, C - data types, or X - exit)
*/
char validate_data_type()
{
  // take input from user
  string input;
  char data_type;
  getline(cin, input);

  while(true)
  {
    stringstream stream(input);

    // check if valid input
    if(stream >> data_type)
    {
      // check if there are multiple characters in input
      char test;

      if(!(stream >> test))
      {
        data_type = toupper(data_type);
        if((data_type == 'A') || (data_type == 'B') || 
          (data_type == 'C') || (data_type == 'X'))
        {
          break;
        }
      }

      else {
        cin.clear();
        cout << "Invalid data type entered! Please do not enter " <<
          "multiple characters. ";
        getline(cin, input);
      }
    }
    
    // invalid input
    cin.clear();
    cout << "Invalid data type entered! Please enter (A, B, C, X)";
    getline(cin, input);
  }

  return data_type;
}

void data_generation_mode(int N, double * freqs, double * means_1,
                          double * means_2, double * sigmas)
{
  // set seed for random number generator
  unsigned int seed = time(0);
  mt19937_64 e(seed);  // initialize 64-bit Mersenne twister
  uniform_real_distribution<double> randreal(0,1);
  
  // generate data types A, B, C
  ofstream f;
  f.open("data.csv");
  f << "sep=\t" << endl;  // to explicitly indicate csv separator
  double total_frequency = freqs[0] + freqs[1] + freqs[2];
  double param_1;
  double param_2;
  char data_type;

  for(int i=0; i<N; i++)
  {
    // choose which data type to generate based on cutoffs
    double random_type = randreal(e) * total_frequency;
    
    if(random_type < freqs[0]) // data type A
    {
      data_type = 'A';
      param_1 = generate_gaussian(means_1[0], sigmas[0], e);
      param_2 = generate_gaussian(means_2[0], sigmas[0], e);
    }

    else if(random_type < freqs[0] + freqs[1])  // data type B
    {
      data_type = 'B';
      param_1 = generate_gaussian(means_1[1], sigmas[1], e);
      param_2 = generate_gaussian(means_2[1], sigmas[1], e);
    }

    else  // data type C
    {
      data_type = 'C';
      param_1 = generate_gaussian(means_1[2], sigmas[2], e);
      param_2 = generate_gaussian(means_2[2], sigmas[2], e);
    }

    // output to csv file
    f << param_1 << " \t" << param_2 << " \t" << data_type << endl;
  }

  f.close();
}

void game_mode(double * freqs, double * means_1, 
               double * means_2, double * sigmas)
{
  // set seed for random number generator
  unsigned int seed = time(0);
  mt19937_64 e(seed);  // initialize 64-bit Mersenne twister
  uniform_real_distribution<double> randreal(0,1);

  // loop for each question
  int score = 0;
  int total_questions = 0;
  double percentage;
  char type_input;
  
  while(true)
  {
    // choose which data type to generate based on cutoffs
    double total_frequency = freqs[0] + freqs[1] + freqs[2];
    double param_1;
    double param_2;
    char data_type;

    // choose which data type to generate based on cutoffs
    double random_type = randreal(e) * total_frequency;
    
    if(random_type < freqs[0]) // data type A
    {
      data_type = 'A';
      param_1 = generate_gaussian(means_1[0], sigmas[0], e);
      param_2 = generate_gaussian(means_2[0], sigmas[0], e);
    }

    else if(random_type < freqs[0] + freqs[1])  // data type B
    {
      data_type = 'B';
      param_1 = generate_gaussian(means_1[1], sigmas[1], e);
      param_2 = generate_gaussian(means_2[1], sigmas[1], e);
    }

    else  // data type C
    {
      data_type = 'C';
      param_1 = generate_gaussian(means_1[2], sigmas[2], e);
      param_2 = generate_gaussian(means_2[2], sigmas[2], e);
    }

    // take input from user
    cout << "Parameter 1: " << param_1 << endl;
    cout << "Parameter 2: " << param_2 << endl;
    cout << "Enter data type (A/B/C), enter X to exit. ";
    type_input = validate_data_type();

    // check if exit is entered
    if(type_input == 'X')
    {
      cout << "Exited Game Mode. " << endl;
      break;
    }

    if(type_input == data_type)  // correct data type
    {
      cout << "Data type correct! The type was " << data_type << 
        "!" << endl;
      score += 1;
    }
    else  // wrong data type
    {
      cout << "Sorry, wrong data type! The correct data type was " 
        << data_type << "!" << endl;
    }

    // print score
    total_questions += 1;
    percentage = (double)score / total_questions * 100;
    cout << "\nScore: " << score << "/" << total_questions << 
      " (" << percentage << "%)" << endl;
  }
}

int main()
{
  // choose mode
  cout << "Choose game mode." << endl;
  cout << "1. Data Generation Mode" << endl;
  cout << "2. Game Mode" << endl;
  cout << "Enter 1 or 2: ";
  double program_mode = validate_program_mode();

  // validate frequencies, means, and standard deviations input
  double * freqs = new double[3]; // relative frequencies A, B, C
  double * means_1 = new double[3];  // parameter 1 for A, B, C
  double * means_2 = new double[3];  // parameter 2 for A, B, C
  double * sigmas = new double[3];  // sigma A, B, C

  cout << "Enter relative frequency A: ";
  freqs[0] = validate_freq_sigma();
  cout << "Enter relative frequency B: ";
  freqs[1] = validate_freq_sigma();
  cout << "Enter relative frequency C: ";
  freqs[2] = validate_freq_sigma();

  cout << "Enter parameter 1 (X-axis mean) for A: ";
  means_1[0] = validate_mean();
  cout << "Enter parameter 1 (X-axis mean) for B: ";
  means_1[1] = validate_mean();
  cout << "Enter parameter 1 (X-axis mean) for C: ";
  means_1[2] = validate_mean();

  cout << "Enter parameter 2 (Y-axis mean) for A: ";
  means_2[0] = validate_mean();
  cout << "Enter parameter 2 (Y-axis mean) for B: ";
  means_2[1] = validate_mean();
  cout << "Enter parameter 2 (Y-axis mean) for C: ";
  means_2[2] = validate_mean();

  cout << "Enter standard deviation A: ";
  sigmas[0] = validate_freq_sigma();
  cout << "Enter standard deviation B: ";
  sigmas[1] = validate_freq_sigma();
  cout << "Enter standard deviation C: ";
  sigmas[2] = validate_freq_sigma();

  // data generation mode
  if(program_mode == 1)
  {
    // validate number of occurrences
    cout << "Enter number of occurrences to generate (integer): ";
    int N = validate_occurrences();

    cout << "\nMode Selected: Data Generation Mode" << endl;
    data_generation_mode(N, freqs, means_1, means_2, sigmas);
  }

  // game mode
  else if(program_mode == 2)
  {
    cout << "\nMode Selected: Game Mode" << endl;
    game_mode(freqs, means_1, means_2, sigmas);
  }

  return 0;
}

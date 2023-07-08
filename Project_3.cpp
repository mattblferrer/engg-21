/**
 * main.cpp
 *
 * FERRER, Matt Brycen L.
 * ENGG 21 - B
 * Linefit
*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**
 * Validates the filename by checking if the file exists. Returns 
 * the filename as the output. 
*/
string validate_filename()
{
  // take filename input from user
  string filename;
  cout << "Enter filename of xy file (Include the extension): ";
  getline(cin, filename);
  ifstream src(filename.c_str());
  
  // check if filename is valid
  while(true)
  {
    if(src) // valid
    {
      cout << "Filename " << filename << " is valid.\n" << endl;
      return filename;
    }
    else  // invalid
    {
      cout << "Filename is invalid. Please enter the filename " <<
        "again. ";
      getline(cin, filename);
      src.close();
      src.open(filename.c_str());  // change name of file opened
    }
  }
}

int main()
{
  // for file parsing 
  string filename = validate_filename();
  ifstream src(filename.c_str());
  string line;
  cout << setprecision(15);
  int lines_read = 0;

  // for calculating the best fit line
  double sum_xy = 0;
  double sum_x = 0;
  double sum_y = 0;
  double sum_x_squares = 0;
  double x;
  double y;

  // process xy file
  while(getline(src, line))
  {
    // parse line
    stringstream stream(line);
    if(!(stream >> x))  // no x-string
    {
      cout << "No x-string found for line " << lines_read + 1 << 
        "." << endl;
      break;
    }
    if(!(stream >> y))  // no y-string
    {
      cout << "No y-string found for line " << lines_read + 1 << 
        "." << endl;
      break;
    }
    else  // calculate sums needed for best fit line
    {
      sum_xy += x*y;
      sum_x += x;
      sum_y += y;
      sum_x_squares += x*x;
      lines_read++;
    }
  }

  // calculate slope and y-intercept of the line
  double b1 = (lines_read * sum_xy - sum_x * sum_y) / (lines_read * 
    sum_x_squares - (sum_x * sum_x));
  double b0 = (sum_y - b1 * sum_x) / lines_read;

  // print results
  if(lines_read < 2)  // invalid for lines read < 2
  {
    cout << "Not enough lines. Cannot calculate slope and " 
      << "y-intercept." << endl;
  }
  else  // valid slope and y-intercept
  {
    cout << "Equation of the line: " << endl;
    cout << b1 << "x + " << b0 << endl;
  }

  cout << lines_read << " lines processed." << endl;

  return 0;
}


/*main.cpp*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

#include "hashCrimeCode.h"

using namespace std;


void nextcode(int& xx, char& y, int& zzzz, int amount)
{
  zzzz = zzzz + amount;

  if (zzzz > 9999)
  {
    zzzz = 0;
    y++;
  }

  if (y > 'Z')
  {
    y = 'A';
    xx++;
  }
}

string tocode(int xx, char y, int zzzz)
{
  string code;

  code = "R";

  if (xx < 10)
    code.push_back('0');
  code += to_string(xx);

  code.push_back(y);

  if (zzzz < 10)
    code += "000";
  else if (zzzz < 100)
    code += "00";
  else if (zzzz < 1000)
    code += "0";

  code += to_string(zzzz);

  return code;
}

void autotest1(int N)
{
  if (N < 25000)
  {
    cout << endl;
    cout << "** Hash table size is too small for testing, must be at least 25,000." << endl;
    cout << endl;
    return;
  }

  cout << "** Test 1 **" << endl;

  hashCrimeCode crimes(N);

  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> randomSeq(0, 1000000);  // 0 .. N-1, inclusive:

  int xx = 0;    // components of a crime code:
  char y = 'A';
  int zzzz = 0;

  string code, value;

  vector<string> values;

  int insert = 0;
  int search = 0;
  int incorrect = 0;

  //
  // insert some reports on the edges of each bin:
  //
  while (xx != 100)
  {
    code = tocode(xx, y, zzzz);
    value = to_string(randomSeq(engine));

    crimes.Insert(code, value);
    values.push_back(value);

    insert++;

    if (zzzz == 0)
      nextcode(xx, y, zzzz, 9999);
    else
      nextcode(xx, y, zzzz, 1);
  }

  //
  // now make sure we get the same values back
  //
  xx = 0;    // reset:
  y = 'A';
  zzzz = 0;

  int vi = 0;  // vector index for checking values:

  while (xx != 100)
  {
    code = tocode(xx, y, zzzz);

    value = crimes.Search(code);

    search++;

    if (value != values[vi])
      incorrect++;

    if (zzzz == 0)
      nextcode(xx, y, zzzz, 9999);
    else
      nextcode(xx, y, zzzz, 1);

    vi++;
  }

  // 
  // search for values we shouldn't find:
  //
  xx = 0;    // reset:
  y = 'A';
  zzzz = 1;

  while (xx != 100)
  {
    code = tocode(xx, y, zzzz);

    value = crimes.Search(code);

    search++;

    if (value != "")
      incorrect++;

    if (zzzz == 1)
      nextcode(xx, y, zzzz, 9997);
    else
    {
      // z == 9998:
      nextcode(xx, y, zzzz, 1);  // 9999
      nextcode(xx, y, zzzz, 1);  // 0
      nextcode(xx, y, zzzz, 1);  // 1
    }
  }

  //
  // results:
  //
  cout << "Insert:    " << insert << endl;
  cout << "Search:    " << search << endl;
  cout << "Incorrect: " << incorrect << endl;
  cout << "Stats: " << crimes.stats() << endl;
  cout << endl;
}

void autotest2(int N)
{
  if (N < 25000)
  {
    cout << endl;
    cout << "** Hash table size is too small for testing, must be at least 25,000." << endl;
    cout << endl;
    return;
  }

  cout << "** Test 2 **" << endl;

  hashCrimeCode crimes(N);

  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> randomSeq(0, 1000000);  // 0 .. N-1, inclusive:

  int xx = 0;    // components of a crime code:
  char y = 'A';
  int zzzz = 0;

  string code, value;

  vector<string> values;

  int insert = 0;
  int search = 0;
  int incorrect = 0;

  //
  // insert reports for every member of 2 different bins:
  //
  while (xx != 100)
  {
    code = tocode(xx, y, zzzz);
    value = to_string(randomSeq(engine));

    crimes.Insert(code, value);
    values.push_back(value);

    insert++;

    if (xx < 99 && zzzz == 9999)
    {
      xx = 99;
      y = 'Y';
      nextcode(xx, y, zzzz, 1);
    }
    else
      nextcode(xx, y, zzzz, 1);
  }

  //
  // now make sure we get the same values back
  //
  xx = 0;    // reset:
  y = 'A';
  zzzz = 0;

  int vi = 0;  // vector index for checking values:

  while (xx != 100)
  {
    code = tocode(xx, y, zzzz);

    value = crimes.Search(code);

    search++;

    if (value != values[vi])
      incorrect++;

    if (xx < 99 && zzzz == 9999)
    {
      xx = 99;
      y = 'Y';
      nextcode(xx, y, zzzz, 1);
    }
    else
      nextcode(xx, y, zzzz, 1);

    vi++;
  }

  // 
  // search for values we shouldn't find:
  //
  xx = 0;    // reset:
  y = 'B';
  zzzz = 0;

  while (y == 'B')
  {
    code = tocode(xx, y, zzzz);

    value = crimes.Search(code);

    search++;

    if (value != "")
      incorrect++;
    
    nextcode(xx, y, zzzz, 1);
  }

  //
  // results:
  //
  cout << "Insert:    " << insert << endl;
  cout << "Search:    " << search << endl;
  cout << "Incorrect: " << incorrect << endl;
  cout << "Stats: " << crimes.stats() << endl;
  cout << endl;
}

void autotest3(int N)
{
  if (N < 25000)
  {
    cout << endl;
    cout << "** Hash table size is too small for testing, must be at least 25,000." << endl;
    cout << endl;
    return;
  }

  cout << "** Test 3 **" << endl;

  hashCrimeCode crimes(N);

  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> randomSeq(0, 1000000);  // 0 .. N-1, inclusive:

  int xx = 11;    // components of a crime code:
  char y = 'M';
  int zzzz = 0;

  string code, value;

  vector<string> values;

  int insert = 0;
  int search = 0;
  int incorrect = 0;

  //
  // insert reports for every member of 2 different bins:
  //
  while (xx != 100)
  {
    code = tocode(xx, y, zzzz);
    value = to_string(randomSeq(engine));

    crimes.Insert(code, value);
    values.push_back(value);

    insert++;

    if (xx == 11 && y == 'M' && zzzz == 9999)
    {
      xx = 12;
      y = 'L';
      nextcode(xx, y, zzzz, 1);
    }
    else if (xx == 12 && y == 'M' && zzzz == 9999)
    {
      xx = 99;
      y = 'Z';
      nextcode(xx, y, zzzz, 1);
    }
    else
      nextcode(xx, y, zzzz, 1);
  }

  //
  // now make sure we get the same values back
  //
  xx = 11;    // reset:
  y = 'M';
  zzzz = 0;

  int vi = 0;  // vector index for checking values:

  while (xx != 100)
  {
    code = tocode(xx, y, zzzz);

    value = crimes.Search(code);

    search++;

    if (value != values[vi])
      incorrect++;

    if (xx == 11 && y == 'M' && zzzz == 9999)
    {
      xx = 12;
      y = 'L';
      nextcode(xx, y, zzzz, 1);
    }
    else if (xx == 12 && y == 'M' && zzzz == 9999)
    {
      xx = 99;
      y = 'Z';
      nextcode(xx, y, zzzz, 1);
    }
    else
      nextcode(xx, y, zzzz, 1);

    vi++;
  }

  // 
  // search for values we shouldn't find:
  //
  xx = 10;    // reset:
  y = 'M';
  zzzz = 0;

  while (xx != 100)
  {
    code = tocode(xx, y, zzzz);

    value = crimes.Search(code);

    search++;

    if (value != "")
      incorrect++;

    if (xx == 10 && y == 'M' && zzzz == 9999)
    {
      xx = 13;
      y = 'L';
      nextcode(xx, y, zzzz, 1);
    }
    else if (xx == 13 && y == 'M' && zzzz == 9999)
    {
      xx = 99;
      y = 'Z';
      nextcode(xx, y, zzzz, 1);
    }
    else
      nextcode(xx, y, zzzz, 1);
  }

  //
  // results:
  //
  cout << "Insert:    " << insert << endl;
  cout << "Search:    " << search << endl;
  cout << "Incorrect: " << incorrect << endl;
  cout << "Stats: " << crimes.stats() << endl;
  cout << endl;
}

void manualtest(int N)
{
  hashCrimeCode crimes(N);
  string code, value;

  cout << "** Insert mode **" << endl;
  cout << "Enter a crime report in format RXXYZZZZ, or # to stop> ";
  cin >> code;

  while (code != "#")
  {
    cout << "Enter a value to store with crime report> ";
    cin >> value;

    crimes.Insert(code, value);

    cout << endl;
    cout << "Enter a crime report in format RXXYZZZZ, or # to stop> ";
    cin >> code;
  }

  cout << endl;
  cout << "** Search mode **" << endl;

  cout << "Enter a crime report in format RXXYZZZZ, or # to stop> ";
  cin >> code;

  while (code != "#")
  {
    value = crimes.Search(code);

    cout << "Search returned: '" << value << "'" << endl;

    cout << endl;
    cout << "Enter a crime report in format RXXYZZZZ, or # to stop> ";
    cin >> code;
  }

  cout << endl;
  cout << "Stats: " << crimes.stats() << endl;
  cout << endl;
}


int main()
{
  int mode, N;

  cout << "Enter 1 for manual testing, 2 for automatic testing> ";
  cin >> mode;

  cout << endl;

  if (mode == 1)  // manual testing:
  {
    cout << "Enter hash table size> ";
    cin >> N;

    manualtest(N);
  }
  else
  {
    cout << "Enter hash table size> ";
    cin >> N;

    autotest1(N);
    autotest2(N);
    autotest3(N);
  }

  return 0;
}

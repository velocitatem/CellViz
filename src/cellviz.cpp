//
// Created by velocitatem on 9/27/24.
//
#include <iostream>
#include  <stdio.h>

using namespace std;
int main(int argc, char *argv[]) {

  int N = 5;
  int grid[N][N];
  int mid = N/2;
  grid[mid][mid] = 1;

  cout << grid[mid][mid];

}


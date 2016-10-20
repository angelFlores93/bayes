#ifndef COMBINATION_H
#define COMBINATION_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

vector <string> get_unknown(string s) {
  vector <string> vec1;
  vec1.push_back(s);
  vector <string> vec2;
  vec2.push_back("+");
  vec2.push_back("-");
  vector <string> res;
  string cpy = ""; 
  for (int i=0; i<vec1.size(); i++) {
    for (int j=0; j<vec2.size(); j++) {
      cpy.append(vec2[j].c_str());
      cpy.append(vec1[i].c_str());

      //cout << cpy << endl;  
      
      res.push_back(cpy); 
      cpy = "";
    }
  }
  return res;
}

void get_comb(vector <vector<string> > &res, vector <string> aux, const vector<vector<string> > &allVecs, size_t vecIndex, string strSoFar)
{
   
    if (vecIndex >= allVecs.size())
    {
        res.push_back(aux);
        return;
    }
    for (size_t i=0; i<allVecs[vecIndex].size(); i++){
        aux.push_back(allVecs[vecIndex][i]);
        get_comb(res, aux, allVecs, vecIndex+1, strSoFar+allVecs[vecIndex][i]);
        aux.pop_back();
      }
}

#endif
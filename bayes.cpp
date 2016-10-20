#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <cmath>
#include "combination.h"

using namespace std;

struct BayesNode
{
	string value; 
	vector<string> parents; 		
};

vector<BayesNode> nodes;
map<string,double> prob_table;
vector<string> queries; 

struct BayesNode* get_node (const char* val){
	for(vector<int>::size_type i = 0; i != nodes.size(); i++) {
	    if (strcmp(nodes[i].value.c_str(), val) == 0){
	    	return &nodes[i];
	    }
	}
}
bool exist (const vector<string> parents, const char*val){
	for(vector<int>::size_type i = 0; i != parents.size(); i++) {
	    if (strcmp(parents[i].c_str(), val) == 0){
	    	return true;
	    }
	}
	return false;
}
double get_probability(string key){
	return prob_table[key];
}
string get_key(string node, vector<string> known, vector<string> unknown){
	string pos = "+"+node;
	string neg = "-"+node;
	for (int i = 0; i < known.size(); i++){
		if (strcmp(pos.c_str(), known[i].c_str()) == 0)
			return pos;
		if (strcmp(neg.c_str(), known[i].c_str()) == 0)
			return neg;
	}
	for (int i = 0; i < unknown.size(); i++){
		if (strcmp(pos.c_str(), unknown[i].c_str()) == 0)
			return pos;
		if (strcmp(neg.c_str(), unknown[i].c_str()) == 0)
			return neg;
	}
}
string get_cond_key(struct BayesNode &node, vector<string>known, vector<string> unknown){
	string res = get_key(node.value, known, unknown);
	res += "|";
	int size = node.parents.size();
	for (int i = 0; i < size; i++){
		res += get_key(node.parents[i], known, unknown);
		if (i < size - 1){
			res += ",";
		}
	}
	return res; 
}
double get_prob(vector<string> known, vector<string> unknown){
	double res = 1.0;
	string key; 
	for (int i = 0; i < nodes.size(); i++){
		if (nodes[i].parents.size() == 0){
			key = get_key(nodes[i].value, known, unknown);	
		}else{
			key = get_cond_key(nodes[i], known, unknown);
		}
		res *= get_probability(key);
	}
	return res;
}
double enum_function(vector <string> &known, vector <string> &unknown){
	double res = 0.0;
	int loop = pow(2,unknown.size()); 
	vector<vector<string> > perm;
	vector<vector<string> > final;
	for(vector<int>::size_type i = 0; i != unknown.size(); i++) {
	    perm.push_back(get_unknown(unknown[i]));
	}
	vector<string> aux;
	get_comb(final, aux, perm, 0,"");
	for (int i = 0; i < final.size(); i++){
		res += get_prob(known, final[i]);
	}
	return res ;	
}
double enumeration (string query){
	vector <string> known; 
	vector <string> unknown;
	char aux[1024];
	strcpy(aux, query.c_str());
	char *token = strtok(aux, "| ,");
	while (token != NULL){
		known.push_back(token);
		token = strtok(NULL, "| ,");
	}
	for (vector<int>::size_type j = 0; j != nodes.size(); j++){
		int flag = 0; 
		string pos = "+";
		string neg = "-";
		pos.append(nodes[j].value);
		neg.append(nodes[j].value);
		for (vector<int>::size_type k = 0; k != known.size(); k++){
			if (strcmp(pos.c_str(), known[k].c_str()) == 0 || strcmp(neg.c_str(), known[k].c_str()) == 0){
				flag = 1; 
				break;
			}
		}
		if (!flag){
			unknown.push_back(nodes[j].value);
		}
	}
	return enum_function (known, unknown);
}
void removeChar(char *str, char garbage) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}
void run_queries(){
	for(vector<int>::size_type i = 0; i != queries.size(); i++) {
	    char nominator[1024];
	    char aux[1024];
	    strcpy(nominator,queries[i].c_str());
	    strcpy(aux, nominator);
	    char *token = strtok(nominator, "|");
	    char *den = token = strtok(NULL, "|");
	    double res;
	    if (den!=NULL){
	    	res = enumeration(aux) / enumeration(den);
	    }
	    else{
	    	res = enumeration(aux);
	    }
	    cout << res;
	    if (i < queries.size()-1){
	    	cout << endl;
	    }
	} 
}
int main (){
	char str[1024];
	while (cin.getline(str,1024) != 0){
		if (strcmp(str, "[Nodes]") == 0){
			cin.getline(str,1024);
			char *token = strtok(str, ", ");
			while (token != NULL){
				struct BayesNode b; 
				b.value = token;
				nodes.push_back(b);
				token = strtok(NULL, ", ");
			}
		}
		if (strcmp(str, "[Probabilities]") == 0){
			cin.getline(str,1024);
			while(strcmp(str,"\0") != 0){
				char *token = strtok(str, "=");
				char *prob = strtok(NULL, "=");
				removeChar(token, ' ' );
				string::size_type sz; 
				prob_table[token] = atof(prob);
				string inverse (token);
				inverse.replace(0, 1, "-");
				prob_table[inverse] = 1 - atof(prob);
				char *child = strtok(token, "+|");
				int i = 0;
				int j = 0;  
				char *parent; 
				while (child != NULL){
					if ( i++ > 0){
						struct BayesNode* n = get_node(parent);
						if (!exist(n->parents, child)){
							n->parents.push_back(child);
						}
					}else{
						strcpy(parent, child);
					}
					child  = strtok(NULL, "+|, -");
				}
				cin.getline(str,1024);
			}
		}
		if (strcmp(str, "[Queries]") == 0){
			while(cin.getline(str,1024)){
				removeChar(str, ' ');
				queries.push_back(str);
			}
		}		
	}
	run_queries();
	for(vector<int>::size_type i = 0; i != nodes.size(); i++) {
	}
	for(vector<int>::size_type i = 0; i != queries.size(); i++) {    
	}		
	
	return 0; 
}
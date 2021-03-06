#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(3);
    v.push_back(4);
    v.push_back(2);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    for(int i = 0; i < v.size(); i++){
        cout << v.at(i) << endl;
    }
}

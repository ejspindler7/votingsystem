#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    vector<int> v = {0};

    for (int i = 0; i < v.size(); i++){
        cout << v.at(i) << endl;;
    }

    int x = v.front();
    v.erase(v.begin());
    v.erase(v.begin());


    cout << "x: " << x << endl;
    cout << "y: " << v.front() << endl;
}

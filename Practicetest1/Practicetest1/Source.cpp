#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


/* int word_count(const vector < string >& words, string word) {
	int count = 0;
	for (int i = 0; i < words.size(); ++i)
	{
		if (words[i].compare(word) == 0)
			++count;
	}
	return count;
}

string modal_value(const vector < string >& words) {
	map<string, int> m;
	for (int i = 0; i < words.size(); ++i)
	{
		if (m.find(words[i]) = 0)
			
	}
} */
//
//double orange() { return 3.1415; }
//
//int orange(int x, int y = 2) { return x * y; }
//
//string orange(string s) {
//
//	cout << orange() << endl;
//
//	return s + s;
//
//}
//
//int main() {
//	cout << orange(" Wow ") << endl;
//	cout << orange(5) << endl;
//	cout << orange(orange(2)) << endl;
//
//	system("pause");
//	return 0;
//}

int triple(int x, vector < int > vec) {
	vec.push_back(x);
	vec.push_back(x);
	vec.push_back(x);
	return 3 * x;
}

int main() {
	vector < int > vec;
	triple(17, vec);
	for (int i = 0; i < 3; i++) cout << vec[i] << endl;
	return 0;
}

// & means passing and changing
//int main(){
	//cout << 10 %11;
//	//vector<string> animal_list = { "bird", "cat", "dog", "bird", "cat", "mouse", "bird", "dog" };
//	//cout << word_count(animal_list, "gouri") << endl;
	//system("pause");
//}

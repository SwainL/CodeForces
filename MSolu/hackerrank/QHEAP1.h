#pragma once

#include <iostream>
#include <queue>
#include <vector>

//template<typename T>
//class custom_priority_queue : public std::priority_queue<T, std::vector<T>> {
//public:
//	bool remove(const T &value) {
//		auto it = std::find(this->c.begin(), this->c.end(), value);
//		if (it != this->c.end()) {
//			this->c.erase(it);
//			std::make_heap(this->c.begin(), )
//		}
//	}
//};

template<typename T>
class custom_priority_queue : public std::priority_queue<T, std::vector<T>>
{
public:

	bool remove(const T& value) {
		auto it = std::find(this->c.begin(), this->c.end(), value);
		if (it != this->c.end()) {
			this->c.erase(it);
			std::make_heap(this->c.begin(), this->c.end(), this->comp);
			return true;
		}
		else {
			return false;
		}
	}
};


using namespace std;

int test() {
	int n;
	cin >> n;
	custom_priority_queue<int> que;
	for (int i = 0; i < n; ++i) {
		int op;
		cin >> op;
		int num;
		switch (op) {
		case 1:
			cin >> num;
			que.push(num);
			break;
		case 2:
			cin >> num;
			que.remove(num);
			break;
		case 3:
			cout << que.top() << endl;
			break;
		}
	}
	return 0;
}

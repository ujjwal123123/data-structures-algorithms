#include <iostream>
#include <vector>

using namespace std;
vector<int> get_array(int length) {
    vector<int> input;
    for (int i = 0; i < length; i++) {
        int inp;
        cin >> inp;
        input.push_back(inp);
    }
    return input;
}

void print_vector(vector<int> vector) {
    cout << "[";
    for (int ele : vector) {
        cout << " " << ele << " ";
    }
    cout << "]" << endl;
}

void find_subset(vector<int> array, int required_sum,
                 vector<int> selected) {
    if (required_sum == 0) {
        print_vector(selected);
        return;
    }
    if (required_sum < 0 or array.empty()) {
        return;
    }
    vector<int> new_vector = {array.begin() + 1, array.end()};
    {
        // include the first element
        vector<int> selected1 = selected;
        selected1.push_back(array[0]);
        find_subset(new_vector, required_sum - array[0], selected1);
    }
    {
        // do not include the first element
        vector<int> selected2 = selected;
        find_subset(new_vector, required_sum, selected2);
    }
}

int main() {
    int length;
    cout << "Length of array: ";
    cin >> length;
    cout << "Array: ";
    vector<int> array = get_array(length);

    int required_sum;
    cout << "Required sum: ";
    cin >> required_sum;

    find_subset(array, required_sum, vector<int>());
}

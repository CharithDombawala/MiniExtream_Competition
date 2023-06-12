#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'activityNotifications' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY expenditure
 *  2. INTEGER d
 */


double median(const std::vector<int>& counting, int d) {
    int count = 0;
    int median1 = -1, median2 = -1;
    int size = counting.size();

    if (d % 2 == 0) {
        for (int i = 0; i < size; i++) {
            count += counting[i];
            if (median1 == -1 && count >= d / 2) {
                median1 = i;
            }
            if (median2 == -1 && count >= d / 2 + 1) {
                median2 = i;
                break;
            }
        }
        return (median1 + median2) / 2.0;
    } else {
        for (int i = 0; i < size; i++) {
            count += counting[i];
            if (count > d / 2) {
                return i;
            }
        }
    }

    return -1;  // Return -1 if no median is found
}

int activityNotifications(const std::vector<int>& expenditure, int d) {
    int count = 0;
    int max_expenditure = *std::max_element(expenditure.begin(), expenditure.end());

    std::vector<int> counting(max_expenditure + 1, 0);

    // Count the frequencies of initial window
    for (int i = 0; i < d; i++) {
        counting[expenditure[i]]++;
    }

    for (int i = d; i < expenditure.size(); i++) {
        if (expenditure[i] >= 2 * median(counting, d)) {
            count++;
        }

        // Update the frequency array
        counting[expenditure[i - d]]--;
        counting[expenditure[i]]++;
    }

    return count;
}


// int activityNotifications(const vector<int>& expenditure, int d) {
//     int count = 0;
    
//     for (int i = d; i < expenditure.size(); i++) {
//         if (expenditure[i] >= 2 * median(expenditure, d)) {
//             count++;
//         }
//     }
    
//     return count;
// }

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int d = stoi(first_multiple_input[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split(rtrim(expenditure_temp_temp));

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

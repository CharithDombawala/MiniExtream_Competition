#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'swapNodes' function below.
 *
 * The function is expected to return a 2D_INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY indexes
 *  2. INTEGER_ARRAY queries
 */
vector<vector<int>> swapNodes(vector<vector<int>>& indexes, vector<int>& queries) {
    struct TreeNode {
        int data;
        TreeNode* left;
        TreeNode* right;
    };

    auto createNode = [](int data) {
        TreeNode* newNode = new TreeNode();
        newNode->data = data;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    };

    function<TreeNode*(int)> insertNode = [&](int index) -> TreeNode* {
        if (index == -1)
            return nullptr;
        TreeNode* newNode = createNode(index);
        newNode->left = insertNode(indexes[index - 1][0]);
        newNode->right = insertNode(indexes[index - 1][1]);
        return newNode;
    };

    function<void(TreeNode*, vector<int>&)> inOrderTraversal = [&](TreeNode* root, vector<int>& result) {
        if (root == nullptr)
            return;
        inOrderTraversal(root->left, result);
        result.push_back(root->data);
        inOrderTraversal(root->right, result);
    };

    function<void(TreeNode*, int, int)> swapSubtrees = [&](TreeNode* root, int k, int depth) {
        if (root == nullptr)
            return;
        if (depth % k == 0) {
            swap(root->left, root->right);
        }
        swapSubtrees(root->left, k, depth + 1);
        swapSubtrees(root->right, k, depth + 1);
    };

    TreeNode* root = insertNode(1);

    vector<vector<int>> result;
    for (int query : queries) {
        swapSubtrees(root, query, 1); 
        vector<int> traversal;
        inOrderTraversal(root, traversal); 
        result.push_back(move(traversal));
    }

    return result;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> indexes(n);

    for (int i = 0; i < n; i++) {
        indexes[i].resize(2);

        string indexes_row_temp_temp;
        getline(cin, indexes_row_temp_temp);

        vector<string> indexes_row_temp = split(rtrim(indexes_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int indexes_row_item = stoi(indexes_row_temp[j]);

            indexes[i][j] = indexes_row_item;
        }
    }

    string queries_count_temp;
    getline(cin, queries_count_temp);

    int queries_count = stoi(ltrim(rtrim(queries_count_temp)));

    vector<int> queries(queries_count);

    for (int i = 0; i < queries_count; i++) {
        string queries_item_temp;
        getline(cin, queries_item_temp);

        int queries_item = stoi(ltrim(rtrim(queries_item_temp)));

        queries[i] = queries_item;
    }

    vector<vector<int>> result = swapNodes(indexes, queries);

    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[i].size(); j++) {
            fout << result[i][j];

            if (j != result[i].size() - 1) {
                fout << " ";
            }
        }

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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

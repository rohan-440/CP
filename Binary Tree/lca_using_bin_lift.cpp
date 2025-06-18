#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to calculate the binary lifting table
vector<vector<int>> binaryLifting(const vector<int> &parent, int root)
{
    int n = parent.size();
    int logN = log2(n) + 1; // Maximum number of ancestors needed

    // Initialize ancestor table with -1 (no ancestor)
    vector<vector<int>> ancestor(n, vector<int>(logN, -1));

    // Base case: 2^0 ancestor is the parent
    for (int i = 0; i < n; i++)
    {
        ancestor[i][0] = parent[i];
    }

    // Build the table iteratively
    for (int j = 1; j < logN; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (ancestor[i][j - 1] != -1)
            {
                int intermediate = ancestor[i][j - 1];          // Get (j-1)th ancestor
                ancestor[i][j] = ancestor[intermediate][j - 1]; // 2^jth is (j-1)th of (j-1)th
            }
        }
    }

    return ancestor;
}

// Function to calculate the LCA using the binary lifting table
int lca(int u, int v, const vector<vector<int>> &ancestor, const vector<int> &depth)
{
    // Ensure u is the deeper node
    if (depth[u] < depth[v])
    {
        swap(u, v);
    }

    // Bring u to the same depth as v
    int logN = ancestor[0].size();
    for (int j = logN - 1; j >= 0; j--)
    {
        if (depth[u] - (1 << j) >= depth[v])
        { // If jump doesn't go above v's depth
            u = ancestor[u][j];
        }
    }

    // If u and v are already equal, it's the LCA
    if (u == v)
    {
        return u;
    }

    // Jump both nodes up until they have the same parent
    for (int j = logN - 1; j >= 0; j--)
    {
        if (ancestor[u][j] != ancestor[v][j])
        { // If ancestors are different, jump up
            u = ancestor[u][j];
            v = ancestor[v][j];
        }
    }

    // Now u and v are one step below the LCA
    return ancestor[u][0];
}

int main()
{
    // Example tree (parent representation, root at index 0)
    vector<int> parent = {-1, 0, 0, 1, 2, 2, 3};

    // Precompute depths (using DFS)
    // For this example, we'll hardcode the depths
    vector<int> depth = {0, 1, 1, 2, 3, 3, 2};

    // Calculate binary lifting table
    vector<vector<int>> table = binaryLifting(parent, 0);

    // Find LCA of nodes 7 and 6 (adjusting indices for 0-based indexing)
    int lcaNode = lca(6, 5, table, depth); // LCA(7, 6) -> indices 6 and 5
    cout << "LCA of 7 and 6: " << lcaNode + 1 << endl;

    return 0;
}
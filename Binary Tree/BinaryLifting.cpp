class TreeAncestor
{
public:
    int depth = 16;
    vector<vector<int>> kth_parent;

    TreeAncestor(int n, vector<int> &parent)
    {
        kth_parent.resize(depth, vector<int>(parent.size(), -1));

        for (int i = 0; i < parent.size(); i++)
        {
            kth_parent[0][i] = parent[i];
        }

        for (int i = 1; i < depth; i++)
        {
            for (int node = 0; node < parent.size(); node++)
            {
                int idx = kth_parent[i - 1][node];
                if (idx != -1)
                {
                    kth_parent[i][node] = kth_parent[i - 1][idx];
                }
            }
        }
    }

    int getKthAncestor(int node, int k)
    {
        int kth_node = -1;
        for (int d = 0; d < depth; d++)
        {
            if ((k >> d) & 1)
            {
                node = kth_parent[d][node];
            }
            if (node == -1)
                return -1;
        }
        return node;
    }
};
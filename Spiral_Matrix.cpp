class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int l = 0, r = n-1, u = 0, d = m-1;
        int i =0;
        vector<int> ans(m*n);
        while(i<m*n)
        {
            for(int j = l;j <=r; j++)
            {
                ans[i++] = matrix[u][j]; 
            }
            if(i>=m*n)
                break;
            u++;
            for(int j = u; j<=d; j++)
            {
                ans[i++] = matrix[j][r];
            }
            if(i>=m*n)
                break;
            r--;
            for(int j = r; j>=l; j--)
            {
                ans[i++] = matrix[d][j];
            }
            if(i>=m*n)
                break;
            d--;
            for(int j = d;j>=u;j--)
            {
                ans[i++] = matrix[j][l];
            }
            l++;
        }
        return ans;
    }
};

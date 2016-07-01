/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Fri, 01 Jul 2016 10:53 CST
Description : Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:
[
[ 1, 2, 3  ],
[ 4, 5, 6  ],
[ 7, 8, 9  ]
]
You should return [1,2,3,6,9,8,7,4,5].
Source      : https://leetcode.com/problems/spiral-matrix/
*******************************************/
class Solution {
public:
	//instead of using several loops for different directions;
	//using r and c to track the position and steps to track
	//the maximal steps and using dirs to control directions;
    vector<int> spiralOrder(vector<vector<int>>& matrix) 
    {
        if(matrix.empty()) return vector<int>();
        int dirs[][2]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int rowSize = matrix.size(), colSize = matrix[0].size();
        int steps[2]{colSize, rowSize-1};
        vector<int> v;
        int r = 0, c = -1, i = 0;
        while(steps[i%2])
        {
            for(int j = 0; j < steps[i%2]; ++j)
            {
                r += dirs[i][0], c += dirs[i][1];
                v.push_back(matrix[r][c]);
            }
            steps[i%2]--;
            i = (i+1)%4;
        }
        return v;
    }
};

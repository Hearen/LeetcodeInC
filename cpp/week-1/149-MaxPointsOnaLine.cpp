/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Thu, 23 Jun 2016 16:00 CST
Description : Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
Source      : https://leetcode.com/problems/max-points-on-a-line/
*******************************************/
class Solution {
private:
    //In mathematics, the greatest common divisor (gcd) of two or more integers, when at least one of them is not zero, is the largest positive integer that divides the numbers without a remainder. For example, the GCD of 8 and 12 is 4.
    //The greatest common divisor is also known as the greatest common factor (gcf),[3] highest common factor (hcf),[4] greatest common measure (gcm),[5] or highest common divisor.[6]
    //Euclid's algorithm
    int gcd(int a, int b)
    {
        while(b)
        {
            int t = b;
            b = a % b;
            a = t;
        return a;
    }

    int GCD(int a, int b) 
    {
        if(b==0) return a;
        else return GCD(b, a%b);
    }
public:
    //AC - 16ms - using map<double, int> to count;
    int maxPoints(vector<Point>& points) 
    {
        int globalMax = 0;
        unordered_map<double, int> slopes;
        for(int i = 0; i < points.size(); ++i)
        {
            int localMax = 0;
            int sameCount = 1;
            slopes.clear(); //just clearing it instead of creating accelerate from 24ms to 16ms;
            for(int j = i+1; j < points.size(); ++j)
            {
                if(points[i].x==points[j].x && points[i].y==points[j].y) sameCount++;
                else if(points[i].x == points[j].x) slopes[INT_MAX]++;
                else slopes[(double)(points[i].y-points[j].y)/(points[i].x-points[j].x)]++;
            }
            for(auto& pair: slopes) localMax = max(localMax, pair.second);
            globalMax = max(globalMax, localMax+sameCount);
        }
        return globalMax;
    }

    //AC - 30ms - using map<pair<int, int>, int> to count points;
    //unordered_map<pair<int, int>, int> will cause error for pair<int, int> as keys cannot be hashed, undefined while map is using binary tree to store the keys;
    int maxPoints(vector<Point>& points)
    {
        int globalMax = 0;
        map<pair<int, int>, int> slopes;
        for(int i = 0; i < points.size(); ++i)
        {
            slopes.clear();
            int localMax = 0, sameCount = 1;
            for(int j = i+1; j < points.size(); ++j)
            {
                if(points[i].x==points[j].x && points[i].y==points[j].y) sameCount++;
                else
                {
                    int dx = points[i].x-points[j].x, dy = points[i].y-points[j].y;
                    int gcf = gcd(dx, dy);
                    slopes[make_pair(dx/gcf, dy/gcf)]++;
                }
            }
            for(auto& pair: slopes) localMax = max(localMax, pair.second);
            globalMax = max(globalMax, localMax+sameCount);
        }
        return globalMax;
    }
};

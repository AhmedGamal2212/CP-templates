class FenwickTree
{
private :
     vector < double > a;
     vector < double > left;
     vector < double > right;
 public :
     void PreProc();
     double Max( int left, int right);
     void Update( int i, double cost);
};

void FenwickTree preproc :: () {
  for ( int i = 0 ; i <a.size (); i ++) Update (i + 1 , a [i]);
}

void FenwickTree :: Update ( int R, Double cost)
{
    a [r- 1 ] = cost;
     int i = R;
     while (i <= pow ( 2.0 , Double (k)))
    {
        left [i] = max (left [i], cost);
        i = i + G (i);
    }
    i = r;
    while (i> 0 )
    {
        right [i] = max (right [i], cost);
        i = iG (i);
    }
}

Double FenwickTree :: Max ( int L, int R) {
     Double RES = 0 ;
     int i = L;
     while (i + G (i) <= R)
    {
        res = max (res, right [i]);
        i = i + G (i);
    }
    if (A [I- 1 ]> res) ans = i;
    res = max (res, a [i- 1 ]);
    i = r;
    while (iG (i)> = L)
    {
        res = max (res, left [i]);
        i = iG (i);
    }
    return RES;
}

#include <iostream>
#include <fstream>
#include <string>

#define FILE_IN  "tests/test6.in"
#define FILE_OUT "tests/test6.out"

using namespace std;

int **mat;
int size_m;
int res = 0;
bool *used;
int mini = -1;
int **way;
string w;

void Mat_new()
{
    ifstream file_in(FILE_IN);
    file_in >> size_m;
    file_in >> w;
    size_m += w.length() + 2;
    mat = new int* [size_m];
    for(int i=0; i<size_m; i++)
    {
        mat[i] = new int [size_m];
        for (int j=0; j<size_m;j++)
            mat[i][j] = 0;
    }
}

void Mat_in ()
{
    ifstream file_in(FILE_IN);
    int n;
    string a;
    file_in >> n;
    file_in >> w;

    for (int i=2; i<w.length()+2; i++)
    {
        mat[0][i]=1;
    }

    for (int i=0; i<n; i++)  // Êóáèêè
    {
        file_in >> a;
        for (int j=0; j<6; j++)  // áóêâû íà êóáèêàõ
        {
            for (int k=0; k<w.length(); k++)  // áóêâû èç ñëîâà
            {
                if (a[j]==w[k])
                {
                    mat[k+2][i+w.length()+2]=1;
                }
            }
        }
        mat[i+w.length()+2][1]=1;
    }
}

void recur(int versh)
{
    if (versh == 1)
        return;
    used[versh] = true;
    for (int i=0; i < size_m; i++)
    {
        if (mat[versh][i] && !used[i])
        {
            if (mini == -1)
                mini = mat[versh][i];
            else
                if (mini>mat[versh][i])
                    mini = mat[versh][i];
            way[versh][i] = 1;
            recur (i);
            return;
        }
    }
    mini = -2;
}

void cut_way()
{
    for (int i=0; i<size_m; i++)
        for (int j=0; j<size_m; j++)
        {
            if (way[i][j])
            {
                mat[i][j] -= mini;
                mat[j][i] += mini;
                way[i][j] = 0;
            }
        }
}

int main()
{
    Mat_new();
    way = mat;
    Mat_new();
    Mat_in();

    used = new bool[size_m];

//    for (int i=0; i<size_m; i++)
//    {
//        for (int j=0; j<size_m; j++)
//            cout << mat[i][j];
//        cout << endl;
//    }

    while (1)
    {
        mini=-1;
        for (int i=0; i<size_m; i++)
            used[i]=false;
        recur(0);
        cut_way();
        if (mini == -2)
            break;
        else
            res +=mini;
    }
    cout << res << " : " << w.length() << endl;
    cout << ((res==w.length())?"YES":"NO");

    string nado;
    ifstream potochek(FILE_OUT);
    potochek >> nado;

    cout << endl << "And needed: " << nado;


}

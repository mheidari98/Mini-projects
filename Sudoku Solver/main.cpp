#include <iostream>

using namespace std;

bool CheckRow(int arr[9][9],int n, int row)
{
    for(int i=0;i<9;i++)
        if(arr[row][i]==n)
            return false;
    return true;
}

bool CheckCol(int arr[9][9],int n, int col)
{
    for(int i=0;i<9;i++)
        if(arr[i][col]==n)
            return false;
    return true;
}

bool CheckBox(int arr[9][9], int n, int a, int b)
{
    int iStart = 3*a;
    int iEnd = iStart+3;
    int jStart = 3*b;
    int jEnd = jStart+3;

    for(; iStart<iEnd ; iStart++ )
        for(; jStart<jEnd ; jStart++)
            if( arr[iStart][jStart]==n)
                return false;

    return true;
}

void MyAdd(int &nextRow,int &nextCol, int row, int col)
{
    nextCol = (col+1)%9;
    nextRow = row + (!nextCol) ;
}

void Recursive(int arr[9][9], int row, int col, bool &Found )
{
    //cout << "at (" << row << " , " << col << ")\n";  
    if( Found )
        return;

    if(row==9)
    {
        Found = true;
        return;
    }

    int nextRow, nextCol;
    MyAdd(nextRow, nextCol, row, col);

    if( arr[row][col] )
    {
        //cout << "at (" << row << " , " << col << ") = " << arr[row][col] <<" \n";  
        Recursive(arr, nextRow, nextCol, Found);
        return;
    }

    for(int i=1; i<10;i++)
    {
        if( CheckRow(arr, i, row) &&  CheckCol(arr, i, col) && CheckBox(arr, i, row/3, col/3) )
        {
            //cout << "can (" << row << " , " << col << ") = " << i <<" \n";  
            arr[row][col] = i;
            Recursive(arr, nextRow, nextCol, Found);
        }
        if( Found )
            break;
        arr[row][col] = 0;
    }

}

void Show(int arr[9][9])
{
    int i,j;

    cout << "--------------\n";

    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
            cout << arr[i][j] << "  ";
        cout << endl;
    }
}

int main()
{
    int i,j;
    bool Found = 0;
    int arr[9][9];

    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            cin >> arr[i][j];

    Recursive(arr, 0, 0, Found);

    Show(arr);

    return 0;
}
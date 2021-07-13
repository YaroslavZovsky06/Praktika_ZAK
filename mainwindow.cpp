#include "mainwindow.h"
#include "ui_mainwindow.h"

int MainWindow::determinant(int N)
{
    int denom(1); //!
        int exchanges(0);

        for(int i(0); i<N-1; ++i)
        {
            int maxN(i);
            int maxValue( arr1[i][i] );
            for(int j(i+1); j<N; ++j)
            {
                int const value(  arr1[j][i] );
                if( value > maxValue ) { maxN=j; maxValue=value; }
            }

            if( maxN > i )
            {
                int *const temp(arr1[i]);
                *arr1[i]=*arr1[maxN];
                *arr1[maxN]=*temp;
                ++exchanges;
            } else {
                if( maxValue == int(0) ) return maxValue;
            }

            int const value1( arr1[i][i] );


            for(int j(i+1); j<N; ++j)
            {
                int const value2( arr1[j][i] );
                arr1[j][i] = int(0);
                for(int c(i+1); c<N; ++c)
                    arr1[j][c]=(arr1[j][c]*value1-arr1[i][c]*value2)/denom;
            }

            denom = value1;
        }

            return arr1[N-1][N-1];
}


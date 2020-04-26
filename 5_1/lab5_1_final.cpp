#include "Header.h"

int main()
{
    srand(time(NULL));

    //Test1
    /*Matrix test1(2);
    Matrix test2(2);
    Matrix test3 = test1 - test2;
    cout << test3;*/

    //Test2
    /*Matrix m1(2);
    cin >> m1;
    cout << m1;*/

    //Test3
    /*Matrix matrix("test", 2, 100);
    matrix.print();
    cout << getDeterminant(matrix) << endl;
    Matrix rev = reverse(matrix);
    Matrix res = rev * matrix;
    res.print();*/
    
    //Test4
    /*Matrix forTime("test", 3, 100);

    auto begin = chrono::steady_clock::now();
    
    for (int i = 0; i < 1000; i++) 
    {
        getDeterminant(forTime);
    }
    
    auto end = chrono::steady_clock::now();

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    cout << "milliseconds - " << ms.count() << endl;
    ///////////////////////////////////////////////////
    begin = chrono::steady_clock::now();
    
    for (int i = 0; i < 1000; i++)
    {
        exp(forTime, 4);
    }
    
    end = chrono::steady_clock::now();
    
    ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "milliseconds - " << ms.count() << endl;*/

    //Test 5
    Matrix a(4);
    cout << getTrace(a) << endl;
    Matrix r("rand", 3, 123);
    r.print();
    cout << endl;
    transpose(r).print();

    return 0;
}

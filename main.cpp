
#include "DataFrame.h"
#include "checkChallenge.h"



int main() {
    
    // see this file for declaration,
    // You can change values to experiment algorithm.
    // During evaluation, we will test a lot of different combinations
    // DO NOT remove include!

//#include "TestValues1.h"
#include "TestValues2.h"
//#include "TestValues3.h"
//#include "TestValues4.h"

    newLine("df1:");
    df_1.print();
    newLine("df2:");
    df_2.print();

    newLine("HSTACK:");
    DataFrame hastackDF = df_1.hstack(df_2);
    hastackDF.print();

    newLine("JOIN on " + ON_MY_COL + " == " + ON_OTHER_COLUMN);
    DataFrame joinDF = df_1.join(df_2, ON_MY_COL, ON_OTHER_COLUMN);
    joinDF.print();

    // will we replaced on correction..
    // DO NOT delete checkChallenge.cpp/h !
    checkChallenge(hastackDF, joinDF);
    
    return 0;


}


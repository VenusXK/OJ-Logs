#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void print_plates(int row, int col,int plates[row][col]){
    for(int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            printf("%d", plates[i][j]);
        }
        printf("\n");
    }
}


int main()
{
    int row, col;
    char tmp[100];
    scanf("%d %d", &col, &row);
    cin.get();
    int plates[row][col];
    for(int i = 0; i < row; i++){
        char input[col];
        getline(cin,input);
        for(int j = 0; j < col; j++){
            printf("%c", input[j]);
            if(input[j] == 'X'){
                plates[i][j] = 1;
            }
            else{
                plates[i][j] = 0;
            }
        }
        printf("\n");
    }
    print_plates(row, col, plates);
    return 0;
}

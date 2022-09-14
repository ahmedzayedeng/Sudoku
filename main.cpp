#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Cell {
public:

    explicit Cell(int num){
        this->num = num;
        empty = num == 0; //<- this is the equivalent to if statement
    }
    int num;
    bool empty = true;

};

class Sudoku {
private:
    int size = 9;
    std::vector<std::vector<Cell>> board;   //=std::vector<std::vector<Cell>>(size, std::vector<Cell>(size, 0));
public:
    explicit Sudoku(std::vector<std::vector<Cell>> board){
        this->board = board;
    }
//    static std::vector<std::vector<Cell>> sud(){
//        return board;
//    }
    static Sudoku read(const std::string& filePath) {
        std::vector<std::vector<Cell>> vectS;

        std::string myText;
        std::ifstream MyFile(filePath);
        int j = 0;
        while (std::getline (MyFile, myText)) {
            std::vector<Cell> temp;
            for (char i : myText){
                temp.emplace_back(i - 48); //48 is the ascii for zero (0)
            }
            vectS.push_back(temp);
            j++;
        }
        MyFile.close();
        return Sudoku(vectS);
    }

    void print() {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                std::cout << board[i][j].num << " ";
                if (j == 2 || j == 5) {
                    std::cout << "|" << " ";
                }
            }
            std::cout << std::endl;
            if (i == 2 || i == 5) {
                std::cout << "---------------------" << std::endl;
            }
        }
    }
    void change(int r, int c, int x){
        board[r][c].num = x;
    }
    int summation(std::vector<Cell> vect){
        int sum = 0;
        for (int i=0; i<vect.size(); i++){
            sum = sum + vect[i].num;
        }
        return sum;
    }
    int summation2(std::vector<std::vector<Cell>> vect, int column){
        int sum = 0;
        for (int i=0; i<vect.size(); i++){
            sum = sum + vect[i][column].num;
        }
        return sum;
    }
    int summation3(std::vector<std::vector<Cell>> vect, int quadrant){
        return 0;
    }
    bool complete(){
        for (int i = 0; i < board.size(); i++) {
            if (summation(board[i]) != 45){
                return false;
            }
        }
        for (int j=0; j<board.size(); j++){
            if (summation2(board, j) != 45){
                return false;
            }
        }
        return true;
    }

};

int main() {

    Sudoku s = Sudoku::read("../Sudoku.txt");
    s.print();
//    Cell c()
//    std::vector<std::vector<Cell>> su = Sudoku::sud();
    int r, c, x;
//    std::cout<<Sudoku::summation(s[0])<<std::endl;
    while (!s.complete()) {
        std::cout << std::endl << "What number where?" << std::endl;
        std::cin >> r >> c >> x;
//    std::cout<<"i = "<<i<<", j = "<<j<<", x = "<<x<<std::endl;
        s.change(r, c, x);
        s.print();
    }
    return 0;
}

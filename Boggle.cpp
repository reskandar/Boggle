


//Got helped by:
// Professor Dr. Varick - a lot of help
//CSu East Bay SCAA tutoring
//Linkedin Courses


#include "Dictionary.h"
#include "Boggle.h"



Boggle::Boggle()
{

    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            visited [i][j] = 0;
        }
    }

    dict.LoadDictionaryFile("dictionary.txt");
}


Boggle::Boggle(string filename)
{
    ifstream inFile;

    inFile.open(filename);
    if (inFile.fail()) {
        cout<<filename<<" failed to open"<<endl;
    }
    string word;
    while(inFile >> word){ //while there are words to read from the file
        dict.AddWord(word); //words get added
    }
    inFile.close();

}




void Boggle::SetBoard(string board[BOARD_SIZE][BOARD_SIZE])
{

    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            this->board[row][col] = board[row][col];
        }
    }

}




void Boggle::PrintBoard(ostream& output)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (visited[i][j])
            {
                output << " '" << board[i][j] << "' ";
                cout << " '" << board[i][j] << "' ";
            }

            else
            {
                output << "  " << board[i][j] << "  ";
                cout << "  " << board[i][j] << "  ";
            }

        }

        output << "\t";
        cout << "\t";
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            output << "  " << visited[i][j] << "  ";
            cout << " " << visited[i][j] << " ";


        }
        output << endl;
        cout << endl;
    }
    output << endl;
    cout << endl;
}


void Boggle::SolveBoard(bool printBoard, ostream& output)
{
    //wordsFound.MakeEmpty();

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            visited[i][j] = 0;
        }
    }

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            SolveBoardHelper(r, c,"", 0, printBoard, output);
        }
    }
}



// This function is complete.
void Boggle::SaveSolve(string filename)
{

    wordsFound.SaveDictionaryFile(filename);
}




void Boggle::SolveBoardHelper(int row, int col, const string& prefix, int step, bool printBoard,ostream& output)
{

    // Out of bounds
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
    {
        return;
    }



    //prefix==prefix+board[row][col];

    // Only progress if this is indeed a valid path.
    if (!dict.IsPrefix(prefix))
    {
        return;
    }


    // If it is a word and we haven't seen this word before
    if (dict.IsWord(prefix) && !wordsFound.IsWord(prefix))
    {

        //numWords++;
        wordsFound.AddWord(prefix);
        if (printBoard)
        {
            output << "Word: " << prefix << endl;
            output << "Number of Words: " << wordsFound.WordCount() << endl;
            PrintBoard(output);
        }
        else
        {
            output << wordsFound.WordCount() << "\t" << prefix << endl;
        }
    }

    // // Already visited

    if (visited[row][col])
    {
        return;
    }

    visited[row][col]=step+1;
    SolveBoardHelper(row - 1, col,     prefix + board[row][col], step + 1, printBoard, output);	// N
    SolveBoardHelper(row - 1, col + 1, prefix + board[row][col], step + 1, printBoard, output);	// NE
    SolveBoardHelper(row,     col + 1, prefix + board[row][col], step + 1, printBoard, output);	// E
    SolveBoardHelper(row + 1, col + 1, prefix + board[row][col], step + 1, printBoard, output);	// SE
    SolveBoardHelper(row + 1, col,     prefix + board[row][col], step + 1, printBoard, output);	// S
    SolveBoardHelper(row + 1, col - 1, prefix + board[row][col], step + 1, printBoard, output);	// SW
    SolveBoardHelper(row,     col - 1, prefix + board[row][col], step + 1, printBoard, output);	// W
    SolveBoardHelper(row - 1, col - 1, prefix + board[row][col], step + 1, printBoard, output);	// NW

    visited[row][col] = 0;
}



//This function is done.
Dictionary Boggle::GetDictionary( )
{

    return dict;
}



//This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}








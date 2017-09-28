#include <vector>
#include <string>
#include <iostream>

using namespace std;

void calculatingLongestPrefixSuffix(string hint, int lengthOfHint, int *LPS);

//Uses KMP patterm searching algorithm
vector<int> KMP(string hint, string initial)
{
    //Converts the length of the strings into int variables
    int lengthOfHint = hint.length();
    int legnthOfInitial = initial.length();

    //Array for storing of LPS values of hint string
    int LPS[lengthOfHint];

    //Vector for storing the index of a char match between the initial and hint string
    vector<int> indexOfMatch;

    //Calulates the LPS values and stroes them
    calculatingLongestPrefixSuffix(hint, lengthOfHint, LPS);

    //Start of  initial index
    int x = 0;
    //Start of  hint index
    int y = 0;

    while (x < legnthOfInitial)
    {
        //Matching chars causes both indices to increment
        if (hint[y] == initial[x])
        {
            y++;
            x++;
        }

        //Storing hint index when result is matched with initial string
        if (y == lengthOfHint)
        {
            //Stores index of hint string
            indexOfMatch.push_back(x-y);

            y = LPS[y - 1];
        }
        //When new char is found
        else if (x < legnthOfInitial && hint[y] != initial[x])
        {
            //When first char is not the same as the hint index
            //Goes to matching index of previous j-1 indices
            if (y != 0)
            {
                y = LPS[y - 1];
            }
            //Else increment initial index
            else
            {
                x++;
            }
        }
    }
    //Retrun result of the matched indices
    return indexOfMatch;
}

//Calculates the Longest Prefix Suffix (LPS) of the hint string
void calculatingLongestPrefixSuffix(string hint, int lengthOfHint, int *LPS)
{
    //int value of the previousLength of the LPS
    int prevLength = 0;

    //Initial value of LPS must always start at 0, the beginning
    LPS[0] = 0;

    //Begin on index 1
    int x = 1;
    while (x < lengthOfHint)
    {
        //If chars match, increments index number and store in LPS array
        if (hint[x] == hint[prevLength])
        {
            prevLength++;
            LPS[x] = prevLength;
            x++;
        }

        else
        {
            //When no matching is found , decrement LPS index value by 1
            if (prevLength != 0)
            {
                prevLength = LPS[prevLength - 1];
            }

            //if no LPS index value initialze to 0.
            else
            {
                LPS[x] = 0;
                x++;
            }
        }
    }
}

//Longest Common Subsequence between fowards and backward index subtractions
void longestCommonCombination(vector<int> indexSubtraction)
{
    int dimension = indexSubtraction.size();
    int y;

    //Create a  square matrix to compare common chars for each backward and forward subtraction of indices
    int matrix[dimension][dimension];

    //When common subsequence is only one char long
    for (int x = 0; x < dimension; x++)
    {
        matrix[x][x] = 1;
    }

    //Loops for the length of the indexSubtraction
    for (int z = 2; z <= dimension; z++)
    {
        //Upper values of foward index subtraction
        for (int x = 0; x < dimension - z + 1; x++)
        {
            //Y value
            y = x + z-1;

            //When common subsequence is only two chars long
            if (indexSubtraction[x] == indexSubtraction[y] && z == 2)
            {
                matrix[x][y] = 2;
            }

            //LCS must have the the same chars at the first and last chars of the string
            else if (indexSubtraction[x] == indexSubtraction[y])
            {
                matrix[x][y] = matrix[x + 1][y - 1] + 2;
            }

            //When chars are not the same find max of both strings
            else
            {
                matrix[x][y] = max(matrix[x][y - 1], matrix[x + 1][y]);
            }
        }
    }


    //Value of combination
    int lengthOfCombination = matrix[0][dimension - 1];
    int combination[lengthOfCombination];

    //first and last chars of the combination
    int first = 0;
    int last = lengthOfCombination - 1;

    //Initial values of each edge of spectrum
    int x = 0;
    y = dimension - 1;

    while (last - first >= 1)
    {

        //When chars of backwards and fowards index subtractions are the same
        //Stores indices of matching chars
        if (indexSubtraction.at(x) == indexSubtraction.at(y))
        {
            combination[first] = indexSubtraction.at(x);
            combination[last] = combination[first];

            first++;
            last--;
            x++;
            y--;
        }

        //When last chars do not match on neither backwards nor fowards index subtractions strings
        else
        {
            if (matrix[x + 1][y] > matrix[x][y - 1])
            {
                x++;
            }
            else
            {
                y--;
            }
        }
    }

    //handling odd number LCS
    if (last == first)
    {
        combination[last] = indexSubtraction.at(x);
    }

    //Printing combination result
    for (int x = 0; x < lengthOfCombination; x++)
    {
        cout << combination[x];
        if (x != lengthOfCombination - 1)
        {
            cout << " ";
        }
    }
}

int main()
{
    string initial;
    string hint;

    getline(cin, initial);
    getline(cin, hint);

    //indexofMatch values stored for both hint and initial strings into vector
    vector<int> indexOfMatch = KMP(hint, initial);

    //Store subtraction of indecies
    vector<int> indexSubtraction;

    //When no matching hint string in initial string or hint string with one occurance
    //Cannot subtract indices of solo index, thus empty string
    if (indexOfMatch.size() == 1 || indexOfMatch.size() == 0 )
    {
        cout << endl;
        return 0;
    }

    //Subtracting index x and index x+1
    for (int x = 0; x < indexOfMatch.size() - 1; x++)
    {
        int result = indexOfMatch[x + 1]-indexOfMatch[x];
        indexSubtraction.push_back(result);
    }

    //Final result
    longestCommonCombination(indexSubtraction);
    cout << endl;
}

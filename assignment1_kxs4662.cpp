#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;


map<int, vector<int> > create_map(int sequence2[], int n){
    vector<int> numbers;
    // Pick all elements one by one 
    for (int i = 0; i < n; i++) { 
        int j = 0; 
        for (j = 0; j < i; j++) 
            if (sequence2[i] == sequence2[j]) 
                break; 
  
        // If not printed earlier, then print it 
        if (i == j) 
            numbers.push_back(sequence2[i]);
    }

    // create and store values into a map
    map<int, vector<int> > position_map;
    for (int i = 0; i < numbers.size(); i++){
        vector<int> positions;
        for (int j = 0; j < n; j++){
            if (sequence2[j] == numbers[i]){
                positions.push_back(j);
            }
        }
        // sorts the values for each key in descending order
        sort(positions.begin(), positions.end(), greater<int>());
        position_map.insert(pair<int, vector<int> >( numbers[i], positions ));
    }

    return position_map;
    
}

int pointer_length(int* sequence1, int m, int n, vector< vector<int> > new_sequence){
    
    int *C=(int*) malloc((n+1)*sizeof(int));
    int *J=(int*) malloc((n+1)*sizeof(int));
    C[0] = -1;
    int pointer = 0;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < new_sequence[i].size(); j++){
            if (C[0] == -1){
                C[0] = new_sequence[i][j];
                J[0] = sequence1[i];
            }
            else if (C[pointer] > new_sequence[i][j]){
                if (pointer > 0){
                    if (new_sequence[i][j] > C[pointer-1]){
                        C[pointer] = new_sequence[i][j];
                        J[pointer] = sequence1[i];
                    }
                }
                else{
                    C[pointer] = new_sequence[i][j];
                    J[pointer] = sequence1[i];
                }  
            }
            else if (C[pointer] < new_sequence[i][j]){
                    C[pointer+1] = new_sequence[i][j];
                    J[pointer+1] = sequence1[i];
                    pointer++;
            }
        }
    }

    return pointer;
}

int* LCS(int* sequence1, int m, int n, vector< vector<int> > new_sequence){
    
    int *C=(int*) malloc((n+1)*sizeof(int));
    int *J=(int*) malloc((n+1)*sizeof(int));
    C[0] = -1;
    int pointer = 0;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < new_sequence[i].size(); j++){
            if (C[0] == -1){
                C[0] = new_sequence[i][j];
                J[0] = sequence1[i];
            }
            else if (C[pointer] > new_sequence[i][j]){
                if (pointer > 0){
                    if (new_sequence[i][j] > C[pointer-1]){
                        C[pointer] = new_sequence[i][j];
                        J[pointer] = sequence1[i];
                    }
                }
                else{
                    C[pointer] = new_sequence[i][j];
                    J[pointer] = sequence1[i];
                }  
            }
            else if (C[pointer] < new_sequence[i][j]){
                    C[pointer+1] = new_sequence[i][j];
                    J[pointer+1] = sequence1[i];
                    pointer++;
            }
        }
    }

    return J;
}

int* LSIS(int* sequence1, int m, int n, vector< vector<int> > new_sequence){
    
    int *C=(int*) malloc((n+1)*sizeof(int));
    int *J=(int*) malloc((n+1)*sizeof(int));
    C[0] = -1;
    int pointer = 0;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < new_sequence[i].size(); j++){
            if (C[0] == -1){
                C[0] = new_sequence[i][j];
                J[0] = sequence1[i];
            }
            else if (C[pointer] > new_sequence[i][j]){
                if (pointer > 0){
                    if (new_sequence[i][j] > C[pointer-1]){
                        C[pointer] = new_sequence[i][j];
                        J[pointer] = sequence1[i];
                    }
                }
                else{
                    C[pointer] = new_sequence[i][j];
                    J[pointer] = sequence1[i];
                }  
            }
            else if (C[pointer] < new_sequence[i][j]){
                    C[pointer+1] = new_sequence[i][j];
                    J[pointer+1] = sequence1[i];
                    pointer++;
            }
        }
    }

    return C;
}

void print(int* arr, int pointer){
    for (int i = 0; i < pointer+1; i++){
        cout << arr[i] << endl;
    }
}

void print_without(int* arr, int pointer){
    for (int i = 0; i < pointer+1; i++){
        cout << arr[i];
    }
}

int main(){
    int m, n, trash;
    
    cin >> m >> n; // getting the size of each of the sequences

    int i = 0;
    int sequence1[m];
    while (i < m){
        cin >> sequence1[i]; // values of first sequence in an array
        i++;
    }

    cin >> trash; // -1

    i = 0;
    int sequence2[n];
    while (i < n){
        cin >> sequence2[i]; // values of second sequence in an array 
        i++;
    }

    cin >> trash; // -1

    map<int, vector<int> > map = create_map(sequence2, n); // creates the map of values in sequence to and their positions as values in descending order

    vector< vector<int> > new_sequence;

    for (int i = 0; i < m; i++){
        auto it = map.find(sequence1[i]);
        vector<int> sequence;
        for (int j = 0; j < it->second.size(); j++){
            // cout << it->second[j] << endl;
            sequence.push_back(it->second[j]);
        }
        new_sequence.push_back(sequence);
    }

    int *C = LSIS(sequence1, m, n, new_sequence); // the Longest Strictly Increasing Substring
    int *J = LCS(sequence1, m, n, new_sequence);    // the longest common subsequence
    int pointer = pointer_length(sequence1, m, n, new_sequence); // gets the length of arrays C and J

    // print(C, pointer);
    cout << "Output: " << endl << pointer+1 << endl;
    print(J, pointer);
    cout << -1 << endl << endl;

    ///////// Text in between 2 method outputs //////////////////////////////////
    // cout << "Matrix Version:" << endl << endl;
    
    // for (i = 0; i < m; i++){
    //     cout << sequence1[i];
    // }
    // cout << endl;
    // for (i = 0; i < m; i++){
    //     cout << sequence2[i];
    // }
    // cout << endl;

    // cout << "LCS is ";
    // print_without(J, pointer);
    // cout << ", length==" << pointer+1 << endl;
    //////////////////////////////////////////////////


    
    // Freeing allocated memory
    free(J);
    free(C);

    return 0;
}
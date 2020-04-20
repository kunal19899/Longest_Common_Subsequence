/*  
    Kunal Samant
    1001534662 
    CSE 5311
*/

// Compile using "g++ assignment_kxs4662.cpp"
// Run using "./a.out < 'text_file' "


#include <iostream>
#include <string>
#include <map>
#include <vector>
// For getrusage()
#include <sys/time.h>
#include <sys/resource.h>

#define MAXSIZE 25000

using namespace std;

float LSISstart, LSISend, LCSstart, LCSend;

float CPUtime()
{
    struct rusage rusage;

    getrusage(RUSAGE_SELF,&rusage);
    return rusage.ru_utime.tv_sec+rusage.ru_utime.tv_usec/1000000.0
        + rusage.ru_stime.tv_sec+rusage.ru_stime.tv_usec/1000000.0;
}

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

int binSearchLast(int *a,int n,int key)
{
    // Input: int array a[] with n elements in ascending order.
    //        int key to find.
    // Output: Returns subscript of the last a element <= key.
    //         Returns -1 if key<a[0].
    // Processing: Binary search.
    int low,high,mid;
    low=0;
    high=n-1;
    // subscripts between low and high are in search range.
    // size of range halves in each iteration.
    // When low>high, low==high+1 and a[high]<=key and a[low]>key.
    while (low<=high)
    {
        mid=(low+high)/2;
        if (a[mid]<=key)
            low=mid+1;
        else
            high=mid-1;
    }
    return high;
}

static int *LCS(int m, int n, int sequence1[], int sequence2[]){
    int LCSlength;
    LCSstart = CPUtime();
    static int LCSstring[MAXSIZE];

    static int cost[MAXSIZE+1][MAXSIZE+1];

    int i,j,k;
    /*string1[i] is associated with row i+1
        string2[i] is associated with column i+1 */
    /*Initialize*/
    for (i=0;i<=m;i++)
        cost[i][0]=0;
    for (i=1;i<=n;i++)
        cost[0][i]=0;

    for (i=1;i<=m;i++)
        for (j=1;j<=n;j++)
        cost[i][j]=
            (sequence1[i-1]==sequence2[j-1])
            ? cost[i-1][j-1]+1
            : (cost[i][j-1]<=cost[i-1][j]) ? cost[i-1][j]
                                            : cost[i][j-1];

    LCSlength=cost[m][n];
    LCSstring[LCSlength]='\0';
    i=m;
    j=n;
    while (cost[i][j]!=0){
        if (sequence1[i-1]==sequence2[j-1])
        {
            if (cost[i][j-1]==cost[i-1][j]){
                LCSstring[cost[i][j]-1]=sequence1[i-1];
                i--;
                j--;
            }
            else if (cost[i][j-1]<cost[i-1][j]){
                i--;
            }
            else if (cost[i][j-1]>cost[i-1][j]){
                j--;
            }
        }
        else if (cost[i][j-1]<cost[i-1][j])
            i--;
        else if (cost[i][j-1]>cost[i-1][j])
            j--;
        else if (cost[i][j-1]==cost[i-1][j]){
            j--;
        }
    }  

    LCSend = CPUtime();
    return LCSstring;
}

int main(){
    int m, n, trash;
    int *y,*bsTabC,*bsTabI,*C,*j;
    int i, k, LISlength;
    
    cin >> m >> n; // getting the size of each of the sequences

    i = 0;
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
            sequence.push_back(it->second[j]);
        }
        new_sequence.push_back(sequence);
    }
    
    int count;
    for (i = 0; i < new_sequence.size(); i++){
        for (int l = 0; l < new_sequence[i].size(); l++){
            count++;
        }
    }

    y=(int*) malloc((count+1)*sizeof(int));
    bsTabC=(int*) malloc((count+1)*sizeof(int));
    bsTabI=(int*) malloc((count+1)*sizeof(int));
    C=(int*) malloc((count+1)*sizeof(int));
    j=(int*) malloc((count+1)*sizeof(int));

    if (!y || !bsTabC || !bsTabI || !C || !j)
    {
        printf("malloc fail %d\n",__LINE__);
        exit(0);
    }

    int z = 1;
    for (i = 0; i < new_sequence.size(); i++){
        for (int l = 0; l < new_sequence[i].size(); l++){
            *(y+z) = new_sequence[i][l];
            z++;
        }
    }


   // Initialize table for binary search for DP
    bsTabC[0]=(-999999);  // Must be smaller than all input values.
    bsTabI[0]=0;          // Index of predecessor (0=grounded)
    for (i=1;i<z;i++)
    bsTabC[i]=999999;   // Must be larger than all input values.

    C[0]=0;  // DP base case
    j[0]=0;

    LSISstart = CPUtime();
    for (i=1;i<z;i++)
    {
        // Find SIS that y[i] could be appended to.
        // See CSE 2320 Notes 01 for binSearchLast()
        k=binSearchLast(bsTabC,n+1,y[i]);
        // y[i] only matters if it is not already in table.
        if (bsTabC[k]<y[i]) {
            C[i]=k+1;         // Save length of LIS for y[i]
            j[i]=bsTabI[k];   // Predecessor of y[i]
            bsTabC[k+1]=y[i]; // Decrease value for this length IS
            bsTabI[k+1]=i;
        }
        else
        {
            C[i]=(-1);        // Mark as ignored
            j[i]=(-1);
        }
    }
    LSISend = CPUtime();

    for (LISlength=n;
        bsTabC[LISlength]==999999;
        LISlength--)
    ;
    vector<int> LSIS;
    for (i=bsTabI[LISlength]; i>0; i=j[i]){
        LSIS.push_back(y[i]);
    }

    static int *LCSstring = LCS(m, n, sequence1, sequence2);

    vector<int> LSISstring;
    
    for (i = LSIS.size()-1; i > -1; i--){
        int key = -1;
        for(int j = 0; j < m; j++){
            for (k = 0; k < new_sequence[j].size(); k++){
                if (new_sequence[j][k] == LSIS[i]){
                    LSISstring.push_back(sequence1[j]);
                    key = 1;
                    break;
                }
            }
            if (key == 1)
                break;
        }
    }

    bool same = true;
    int u = 0;
    for (k = 0; k < LSIS.size(); k++){
        if (*(LCSstring+k) != LSISstring[k]){
            same = false;
            u++;
        }
    }

    if (same){
        cout << LSIS.size() << endl;
        for (k = 0; k < LSIS.size(); k++){
            cout << *(LCSstring+k) << endl;
        }
        cout << -1 << endl;
    }
    
    cout << "LSIS time: " << LSISend-LSISstart << " s" << endl << "LCS time: " << LCSend-LCSstart << " s" <<  endl;

    free(y);
    free(bsTabC);
    free(bsTabI);
    free(C);
    free(j);
    
    return 0;
}
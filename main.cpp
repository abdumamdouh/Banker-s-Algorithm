#include <iostream>
#include <vector>
#define endl '\n'

using namespace std;

void read_m_vector(vector<int> &vector, string name, int m){
    cout << "Enter the " << name <<" Vector"<<endl;
    char out = 'A';

    cout << "";
    for(int i = 0 ; i< m ;i++){
        cout << out << " ";
        out = out +1;
    }
    cout << endl;

    for(int i = 0 ; i< m ;i++)
        cin >> vector[i];
}
void read_nm_matrix(vector<vector<int>> &twoDvector, string name, int n, int m){
    cout << "Enter the " << name <<" Matrix"<<endl;
    char out = 'A';

    cout << "   ";
    for(int i = 0 ; i< m ;i++){
        cout << out << " ";
        out = out +1;
    }

    cout << endl;

    for(int i = 0 ; i< n ;i++){
        cout << "P" << i << ":";
        for(int j = 0 ; j < m ; j++){
            cin >> twoDvector[i][j];
        }

        cout << endl;
    }
}
void readReq(vector<int> &pro,int &p,int &m){
    cout << endl;
    cout << "Enter the number of the process to inquiry about immediate requests" << endl;

    cin >> p;

    cout << "Enter the request vector" << endl;

    for(int i = 0 ; i < m ; i++)
        cin >> pro[i];
}
void calc_need(vector<vector<int>> &Need, vector<vector<int>> &Max, vector<vector<int>> &Allocation, int n, int m){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];


    char out = 'A';

    cout << "The Need Matrix:"<< endl << endl;

    cout << "   ";
    for(int i = 0 ; i< m ;i++){
        cout << out << " ";
        out = out +1;
    }

    cout << endl;

    for(int i = 0 ; i< n ;i++){
        cout << "P" << i << ":";
        for(int j = 0 ; j < m ; j++){
            cout << Need[i][j] << " ";
        }
        cout << " " << endl;
    }

    cout << endl;
}
bool safeState(vector<int> &sequence, vector<vector<int>> &Need, vector<int> &Available, vector<vector<int>> &Allocation,int n, int m){

    // Safety Algorithm

    //declare the finish vector and Initialize it with false for all elements
    vector<bool>finish (n);

    for (int k = 0; k < n; k++)
        finish[k] = false;

    // sequence vector to hold the safe sequence

    int index = 0;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {

                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Available[j]){
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    sequence[index++] = i;
                    for (int y = 0; y < m; y++)
                        Available[y] += Allocation[i][y];
                    finish[i] = true;
                }
            }
        }
    }


    //if any element of the finish vector is false then the system is in a unsafe state

    for (int k = 0; k < n; k++){
        if (!finish[k]){
            return false;
        }
    }

    //if all the elements of the finish vector is true then the system is in a safe state

    return true;

}
bool validReq(vector<int> &pro, vector<vector<int>> &Need, vector<int> &Available, vector<vector<int>> &Allocation,int m,int p){

    //Resource-Request Algorithm

    for (int i = 0; i < m; i++){
        if(pro[i] <= Need[p][i]){
            if(pro[i] <= Available[i]){
                Available[i] -= pro[i];
                Allocation[p][i] += pro[i];
                Need[p][i] -= pro[i];
            }

            else
                return false;

        }

        else
            return false;


    }

    return true;
}

int main() {

    // Process Format P0, P1, P2, P3....
    // Resources Types Format A, B, C, ....
    // n > number of process, m > number or Resources types

    int n, m;
    char out = 'A';

    cout << "Enter the Number of Process"<<endl;
    cin >> n;

    cout << "Enter the Number of Resources"<<endl;
    cin>> m;

    vector<vector<int>> Allocation (n, vector<int> (m));
    vector<vector<int>> Max (n, vector<int> (m));
    vector<vector<int>> Need (n, vector<int> (m));
    vector<int> Available (m);

    //taking the input matrices from the user

    read_nm_matrix(Allocation,"Allocation",n , m);
    read_nm_matrix(Max, "Max", n, m);
    read_m_vector(Available, "Available", m);

    cout << endl;

    // calculate the need matrix & output it
    calc_need(Need, Max, Allocation, n, m);

    //handling the inquiry of the user

    cout << "Enter 0 to know if the system is in a safe state or not " << endl <<
         "Enter 1 to determine a certain immediate request by one of the processes can be granted or not" <<endl;

    int input;
    cin >> input;

    if (input == 0){
        vector<int>sequence (n);
        // checking if the system is in a safe state or not
        bool isSafeState = safeState(sequence,Need, Available, Allocation,n,m);
        if(isSafeState){
            cout << "Yes , Safe state <";
            for (int i = 0; i < n - 1; i++)
                cout << "P" << sequence[i] << ",";
            cout << "P" << sequence[n - 1] << ">" << endl << endl;
        } else{
            cout << "No, unsafe state" << endl;
            return 0;
        }

    } else if(input == 1){
        int p;
        vector<int> pro (m);
        readReq(pro,p,m);

        bool isValid = validReq(pro,Need,Available,Allocation,m,p);
        if(isValid){
            vector<int>sequence (n);
            // checking if the system is in a safe state or not
            bool isSafeState = safeState(sequence,Need, Available, Allocation,n,m);

            if(isSafeState){
                cout << "Yes request can be granted with safe state , Safe state <P" << p << "req,";
                for (int i = 0; i < n - 1; i++)
                    cout << "P" << sequence[i] << ",";
                cout << "P" << sequence[n - 1] << ">" << endl << endl;
            } else{
                cout << "No request can't be granted" << endl;
                return 0;
            }

        } else{
            cout << "No the request can't be granted" << endl;
            return 0;
        }

    }
    else{
        cout << "Wrong input!"<< endl << "Please Try again";
        return 0;
    }


    system("pause");

    return 0;

}

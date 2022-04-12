#include <bits/stdc++.h>
using namespace std;
class Farmer
{
public:
    friend class manager;
    vector<int> allocation ;
    vector<int>request;
    Farmer()
    = default;
    Farmer(vector<int> &allocations , vector<int>& requests)
    {
        allocation.clear();
        for(auto it : allocations)
            allocation.push_back(it);
        request.clear();
        for(auto it : requests)
            request.push_back(it);

    }

};
class manager{
public:
    int no_of_farmers;
    int number_of_resources;
    vector<vector<int>> allocated_resources;
    vector<vector<int>> request_matrix;
    vector<vector<int>> needed_resources;
    vector<int> available_resources;
    vector<int> finished_allocation;
    manager()
    {
        no_of_farmers = 0;
        number_of_resources = 0;
    }
    manager(int resource_no , vector<int> &values)
    {
        no_of_farmers = 0;
        number_of_resources = resource_no;
        for(auto it : values)
        {
            available_resources.push_back(it);
        }
    }
    void print()
    {

        cout << "\nFarmer\t Allocation\t Need\t\tRequest\t\t Available\t";
        for (int i = 0; i < no_of_farmers; i++){
            cout << "\nF" << i + 1 << "\t ";
            for (int j = 0; j < number_of_resources; j++)
            {
                cout << allocated_resources[i][j] << " ";
            }
            cout << "\t\t";
            for (int j = 0; j < number_of_resources; j++)
            {
                cout << needed_resources[i][j] << " ";
            }
            cout << "\t\t";
            for (int j = 0; j < number_of_resources; j++)
            {
                cout << request_matrix[i][j] << " ";
            }
            cout << "\t\t ";
            if (i == 0)
            {
                for (int j = 0; j < number_of_resources; j++)
                    cout << available_resources[j] << " ";
            }
        }
        cout<<"\n";
    }
    bool deadlock_check()
    {
        finished_allocation.clear();
        finished_allocation.resize(no_of_farmers);
        finished_allocation.assign(no_of_farmers , 0);
        int i , j , flag = 1;
        int n = no_of_farmers , r = number_of_resources;
        vector<vector<int>> need_resource_temp = needed_resources;
        vector<int> avail_resource = available_resources;
        vector<vector<int>> allocated_resource_temp = allocated_resources;
        while (flag)
        {
            flag = 0;
            for (i = 0; i < n; i++)
            {
                int c = 0;
                for (j = 0; j < r; j++)
                {
                    if ((finished_allocation[i] == 0) && (need_resource_temp[i][j] <= avail_resource[j]))
                    {
                        c++;
                        if (c == r)
                        {
                            for (int k = 0; k < r; k++)
                            {
                                avail_resource[k] += allocated_resource_temp[i][j];
                                finished_allocation[i] = 1;
                                flag = 1;
                            }
                            if (finished_allocation[i] == 1)
                            {
                                i = n;
                            }
                        }
                    }
                }
            }
        }
        j = 0;
        flag = 0;
        for (i = 0; i < n; i++)
        {
            if (finished_allocation[i] == 0)
            {
                j++;
                flag = 1;
            }
        }
        return flag;
    }
    void add_farmer(Farmer &f1)
    {

        no_of_farmers++;
        allocated_resources.push_back(f1.allocation);
        request_matrix.push_back(f1.request);
        vector<int> need;
        need.reserve(number_of_resources);
need.reserve(number_of_resources);
for(int i = 0 ; i < number_of_resources ; i++)
        {
            need.push_back(f1.request[i] - f1.allocation[i]);
        }

        needed_resources.push_back(need);
        need.clear();
    }

    void safe_sequence() const
    {
        int n = no_of_farmers;
        int r = number_of_resources;
        vector<bool> finish(n);
        int safeSeq[n];
        int work[r];
        vector<int> avail = available_resources;
        for (int i = 0; i < r ; i++)
            work[i] = avail[i];
        int count = 0;
        vector<vector<int>> need = needed_resources;
        vector<vector<int>> allot = allocated_resources;
        while (count < n)
        {
            bool found = false;
            for (int p = 0; p < n; p++)
            {
                if (finish[p] == 0)
                {
                    int j;
                    for (j = 0; j < r; j++)
                        if (need[p][j] > work[j])
                            break;
                    if (j == r)
                    {
                        for (int k = 0 ; k < r ; k++)
                            work[k] += allot[p][k];
                        safeSeq[count++] = p;
                        finish[p] = true;
                        found = true;
                    }
                }
            }

            if (!found)
            {
                cout << "System is not in safe state";
            }
        }
        for (int i = 0; i < n-1 ; i++)
            cout << "Farmer"<<safeSeq[i]+1 <<" -> ";
        cout<<"Farmer"<<safeSeq[n-1] + 1<<"\n";
    }
    void remove_deadlock()
    {
        vector<int> max_possible = available_resources;
        for(int j = 0 ; j < no_of_farmers ; j++)
        {
            for(int k = 0 ; k < number_of_resources ; k++)
            {
                max_possible[k] += allocated_resources[j][k];
            }
        }
        for(int j = 0 ; j < no_of_farmers ; j++)
        {
            for(int k = 0 ; k < number_of_resources ; k++)
            {
                if(request_matrix[j][k] > max_possible[k])
                {
                    cout<<"Deadlock cannot be Removed as one or more farmers are requesting resources greater than the overall available resources.\n";
                    return;
                }
            }
        }
        int ans = (1<<no_of_farmers);
        ans--;
        int cnt = no_of_farmers;
        vector<vector<int>> temp = allocated_resources;
        vector<int> avail_rs = available_resources;
        vector<vector<int>> need = needed_resources;
        for(int i = 0 ; i <(1<<no_of_farmers) ; i++)
        {
            allocated_resources = temp;
            available_resources = avail_rs;
            needed_resources = need;
            for(int j = 0 ; j < no_of_farmers ; j++)
            {
                if(i & (1<<j))
                {
                    for(int k = 0 ; k < number_of_resources ; k++)
                    {
                        available_resources[k] += allocated_resources[j][k];
                        allocated_resources[j][k] = 0;
                        needed_resources[j][k] = request_matrix[j][k];
                    }
                }
            }
            if(!deadlock_check())
            {
                int mini = 0;
                for(int j = 0 ; j < no_of_farmers ; j++)
                {
                    if(i & (1<<j))
                    {
                        mini++;
                    }
                }
                if(mini < cnt){
                    cnt = mini;
                    ans = i;
                }
            }
        }
        cout<<"Deallocate all Resources from following farmers :\n";
        for(int j = 0 ; j < no_of_farmers ; j++)
        {
            if(ans & (1<<j))
            {
                cout<<"Farmer"<<j+1<<" ";
            }
        }
        cout<<endl;
        available_resources = avail_rs;
        allocated_resources = temp;
        needed_resources = need;
        for(int j = 0 ; j < no_of_farmers ; j++)
        {
            if(ans & (1<<j))
            {
                for(int k = 0 ; k < number_of_resources ; k++)
                {
                    available_resources[k] += allocated_resources[j][k];
                    allocated_resources[j][k] = 0;
                    needed_resources[j][k] = request_matrix[j][k];
                }
            }
        }
        cout<<"After De-allocation , data is :\n";
        print();
        safe_sequence();
        available_resources = avail_rs;
        allocated_resources = temp;
        needed_resources = need;
    }

};
int main()
{
    cout<<"\nEnter the number of resources: ";
    int number_of_resources;
    cin>>number_of_resources;
    cout<<"\nEnter the available resources:\n";
    vector<int> avail_resources(number_of_resources);
    for(int i=0; i < number_of_resources; i+=1){
        cin>>avail_resources[i];
    }
    manager man(number_of_resources , avail_resources);
    int x = 1;
    cout<<"Press 1 for adding farmer\nPress 2 for checking safe state and getting safe sequence\nPress 3 to print available date\nPress 4 to exit.\n ";
    cin>>x;
    vector<Farmer> farmers;
    vector<int> allocated(number_of_resources) , request(number_of_resources);
    while( x< 4)
    {
        if(x == 1)
        {
            cout<<"Allocation Matrix of Farmer \n";
            for(int i = 0 ; i < number_of_resources ; i++)
            {
                cin>>allocated[i];
            }
            cout<<"Request Matrix of Farmer \n";
            for(int i = 0 ; i < number_of_resources ; i++)
            {
                cin>>request[i];
            }
            Farmer f(allocated , request);
            farmers.push_back(f);
            man.add_farmer(f);
            cout<<"Press 1 for adding farmer\nPress 2 for checking safe state and getting safe sequence\nPress 3 to print available date\nPress 4 to exit. \n";
            cin>>x;

        }
        else if(x == 2)
        {
            if(!man.deadlock_check()){
                cout<<"No deadlock\nSafe Sequence is :\n";
                man.safe_sequence();

            }
            else
            {
                cout<<"Deadlock Occurs :\n";
                man.remove_deadlock();
            }
            cout<<"Press 1 for adding farmer\nPress 2 for checking safe state and getting safe sequence\nPress 3 to print available date\nPress 4 to exit.\n ";
            cin>>x;
        }
        else if(x == 3)
        {
            man.print();
            cout<<"Press 1 for adding farmer\nPress 2 for checking safe state and getting safe sequence\nPress 3 to print available date\nPress 4 to exit.\n ";
            cin>>x;
        }
        else
        {
            break;
        }
    }

    return 0;
}
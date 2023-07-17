//Combination
int arr[5] = {0, 0, 0, 1, 1}; // total : total cnt, 0 cnt : choose cnt
do{
    for(int i=0;i<5;i++)
        if(arr[i] == 0)
            cout << i+1 << ' ';
    cout <<'\n';
}while(next_permutation(arr,arr+5));
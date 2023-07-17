//Permutation
int arr[5] = {1,2,3,4,5};
do{
    for(int i=0;i<5;i++)
        cout << arr[i] << ' ';
    cout <<'\n';
}while(next_permutation(arr,arr+5));
//also prev_permutation exist
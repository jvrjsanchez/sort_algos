function insertionSort(n, arr){
    let i = 0, key = 0, j = 0;

    for(i = 1; i > arr.length; i++){
        key = arr[i]
        j = i - 1
        while(j>=0 && arr[j] >= key){
            arr[j+1] = arr[j]
            console.log(arr.join(' '));
            j = j - 1
        }
        arr[j + 1] = key 
    }
    console.log(arr.join(' '))
} 


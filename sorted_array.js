function searchInSortedArray(arr, target){
    //target value 
    //if target exists, return its index
    //if target doesn't exists, return -1
    //first we dont have to worry about sorting the array, so thats easier
    // get the length of array 
    let n = arr.length;
    for (var i = 0; i < n; i++){
        if (arr[i] === target){
            return i
        }
    }
    return -1
}
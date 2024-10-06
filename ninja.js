var arr = [1, 2, 3, 4, 5, 6, 7];
var map = arr.map(function(item){
    return item + 10;
}).filter(function(item){
    return item > 13;
})

console.log(map)
/*
var map = arr.map(function(item, index, array) {
    return {index: index, item: item};

});
console.log(arr, map)

var newArr = [];
arr.forEach(function(item, index, array){
    newArr.push({ index: index, item: item})

})
console.log( 'newArr:' )
console.log( newArr)
/*
var some = arr.some(function (item){
    return item % 2 === 0;
})
console.log(some)

/*
var every = arr.every(function(item) {
    console.log( item )
    return item < 8;
})
console.log( every )


/*
var sum = 0;
arr.forEach(function( item ){
    sum += item;
});
console.log ( sum );
/*
for (var i = 0; i < arr.length; i++) {
    console.log( arr[i], i, arr);
}
*/


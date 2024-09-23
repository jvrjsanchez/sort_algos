let nums = [-1,0,3,5,9,12];
const target = 12

var search = function(nums, target) {
    let n = nums.length
    for (var i = 0; i < n; i++) {
        if (nums[i] === target) {
            return i
        }
    }
    return -1
}
console.log(search(nums, target))
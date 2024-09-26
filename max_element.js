function getMaxelement(list) {       // What is n? 
    let maxElement = Number.NEGATIVE_INFINITY;      // n is the length of the list
    for (let element in list) {                 // What is the "basic operation"?
        if (element > maxElement) {                     // The maxElement comparison
            maxElement = element;                   // How does it relate to n?
        }                                       // The operation happens n times
    }
    return maxElement;
}
// Formal procedure for analyzing a non-recursive algorithm
// 1. figure out what 'n' is
    // this generally be the length of a collection ie. n = nums.length, passed in as input, or a numeric value pass as input. 
// 2. identify the basic operation
    // this is usually happening with the innermost loop of the algorithm ie. an if else condition
// 3. Evaluate the relationship between this operation and n 
    // is n being iterated over? Is some value growing until it reaches the size of n? How is it growing??
// 4. Setup a sum expressing the number of times the algorithms basic operation is executed as a function of n
    // find a close form formula that describes this sum
 
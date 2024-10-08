function findCombinations(letters){
    let combinations = []
    for(let letter1 in letters){
        for(let letter2 in letters){
            for(let letter3 in letters){
                let combination = letter1 + letter2 + letter3
                combinations.push(combination)
            }
        }
    }
    let validCombinations = combinations.filter(combination => containsVowel(combination))
    return validCombinations;
}

function containsVowel(combination){
    return combination.includes('A') || combination.includes('E') || combination.includes('I') || combination.includes('O') || combination.includes('U')
}

const letters = ['A', 'E', 'O']

console.log(findCombinations(letters))

var longestStrChain = function(words) {
        words.sort((a,b) => a.length - b.length)
        const dp = new Map()
        let longestChain = 1
        for (const word of words){
            dp.set(word, 1)
        }
        for (const word of words){
            for(var i = 0; i < word.length; i++){
                const predecessor = word.slice(0, i) + word.slice(i + 1)
                if (dp.has(predecessor)){
                    dp.set(word, Math.max(dp.get(word), dp.get(predecessor) + 1))
                }
                longestChain = Math.max(longestChain, dp.get(word))
            }
        }
        return longestChain;
    }
// Example usage:
const words = ["abcd","dbqca"];
console.log(longestStrChain(words)); // Output: 5
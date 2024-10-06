function hackerrankInString(str) {
    var string = 'hackerrank';
    var c = 0;
    for (var s in str) {
        console.log(s);
        if(str[s] === string[c]){
            c++;
        }
    }
    return c === string.length ? "YES" : "NO";
}
console.log(hackerrankInString('alabama'))
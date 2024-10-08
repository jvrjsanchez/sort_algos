(function (){
    var myObject = {
        myProperty: 1,
        init: function init() {
            return this.myProperty;
        }
    };
    console.log(myObject.init())
})();
// A $( document ).ready() block.
$( document ).ready(function() {
    console.log( "ready!" ); 
    

});

function restGet(address){
    $.get(address);
    console.log("called :" + address);
};
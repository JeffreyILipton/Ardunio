from bottle import route, get,post, request, run, template
from irinterface import *

ir = IRInterface()
ir.connect("COM10",9600)


@route('/stereo')
def stereo_index():    
    return '<b>Hello </b>!'


@route('/stereo/:letter')
def stereo_put(letter=''):
    ir.write("s"+letter)
    return template('<b>Command s{{letter}}</b>!', letter=letter)

@route('/tv')
def tv_index():    
    return '<b>Hello </b>!'


@route('/tv/:letter')
def tv_put(letter=''):
    ir.write("t"+letter)
    return template('<b>Command t{{letter}}</b>!', letter=letter)
    
    
run(host='localhost', port=8080)
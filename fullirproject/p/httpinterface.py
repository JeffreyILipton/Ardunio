from bottle import *
from irinterface import *
from os import getcwd


class HTTPInterface:
    def __init__(self,port='',baud=0):
        self.ir = IRInterface();
        if ((port!='') and (baud!=0)):
            try: 
                self.ir.connect(port,baud)
            except:
                print "failed to open"
    #@route(/settings)
    def settings_index(self):
        return '''
        <form action="/settings" method="post">
            Comport:    <input type="text" name="comport" />
            Baud: <input type="text" name="baud" />
            <input type="submit" value="Set" />
        </form>
        '''
        
    #@route('/settings',method = 'POST')
    def settings_post(self):
        comport = request.forms.get('comport')
        baud = request.forms.get('baud')
        try:
            self.ir.connect(comport,baud)
        except:
            return 'incorrect settings'
        return 'comport changed'

    #@route('/ui')
    def mainui(self):
        print self.send_static('main.html')
        return self.send_static('main.html')
        #'<b>Hello, this is where the UI should be </b>!'
    
    #@route('/stereo')
    def stereo_index(self):    
        return '<b>THIS PAGE IS BLANK</b>!'

    #@route('/stereo/:letter')
    def stereo_get(self,letter=''):
        if (self.ir.write("s"+letter)):
            return template('<b>Command s{{letter}} sent</b>!', letter=letter)
        else:
            return 'command failed'

    #@route('/tv')
    def tv_index(self):    
        return '<b>THIS PAGE IS BLANK</b>!'

    #@route('/tv/:letter')
    def tv_get(self,letter=''):
        if(self.ir.write("t"+letter)):
            return template('<b>Command t{{letter}} sent</b>!', letter=letter)
        else:
            return 'command failed'
            
    #@route('/static/<filename:path>')
    def send_static(self,filename):
        newroot = getcwd().replace("\\","\\\\")+"\\\\"+ "static"
        return static_file(filename, root=newroot)
        
if __name__ == '__main__':
    comport = "COM10"
    baud = 9600
    ipport = 88
    ipaddr='localhost'
    app = Bottle()
    httpi = HTTPInterface(comport,baud)
    app.route('/settings')(httpi.settings_index)
    app.route('/settings',method = 'POST')(httpi.settings_post)
    app.route('/ui')(httpi.mainui)
    app.route('/stereo')(httpi.stereo_index)
    app.route('/stereo/:letter')(httpi.stereo_get)
    app.route('/tv')(httpi.tv_index)
    app.route('/tv/:letter')(httpi.tv_get)
    app.route('/static/<filename:path>')(httpi.send_static)
    
    run(app,host=ipaddr, port=ipport)
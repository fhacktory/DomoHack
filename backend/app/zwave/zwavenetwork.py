import logging
import sys,os
import resource
zwave = True
try:
    import openzwave
    from openzwave.node import ZWaveNode
    from openzwave.value import ZWaveValue
    from openzwave.scene import ZWaveScene
    from openzwave.controller import ZWaveController
    from openzwave.network import ZWaveNetwork
    from openzwave.option import ZWaveOption
    from louie import dispatcher, All
except:
    zwave = False
import time


class ZWave(object):

    network=None
    zwave = True

    def __init__(self, app):
        if self.network is None:
            self.zwave = zwave
            self.app = None
            self.blueprint = None
            if app is not None:
                self.app = app
            if zwave:
                logging.basicConfig(level=logging.INFO)
        
                logger = logging.getLogger('openzwave')
                device="/dev/ttyACM0"
                log="Debug"
        
                options = ZWaveOption(device, \
                   config_path="%s/config" % os.path.abspath(os.path.dirname(__file__)), \
                   user_path=".", cmd_line="")
                options.set_log_file("zwave_test.log")
                options.set_append_log_file(False)
                options.set_console_output(False)
                options.set_save_log_level(log)
                options.set_logging(False)
                options.lock()
                self.network = ZWaveNetwork(options, log=None)
                
                
                print "------------------------------------------------------------"
                print "Init Network : "
                print "------------------------------------------------------------"
                for i in range(0,2200):
                    if self.network.state>=self.network.STATE_AWAKED:
                        print(" done")
                        break
                    else:
                        sys.stdout.write(".")
                        sys.stdout.flush()
                
                
                for node in self.network.nodes:
                    print node

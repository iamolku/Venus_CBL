import threading
import time

def importMap(id, stop):
    import mapv4

def importMQTT1(id, stop):
    import robot1

def importMQTT2(id, stop):
    import robot2

stop_threads = False
t1 = threading.Thread(target=importMap, args=(id, lambda: stop_threads))
t1.start()
t2 = threading.Thread(target=importMQTT1, args=(id, lambda: stop_threads))
t2.start()
t3 = threading.Thread(target=importMQTT2, args=(id, lambda: stop_threads))
t3.start()

try:
    while 1:
        time.sleep(.1)
except KeyboardInterrupt:
    stop_threads = True
    t1.join()
    t2.join()
    t3.join()
    print("threads successfully closed")
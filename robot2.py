import paho.mqtt.client as paho
import pyautogui as gui
import re

class init:
    ch1 = 'x'
    ch2 = 'x'
    ch3 = 'x'
    count = 0
    dir = "e"
    oldDir = "e"

class Broker:
    def __init__(
        self, 
        host : str,
        username: str,
        password: str,
        topicSubList: list[str],
        messageHandler: callable,
        reconnect: callable,
    ) -> None:
        self.client = paho.Client("1", True)
        self.client.username_pw_set(username, password)
        self.client.on_message = messageHandler
        self.client.on_connect = reconnect
        self.client.connect("mqtt.ics.ele.tue.nl", port=1883)
        try:
            # Check for a successful subscription.
            for topic in topicSubList:
                if self.client.subscribe(topic)[0] != paho.MQTT_ERR_SUCCESS: 
                    print (f"Couldn't subscribe to the topic: {topic}")
                
            self.client.on_message = messageHandler

            #Let an unexperienced user know how to kill the process 
            print("Press CTRL+C to exit...")
            self.client.loop_forever(timeout=1000)
            print("timed out")
                
        except Exception as error:
            print(error)
        finally :
            print("Disconnecting from the MQTT broker") 
            self.client.disconnect()

#Define the message handler function
def messageHandler (client, userdata, message):
    msg = str(message.payload)
    s2=re.sub("b'","",msg, 1)
    s=re.sub("'", "", s2)
    print(s)
    for x in s:
        if init.count == 0:
            init.ch1 = x
            init.count = init.count + 1
        elif init.count == 1:
            init.ch2 = x
            init.count = init.count + 1
        elif init.count == 2:
            init.ch3 = x
            init.count = init.count + 1
        elif init.count == 3:
            init.dir = x
            
    init.count = 0

    if init.oldDir != init.dir:
        if init.oldDir in ["n"]:
            if init.dir in ["e"]:
                gui.press('e')
                gui.press('e')
            elif init.dir in ["s"]:
                gui.press('e')
            elif init.dir in ["w"]:
                gui.press('e')
                gui.press('e')
                gui.press('e')
        elif init.oldDir in ["e"]:
            if init.dir in ["n"]:
                gui.press('e')
                gui.press('e')
            elif init.dir in ["w"]:
                gui.press('e')
            elif init.dir in ["s"]:
                gui.press('e')
                gui.press('e')
                gui.press('e')
        elif init.oldDir in ["s"]:
            if init.dir in ["w"]:
                gui.press('e')
                gui.press('e')
            elif init.dir in ["e"]:
                gui.press('e')
            elif init.dir in ["n"]:
                gui.press('e')
                gui.press('e')
                gui.press('e')
        elif init.oldDir in ["w"]:
            if init.dir in ["s"]:
                gui.press('e')
                gui.press('e')
            elif init.dir in ["n"]:
                gui.press('e')
            elif init.dir in ["e"]:
                gui.press('e')
                gui.press('e')
                gui.press('e')

    if init.ch1 in ["r"]:
        if init.ch2 in ["r"]:
            if init.ch3 in ["3"]:
                gui.press('c')
            elif init.ch3 in ["6"]:
                gui.press('g')
        elif init.ch2 in ["g"]:
            if init.ch3 in ["3"]:
                gui.press('v')
            elif init.ch3 in ["6"]:
                gui.press('h')
        elif init.ch2 in ["b"]:
            if init.ch3 in ["3"]:
                gui.press('b')
            elif init.ch3 in ["6"]:
                gui.press('j')
        elif init.ch2 in ["l"]:
            if init.ch3 in ["3"]:
                gui.press('n')
            elif init.ch3 in ["6"]:
                gui.press('k')
        elif init.ch2 in ["w"]:
            if init.ch3 in ["3"]:
                gui.press('m')
            elif init.ch3 in ["6"]:
                gui.press('l')
        elif init.ch2 in ["e"]:
            print("error encountered :(")
    elif init.ch1 in ["c"]:
        gui.press('f')
    elif init.ch1 in ["m"]:
        gui.press('a')
    elif init.ch1 in ["n"]:
        gui.press('w')
    
    init.oldDir = init.dir

def reconnect (client, userdata, flags, rc):
    client.subscribe("/pynqbridge/16/send")
    client.subscribe("/pynqbridge/54/send")
    print("reconnecting")

#Instantiate the Broker class with the provided arguments
broker = Broker(
    "mqtt.ics.ele.tue.nl", #MQTT broker host
    "Student103", #Username
    "aw1Aexuk", #Password
    ["/pynqbridge/16/send", "/pynqbridge/54/send"], # Topics
    messageHandler, #Message handler function
    reconnect
    )
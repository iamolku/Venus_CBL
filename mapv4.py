from tkinter import *
from tkinter import ttk
import tkinter as tk

class init:
    root = Tk()
    root.geometry()
    frm = ttk.Frame(root, padding=10)
    blank = tk.PhotoImage()

    i=900              #starting position x robot1
    j=400              #starting position y robot1
    x=700              #starting position x robot2
    y=300              #starting position y robot2
    direction1=0       #0 is right, 1 is left, 2 is up, 3 is down
    oldDir1 = 0        #"memory" for last direction
    direction2=0       #0 is right, 1 is left, 2 is up, 3 is down
    oldDir2 = 0        #"memory" for last direction

class Map:
    #a simple method that makes a "block" with completely customisable attributes
    def default(x, y, w, h, c): 
        label = tk.Label(init.root, image=init.blank, width=w, height=h, bg=c)
        label.place(x=x, y=y)

    #check the direction and make sure that we continue from the right point
    def checkDir(amount, robot):
        if robot == 1:
            if init.direction1 == 0:
                init.i = init.i + amount
            if init.direction1 == 1:
                init.i = init.i - amount
            if init.direction1 == 2:
                init.j = init.j - amount
            if init.direction1 == 3:
                init.j = init.j + amount
        else:
            if init.direction2 == 0:
                init.x = init.x + amount
            if init.direction2 == 1:
                init.x = init.x - amount
            if init.direction2 == 2:
                init.y = init.y - amount
            if init.direction2 == 3:
                init.y = init.y + amount
    
    #handles the orientation of the robot
    def robot(x, y, robot):
        if robot == 1:
            if init.direction1 == 0:
                Map.default(x, y, 20, 10, "white")
                Map.default(x, y+14, 20, 30, "black")
                Map.default(x, y+42, 20, 8, "white")
                Map.default(x+20, y, 30, 50, "black")
                init.oldDir1 = init.direction1

            if init.direction1 == 1:
                Map.default(x+30, y, 20, 10, "white")
                Map.default(x+30, y+14, 20, 30, "black")
                Map.default(x+30, y+42, 20, 8, "white")
                Map.default(x, y, 30, 50, "black")
                init.oldDir1 = init.direction1

            if init.direction1 == 2:
                Map.default(x, y+30, 10, 20, "white")
                Map.default(x+14, y+30, 30, 20, "black")
                Map.default(x+42, y+30, 8, 20, "white")
                Map.default(x, y, 50, 30, "black")
                init.oldDir1 = init.direction1
                
            if init.direction1 == 3:
                Map.default(x, y, 10, 20, "white")
                Map.default(x+14, y, 30, 20, "black")
                Map.default(x+42, y, 8, 18, "white")
                Map.default(x, y+20, 50, 30, "black")
                init.oldDir1 = init.direction1
        else:
            if init.direction2 == 0:
                Map.default(x, y, 20, 10, "white")
                Map.default(x, y+14, 20, 30, "black")
                Map.default(x, y+42, 20, 8, "white")
                Map.default(x+20, y, 30, 50, "black")
                init.oldDir2 = init.direction2

            if init.direction2 == 1:
                Map.default(x+30, y, 20, 10, "white")
                Map.default(x+30, y+14, 20, 30, "black")
                Map.default(x+30, y+42, 20, 8, "white")
                Map.default(x, y, 30, 50, "black")
                init.oldDir2 = init.direction2

            if init.direction2 == 2:
                Map.default(x, y+30, 10, 20, "white")
                Map.default(x+14, y+30, 30, 20, "black")
                Map.default(x+42, y+30, 8, 20, "white")
                Map.default(x, y, 50, 30, "black")
                init.oldDir2 = init.direction2
                
            if init.direction2 == 3:
                Map.default(x, y, 10, 20, "white")
                Map.default(x+14, y, 30, 20, "black")
                Map.default(x+42, y, 8, 18, "white")
                Map.default(x, y+20, 50, 30, "black")
                init.oldDir2 = init.direction2

    def oldRob(x, y, robot):
        if robot == 1:
            if init.oldDir1 == 0:
                Map.default(x-10, y, 10, 50, "white")
            if init.oldDir1 == 1:
                Map.default(x+50, y, 10, 50, "white")
            if init.oldDir1 == 2:
                Map.default(x, y+50, 50, 10, "white")
            if init.oldDir1 == 3:
                Map.default(x, y-10, 50, 10, "white")
        else:
            if init.oldDir2 == 0:
                Map.default(x-10, y, 10, 50, "white")
            if init.oldDir2 == 1:
                Map.default(x+50, y, 10, 50, "white")
            if init.oldDir2 == 2:
                Map.default(x, y+50, 50, 10, "white")
            if init.oldDir2 == 3:
                Map.default(x, y-10, 50, 10, "white")

    def rock6(cl, robot):
        if robot == 1:
            if init.direction1 == 0:
                Map.default(init.i+54, init.j+9, 20, 5, "white")
                Map.default(init.i+54, init.j+17, 20, 20, cl)
                Map.default(init.i+54, init.j+41, 20, 5, "white")
            if init.direction1 == 1:
                Map.default(init.i-24, init.j+9, 20, 5, "white")
                Map.default(init.i-24, init.j+17, 20, 20, cl)
                Map.default(init.i-24, init.j+41, 20, 5, "white")
            if init.direction1 == 2:
                Map.default(init.i+9, init.j-24, 5, 20, "white")
                Map.default(init.i+17, init.j-24, 20, 20, cl)
                Map.default(init.i+41, init.j-24, 5, 20, "white")
            if init.direction1 == 3:
                Map.default(init.i+9, init.j+54, 5, 20, "white")
                Map.default(init.i+17, init.j+54, 20, 20, cl)
                Map.default(init.i+41, init.j+54, 5, 20, "white")
        else:
            if init.direction2 == 0:
                Map.default(init.x+54, init.y+9, 20, 5, "white")
                Map.default(init.x+54, init.y+17, 20, 20, cl)
                Map.default(init.x+54, init.y+41, 20, 5, "white")
            if init.direction2 == 1:
                Map.default(init.x-24, init.y+9, 20, 5, "white")
                Map.default(init.x-24, init.y+17, 20, 20, cl)
                Map.default(init.x-24, init.y+41, 20, 5, "white")
            if init.direction2 == 2:
                Map.default(init.x+9, init.y-24, 5, 20, "white")
                Map.default(init.x+17, init.y-24, 20, 20, cl)
                Map.default(init.x+41, init.y-24, 5, 20, "white")
            if init.direction2 == 3:
                Map.default(init.x+9, init.y+54, 5, 20, "white")
                Map.default(init.x+17, init.y+54, 20, 20, cl)
                Map.default(init.x+41, init.y+54, 5, 20, "white")
    
    def rock(cl, robot):
        if robot == 1:
            if init.direction1 == 0:
                Map.default(init.i+54, init.j+10, 10, 10, "white")
                Map.default(init.i+54, init.j+22, 10, 10, cl)
                Map.default(init.i+54, init.j+34, 10, 10, "white")
            if init.direction1 == 1:
                Map.default(init.i-14, init.j+10, 10, 10, "white")
                Map.default(init.i-14, init.j+22, 10, 10, cl)
                Map.default(init.i-14, init.j+34, 10, 10, "white")
            if init.direction1 == 2:
                Map.default(init.i+10, init.j-14, 10, 10, "white")
                Map.default(init.i+22, init.j-14, 10, 10, cl)
                Map.default(init.i+34, init.j-14, 10, 10, "white")
            if init.direction1 == 3:
                Map.default(init.i+10, init.j+54, 10, 10, "white")
                Map.default(init.i+22, init.j+54, 10, 10, cl)
                Map.default(init.i+34, init.j+54, 10, 10, "white")
        else:
            if init.direction2 == 0:
                Map.default(init.x+54, init.y+10, 10, 10, "white")
                Map.default(init.x+54, init.y+22, 10, 10, cl)
                Map.default(init.x+54, init.y+34, 10, 10, "white")
            if init.direction2 == 1:
                Map.default(init.x-14, init.y+10, 10, 10, "white")
                Map.default(init.x-14, init.y+22, 10, 10, cl)
                Map.default(init.x-14, init.y+34, 10, 10, "white")
            if init.direction2 == 2:
                Map.default(init.x+10, init.y-14, 10, 10, "white")
                Map.default(init.x+22, init.y-14, 10, 10, cl)
                Map.default(init.x+34, init.y-14, 10, 10, "white")
            if init.direction2 == 3:
                Map.default(init.x+10, init.y+54, 10, 10, "white")
                Map.default(init.x+22, init.y+54, 10, 10, cl)
                Map.default(init.x+34, init.y+54, 10, 10, "white")

    def hill(clr, robot):
        if robot == 1:
            if init.direction1 == 0:
                Map.default(init.i+54, init.j+10, 10, 30, clr)
            if init.direction1 == 1:
                Map.default(init.i-14, init.j+10, 10, 30, clr)
            if init.direction1 == 2:
                Map.default(init.i+10, init.j-14, 30, 10, clr)
            if init.direction1 == 3:
                Map.default(init.i+10, init.j+54, 30, 10, clr)
        else:
            if init.direction2 == 0:
                Map.default(init.x+54, init.y+10, 10, 30, clr)
            if init.direction2 == 1:
                Map.default(init.x-14, init.y+10, 10, 30, clr)
            if init.direction2 == 2:
                Map.default(init.x+10, init.y-14, 30, 10, clr)
            if init.direction2 == 3:
                Map.default(init.x+10, init.y+54, 30, 10, clr)

class Robot1:
    def changeDirection(event):
        init.direction1 = (init.direction1 + 1)%4
        if init.direction1 == 0:
            Map.robot(init.i, init.j, 1)
        if init.direction1 == 1:
            Map.robot(init.i, init.j, 1)
        if init.direction1 == 2:
            Map.robot(init.i, init.j, 1)
        if init.direction1 == 3:
            Map.robot(init.i, init.j, 1)
        
    def rockr(event):
        Map.rock("red", 1)

    def rockg(event):
        Map.rock("green", 1)

    def rockbl(event):
        Map.rock("blue", 1)

    def rockba(event):
        Map.rock("black", 1)

    def rockw(event):
        Map.rock("#e6e6e6", 1)

    def cliff(event):
        if init.direction1 == 0:
            Map.default(init.i+54, init.j+10, 10, 30, "black")
        if init.direction1 == 1:
            Map.default(init.i-14, init.j+10, 10, 30, "black")
        if init.direction1 == 2:
            Map.default(init.i+10, init.j-14, 30, 10, "black")
        if init.direction1 == 3:
            Map.default(init.i+10, init.j+54, 30, 10, "black")

    def robot(event):
        Map.checkDir(10, 1)
        Map.oldRob(init.i, init.j, 1)
        Map.robot(init.i, init.j, 1)
        print(init.i, init.j)

    def rock6r(event):
        Map.rock6("red", 1)

    def rock6g(event):
        Map.rock6("green", 1)
    
    def rock6bl(event):
        Map.rock6("blue", 1)

    def rock6ba(event):
        Map.rock6("black", 1)

    def rock6w(event):
        Map.rock6("#e6e6e6", 1)

    def hill(event):
        Map.hill("#c19a6c", 1)

class Robot2:
    def changeDirection(event):
        init.direction2 = (init.direction2 + 1)%4
        if init.direction2 == 0:
            Map.robot(init.x, init.y, 2)
        if init.direction2 == 1:
            Map.robot(init.x, init.y, 2)
        if init.direction2 == 2:
            Map.robot(init.x, init.y, 2)
        if init.direction2 == 3:
            Map.robot(init.x, init.y, 2)
        
    def rockr(event):
        Map.rock("red", 2)

    def rockg(event):
        Map.rock("green", 2)

    def rockbl(event):
        Map.rock("blue", 2)

    def rockba(event):
        Map.rock("black", 2)

    def rockw(event):
        Map.rock("#e6e6e6", 2)

    def cliff(event):
        if init.direction2 == 0:
            Map.default(init.x+54, init.y+10, 10, 30, "black")
        if init.direction2 == 1:
            Map.default(init.x-14, init.y+10, 10, 30, "black")
        if init.direction2 == 2:
            Map.default(init.x+10, init.y-14, 30, 10, "black")
        if init.direction2 == 3:
            Map.default(init.x+10, init.y+54, 30, 10, "black")

    def robot(event):
        Map.checkDir(10, 2)
        Map.oldRob(init.x, init.y, 2)
        Map.robot(init.x, init.y, 2)

    def rock6r(event):
        Map.rock6("red", 2)

    def rock6g(event):
        Map.rock6("green", 2)
    
    def rock6bl(event):
        Map.rock6("blue", 2)

    def rock6ba(event):
        Map.rock6("black", 2)

    def rock6w(event):
        Map.rock6("#e6e6e6", 2)

    def hill(event):
        Map.hill("#c19a6c", 2)

class Main:
    label = tk.Label(init.root, text="Status robot 1: online", bg="#e6ffff")
    label.place(x=5, y=5)
    label2 = tk.Label(init.root, text="Status robot 2: online", bg="#e6ffff")
    label2.place(x=5, y=25)

    init.root.bind('<q>', Robot1.robot)
    init.root.bind('<r>', Robot1.changeDirection)
    init.root.bind('<d>', Robot1.cliff)
    init.root.bind('<t>', Robot1.rockr)
    init.root.bind('<y>', Robot1.rockg)
    init.root.bind('<u>', Robot1.rockbl)
    init.root.bind('<i>', Robot1.rockba)
    init.root.bind('<o>', Robot1.rockw)
    init.root.bind('<6>', Robot1.rock6r)
    init.root.bind('<7>', Robot1.rock6g)
    init.root.bind('<8>', Robot1.rock6bl)
    init.root.bind('<9>', Robot1.rock6ba)
    init.root.bind('<0>', Robot1.rock6w)
    init.root.bind('<p>', Robot1.hill)

    init.root.bind('<w>', Robot2.robot)
    init.root.bind('<e>', Robot2.changeDirection)
    init.root.bind('<f>', Robot2.cliff)
    init.root.bind('<c>', Robot2.rockr)
    init.root.bind('<v>', Robot2.rockg)
    init.root.bind('<b>', Robot2.rockbl)
    init.root.bind('<n>', Robot2.rockba)
    init.root.bind('<m>', Robot2.rockw)
    init.root.bind('<g>', Robot2.rock6r)
    init.root.bind('<h>', Robot2.rock6g)
    init.root.bind('<j>', Robot2.rock6bl)
    init.root.bind('<k>', Robot2.rock6ba)
    init.root.bind('<l>', Robot2.rock6w)
    init.root.bind('<a>', Robot2.hill)

    init.root.mainloop()
import pyqtgraph as pg
from PySide6.QtCore import QTimer
from PySide6.QtWidgets import QApplication, QPushButton, QGridLayout, QWidget

import time

import numpy as np
import sys
####################################################
#                                                  #
#               Zone de config                     #
#                                                  #
####################################################
#voir fichier Configuration.py
from Configuration import *

####################################################
#                                                  #
#               FIN Zone de config                 #
#                                                  #
####################################################
from Data import Data
from Page import *

class Bouton(QWidget):
    def __init__(self,text_,win,parent=None):
        super().__init__(parent)
        self.affiche = False
        self.windows = win
        self.btn = QPushButton(text=text_, parent=self)
        self.btn.setFixedSize(100, 60)
        self.btn.clicked.connect(self.click)
        self.update()


    def click(self):
        if(self.affiche):
            self.affiche = False
            self.windows.hide()
        else:
            self.affiche = True
            self.windows.show()
    
    def update(self):
        if(self.windows.isHidden()):
            self.affiche = False
        if(self.affiche):
            self.btn.setStyleSheet("background-color : green")
        else:
            self.btn.setStyleSheet("background-color : white")

class Window(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)

        #initialisation variable
        self.data = Data()

        self.lastTimeConnect = time.time()
        
        self.id = 0

        self.msg_GPS = " "
        self.msg_color_GPS = "red"

        self.penJaune = pg.mkPen(color=(255, 255, 0))
        self.penCyan = pg.mkPen(color=(0, 255, 255))


        #initialisation des composant
        self.init_windowns()
        self.init_button()
        
        #boucle exécution de la fenetre
        self.timer = QTimer()
        self.timer.setInterval(50)
        self.timer.timeout.connect(self.loop)
        self.timer.start()

    def init_windowns(self):
        self.temperature = PageUnGraph("Température","°C")
        self.pression = PageUnGraph("Pression","hPa")
        self.altitudeGPS = PageUnGraph("Altitude GPS","m")
        self.altitude = PageUnGraph("Altitude","m")

        self.winADC1 = PageUnGraph.PageAdc(self.data.adc1,"ADC 1")
        self.winADC2 = PageUnGraph.PageAdc(self.data.adc2,"ADC 2")

        self.qualiteConnection = PageTextConnection("Qualite Connection")

        self.winNO2 = PageDoubleVal("NO2")
        self.winOX = PageDoubleVal("OX")
        self.winNO = PageDoubleVal("NO")
        self.winCO = PageDoubleVal("CO")
        self.winSO2 = PageDoubleVal("SO2")

    def init_button(self):
        self.temperature_BT = Bouton("Température",self.temperature.win)
        self.altitude_BT = Bouton("Altitude",self.altitude.win)
        self.adc1_gaz1_BT = Bouton("ADC 1\n" + self.data.adc1.gaz1().typeGaz,self.winADC1.gaz1.win)
        self.adc1_gaz2_BT = Bouton("ADC 1\n" + self.data.adc1.gaz2().typeGaz,self.winADC1.gaz2.win)
        self.adc1_gaz3_BT = Bouton("ADC 1\n" + self.data.adc1.gaz3().typeGaz,self.winADC1.gaz3.win)
        self.adc1_gaz4_BT = Bouton("ADC 1\n" + self.data.adc1.gaz4().typeGaz,self.winADC1.gaz4.win)

        self.pression_BT = Bouton("Pression",self.pression.win)
        self.qualiteConnection_BT = Bouton("Connection",self.qualiteConnection.win)
        self.adc2_gaz1_BT = Bouton("ADC 2\n" + self.data.adc2.gaz1().typeGaz, self.winADC2.gaz1.win)
        self.adc2_gaz2_BT = Bouton("ADC 2\n" + self.data.adc2.gaz2().typeGaz, self.winADC2.gaz2.win)
        self.adc2_gaz3_BT = Bouton("ADC 2\n" + self.data.adc2.gaz3().typeGaz, self.winADC2.gaz3.win)
        self.adc2_gaz4_BT = Bouton("ADC 2\n" + self.data.adc2.gaz4().typeGaz, self.winADC2.gaz4.win)

        self.altitudeGPS_BT = Bouton("Altitude GPS",self.altitudeGPS.win)
        self.no2_BT = Bouton(" NO2 ",self.winNO2.win)
        self.ox_BT = Bouton(" OX ",self.winOX.win)
        self.no_BT = Bouton(" NO ",self.winNO.win)
        self.co_BT = Bouton(" CO ",self.winCO.win)
        self.so2_BT = Bouton(" SO2 ",self.winSO2.win)
        layout = QGridLayout()

        layout.addWidget(self.temperature_BT.btn,0,0)
        layout.addWidget(self.altitude_BT.btn,1,0)
        layout.addWidget(self.adc1_gaz1_BT.btn,2,0)
        layout.addWidget(self.adc1_gaz2_BT.btn,3,0)
        layout.addWidget(self.adc1_gaz3_BT.btn,4,0)
        layout.addWidget(self.adc1_gaz4_BT.btn,5,0)
        
        layout.addWidget(self.pression_BT.btn,0,1)
        layout.addWidget(self.qualiteConnection_BT.btn,1,1)
        layout.addWidget(self.adc2_gaz1_BT.btn,2,1)
        layout.addWidget(self.adc2_gaz2_BT.btn,3,1)
        layout.addWidget(self.adc2_gaz3_BT.btn,4,1)
        layout.addWidget(self.adc2_gaz4_BT.btn,5,1)

        layout.addWidget(self.altitudeGPS_BT.btn,0,2)
        layout.addWidget(self.no2_BT.btn,2,2)
        layout.addWidget(self.ox_BT.btn,3,2)
        layout.addWidget(self.no_BT.btn,4,2)
        layout.addWidget(self.co_BT.btn,5,2)
        layout.addWidget(self.so2_BT.btn,6,2)
        
        self.setLayout(layout)
        self.setWindowTitle("IHM MicroMega")

    def update_button(self):
        self.temperature_BT.update()
        self.altitude_BT.update()
        self.adc1_gaz1_BT.update()
        self.adc1_gaz2_BT.update()
        self.adc1_gaz3_BT.update()
        self.adc1_gaz4_BT.update()

        self.pression_BT.update()
        self.qualiteConnection_BT.update()
        self.adc2_gaz1_BT.update()
        self.adc2_gaz2_BT.update()
        self.adc2_gaz3_BT.update()
        self.adc2_gaz4_BT.update()

        self.altitudeGPS_BT.update()
        self.no2_BT.update()
        self.ox_BT.update()
        self.no_BT.update()
        self.co_BT.update()
        self.so2_BT.update()
        

    def update_value(self):
        newData = False
        newData= self.data.update_data()
        # else:
        #     self.msg_timeReception= "temps depuit <br />la dernière reception "+"<br />" +"<font color=\"red\"> "+str(self.tempsEcoule)+" s </font>"+"<br />"

        self.tempsEcoule = float("{:.2f}".format(time.time() - self.lastTimeConnect))



        if(newData == True):
            self.lastTimeConnect = time.time()
            self.id += 1
            #print(self.id)

            self.temperature.update_msg(self.data.temperature)
            self.pression.update_msg(self.data.pression)
            self.altitude.update_msg(self.data.altitude)

            self.altitudeGPS.update_msg(self.data.altitudeGPS)

            self.winADC1.update_msg(self.data.adc1)
            self.winADC2.update_msg(self.data.adc1)

            self.winNO2.update_msg(self.data.adc1.gazNO2().val_calc, self.data.adc2.gazNO2().val_calc)
            self.winOX.update_msg(self.data.adc1.gazOX().val_calc, self.data.adc2.gazOX().val_calc)
            self.winNO.update_msg(self.data.adc1.gazNO().val_calc, self.data.adc2.gazNO().val_calc)
            self.winCO.update_msg(self.data.adc1.gazCO().val_calc, self.data.adc2.gazCO().val_calc)
            self.winSO2.update_msg(self.data.adc1.gazSO2().val_calc, self.data.adc2.gazSO2().val_calc)

            match self.data.qualiteGPS :
                case '3':
                    self.msg_GPS= "BON"
                    self.msg_color_GPS = "green"
                case '2':
                    self.msg_GPS= " OK (UTC + ALT)"
                    self.msg_color_GPS = "orange"
                case '1':
                    self.msg_GPS= "MOYEN (UTC)"
                    self.msg_color_GPS = "orange"
                case '0':
                    self.msg_GPS= "MAUVAIS"
                    self.msg_color_GPS = "red"
        
        colorTime = "red"
        if(self.tempsEcoule < 1.5):
            colorTime= "green"
        elif(self.tempsEcoule < 3.5):
            colorTime="orange"
        self.qualiteConnection.update_msg(self.msg_GPS,str(self.tempsEcoule),self.msg_color_GPS,colorTime)

    def update_plot_data(self):
        self.temperature.update(self.data.x, self.data.tabTemperature, pen = self.penJaune)
        self.temperature.graph.enableAutoRange(axis ="y")
        #setXRange(int(self.data.x[-1] - 20), int(self.data.x[-1]),update=False)
        #setVisible(x=5)#setXRange(int(self.data.x[-1] - 20), int(self.data.x[-1]))
        self.pression.update(self.data.x, self.data.tabPression, pen = self.penJaune)

        self.altitude.update(self.data.x, self.data.tabAltitude, pen = self.penJaune)
        
        self.altitudeGPS.update(self.data.x, self.data.tabAltitudeGPS, pen = self.penJaune)

        self.qualiteConnection.update()
        self.winADC1.update(self.data.x, self.data.adc1, pen = self.penJaune)
        self.winADC2.update(self.data.x, self.data.adc1, pen = self.penCyan)

        self.winNO2.update(self.data.x, self.data.adc1.tabGazNO2(), self.data.adc2.tabGazNO2(), self.penJaune, self.penCyan)
        self.winOX.update(self.data.x, self.data.adc1.tabGazOX(), self.data.adc2.tabGazOX(), self.penJaune, self.penCyan)
        self.winNO.update(self.data.x, self.data.adc1.tabGazNO(), self.data.adc2.tabGazNO(), self.penJaune, self.penCyan)
        self.winCO.update(self.data.x, self.data.adc1.tabGazCO(), self.data.adc2.tabGazCO(), self.penJaune, self.penCyan)
        self.winSO2.update(self.data.x, self.data.adc1.tabGazSO2(), self.data.adc2.tabGazSO2(), self.penJaune, self.penCyan)
    
    def loop(self):
        self.update_value()
        self.update_button()
        self.update_plot_data()
        if(self.isHidden()):
            sys.exit(app.exec())

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = Window()
    window.show()
    sys.exit(app.exec())




    
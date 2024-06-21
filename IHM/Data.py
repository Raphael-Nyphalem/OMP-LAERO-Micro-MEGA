import serial
import numpy as np
from Configuration import * 

class Data():
    """
    \brief Classe principale pour la gestion des données.
    """
    def __init__(self) -> None:

        """
        \brief Constructeur de la classe Data.
        """
        #init value
        self.timeArduino = int(0)
        self.qualiteGPS = '0'
        self.temperature = 0
        self.pression = 0
        self.altitude = 0.0
        self.altitudeGPS = "XXXXX"

        self.lectureData = self.LectureCom()

        #init adc
        self.adc1 = self.Capteur(configADC1)
        self.adc2 = self.Capteur(configADC2)

        test = False
        while(test == False):
            test= self._update_lecture()
        print("On est connecté, ")


        #Init tableaux
        self.comptReduction = 0 #on compte le nombre de 
        self.x = np.array([0,1])
        self.tabTemperature = np.array([self.temperature,self.temperature])
        self.tabPression = np.array([self.pression,self.pression])
        self.tabAltitude = np.array([self.altitude,self.altitude])
        if(self.altitudeGPS[0]=='X'):
            self.tabAltitudeGPS = np.array([ALTITUDE_GRAPH_DEFAUT,ALTITUDE_GRAPH_DEFAUT])
        else:    
            self.tabAltitudeGPS = np.array([float(self.altitudeGPS),float(self.altitudeGPS)])

        self.adc1.init_tab()
        self.adc2.init_tab()
    
    class Capteur():
        """
        \brief Classe pour la gestion des capteurs.
        """
        def __init__(self,configADC):
            """
            \brief Constructeur de la classe Capteur.
            param configADC Configuration ADC spécifique au capteur alphasense.
            """
            self._gaz1 = self.GazData("gaz1",configADC)
            self._gaz2 = self.GazData("gaz2",configADC)
            self._gaz3 = self.GazData("gaz3",configADC)
            self._gaz4 = self.GazData("gaz4",configADC)

            self._gazNone = self.GazData("None",configADC)

            self._gazNO2 = None
            self._gazOX = None
            self._gazNO = None
            self._gazCO = None
            self._gazSO2 = None

            self.existanceGazNO2 = False
            self.existanceGazOX = False
            self.existanceGazNO = False
            self.existanceGazCO = False
            self.existanceGazSO2 = False

            self._tabGazNO2 = None
            self._tabGazOX = None
            self._tabGazNO = None
            self._tabGazCO = None
            self._tabGazSO2 = None

            self._foundGazType()
        
        def init_tab(self):
            """
            \brief Initialise les tableaux de valeurs des gaz.
            \note doit être initialiser apres que les variables soit déclarées
            """
            self._tabGaz1 = np.array([self._gaz1.val_calc,self._gaz1.val_calc])
            self._tabGaz2 = np.array([self._gaz2.val_calc,self._gaz2.val_calc])
            self._tabGaz3 = np.array([self._gaz3.val_calc,self._gaz3.val_calc])
            self._tabGaz4 = np.array([self._gaz4.val_calc,self._gaz4.val_calc])
            self._tabGazNone = np.array([NONE_VALUE_GAZ,NONE_VALUE_GAZ])
        
        def gaz1(self):
            """
            \brief Retourne la données du gaz 1.
            \return Données du gaz 1.
            """
            return self._gaz1      
        def gaz2(self):
            """
            \brief Retourne la données du gaz 2.
            \return Données du gaz 2.
            """
            return self._gaz2     
        def gaz3(self):
            """
            \brief Retourne la données du gaz 3.
            \return Données du gaz 3.
            """
            return self._gaz3      
        def gaz4(self):
            """
            \brief Retourne la données du gaz 4.
            \return Données du gaz 4.
            """
            return self._gaz4
        
        def tabGaz1(self):
            return self._tabGaz1      
        def tabGaz2(self):
            return self._tabGaz2     
        def tabGaz3(self):
            return self._tabGaz3    
        def tabGaz4(self):
            return self._tabGaz4
        
        def gazNO2(self):
            if(self.existanceGazNO2):
                return (getattr(self, self._gazNO2)())
            else:
                return (self._gazNone)
            
        def gazOX(self):
            if(self.existanceGazOX):
                return (getattr(self, self._gazOX)())
            else:
                return (self._gazNone)
            
        def gazNO(self):
            if(self.existanceGazNO):
                return (getattr(self, self._gazNO)())
            else:
                return (self._gazNone)
            
        def gazCO(self):
            if(self.existanceGazCO):
                return (getattr(self, self._gazCO)())
            else:
                return (self._gazNone)
        def gazSO2(self):
            if(self.existanceGazSO2):
                return (getattr(self, self._gazSO2)())
            else:
                return (self._gazNone)
            

        
        def tabGazNO2(self):
            if(self.existanceGazNO2):
                return (getattr(self, self._tabGazNO2)())
            else:
                return (self._tabGazNone)
            
        def tabGazOX(self):
            if(self.existanceGazOX):
                return (getattr(self, self._tabGazOX)())
            else:
                return (self._tabGazNone)
            
        def tabGazNO(self):
            if(self.existanceGazNO):
                return (getattr(self, self._tabGazNO)())
            else:
                return (self._tabGazNone)
            
        def tabGazCO(self):
            if(self.existanceGazCO):
                return (getattr(self, self._tabGazCO)())
            else:
                return (self._tabGazNone)

        def tabGazSO2(self):
            if(self.existanceGazSO2):
                return (getattr(self, self._tabGazSO2)())
            else:
                return (self._tabGazNone)
            

        def _foundGazType(self):
            for gaz in [self._gaz1,self._gaz2,self._gaz3,self._gaz4]:
                if(gaz.typeGaz == "NO2"):
                    self._gazNO2 = gaz.gazNb
                    self.existanceGazNO2 = True 
                    self._tabGazNO2 = "tabG" + gaz.gazNb[1:]
                if(gaz.typeGaz == "OX"):
                    self._gazOX = gaz.gazNb
                    self.existanceGazOX = True 
                    self._tabGazOX = "tabG" + gaz.gazNb[1:]
                if(gaz.typeGaz == "NO"):
                    self._gazNO = gaz.gazNb
                    self.existanceGazNO = True 
                    self._tabGazNO = "tabG" + gaz.gazNb[1:]
                if(gaz.typeGaz == "CO"):
                    self._gazCO = gaz.gazNb
                    self.existanceGazCO = True 
                    self._tabGazCO = "tabG" + gaz.gazNb[1:]
                if(gaz.typeGaz == "SO2"):
                    self._gazSO2 = gaz.gazNb
                    self.existanceGazSO2 = True 
                    self._tabGazSO2 = "tabG" + gaz.gazNb[1:]
                
        def addValueTabs(self):
            self._tabGaz1 = np.append(self._tabGaz1,self._gaz1.val_calc)
            self._tabGaz2 = np.append(self._tabGaz2,self._gaz2.val_calc)
            self._tabGaz3 = np.append(self._tabGaz3,self._gaz3.val_calc)
            self._tabGaz4 = np.append(self._tabGaz4,self._gaz4.val_calc)
            self._tabGazNone = np.append(self._tabGazNone,NONE_VALUE_GAZ)

        def reduction(self):
            self._tabGaz1 = Data._reduction(self,self._tabGaz1)
            self._tabGaz2 = Data._reduction(self,self._tabGaz2)
            self._tabGaz3 = Data._reduction(self,self._tabGaz3)
            self._tabGaz4 = Data._reduction(self,self._tabGaz4)
            self._tabGazNone = Data._reduction(self,self._tabGazNone)

        class GazData():
            def __init__(self, gazNb,config):
                self.gazNb = gazNb
                if(gazNb != "None"):
                    self.typeGaz = id_to_name[config[self.gazNb]["type"]]
                    self.value(config)
                else:
                    self.typeGaz ="None"
                    self.ref = "None"
                    self.we_zero = "None"
                    self.ae_zero = "None"
                    self.sensitivity = "None"
                
            
            def value(self,config):
                self.ref = config[self.gazNb]["ref"]
                self.we_zero = config[self.gazNb]["WE_zero"]
                self.ae_zero = config[self.gazNb]["AE_zero" ]
                self.sensitivity =config[self.gazNb]["Sensitivity"]
                
            def calcul(self, work, aux):
                self.val_calc = float("{:.1f}".format((((work*(VREF / 4096)- self.we_zero )-(aux*(VREF / 4096)- self.ae_zero ))/self.sensitivity))) #calcul applique au mots de l'adc

    class LectureCom():
        def __init__(self):
            self.tableau1Lu = []
            self.tableau2Lu = []
            self.flagtableau1Lu = False
            self.flagtableau2Lu = False
            self.nom = 'COM3'
            self.affiche_erreur0 = True
            # ports = list(serial.tools.list_ports.comports())
            # for p in ports:
            #     if 'Arduino' in p.description :
            #         mData = serial.Serial(p.device,115200)
            # print(mData.is_open) # Affiche et vérifie que le port est ouvert
            # print(mData.name) # Affiche le nom du port
            self._connectionSerial()
        
        def _connectionSerial(self):
            while(True):
                try:
                    self._Data = serial.Serial(self.nom, 115200, timeout=5)
                    self.affiche_erreur0 = True
                    break
                except:
                    if(self.affiche_erreur0):
                        print("Erreur Branchement arduino, Verifier la connection sur du port " + self.nom)
                        self.affiche_erreur0 = False
            
        def lectureCom(self):
            lectureEffectuer = False
            self._recupTableauLu()
            if( self.flagtableau1Lu == True  ): #and self.flagtableau2Lu == True
                self.flagtableau1Lu = False
                self.flagtableau2Lu = False
                lectureEffectuer = True
            
            
            return(lectureEffectuer)
        
        def _recupTableauLu(self):
            inWaiting = False
            try:
                inWaiting = self._Data.inWaiting()
            except:
                self._connectionSerial()
                
            if(inWaiting):
                try:
                    line = str(self._Data.readline(), encoding='utf-8')
                except:
                    line = "fail lecture"
                print(line)
                if(line[0]=="#"):
                    line.replace('\00','')
                    line = line.split("#")[1]
                    line = line.split("!")[0]
                    tableauLu = line.split(":")
                    self._saveTableauFonctionIndice(tableauLu)

        def _saveTableauFonctionIndice(self,tableauLu):
            indice = int(tableauLu[0].replace('\00',''))
            if (indice == 1):
                self.tableau1Lu = tableauLu
                self.flagtableau1Lu = True
            if (indice == 2):
                self.tableau2Lu = tableauLu
                self.flagtableau2Lu = True
    
    def _update_lecture(self):
        lectureEffectuer = False
        if(self.lectureData.lectureCom()==True):
            self._splitDataTab(self.lectureData.tableau1Lu,self.lectureData.tableau2Lu)
            lectureEffectuer = True
        return(lectureEffectuer)
    
    def _splitDataTab(self,tableau1Lu,tableau2Lu):
        self.timeArduino = int(tableau1Lu[1].replace('\00',''))
        self.qualiteGPS=tableau1Lu[2]
        self.temperature=float(tableau1Lu[3].replace('\00',''))
        
        self.pression = float(tableau1Lu[4].replace('\00',''))

        self.altitude = float("{:.2f}".format(44330.0 * (1.0 - pow( self.pression / SEALEVEL_HPA, 1/5.255))))

        self.altitudeGPS = tableau1Lu[5].replace('\00','')
        _adc1_gaz1_work = int(tableau1Lu[6].replace('\00',''))
        _adc1_gaz1_aux = int(tableau1Lu[7].replace('\00',''))
        _adc1_gaz2_work = int(tableau1Lu[8].replace('\00',''))
        _adc1_gaz2_aux = int(tableau1Lu[9].replace('\00',''))

        _adc1_gaz3_work = int(tableau1Lu[10].replace('\00',''))
        _adc1_gaz3_aux = int(tableau1Lu[11].replace('\00',''))
        _adc1_gaz4_work = int(tableau1Lu[12].replace('\00',''))
        _adc1_gaz4_aux = int(tableau1Lu[13].replace('\00',''))
        _adc2_gaz1_work = int(tableau1Lu[14].replace('\00',''))
        _adc2_gaz1_aux = int(tableau1Lu[15].replace('\00',''))
        _adc2_gaz2_work = int(tableau1Lu[16].replace('\00',''))
        _adc2_gaz2_aux = int(tableau1Lu[17].replace('\00',''))
        _adc2_gaz3_work = int(tableau1Lu[18].replace('\00',''))
        _adc2_gaz3_aux = int(tableau1Lu[19].replace('\00',''))
        _adc2_gaz4_work = int(tableau1Lu[20].replace('\00',''))
        _adc2_gaz4_aux = int(tableau1Lu[21].replace('\00',''))

        self.adc1._gaz1.calcul( _adc1_gaz1_work, _adc1_gaz1_aux )
        self.adc1._gaz2.calcul( _adc1_gaz2_work, _adc1_gaz2_aux )
        self.adc1._gaz3.calcul( _adc1_gaz3_work, _adc1_gaz3_aux )
        self.adc1._gaz4.calcul( _adc1_gaz4_work, _adc1_gaz4_aux )
        self.adc1._gazNone.val_calc = NONE_VALUE_GAZ

        self.adc2._gaz1.calcul( _adc2_gaz1_work, _adc2_gaz1_aux )
        self.adc2._gaz2.calcul( _adc2_gaz2_work, _adc2_gaz2_aux )
        self.adc2._gaz3.calcul( _adc2_gaz3_work, _adc2_gaz3_aux )
        self.adc2._gaz4.calcul( _adc2_gaz4_work, _adc2_gaz4_aux )
        self.adc2._gazNone.val_calc = NONE_VALUE_GAZ

    def _update_reduction(self):
        self.x = self._reductionX(self.x)
        self.tabTemperature = self._reduction(self.tabTemperature)
        self.tabPression = self._reduction(self.tabPression)
        self.tabAltitude = self._reduction(self.tabAltitude)

        self.adc1.reduction()
        self.adc2.reduction()

        self.tabAltitudeGPS = self._reduction(self.tabAltitudeGPS)

        self.compt = len(self.x)
    
    def _reduction(self,tab):
        tab1 = tab[:NB_VALUE_REDUC]
        tab2 = tab[NB_VALUE_REDUC:]

        tab = np.array([])
        
        for i in range(int(NB_VALUE_REDUC/2)):
            tab = np.append(tab, ((tab1[i*2]+tab1[i*2+1])/2) )
        tab=np.append(tab,tab2)
        return tab
    
    def _reductionX(self,tab):
        tab1 = tab[:NB_VALUE_REDUC]
        tab2 = tab[NB_VALUE_REDUC:]

        tab = np.array([])
        
        for i in range(int(NB_VALUE_REDUC/2)):
            tab = np.append(tab, tab1[i*2] )
        tab=np.append(tab,tab2)
        return tab

    def update_data(self):
            lectureEffectuer = False
            if(self._update_lecture()==True):
                lectureEffectuer = True
                self.comptReduction += 1
                self.x = np.append(self.x,(self.x[-1] + 1))
                self.tabTemperature = np.append( self.tabTemperature, self.temperature)
                self.tabPression = np.append( self.tabPression, self.pression)
                self.tabAltitude = np.append( self.tabAltitude, self.altitude)
                
                if(self.altitudeGPS[0]=='X'):
                    self.tabAltitudeGPS = np.append( self.tabAltitudeGPS, ALTITUDE_GRAPH_DEFAUT)
                else:    
                    self.tabAltitudeGPS = np.append( self.tabAltitudeGPS, float(self.altitudeGPS))
                self.adc1.addValueTabs()
                self.adc2.addValueTabs()

                if (self.comptReduction >= NB_VALUE_TOT ):
                    self._update_reduction()
                    self.comptReduction = len(self.x)
            return(lectureEffectuer)
    


if __name__ == "__main__":
    data = Data()
    print(data.adc1._tabGazNO)
    print(data.adc1.tabGazNO())
    print(data.adc1.tabGazOX())
    print(data.adc1.tabGazSO2())
    print(data.adc1.tabGazCO())
    print(data.adc1.tabGaz1())
    
    data.x = np.arange(1500)
    data.altitudeGPS = np.arange(1500)

    data.x= data._reductionX(data.x)
    data.altitudeGPS = data._reduction(data.altitudeGPS)

    print(len(data.x))
    print(len(data.altitudeGPS))
    # print(data.adc1.gaz2() == data.adc1.gazNO()())

    # print(data.adc1._tabGazNO)


    # print(data.adc1.tabGaz1 )
    
    # print(data.adc1.gaz1().typeGaz)
    # print(data.adc1.tabGazNO2)
    # print(data.adc1.tabGaz3, data.adc1.tabGazSO)

    # print("avant",data.adc1._tabGaz2)
    # print("avant",data.tabTemperature)
    # test = False
    # while(not(test)):
    #     test=data.update_data()
    # print("apres",data.adc1._tabGaz2)
    # print("apres",data.tabTemperature)
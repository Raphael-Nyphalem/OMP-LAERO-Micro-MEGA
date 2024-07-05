"""

"""
import serial
import numpy as np
from Configuration import * 

class Data():
    """
    Classe principale pour la gestion des données du capteur connecté.
    
    :param int timeArduino: Temps fourni par l'Arduino.
    :param str qualiteGPS: Qualité du signal GPS.
    :param float temperature: Température mesurée.
    :param float pression: Pression mesurée.
    :param float altitude: Altitude calculée.
    :param str altitudeGPS: Altitude fournie par le GPS.
    :param LectureCom lectureData: Instance pour la lecture des données.
    :param Capteur adc1: Instance du capteur ADC1.
    :param Capteur adc2: Instance du capteur ADC2.
    :param int comptReduction: Compteur de réduction des données.
    :param np.array x: Tableau des valeurs de l'axe X.
    :param np.array tabTemperature: Tableau des valeurs de température.
    :param np.array tabPression: Tableau des valeurs de pression.
    :param np.array tabAltitude: Tableau des valeurs d'altitude.
    :param np.array tabAltitudeGPS: Tableau des valeurs d'altitude GPS.
    
    """
    def __init__(self) -> None:

        """
        Constructeur de la classe Data. Initialise les attributs et effectue la connexion.
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
    
    def _update_lecture(self):
        """
        Met à jour les lectures des données.

        return:
            bool: True si la mise à jour est effectuée, sinon False.
        """
        lectureEffectuer = False
        if self.lectureData.lectureCom():
            self._splitDataTab(self.lectureData.tableau1Lu, self.lectureData.tableau2Lu)
            lectureEffectuer = True
        return lectureEffectuer

    def _splitDataTab(self, tableau1Lu, tableau2Lu):
        """
        Sépare les données des tableaux et les traite.

        :param str tableau1Lu : Données du tableau 1.
        :param str tableau2Lu : Données du tableau 2.
        """
        self.timeArduino = int(tableau1Lu[1].replace('\00', ''))
        self.qualiteGPS = tableau1Lu[2]
        self.temperature = float(tableau1Lu[3].replace('\00', ''))
        self.pression = float(tableau1Lu[4].replace('\00', ''))
        self.altitude = float("{:.2f}".format(44330.0 * (1.0 - pow(self.pression / SEALEVEL_HPA, 1/5.255))))
        self.altitudeGPS = tableau1Lu[5].replace('\00', '')

        _adc1_gaz1_work = int(tableau1Lu[6].replace('\00', ''))
        _adc1_gaz1_aux = int(tableau1Lu[7].replace('\00', ''))
        _adc1_gaz2_work = int(tableau1Lu[8].replace('\00', ''))
        _adc1_gaz2_aux = int(tableau1Lu[9].replace('\00', ''))
        _adc1_gaz3_work = int(tableau1Lu[10].replace('\00', ''))
        _adc1_gaz3_aux = int(tableau1Lu[11].replace('\00', ''))
        _adc1_gaz4_work = int(tableau1Lu[12].replace('\00', ''))
        _adc1_gaz4_aux = int(tableau1Lu[13].replace('\00', ''))
        _adc2_gaz1_work = int(tableau1Lu[14].replace('\00', ''))
        _adc2_gaz1_aux = int(tableau1Lu[15].replace('\00', ''))
        _adc2_gaz2_work = int(tableau1Lu[16].replace('\00', ''))
        _adc2_gaz2_aux = int(tableau1Lu[17].replace('\00', ''))
        _adc2_gaz3_work = int(tableau1Lu[18].replace('\00', ''))
        _adc2_gaz3_aux = int(tableau1Lu[19].replace('\00', ''))
        _adc2_gaz4_work = int(tableau1Lu[20].replace('\00', ''))
        _adc2_gaz4_aux = int(tableau1Lu[21].replace('\00', ''))

        self.adc1._gaz1.calcul(_adc1_gaz1_work, _adc1_gaz1_aux)
        self.adc1._gaz2.calcul(_adc1_gaz2_work, _adc1_gaz2_aux)
        self.adc1._gaz3.calcul(_adc1_gaz3_work, _adc1_gaz3_aux)
        self.adc1._gaz4.calcul(_adc1_gaz4_work, _adc1_gaz4_aux)
        self.adc1._gazNone.val_calc = NONE_VALUE_GAZ

        self.adc2._gaz1.calcul(_adc2_gaz1_work, _adc2_gaz1_aux)
        self.adc2._gaz2.calcul(_adc2_gaz2_work, _adc2_gaz2_aux)
        self.adc2._gaz3.calcul(_adc2_gaz3_work, _adc2_gaz3_aux)
        self.adc2._gaz4.calcul(_adc2_gaz4_work, _adc2_gaz4_aux)
        self.adc2._gazNone.val_calc = NONE_VALUE_GAZ

    def _update_reduction(self):
        """
        Met à jour la réduction des données.
        """
        self.x = self._reductionX(self.x)
        self.tabTemperature = self._reduction(self.tabTemperature)
        self.tabPression = self._reduction(self.tabPression)
        self.tabAltitude = self._reduction(self.tabAltitude)

        self.adc1.reduction()
        self.adc2.reduction()

        self.tabAltitudeGPS = self._reduction(self.tabAltitudeGPS)
        self.compt = len(self.x)

    def _reduction(self, tab):
        """
        Réduit les données du tableau.

        Args:
            tab (np.array): Tableau de données à réduire.

        return:
            np.array: Tableau de données réduit.
        """
        tab1 = tab[:NB_VALUE_REDUC]
        tab2 = tab[NB_VALUE_REDUC:]

        tab = np.array([])
        for i in range(int(NB_VALUE_REDUC / 2)):
            tab = np.append(tab, (tab1[i * 2] + tab1[i * 2 + 1]) / 2)
        tab = np.append(tab, tab2)
        return tab

    def _reductionX(self, tab):
        """
        Réduit les données de l'axe X.

        Args:
            tab (np.array): Tableau de données de l'axe X à réduire.

        return:
            np.array: Tableau de données de l'axe X réduit.
        """
        tab1 = tab[:NB_VALUE_REDUC]
        tab2 = tab[NB_VALUE_REDUC:]

        tab = np.array([])
        for i in range(int(NB_VALUE_REDUC / 2)):
            tab = np.append(tab, tab1[i * 2])
        tab = np.append(tab, tab2)
        return tab

    def update_data(self):
        """
        Met à jour les données en effectuant des réductions si nécessaire.

        :returns: True si les données sont mises à jour, sinon False.
        :rtype: bool

        """
        lectureEffectuer = False
        if self._update_lecture():
            lectureEffectuer = True
            self.comptReduction += 1
            self.x = np.append(self.x, self.x[-1] + 1)
            self.tabTemperature = np.append(self.tabTemperature, self.temperature)
            self.tabPression = np.append(self.tabPression, self.pression)
            self.tabAltitude = np.append(self.tabAltitude, self.altitude)

            if self.altitudeGPS[0] == 'X':
                self.tabAltitudeGPS = np.append(self.tabAltitudeGPS, ALTITUDE_GRAPH_DEFAUT)
            else:
                self.tabAltitudeGPS = np.append(self.tabAltitudeGPS, float(self.altitudeGPS))
            self.adc1.addValueTabs()
            self.adc2.addValueTabs()

            if self.comptReduction >= NB_VALUE_TOT:
                self._update_reduction()
                self.comptReduction = len(self.x)
        return lectureEffectuer


    class Capteur():
        """
        Classe pour la gestion des valeurs des capteurs.

        """
        def __init__(self, configADC):
            """
            Constructeur de la classe Capteur.

            :param dict configADC Configuration ADC spécifique au capteur alphasense.
            """
            self._gaz1 = self.GazData("gaz1", configADC)
            self._gaz2 = self.GazData("gaz2", configADC)
            self._gaz3 = self.GazData("gaz3", configADC)
            self._gaz4 = self.GazData("gaz4", configADC)

            self._gazNone = self.GazData("None", configADC)

            self._gazNO2 = None
            self._gazOX = None
            self._gazNO = None
            self._gazCO = None
            self._gazSO2 = None

            self._existanceGazNO2 = False
            self._existanceGazOX = False
            self._existanceGazNO = False
            self._existanceGazCO = False
            self._existanceGazSO2 = False

            self._tabGazNO2 = None
            self._tabGazOX = None
            self._tabGazNO = None
            self._tabGazCO = None
            self._tabGazSO2 = None

            self._foundGazType()

        def init_tab(self):
            """
            Initialise les tableaux de valeurs des gaz.
            """
            self._tabGaz1 = np.array([self._gaz1.val_calc, self._gaz1.val_calc])
            self._tabGaz2 = np.array([self._gaz2.val_calc, self._gaz2.val_calc])
            self._tabGaz3 = np.array([self._gaz3.val_calc, self._gaz3.val_calc])
            self._tabGaz4 = np.array([self._gaz4.val_calc, self._gaz4.val_calc])
            self._tabGazNone = np.array([NONE_VALUE_GAZ, NONE_VALUE_GAZ])

        def gaz1(self):
            """
            :returns: Données du gaz 1.
            :rtype: GazData
            """
            return self._gaz1

        def gaz2(self):
            """
            :returns: Données du gaz 2.
            :rtype: GazData
            """
            return self._gaz2

        def gaz3(self):
            """
            :returns: Données du gaz 3.
            :rtype: GazData
            """
            return self._gaz3

        def gaz4(self):
            """
            :returns: Données du gaz 4.
            :rtype: GazData
            """
            return self._gaz4

        def tabGaz1(self):
            """
            :returns: Retourne le tableau de valeurs du gaz 1.
            :rtype: ndarray
            """
            return self._tabGaz1

        def tabGaz2(self):
            """
            :returns: Retourne le tableau de valeurs du gaz 2.
            :rtype: ndarray
            """
            return self._tabGaz2

        def tabGaz3(self):
            """
            :returns: Retourne le tableau de valeurs du gaz 3.
            :rtype: ndarray
            """
            return self._tabGaz3

        def tabGaz4(self):
            """
            :returns: Retourne le tableau de valeurs du gaz 4.
            :rtype: ndarray
            """
            return self._tabGaz4

        def gazNO2(self):
            """
            :returns: Retourne les données du gaz NO2.
            :rtype: GazData
            """
            if self._existanceGazNO2:
                return getattr(self, self._gazNO2)()
            else:
                return self._gazNone

        def gazOX(self):
            """
            :returns: Retourne les données du gaz OX.
            :rtype: GazData
            """
            if self._existanceGazOX:
                return getattr(self, self._gazOX)()
            else:
                return self._gazNone

        def gazNO(self):
            """
            :returns: Retourne les données du gaz NO.
            :rtype: GazData
            """
            if self._existanceGazNO:
                return getattr(self, self._gazNO)()
            else:
                return self._gazNone

        def gazCO(self):
            """
            :returns: Retourne les données du gaz CO.
            :rtype: GazData
            """
            if self._existanceGazCO:
                return getattr(self, self._gazCO)()
            else:
                return self._gazNone

        def gazSO2(self):
            """
            :returns: Retourne les données du gaz SO2.
            :rtype: GazData
            """
            if self._existanceGazSO2:
                return getattr(self, self._gazSO2)()
            else:
                return self._gazNone

        def tabGazNO2(self):
            """
            :returns: Retourne le tableau de valeurs du gaz NO2.
            :rtype: ndarray
            """
            if self._existanceGazNO2:
                return getattr(self, self._tabGazNO2)()
            else:
                return self._tabGazNone

        def tabGazOX(self):
            """
            :returns: Retourne le tableau de valeurs du gaz OX.
            :rtype: ndarray
            """
            if self._existanceGazOX:
                return getattr(self, self._tabGazOX)()
            else:
                return self._tabGazNone

        def tabGazNO(self):
            """
            :returns: Retourne le tableau de valeurs du gaz NO.
            :rtype: ndarray
            """
            if self._existanceGazNO:
                return getattr(self, self._tabGazNO)()
            else:
                return self._tabGazNone

        def tabGazCO(self):
            """
            :returns: Retourne le tableau de valeurs du gaz CO.
            :rtype: ndarray
            """
            if self._existanceGazCO:
                return (getattr(self, self._tabGazCO)())
            else:
                return getattr(self._tabGazNone)

        def tabGazSO2(self):
            """
            :returns: Retourne le tableau de valeurs du gaz SO2.
            :rtype: ndarray
            """
            if self._existanceGazSO2:
                return getattr(self, self._tabGazSO2)()
            else:
                return self._tabGazNone

        def _foundGazType(self):
            """
            Recherche et assigne les types de gaz spécifiques.

            Parcourt une liste de gaz et identifie chaque type, assignant les valeurs correspondantes
            aux attributs de l'instance selon le type de gaz trouvé.

            Notes :
                Utilise les attributs gazNb et typeGaz de chaque instance de gaz pour l'identification.
            """
            for gaz in [self._gaz1, self._gaz2, self._gaz3, self._gaz4]:
                if gaz.typeGaz == "NO2":
                    self._gazNO2 = gaz.gazNb
                    self._existanceGazNO2 = True 
                    self._tabGazNO2 = "tabG" + gaz.gazNb[1:]
                if gaz.typeGaz == "OX":
                    self._gazOX = gaz.gazNb
                    self._existanceGazOX = True 
                    self._tabGazOX = "tabG" + gaz.gazNb[1:]
                if gaz.typeGaz == "NO":
                    self._gazNO = gaz.gazNb
                    self._existanceGazNO = True 
                    self._tabGazNO = "tabG" + gaz.gazNb[1:]
                if gaz.typeGaz == "CO":
                    self._gazCO = gaz.gazNb
                    self._existanceGazCO = True 
                    self._tabGazCO = "tabG" + gaz.gazNb[1:]
                if gaz.typeGaz == "SO2":
                    self._gazSO2 = gaz.gazNb
                    self._existanceGazSO2 = True 
                    self._tabGazSO2 = "tabG" + gaz.gazNb[1:]

        def addValueTabs(self):
            """
            Ajoute des valeurs aux tableaux de valeurs de gaz.

            """
            self._tabGaz1 = np.append(self._tabGaz1, self._gaz1.val_calc)
            self._tabGaz2 = np.append(self._tabGaz2, self._gaz2.val_calc)
            self._tabGaz3 = np.append(self._tabGaz3, self._gaz3.val_calc)
            self._tabGaz4 = np.append(self._tabGaz4, self._gaz4.val_calc)
            self._tabGazNone = np.append(self._tabGazNone, NONE_VALUE_GAZ)

        def reduction(self):
            """
            Applique une réduction aux tableaux de valeurs de gaz.
            """
            self._tabGaz1 = Data._reduction(self, self._tabGaz1)
            self._tabGaz2 = Data._reduction(self, self._tabGaz2)
            self._tabGaz3 = Data._reduction(self, self._tabGaz3)
            self._tabGaz4 = Data._reduction(self, self._tabGaz4)
            self._tabGazNone = Data._reduction(self, self._tabGazNone)

        class GazData():
            """
            Classe représentant les données d'un gaz spécifique.

            :param str gazNb: Numéro identifiant le gaz.
            :param str typeGaz: Type de gaz identifié à partir de la configuration.
            :param str ref: Référence associée au gaz.
            :param str we_zero: Valeur de WE_zero du gaz donnée par le constructeur.
            :param str ae_zero: Valeur de AE_zero du gaz donnée par le constructeur.
            :param str sensitivity: Sensibilité du gaz donnée par le constructeur.
            :param float val_calc: Valeur concentration calculée du gaz en fonction des mesures et des paramètres constructeur.

            """
            def __init__(self, gazNb, config):
                """
                Initialise une instance de GazData.

                :param str gazNb: Numéro identifiant le gaz.
                :param dict config: Configuration contenant les informations spécifiques au gaz.

                Notes :
                    Si gazNb est "None", initialise les attributs à "None".
                    Sinon, utilise la configuration pour initialiser typeGaz et appelle self.value(config) pour les autres attributs.

                """
                self.gazNb = gazNb
                if gazNb != "None":
                    self.typeGaz = id_to_name[config[self.gazNb]["type"]]
                    self.value(config)
                else:
                    self.typeGaz = "None"
                    self.ref = "None"
                    self.we_zero = "None"
                    self.ae_zero = "None"
                    self.sensitivity = "None"

            def value(self, config):
                """
                Initialise les attributs ref, we_zero, ae_zero et sensitivity à partir de la configuration.

                :param dict config: Configuration contenant les informations spécifiques au gaz.    
                """
                self.ref = config[self.gazNb]["ref"]
                self.we_zero = config[self.gazNb]["WE_zero"]
                self.ae_zero = config[self.gazNb]["AE_zero"]
                self.sensitivity = config[self.gazNb]["Sensitivity"]

            def calcul(self, work, aux):
                """
                Calcule la consentration calculée du gaz en fonction des mesures et des paramètres constructeur.

                :param float work: Valeur de travail pour le calcul.
                :param float aux: Valeur auxiliaire pour le calcul.

                Notes :
                    La formule utilise les attributs we_zero, ae_zero, sensitivity pour effectuer le calcul.
                    La valeur calculée est arrondie à une décimale.
                """
                self.val_calc = float("{:.1f}".format((((work*(VREF / 4096)- self.we_zero )-(aux*(VREF / 4096)- self.ae_zero ))/self.sensitivity))) #calcul applique au mots de l'adc


    class LectureCom(): 
        """
        Classe gérant la connexion série et la lecture des données du capteur.

        :param list tableau1Lu: Données lues du tableau 1.
        :param list tableau2Lu: Données lues du tableau 2.
        :param bool flagtableau1Lu: Indicateur si le tableau 1 a été lu.
        :param bool flagtableau2Lu: Indicateur si le tableau 2 a été lu.
        :param str nom: Nom du port de connexion.
        :param bool affiche_erreur0: Indicateur pour l'affichage des erreurs de connexion.

        """

        def __init__(self):
            """
            Initialise les attributs et établit la connexion série.
            """
            self.tableau1Lu = []
            self.tableau2Lu = []
            self.flagtableau1Lu = False
            self.flagtableau2Lu = False
            self.nom = COM
            self.affiche_erreur0 = True
            self._connectionSerial()

        def _connectionSerial(self):
            """
            Établit la connexion série avec le capteur.
            """
            while(True):
                try:
                    self._Data = serial.Serial(self.nom, 115200, timeout=5)
                    self.affiche_erreur0 = True
                    break
                except:
                    if(self.affiche_erreur0):
                        print("Erreur de branchement Arduino. Veuillez vérifier la connexion sur le port. " + self.nom)
                        self.affiche_erreur0 = False

        def lectureCom(self):
            """
            Lit les données des tableaux si disponibles.

            :returns: True si la lecture est effectuée, sinon False.
            :rtype: bool

            """
            lectureEffectuer = False
            self._recupTableauLu()
            if( self.flagtableau1Lu == True  ): #and self.flagtableau2Lu == True
                self.flagtableau1Lu = False
                self.flagtableau2Lu = False
                lectureEffectuer = True
            return lectureEffectuer

        def _recupTableauLu(self):
            """
            Récupère les données du tableau lu via le port série.
            """
            inWaiting = False
            try:
                inWaiting = self._Data.inWaiting()
            except:
                self._connectionSerial()

            if inWaiting:
                try:
                    line = str(self._Data.readline(), encoding='utf-8')
                except:
                    line = "fail lecture"
                print(line)
                if line[0] == "#":
                    line.replace('\00', '')
                    line = line.split("#")[1]
                    line = line.split("!")[0]
                    tableauLu = line.split(":")
                    self._saveTableauFonctionIndice(tableauLu)

        def _saveTableauFonctionIndice(self, tableauLu):
            """
            Sauvegarde les données en fonction de l'indice.

            :param list tableauLu: Données lues à sauvegarder.

            """
            indice = int(tableauLu[0].replace('\00', ''))
            if indice == 1:
                self.tableau1Lu = tableauLu
                self.flagtableau1Lu = True
            if indice == 2:
                self.tableau2Lu = tableauLu
                self.flagtableau2Lu = True

    

    


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
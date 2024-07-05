#code1.py
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import csv


VREF = 1.560

id_to_name = {
            1:"NO2",
            2:"OX",
            3:"NO",
            4:"CO",
            5:"SO2"
            }

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
        self.val_calc = (((work*(VREF / 4096)- self.we_zero )-(aux*(VREF / 4096)- self.ae_zero ))/self.sensitivity) #calcul applique au mots de l'adc


class Open_SD_MicroMEGA:
    def __init__(self,filename,configADC1, configADC2) -> None:

        
        self.filename = filename
        data = self.tableau_de_mesure()
        self.init_variable(data,configADC1,configADC2)
        del data
    
    def init_variable(self,data,configADC1,configADC2):
        id_id = 0
        id_HH=1
        id_MM=2
        id_SS=3
        id_longitude=4
        id_latitude=5
        id_altitude=6	
        id_adc_1_ch0_Temperature=7
        id_adc_1_ch1=8
        id_adc_1_ch2=9
        id_adc_1_ch3=10
        id_adc_1_ch4=11
        id_adc_1_ch5=12
        id_adc_1_ch6=13
        id_adc_1_ch7=14
        id_adc_1_ch8=15
        id_adc_2_ch0_Temperature=16	
        id_adc_2_ch1=17
        id_adc_2_ch2=18
        id_adc_2_ch3=19	
        id_adc_2_ch4=20
        id_adc_2_ch5=21
        id_adc_2_ch6=22
        id_adc_2_ch7=23
        id_adc_2_ch8=24
        id_temp=25
        id_hum=26
        id_pres=27
        id_temp_baro=28
        id_t_prog=29

        self.id=  data[:,id_id]
        self.temperature  = data[:,id_temp]
        self.temperature_baro  = data[:,id_temp_baro]
        self.temperature_ADC1  = data[:,id_adc_1_ch0_Temperature]
        self.temperature_ADC2  = data[:,id_adc_2_ch0_Temperature]

        self.pression  = data[:,id_pres]
        self.humidite  = data[:,id_hum]
        self.altitude  = data[:,id_altitude]
        self.longitude =data[:,id_longitude]
        self.latitude  = data[:,id_latitude]
        self.time  = [data[:,id_HH],data[:,id_MM],data[:,id_SS]]
        self.timeProg  = data[:,id_t_prog]


        try:
            self.ADC1_gaz1 =GazData("gaz1",configADC1)
            self.ADC1_gaz2 =GazData("gaz2",configADC1)
            self.ADC1_gaz3 =GazData("gaz3",configADC1)
            self.ADC1_gaz4 =GazData("gaz4",configADC1)

            self.ADC2_gaz1 =GazData("gaz1",configADC2)
            self.ADC2_gaz2 =GazData("gaz2",configADC2)
            self.ADC2_gaz3 =GazData("gaz3",configADC2)
            self.ADC2_gaz4 =GazData("gaz4",configADC2)
        except:
            print("Erreur Donner une config valide")
            input("Puch 'Enter' to quit")
            exit() 

        

        self.ADC1_gaz1.calcul(data[:,id_adc_1_ch1],data[:,id_adc_1_ch2])
        self.ADC1_gaz2.calcul(data[:,id_adc_1_ch3],data[:,id_adc_1_ch4])
        self.ADC1_gaz3.calcul(data[:,id_adc_1_ch5],data[:,id_adc_1_ch6])
        self.ADC1_gaz4.calcul(data[:,id_adc_1_ch7],data[:,id_adc_1_ch8])

        self.ADC2_gaz1.calcul(data[:,id_adc_2_ch1],data[:,id_adc_2_ch2])
        self.ADC2_gaz2.calcul(data[:,id_adc_2_ch3],data[:,id_adc_2_ch4])
        self.ADC2_gaz3.calcul(data[:,id_adc_2_ch5],data[:,id_adc_2_ch6])
        self.ADC2_gaz4.calcul(data[:,id_adc_2_ch7],data[:,id_adc_2_ch8])

    def tableau_de_mesure(self):
        tableau_valeur_mesurer =self.import_tableau_float_csv()
        data = np.asarray(tableau_valeur_mesurer[1:])
        num_data = np.float64(data[:,:-2]) #on del les 2 dernière colone (qui sont la date et un vide)
        return num_data
    
    def import_tableau_float_csv(self):
        tableau_valeur=[]
        spreadsheet = csv.reader(open(self.filename, 'r'), delimiter=' ' )
        x =0
        for row in spreadsheet: # List of columns
            result = []
            #print(x)
            for elem in row:
                if(x == 0):
                    None
                else:
                    if(elem!='nan' and elem!=''):
                        try:
                            result.append(float(elem.replace('\00','')))
                        except:
                            result.append('')
                    else:
                        result.append('')
            x+=1
            tableau_valeur.append(result)
        return(tableau_valeur)

    def del_aberation(tabVal):
        print(type(tabVal[2]))
        for a in range(len(tabVal)) :
            if(tabVal[a] ==  -1 ):
                print("oui")
                tabVal[a] = tabVal[a-1]
        return(tabVal)


    











if(__name__ == "__main__"):
    """
    Indispensable d'import les configs

    """
    from config_466 import config_466
    from config_467 import config_467
    data = Open_SD_MicroMEGA("data/020724.csv",config_466,config_467)

    def show(x,dat,name = " ",unite=" "):
        fig, ax = plt.subplots() 
        ax.plot(x, dat) 
        ax.set(xlabel='time (s)', ylabel=unite, title=name)
        ax.grid()
        plt.show()

    def show_adc(x,dat):
        # fig, ax = plt.subplots()
        # ax.plot(t, s)

        # ax.set(xlabel='time (s)', ylabel='voltage (mV)',
        #     title='About as simple as it gets, folks')
        # ax.grid()

        # fig.savefig("test.png")
        fig, ax = plt.subplots() 
        ax.plot(x, dat.val_calc) 
        ax.set(xlabel='time (s)', ylabel='consentration', title=dat.typeGaz)
        ax.grid()
        plt.show()

    
    a =data.timeProg[1:] - data.timeProg[:-1]
    print(a)
    print(np.max(a))
    print(np.min(a))
    print(np.average(a))
    print(np.sum(a>1500))
    print(np.sum(a<900))
    print(np.sum(a<500))

    b =data.id[1:] - data.id[:-1]
    print(b)
    print(np.max(b))
    print(np.min(b))
    print(np.sum(b<1.5))
    print(np.sum(b>1.5))

    for i in range(len(a)):
        if a[i]<500:
            print(i)

    names = np.arange(222,1016,1)

    values = []

    for i in names:
        val = np.sum(a==i)
        values.append(val)

    plt.bar(names, values) ; plt.show()

    show(data.id,data.temperature)
    # show(x,temperature_baro)
    # show(x,temperature_ADC1)
    # show(x,temperature_ADC2)
    # show(x,pression)
    # show(x,humidite)
    # show(x,altitude)
    # show(x,latitude)
    # show_adc(x,ADC1_gaz1)
    # show_adc(x,ADC1_gaz2)
    # show_adc(x,ADC1_gaz3)
    # show_adc(x,ADC1_gaz4)
    # show_adc(x,ADC2_gaz1)
    # show_adc(x,ADC2_gaz2)
    # show_adc(x,ADC2_gaz3)
    # show_adc(x,ADC2_gaz4)
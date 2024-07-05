"""
    Ce module permet de définir les paramètres et les configurations utilisés dans le système.
    Il contient plusieurs variables clés pour la personnalisation et le fonctionnement du programme.
"""

#from config_vide import config_vide
from config_466 import config_466
from config_467 import config_467

configADC1 = config_466
configADC2 = config_467

COM = 'COM3'

VREF = 1.560

NB_VALUE_REDUC=1200
NB_VALUE_GARDE=300
NB_VALUE_TOT = NB_VALUE_REDUC+NB_VALUE_GARDE

SEALEVEL_HPA = 1013.25

NONE_VALUE_GAZ = 0
ALTITUDE_GRAPH_DEFAUT = -1

id_to_name = {
            1:"NO2",
            2:"OX",
            3:"NO",
            4:"CO",
            5:"SO2"
            }


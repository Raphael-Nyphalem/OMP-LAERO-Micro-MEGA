import pyqtgraph as pg

class Page():
    """
    Classe de base pour créer une fenêtre PyQtGraph.

    :param GraphicsLayoutWidget win: Fenêtre PyQtGraph principale.
    :param str titre: Titre de la fenêtre.
    """
    def __init__(self, titre):
        """
        Initialise une nouvelle fenêtre PyQtGraph avec un titre donné.

        :param str titre: Titre de la fenêtre.
        """
        self.win = pg.GraphicsLayoutWidget()
        self.win.setWindowTitle(titre)
        self.titre = titre

class PageUnGraph(Page):
    """
    Classe pour créer une page avec un seul graphique dans PyQtGraph.

    :param LabelItem val: Label pour afficher des messages.
    :param PlotItem graph: Graphique pour tracer les données.
    :param str msg: Message à afficher dans le graphique.

    """
    def __init__(self, titre, unite=" "):
        """
        Initialise une nouvelle page avec un graphique dans PyQtGraph.

        :param str titre: Titre de la page.
        :param str unite: Unité des données affichées. Par défaut, c'est une chaîne vide.

        """
        super().__init__(titre)
        self.val = self.win.addLabel(row=0, col=0)
        self.graph = self.win.addPlot(row=1, col=0, title=self.titre, labels={'left': unite})
        self.msg = " "
    
    def update(self, x, tab, pen, taille="18pt"):
        """
        Met à jour le graphique avec de nouvelles données et met à jour le texte du label.

        :param list x: Données sur l'axe des x.
        :param list tab: Données sur l'axe des y.
        :param Pen pen: Couleur de ligne pour le tracé.
        :param str taille: Taille de la police pour le texte. Par défaut, c'est "18pt".
        """
        self.graph.plot(x, tab, pen=pen, clear=True)
        self.val.setText(self.msg, size=taille)
    
    def update_msg(self, var):
        """
        Met à jour le message affiché dans le graphique.

        :param str var: Nouveau message à afficher.
            
        """
        self.msg = " </font>" + "<br />" + self.titre + "<br />" + "<font color=\"yellow\">" + str(var) + " </font>"

    class PageAdc():
        """
        Classe pour créer plusieurs graphiques associés à un ADC (convertisseur analogique-numérique).

        :param PageUnGraph gaz1: Graphique pour le premier gaz détecté.
        :param PageUnGraph gaz2: Graphique pour le deuxième gaz détecté.
        :param PageUnGraph gaz3: Graphique pour le troisième gaz détecté.
        :param PageUnGraph gaz4: Graphique pour le quatrième gaz détecté.
        """
        def __init__(self, adc, adcName):
            """
            Initialise les graphiques associés à un ADC spécifique.

            :param Data.ADC adc: Instance de l'ADC.
            :param str adcName: Nom de l'ADC.
            """
            self.gaz1 = PageUnGraph((adcName + " " + adc.gaz1().typeGaz))
            self.gaz2 = PageUnGraph((adcName + " " + adc.gaz2().typeGaz))
            self.gaz3 = PageUnGraph((adcName + " " + adc.gaz3().typeGaz))
            self.gaz4 = PageUnGraph((adcName + " " + adc.gaz4().typeGaz))

        def update(self, x, adc, pen, taille="18pt"):
            """
            Met à jour tous les graphiques de gaz avec de nouvelles données de l'ADC.

            :param list x: Données sur l'axe des x.
            :param list tab: Données sur l'axe des y.
            :param Pen pen: Couleur de ligne pour le tracé.
            :param str taille: Taille de la police pour le texte. Par défaut, c'est "18pt".
            """
            self.gaz1.update(x, adc.tabGaz1(), pen, taille)
            self.gaz2.update(x, adc.tabGaz2(), pen, taille)
            self.gaz3.update(x, adc.tabGaz3(), pen, taille)
            self.gaz4.update(x, adc.tabGaz4(), pen, taille)
        
        def update_msg(self, adc):
            """
            Met à jour les messages affichés pour chaque gaz détecté par l'ADC.
            :param str var: Nouveau message à afficher. 
            """
            self.gaz1.update_msg(adc.gaz1().val_calc)
            self.gaz2.update_msg(adc.gaz2().val_calc)
            self.gaz3.update_msg(adc.gaz3().val_calc)
            self.gaz4.update_msg(adc.gaz4().val_calc)

class PageText(Page):
    """
    Classe pour afficher du texte dans une fenêtre PyQtGraph.

    :param str msg: Message à afficher.
    :param LabelItem val: Label pour afficher le message.
    """
    def __init__(self, titre):
        """
        Initialise une nouvelle fenêtre pour afficher du texte.

        :param str titre: Titre de la fenêtre.
        """
        super().__init__(titre)
        self.msg = " "
        self.val = self.win.addLabel(row=0, col=0)

class PageDoubleVal(Page):
    """
    Classe pour afficher deux ensembles de valeurs dans un graphique et des labels associés.

    :param str msg_adc1: Message à afficher pour la première valeur.
    :param str msg_adc2: Message à afficher pour la deuxième valeur.
    :param str msg_Name: Nom du graphique.
    :param LabelItem val_adc1: Label pour afficher la première valeur.
    :param LabelItem val_Name: Label pour afficher le nom du graphique.
    :param LabelItem val_adc2: Label pour afficher la deuxième valeur.
    :param PlotItem graph: Graphique pour tracer les données.
    """
    def __init__(self, msg_Name, unite=" "):
        """
        Initialise un graphique avec deux ensembles de valeurs.

        :param str msg_Name: Nom du graphique.
        :param str unite: Unité des données affichées. Par défaut, c'est une chaîne vide.
        """
        super().__init__(msg_Name)
        self.msg_adc1 = " "
        self.msg_Name = msg_Name
        self.msg_adc2 = " "
        self.val_adc1 = self.win.addLabel(row=0, col=0)
        self.val_Name = self.win.addLabel(row=0, col=1)
        self.val_adc2 = self.win.addLabel(row=0, col=2)
        self.graph = self.win.addPlot(row=1, col=0, colspan=3, title=self.titre, labels={'left':  unite})
    
    def update(self, x, tab1, tab2, pen1, pen2, nameplot1="ADC1", nameplot2="ADC2", taille="18pt", tailleTitre="18pt"):
        """
        Met à jour le graphique avec deux ensembles de données et les labels associés.

        :param list x: Données sur l'axe des x.
        :param list tab1: Données pour le premier ensemble.
        :param list tab2: Données pour le deuxième ensemble.
        :param Pen pen1: Style de ligne pour le premier tracé.
        :param Pen pen2: Style de ligne pour le deuxième tracé.
        :param str nameplot1: Nom du premier ensemble. Par défaut est "ADC1".
        :param str nameplot2: Nom du deuxième ensemble. Par défaut est "ADC2".
        :param str taille: Taille de la police pour le texte. Par défaut est "18pt".
        :param str tailleTitre: Taille de la police pour le titre du graphique. Par défaut est "18pt".

        """
        self.val_adc1.setText(self.msg_adc1, size=taille)
        self.val_Name.setText(self.msg_Name, size=tailleTitre)
        self.val_adc2.setText(self.msg_adc2, size=taille)

        self.graph.plot(x, tab1, pen=pen1, name=nameplot1, clear=True)  # Met à jour les données.
        self.graph.plot(x, tab2, pen=pen2, name=nameplot2)
        self.graph.addLegend()
    
    def update_msg(self, val1, val2, color1="yellow", color2="cyan", nameplot1="ADC1", nameplot2="ADC2"):
        """
        Met à jour les messages affichés pour chaque ensemble de données.
        :param str val1: Valeur à afficher pour le premier ensemble.
        :param str val2: Valeur à afficher pour le deuxième ensemble.
        :param str color1: Couleur du texte pour le premier ensemble. Par défaut est "yellow".
        :param str color2: Couleur du texte pour le deuxième ensemble. Par défaut est "cyan".
        :param str nameplot1: Nom du premier ensemble. Par défaut est "ADC1".
        :param str nameplot2: Nom du deuxième ensemble. Par défaut est "ADC2".
        """
        self.msg_adc1 = " </font>" + "<br />" + nameplot1 + "<br />" + "<font color=\"" + color1 + "\">" + str(val1) + " </font>"
        self.msg_adc2 = " </font>" + "<br />" + nameplot2 + "<br />" + "<font color=\"" + color2 + "\">" + str(val2) + " </font>"

class PageTextConnection(Page):
    """
    Classe pour afficher des informations de connexion dans une fenêtre PyQtGraph.

    :param str msg: Message à afficher.
    :param LabelItem showMsg: Label pour afficher le message.
    """
    def __init__(self, msg_Name):
        """
        Initialise une nouvelle fenêtre pour afficher des informations de connexion.

        :param str msg_Name: Nom de la fenêtre.
        """
        super().__init__(msg_Name)
        self.msg = " "
        self.showMsg = self.win.addLabel(row=0, col=0)
    
    def update(self, taille="18pt"):
        """
        Met à jour le message affiché dans la fenêtre.

        :param str taille: Taille de la police pour le texte. Par défaut est "18pt".
        """
        self.showMsg.setText(self.msg, size=taille)
    
    def update_msg(self, str1, str2, color1="yellow", color2="yellow", nameplot1="Signal GPS", nameplot2="temps depuit <br />la dernière reception"):
        """
        Met à jour les messages affichés pour les informations de connexion.

        :param str str1: Première chaîne de texte à afficher.
        :param str str2: Deuxième chaîne de texte à afficher.
        :param str color1: Couleur du texte pour la première chaîne. Par défaut est "yellow".
        :param str color2: Couleur du texte pour la deuxième chaîne. Par défaut est "yellow".
        :param str nameplot1: Nom associé à la première chaîne. Par défaut est "Signal GPS".
        :param str nameplot2: Nom associé à la deuxième chaîne. Par défaut est "temps depuit <br />la dernière reception".

        """
        # Message écrit en HTML
        self.msg = " "
        self.msg += " </font>" + "<br />" + nameplot1 + "<br />"
        self.msg += "<font color=\"" + color1 + "\">" + str1 + " </font>" + "<br />"

        self.msg += " </font>" + "<br />" + nameplot2 + "<br />"
        self.msg += "<font color=\"" + color2 + "\">" + str2 + " </font>" + "<br />"



"""
class PageExemple(Page):
    def __init__(self,msg_Name,unite = " ") -> None:
        super().__init__(msg_Name)

        #exemple
        self.msg = "Un message"
        self.affichage_unMessage= self.win.addLabel(row=0, col=0)
        self.affichage_unGraph = self.win.addPlot(row=1, col=0,colspan=3,title =self.titre ,labels = {'left':  unite})
    

    def update(self,x,tab1,pen1,nameplot1 ="ADC1",taille =  "18pt" ):
    
        #exemple
        self.affichage_unMessage.setText(self.msg,size = taille)
        self.affichage_unGraph.plot(x, tab1,pen=pen1,name=nameplot1,clear = True)  # Update the data.
        self.affichage_unGraph.addLegend()
    
    def update_msg(self,val1,color1 = "yellow", nameplot1 ="ADC1"):
        #message ecrit en HTML
        self.msg = " </font>"+"<br />"+nameplot1+"<br />"+"<font color=\""+ color1 +"\">"+str(val1)+" </font>"


"""

# Exemple d'utilisation dans le programme principal
if __name__ == "__main__":
    from Data import Data

    data = Data()

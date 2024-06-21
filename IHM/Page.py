import pyqtgraph as pg

class Page():
    def __init__(self,titre):
        self.win = pg.GraphicsLayoutWidget()
        self.win.setWindowTitle(titre)
        self.titre = titre


    
class PageUnGraph(Page):
    def __init__(self,titre,unite = " ") -> None:
        super().__init__(titre)
        self.val = self.win.addLabel(row=0, col=0)
        self.graph = self.win.addPlot(row=1, col=0,title = self.titre,labels = {'left': unite})
        self.msg = " "
    
    def update(self,x,tab,pen,taille =  "18pt" ):
        self.graph.plot(x, tab,pen=pen,clear = True)
        self.val.setText(self.msg,size=taille)
    
    def update_msg(self,var):
        self.msg = " </font>"+"<br />"+self.titre+"<br />"+"<font color=\"yellow\">"+str(var)+" </font>"


    class PageAdc():    
        def __init__(self,adc,adcName):
            self.gaz1 = PageUnGraph((adcName +" " +adc.gaz1().typeGaz))
            self.gaz2 = PageUnGraph((adcName +" " +adc.gaz2().typeGaz))
            self.gaz3 = PageUnGraph((adcName +" " +adc.gaz3().typeGaz))
            self.gaz4 = PageUnGraph((adcName +" " +adc.gaz4().typeGaz))

        def update(self,x,adc,pen,taille =  "18pt"):
            self.gaz1.update(x,adc.tabGaz1(),pen,taille)
            self.gaz2.update(x,adc.tabGaz2(),pen,taille)
            self.gaz3.update(x,adc.tabGaz3(),pen,taille)
            self.gaz4.update(x,adc.tabGaz4(),pen,taille)
        
        def update_msg(self,adc):
            self.gaz1.update_msg(adc.gaz1().val_calc)
            self.gaz2.update_msg(adc.gaz2().val_calc)
            self.gaz3.update_msg(adc.gaz3().val_calc)
            self.gaz4.update_msg(adc.gaz4().val_calc)

class PageText(Page):
    def __init__(self, titre):
        super().__init__(titre)
        self.msg = " "
        self.val= self.win.addLabel(row=0, col=0)

class PageDoubleVal(Page):
    def __init__(self,msg_Name,unite = " ") -> None:
        super().__init__(msg_Name)
        self.msg_adc1 = " "
        self.msg_Name = msg_Name
        self.msg_adc2 = " "
        self.val_adc1= self.win.addLabel(row=0, col=0)
        self.val_Name= self.win.addLabel(row=0, col=1)
        self.val_adc2= self.win.addLabel(row=0, col=2)
        self.graph = self.win.addPlot(row=1, col=0,colspan=3,title =self.titre ,labels = {'left':  unite})
    

    def update(self,x,tab1,tab2,pen1,pen2,nameplot1 ="ADC1",nameplot2 ="ADC2",taille =  "18pt",tailleTitre = "18pt" ):

        self.val_adc1.setText(self.msg_adc1,size = taille)
        self.val_Name.setText(self.msg_Name,size = tailleTitre)
        self.val_adc2.setText(self.msg_adc2,size = taille)

        self.graph.plot(x, tab1,pen=pen1,name=nameplot1,clear = True)  # Update the data.
        self.graph.plot(x, tab2,pen=pen2,name=nameplot2)
        self.graph.addLegend()
    
    def update_msg(self,val1,val2,color1 = "yellow",color2 = "cyan", nameplot1 ="ADC1",nameplot2 ="ADC2"):
        self.msg_adc1 = " </font>"+"<br />"+nameplot1+"<br />"+"<font color=\""+ color1 +"\">"+str(val1)+" </font>"
        self.msg_adc2 = " </font>"+"<br />"+nameplot2+"<br />"+"<font color=\""+ color2 +"\">"+str(val2)+" </font>"


class PageTextConnection(Page):
    def __init__(self,msg_Name):
        super().__init__(msg_Name)

        #exemple
        self.msg = " "
        self.showMsg= self.win.addLabel(row=0, col=0)
    

    def update(self,taille =  "18pt" ):
    
        self.showMsg.setText(self.msg,size = taille)
    
    def update_msg(self,str1,str2,color1 = "yellow",color2 = "yellow", nameplot1 ="Signal GPS",nameplot2 = "temps depuit <br />la dernière reception"):
        #message ecrit en HTML
        self.msg  = " "
        self.msg += " </font>"+"<br />"+nameplot1+"<br />"
        self.msg += "<font color=\"" + color1 + "\">" + str1 + " </font>"+"<br />"

        self.msg += " </font>"+"<br />"+nameplot2+"<br />"
        self.msg += "<font color=\"" + color2 + "\">" + str2 + " </font>"+"<br />"



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


if __name__ == "__main__":
    from Data import Data

    data = Data()

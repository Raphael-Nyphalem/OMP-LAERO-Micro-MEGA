#ifndef Data_H
#define Data_H

#include <ArduinoSTL.h>  
#include <map>
#include <DHT.h>

using namespace std;


class MapData{
  protected :
    static std::map<String, int> Data_map;  //attribut 
  public :
    void beginData(); //initialisation de la MAP
    static const std::map <String, int>& GetMap();  //Récupère Data_Map
    void afficher_map();  //Affiche le contenu de Data_Map
  friend class Data;
};

class Data{
  protected :
    String ID;  //attribut ID => nom du capteur
    float SensorData; //attribut valeur => valeur du capteur
  public :
    Data(String a); //Constructeur
    virtual void CollectData(MapData Dmap) = 0;
    float getData();
    void chargeData(MapData Dmap);
  friend class MapData;
}; 

class Humidity : public Data {
  public :
    Humidity():Data("HUMIDITY"){};
    void CollectData(MapData Dmap);
    void AfficheHumidity();
};

class Temperature : public Data {
  public :
    Temperature():Data("TEMPERATURE"){};
    void CollectData(MapData Dmap);
    void AfficheTemperature();
};    

#endif

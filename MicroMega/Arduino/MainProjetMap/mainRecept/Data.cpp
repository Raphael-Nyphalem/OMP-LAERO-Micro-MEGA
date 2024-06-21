#include "Data.h"

DHT dht(2, DHT11);

  void MapData::beginData(){           //Constructeur de MapData, pour initialisation 
      Data_map["TEMPERATURE"]=0;
      Data_map["HUMIDITY"]=0;
  }

  const std::map <String, int>& MapData::GetMap(){return Data_map;}

  void MapData::afficher_map(){
      for ( std::map<String,int>::iterator it = Data_map.begin(); it!=Data_map.end(); it++){
              Serial.print("ID : ");
              Serial.print(it->first);
              Serial.print(", Valeur : ");
              Serial.println(it->second);
     }
  }

  Data::Data(String a){ //Constructeur de class Data
    ID = a;
    SensorData = 0.;
  }
  
  float Data::getData(){return SensorData;}   //accès en lercture à SensorData

  void Data::chargeData(MapData Dmap){       //Charge la donnée SensorData dans Data_Map  <=> cf "class MapData"   
    Dmap.Data_map[ID]=SensorData;
  }

  void Humidity::CollectData(MapData Dmap){ //Récupère et stock la donnée du capteur d'humidité
      float humidity = dht.readHumidity();
      SensorData = humidity;
      chargeData(Dmap);
  }

  void Humidity::AfficheHumidity(){
    Serial.println(dht.readHumidity());
  }

  void Temperature::CollectData(MapData Dmap){       //Récupère et stock la donnée du capteur de temperature
      float temperature = dht.readTemperature();
      SensorData = temperature;
      chargeData(Dmap);
  }

   void Temperature::AfficheTemperature(){
    Serial.println(dht.readTemperature());
  }

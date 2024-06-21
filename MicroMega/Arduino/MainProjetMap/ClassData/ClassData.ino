#include <ArduinoSTL.h>  //librairie map, math, string et autre... => STL
#include <map>
#include <DHT.h>

using namespace std;

DHT dht(2, DHT11); //créé dht l'objet capteur Temp/Hum connecté à la pin 2 et de model DHT11 

class MapData{
  protected :
    static std::map<String, int> Data_map;  //attribut 
  public :
    void beginData(){             //Constructeur, pour initialisation 
      Data_map["TEMPERATURE"]=0;
      Data_map["HUMIDITY"]=0;
      }
    static const std::map <String, int>& GetMap(){return Data_map;}
    void afficher_map(){
        for ( std::map<String,int>::iterator it = Data_map.begin(); it!=Data_map.end(); it++){
                Serial.print("ID : ");
                Serial.print(it->first);
                Serial.print(", Valeur : ");
                Serial.println(it->second);
            }
      }
    friend class Data;
};

class Data{
  protected :
    String ID;  //attribut ID => nom du capteur
    float SensorData; //attribut valeur => valeur du capteur
  public :
    Data(String a){ //Constructeur
      ID = a;
      SensorData = 0.;
    }
    float getData(){return SensorData;}   //accès en lercture à SensorData
    void chargeData(MapData Dmap){       //Charge la donnée SensorData dans Data_Map  <=> "class MapData"   
      Dmap.Data_map[ID]=SensorData;
    }
  friend class Data;   
};

class Temperature : public Data {
  public :
    Temperature():Data("TEMPERATURE"){}   //Constructeur
    void CollectData(MapData Dmap){       //Récupère et stock la donnée du capteur de temperature
      float temperature = dht.readTemperature();
      SensorData = temperature;
      chargeData(Dmap);
    }
};

class Humidity : public Data {
  public :
    Humidity():Data("HUMIDITY"){}   //Constructeur
    void CollectData(MapData Dmap){ //Récupère et stock la donnée du capteur d'humidité
      float humidity = dht.readHumidity();
      SensorData = humidity;
      chargeData(Dmap);
    }
};


Humidity H1; //= Humidity()
Temperature T1; //= Temperature()
MapData M1; //= MapData()
std::map <String, int> MapData::Data_map;

void setup(){
  Serial.begin(9600);
  dht.begin();
  M1.beginData();

  Serial.println("Data initiale dans la Map :");
  M1.afficher_map();
  Serial.println();
  }

void loop(){
  
  //***TEST TEMPERATURE et HUMIDITE***
  Serial.print("Lecture du capteur d'Humidité :");
  Serial.println(dht.readHumidity());
  Serial.print("Lecture du capteur de Temperature :");
  Serial.println(dht.readTemperature());
  T1.CollectData(M1);
  H1.CollectData(M1);
  Serial.println();

  //***Affichage de la MAP de donné***
  Serial.println("Data dans la Map :");
  M1.afficher_map();
  Serial.println();

  
  delay(3000);
  }

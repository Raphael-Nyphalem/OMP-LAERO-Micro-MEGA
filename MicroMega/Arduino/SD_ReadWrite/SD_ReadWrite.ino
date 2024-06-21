/*
   ______               _                  _///_ _           _                   _
  /   _  \             (_)                |  ___| |         | |                 (_)
  |  [_|  |__  ___  ___ _  ___  _ __      | |__ | | ___  ___| |_ _ __ ___  _ __  _  ___  _   _  ___
  |   ___/ _ \| __|| __| |/ _ \| '_ \_____|  __|| |/ _ \/  _|  _| '__/   \| '_ \| |/   \| | | |/ _ \
  |  |  | ( ) |__ ||__ | | ( ) | | | |____| |__ | |  __/| (_| |_| | | (_) | | | | | (_) | |_| |  __/
  \__|   \__,_|___||___|_|\___/|_| [_|    \____/|_|\___|\____\__\_|  \___/|_| |_|_|\__  |\__,_|\___|
                                                                                      | |
                                                                                      \_|
  Fichier :       RecupInfosCarteSD.ino
  
  Description :   Ce programme permet de récupérer tout un tas d'infos sur la carte SD raccordée à l'Arduino,
                  et d'afficher toutes ces données sur le Moniteur Série de l'IDE Arduino

  Auteur :        Jérôme TOMSKI (https://passionelectronique.fr/)
  Créé le :       07.06.2021

*/
#include <SD.h>

// Variables SD Card
Sd2Card CarteSD;
SdVolume VolumeCarteSD;
uint32_t volumesize;

// Lecteur SD card branché sur les pins 10 (CS), 11 (MOSI), 12 (MISO), et 13 (SCK). Les 3 dernières étant le traditionnel bus SPI, il faut juste préciser la pin raccordée au chip select du lecteur de SD card
#define sdCardSelect 10

// ========================
// Initialisation programme
// ========================
void setup () {
  
  // Initialisation de la liaison série (pour retourner les infos au moniteur série de l'ordi)
  Serial.begin(9600);
  Serial.println(F("Affichage des informations de la carte SD raccordée à l'Arduino"));
  Serial.println(F("==============================================================="));
  Serial.println();

  // Étape 1 : test la présence d'une carte raccordée ou non
  if (!CarteSD.init(SPI_HALF_SPEED, sdCardSelect)) {
    Serial.println(F("Échec lors de l'initialisation. Essayez de jeter un coup d'oeil à : "));
    Serial.println(F("- est-ce que la carte SD est bien insérée dans le lecteur ?"));
    Serial.println(F("- est-ce que vos branchements électriques sont corrects ?"));
    Serial.println(F("- est-ce que le 'chipSelect' choisi dans le programme correspond bien à celui branché sur l'arduino ? (pin D10, par défaut)"));
    Serial.println();
    Serial.println(F("Appuyez sur RESET pour relancer le programme, au besoin."));
    while (1);      // Boucle infinie, arrêt du programme
  } else {
    Serial.println(F("Câblage correct, carte SD trouvée."));
    Serial.println();
  }

  // Étape 2 : déterminer le type de carte SD insérée dans le lecteur
  Serial.print(F("Type de carte SD insérée : "));
  switch (CarteSD.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println(F("SD1"));
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println(F("SD2"));
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println(F("SDHC"));
      break;
    default:
      Serial.println(F("Inconnu"));
  }
  Serial.println();

  // Étape 3 : tentative d'ouverture du volume/de la partition (qui doit être en FAT16, ou FAT32), et affichage du format
  if (!VolumeCarteSD.init(CarteSD)) {
    Serial.println(F("Aucune partition FAT16/FAT32 trouvée."));
    Serial.println(F("Vérifiez si votre carte SD est bien formatée !"));
    while (1);      // Boucle infinie, arrêt du programme
  } else {
    Serial.print(F("Format du volume : FAT"));
    Serial.println(VolumeCarteSD.fatType(), DEC);
  }

  // Étape 4 : affichage du nombre de cluster, et de blocs
  Serial.print(F("Nombre de clusters : ")); 
  Serial.println(VolumeCarteSD.clusterCount());
  Serial.print(F("Nombre de blocs par cluster : "));
  Serial.println(VolumeCarteSD.blocksPerCluster());
  Serial.print(F("Nombre total de blocs : "));
  Serial.println(VolumeCarteSD.blocksPerCluster() * VolumeCarteSD.clusterCount());
  Serial.println();

  // Étape 5 : affichage de la taille du volume, en KB/MB/GB
  volumesize = VolumeCarteSD.clusterCount() * VolumeCarteSD.blocksPerCluster();
  volumesize = volumesize / 2;         // Nota : les blocs d'une carte SD font toujours 512 octets (il faut donc 2 blocs pour faire 1KB)
  Serial.print(F("Taille du volume (en KB): ")); Serial.println(volumesize);
  Serial.print(F("Taille du volume (en MB): ")); Serial.println(volumesize / 1024);
  Serial.print(F("Taille du volume (en GB): ")); Serial.println(volumesize / 1024 / 1024.0);
  Serial.println();

  Serial.println(F("Fin !"));

}
 
// =================
// Boucle principale
// =================
void loop () {
  // Vide (tout se passe dans la fonction "setup" !)
}

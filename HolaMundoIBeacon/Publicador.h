// -*- mode: c++ -*-

// --------------------------------------------------------------
// Hugo Martin Escrihuela
// 08-10-2023
// --------------------------------------------------------------

#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

// ............................................................
//   obtenerDispositivoID() --> Texto
// ............................................................
char[] obtenerDispositivoID(){
  // Obtiene el identificador único del chip NRF52840
  uint32_t uniqueID[3];
  NRF_FICR->DEVICEID[0] = NRF_FICR->DEVICEID[0] & 0xFFFFFFFC; // Garantiza que el ID sea único
  uniqueID[0] = NRF_FICR->DEVICEID[0];
  uniqueID[1] = NRF_FICR->DEVICEID[1];
  uniqueID[2] = NRF_FICR->DEVICEID[2];
  
  // Envía el identificador único por Bluetooth
  char uniqueIDString[32];
  snprintf(uniqueIDString, sizeof(uniqueIDString), "%08X%08X%08X", uniqueID[0], uniqueID[1], uniqueID[2]);

  elPuerto.escribir( "\n---- id prueboID(): empieza " );
  elPuerto.escribir( uniqueIDString );
  elPuerto.escribir( "\n---- id prueboID(): acaba \n" );

  return uniqueIDString;
}
// --------------------------------------------------------------
// --------------------------------------------------------------
class Publicador {

  // ............................................................
  // ............................................................
private:

  uint8_t beaconUUID[16] = { 
	'E', 'P', 'S', 'G', '-', 'G', 'T', 'I', 
	'-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
	};

  // ............................................................
  // ............................................................
public:
  EmisoraBLE laEmisora {
	"GTI-3A", //  nombre emisora
	  0x004c, // fabricanteID (Apple)
	  //4 // txPower
    obtenerDispositivoID()
	  };
  
  const int RSSI = -53; // por poner algo, de momento no lo uso

  // ............................................................
  // ............................................................
public:

  // ............................................................
  // ............................................................
  enum MedicionesID  {
	CO2 = 11,
	TEMPERATURA = 12,
	RUIDO = 13
  };

  // ............................................................
  //   constructor()
  // ............................................................
  Publicador( ) {
	// ATENCION: no hacerlo aquí. (*this).laEmisora.encenderEmisora();
	// Pondremos un método para llamarlo desde el setup() más tarde
  } // ()

  // ............................................................
  //   encenderEmisora()
  // ............................................................
  void encenderEmisora() {
	(*this).laEmisora.encenderEmisora();
  } // ()

  // ............................................................
  //   publicarCO2() <-- N, N, N
  // ............................................................
  void publicarCO2( int16_t valorCO2, uint8_t contador,
					long tiempoEspera ) {

	//
	// 1. empezamos anuncio
	//
	uint16_t major = (MedicionesID::CO2 << 8) + contador;
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
											major,
											valorCO2, // minor
											(*this).RSSI // rssi
									);

	/*
	Globales::elPuerto.escribir( "   publicarCO2(): valor=" );
	Globales::elPuerto.escribir( valorCO2 );
	Globales::elPuerto.escribir( "   contador=" );
	Globales::elPuerto.escribir( contador );
	Globales::elPuerto.escribir( "   todo="  );
	Globales::elPuerto.escribir( major );
	Globales::elPuerto.escribir( "\n" );
	*/

	//
	// 2. esperamos el tiempo que nos digan
	//
	esperar( tiempoEspera );

	//
	// 3. paramos anuncio
	//
	(*this).laEmisora.detenerAnuncio();
  } // ()

  // ............................................................
  //   publicarTemperatura() <-- N, N, N
  // ............................................................
  void publicarTemperatura( int16_t valorTemperatura,
							uint8_t contador, long tiempoEspera ) {

	uint16_t major = (MedicionesID::TEMPERATURA << 8) + contador;
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
											major,
											valorTemperatura, // minor
											(*this).RSSI // rssi
									);
	esperar( tiempoEspera );

	(*this).laEmisora.detenerAnuncio();
  } // ()

  // ............................................................
  //   publicarTemperaturaGasId() <-- R, R
  // ............................................................
  void publicarTemperaturaGasId( double valorTemperatura,
							double valorGas ) {
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
											valorGas,
											valorTemperatura, // minor
											(*this).RSSI // rssi
									);
	esperar( tiempoEspera );

	(*this).laEmisora.detenerAnuncio();
  } // ()
	
}; // class

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif

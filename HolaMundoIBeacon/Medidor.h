// -*- mode: c++ -*-

// --------------------------------------------------------------
// Hugo Martin Escrihuela
// 08-10-2023
// --------------------------------------------------------------

#include <math.h>

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

#define pinVgas 5
#define pinVref 28
#define pinVtemp 29

// ------------------------------------------------------
// ------------------------------------------------------
class Medidor {

  // .....................................................
  // .....................................................
private:

public:

  // .....................................................
  // constructor()
  // .....................................................
  Medidor() {
  }  // ()

  // .....................................................
  //   iniciarMedidor()
  // .....................................................
  void iniciarMedidor() {
    // las cosas que no se puedan hacer en el constructor, if any
    pinMode(pinVgas, INPUT);
    pinMode(pinVref, INPUT);
    pinMode(pinVtemp, INPUT);
  }  // ()

  // .....................................................
  //   medirCO2() --> R
  // .....................................................
  double medirCO2() {
    return concentracionGas(general_code_to_voltage(analogRead(pinVgas)), general_code_to_voltage(analogRead(pinVref)));
  }  // ()

  // .....................................................
  //   medirTemperatura() --> R
  // .....................................................
  double medirTemperatura() {
    return -temp(general_code_to_voltage(analogRead(pinVtemp)));
  }              // ()

  // .....................................................
  //   N --> general_code_to_voltage() --> R
  // .....................................................
  double general_code_to_voltage(int pinValue) {
    return (pinValue / pow(2, 12)) * 3.3;
  }

  // .....................................................
  //   R --> temp() --> R
  // .....................................................
  double temp(double Vtemp) {
    double temperatura = (Vtemp * 87) - 18;

    // Imprimir el valor de la temperatura en grados centigrados (ºC)
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" ºC");

    return temperatura;
  }

  // .....................................................
  //   R --> concentracionGas() --> R
  // .....................................................
  double concentracionGas(double Vgas, double Vref) {
    // Factor de calibración proporcionado en el datasheet en nA/ppm
    float M = 4.94;  // Este valor debe obtenerse del datasheet
    // Realizar cálculos para convertir el voltaje a concentración de ozono según la fórmula Cx = (Vgas - Vgas0) / M
    double ozoneConcentration = ((Vgas - (Vref / 2)) / M) * 1000;  // Multiplicar por 1000 para convertir de nA a µA y obtener ppm

    // Imprimir el valor de la concentración de ozono en ppm (partes por millón)
    Serial.print("Concentración de Ozono: ");
    Serial.print(ozoneConcentration);
    Serial.println(" ppm");

    return ozoneConcentration;
  }
};  // class

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
#endif

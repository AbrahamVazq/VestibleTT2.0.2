
Version 2.0.2 del Dispositivo, el sensor de pulsos funciona, sin embargo es considerable que se acondicione ya sea con el velcro para el dedo o con el sujetador para el lóbulo de la oreja.

Pruebas Exitosas, se obtienen datos coherentes de los sensores
////////////////////////////////////////////////////////////////////////////////////////////////////////

Fecha: Viernes 6 Mayo 2016
Estado: Pruebas Exitosas
Mejoras: Depuración y revisión de código
Fallas: El Led de propósito de lectura esta encendido por lo que el modulo SD sigue escribiendo no respetando el código de comparación y parado de lectura

////////////////////////////////////////////////////////////////////////////////////////////////////////

Fecha: Miércoles 11 de Mayo 2016
Estado: Pruebas Exitosas
Mejoras: Depuración, revisión de código y eliminación de bugs encontrados en ejecución
Fallas: El Dispositivo sigue escribiendo despues de la pausa en el push button, no respetando el If que comprueba que la Tarjeta SD esta conectada en una de las funciones del lectura e impresión a pantalla del sensor de pulso.

////////////////////////////////////////////////////////////////////////////////////////////////////////

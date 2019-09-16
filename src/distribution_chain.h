//
// Created by lucas on 9/6/19.
//

#ifndef TP1_DISTRIBUTIONCHAIN_H
#define TP1_DISTRIBUTIONCHAIN_H

/*
 * Crea una cadena de centros (producción, distribución y punto de venta).
 * Maneja toda la parte del armado de concurrencia e IPC (pero no el mantenimiento!).
 */
class DistributionChain {
    int chain_id;
public:
    explicit DistributionChain(int chain_id);
    // Devuelve el PID del hijo que se crea.
    // Hay que laburar más el diseño de este return creo... Funciona OK para main,
    // pero para los puntos intermedios no resulta suficiente.
    int start();
};


#endif //TP1_DISTRIBUTIONCHAIN_H

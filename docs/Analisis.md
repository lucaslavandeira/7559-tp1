# Análisis del problema 

Muchos productores, que constantemente producen ramos de flores, y los distribuyen en cajones de 10 ramos a centros (según cierto criterio). Muchos centros, que clasifican y envían a muchos puntos de venta. Los puntos de venta venden los ramos a clientes, ya sea a través de Internet, o en el local. 

La cadena de producción y logística descripta requiere una implementación que mantenga inventarios de cada actor en el sistema, y transacciones (compras-ventas). 

La producción de flores es constante, es decir la simulación debe comenzar con los inventarios con algún valor inicial (podría ser vacío por hipótesis), e ir llenándose a medida que los productores envían ramos de flores a los centros de distribución, y los centros, a los puntos de venta. Los puntos de venta luego van utilizando su stock para efectuar ventas a clientes. La simluación finalizaría una vez que todos los clientes de todos los puntos de venta.

El enunciado habla de ramos inicialmente, y luego de flores (individuales) en los puntos de venta. Asumimos que la unidad mínima en realidad son los ramos, y los pedidos hechos son de varios ramos ("flores"). Un pedido entonces podría ser de 10 ramos de rosas, y 5 de tulipanes, por ejemplo. A su vez, los ramos producidos por los campos, son de un tipo único de flores, no existen ramos que mezclen ambos tipos.

# Hipótesis

* Un ramo de flores es la mínima unidad.
* La cosecha de flores en los campos es una función del tiempo (U otro proceso que se lanza y genera flores?)
* No hay límite de cajones de distribución.
* El transporte de los cajones a los centros de distribución es independiente de la cosecha de flores (No hay tiempo de espera para seguir cosechando o está contemplado en la función de cosecha).
* La cantidad de campos de producción, centros de distribución y puntos de venta deben ser mayor a cero (Un mínimo de un campo de producción, un centro de distribución y un punto de venta).
* Los pedidos ya fueron generados y están en espera.
* Se atiende según orden de llegada (FIFO) y de a un cliente por vez.
* Hasta que no se termina de atender un cliente, no se atiende al siguiente.
* El envío desde los puntos de distribución hasta los puntos de venta es inmediato.
* Los ramos se transportan desde los centros de distribución a los puntos de venta de manera aleatoria.
* Los cajones se transportan desde los campos de producción a los centros de distribución de manera aleatoria. 

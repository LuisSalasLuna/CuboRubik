# CuboRubik
Objetivo:
Este proyecto busca programar un cubo de Rubik virtual creado con computación gráfica usando la biblioteca OpenGL y adicionalmente unir esta implementación a un solver especifico que resuelva el cubo. Adicionalmente, se definio un conjunto de animaciones especifica para los grupos:
* Respiración: Combina transformaciones de escala y transformacio para simular un efecto de respiracion individual por cubo
* Armado: Genera posiciones aleatorias iniciales para los cubos individuales y los reordena en intervalos

Solver:

Implementamos una versión del algoritmo de Thisletwaite junto con la técnica de la base de datos de patrones

https://github.com/conanwu777/rubik

Cubo armado:

![ezgif com-gif-maker (1)](https://user-images.githubusercontent.com/54364183/177815789-47f5b831-a968-4108-86d2-3a7f461141c5.gif)

Camadas:
- F: Movimiento de camada Front (RED)
- G: Movimiento inverso de camada Front (RED)
- B: Movimiento de camada Back (ORANGE)
- N: Movimiento inverso de camada Back (ORANGE)
- R: Movimiento de camada Right (YELLOW)
- T: Movimiento inverso de camada Right (YELLOW)
- L: Movimiento de camada Left (WHITE)
- K: Movimiento inverso de camada Left (WHITE)
- U: Movimiento de camada Up (BLUE)
- I: Movimiento inverso de camada Up (BLUE)
- D: Movimiento de camada Down (GREEN)
- S: Movimiento inverso de camada Down (GREEN)
  
Cámara:
- 1: Giro de cámara en Eje X
- 2: Giro de cámara en Eje Y
- 3: Giro de cámara en Espiral
- 4: Cámara Libre (Default)
  
Libre: 
- UP: 	Acercamiento a cámara.
- DOWN:	 Alejamiento de cámara.
- RIGHT: Camara desplazada en eje X e Y (lateral derecho)
- LEFT:Camara desplazada en eje X e Y (lateral izquierdo)
- SPACE: Cámara desplazada al eje Y(positivo)
- SHIFT: Cámara desplazada al eje Y(negativo)
  
Armado (2da animación): 
- Z: Ensambla el cubo en partes.
  
![ezgif com-gif-maker (2)](https://user-images.githubusercontent.com/54364183/177817180-3ca2c5db-f34b-4250-b576-59e82f7baa1b.gif)





1. ### Nombre completo y usuario de GitHub:
   
   Julio Emmanuel Bautista Apolinar Cayojuio
   
   [Release v0.4 · Cayojulio/Motores2D · GitHub](https://github.com/Cayojulio/Motores2D/releases/tag/v0.4)

2. ### Justificacion matematica
   
   Al ser rectangulos soo basta ver el vertice superior izquierdo y sumar su tamaño para saber la distancia con el vertice superior derecho y el vertice inferior izquierdo, con esto puedes ver la coordenada en donde debe estar el objeto contrario para que haya colision, negamos todo con las leyes de morgan y obtenemos un conjunto de desigualdades que se deben de cumplir para saber cuando No colisionan

3. ### Espacio Local vs Mundo
   
   el collider una caja por aparte, entonces necesita un vector direccion para seguir al objeto, la distancia que dejara es la variable offset

4. ### Complejidad algoritmica:
   
   la iteracion triangular permite no comparar valores en diagonal de forma (i,i) y una vez revisado el (i,j) con i mayor que j jamas se compara el (j,i)

5. ### Capturas de pantalla de la aplicación ejecutándose:
   
   1.
   
   ![](/home/cayo/snap/marktext/9/.config/marktext/images/2026-09-26-19-18-14-image.png)
   
   2.
   
   ![](/home/cayo/snap/marktext/9/.config/marktext/images/2026-09-26-19-20-09-image.png)
   
   3.
   
   ![](/home/cayo/snap/marktext/9/.config/marktext/images/2026-09-26-19-20-48-image.png)

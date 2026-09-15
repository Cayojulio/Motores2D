# Captura de pantalla de la aplicación ejecutándose con el jugador y al menos una

# Explica el rol de dynamic_cast en GetComponent<T>() y cómo permite la comunicación



# Nombre completo y usuario:

Julio Emmanuel Bautista Apolinar y Cayojulio

# Justificación teórica: explica por qué std::vector<std::unique_ptr<Component>> previene el problema del Object Slicing y qué ocurriría si se usara un vector de objetos directos std::vector<Component>

Cuando creas el vector se da una cierta memoria a cada componente igual a la memoria que ocuparia solo Component pero a la hora de poner una clase derivada va  tener Component mas cosas extras, por lo cual ocupa mas espacio y recorta ese sobrante, perdiendo informacion 

# Explica el rol de dynamic_cast en GetComponent<T>() y cómo permite la comunicación

GetComponent busca un tipo de clase y lo que hace es ver todo el vector de componentes de un objeto y con dynamic_cast verifica cual de todo es del tipo solicitado y una vez localizado ya lo retorna

# Captura de pantalla de la aplicación ejecutándose con el jugador y al menos una

![](/home/cayo/snap/marktext/9/.config/marktext/images/2026-09-14-22-08-46-image.png)

# Enlace o captura al commit en GitHub.

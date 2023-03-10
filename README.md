# **Manual de usuario** 馃搩

## **Proyecto Final CGeIHC** 馃捇
Proyecto Final para la materia de Computaci贸n Gr谩fica e Interacci贸n Humano Computadora (Teor铆a).

## **Alumno:** 馃懄馃徑
- Cruz Rangel Leonardo Said
- N煤mero de cuenta: 316031062

### **Semestre 2023-1 | Grupo 05**

### **Requerimientos**
+ Para ejecuci贸n con Visual Studio 2022 con instalaci贸n de C++ o con el ejecutable .exe:
	+ Windows 7 (煤ltima actualizaci贸n), Windows 8 (2919355), Windows 10 (versi贸n 1703 o superior)
	+ Procesador: 1.8 GHz (recomendado 4 n煤cleos o m谩s)
	+ 2.5 GB de memoria RAM (8 GB recomendado)
	+ 20 GB de espacio en disco (recomendado)
	+ Chip gr谩fico de m铆nimo 720p de resoluci贸n

### **Apertura y ejecuci贸n del proyecto**
Descargar el proyecto desde GitHub dando click al bot贸n verde "Code" y seleccionando una de las opciones

<img src=img/captura1.png></img>

Si selecciona "Open with GitHub Desktop" deber谩 tener dicha aplicaci贸n instaada en su equipo y seguir los pasos para clonar el repositorio de manera local, una vez clonado saltar hasta ["Ejecuci贸n del archivo .exe"](#item1).

La selecci贸n "Download ZIP" descargar谩 un archivo .zip del proyecto, habr谩 que descomprimirlo en su equipo, regresar a este manual y saltarse hasta ["Ejecuci贸n del archivo .exe"](#item1).

### ***Ejecuci贸n con Visual Studio*** 馃捇
Si se desea y se tiene instalado el IDE Visual Studio, se puede ejecutar la aplicaci贸n siguiendo los siguientes pasos: descargar el proyecto de GitHub y descomprimir la carpeta zip. Una vez hecho esto, abrir Visual Studio y seleccionar la opci贸n "Abrir un proyecto o una soluci贸n".

<div align = "center">
<img src=img/captura2.png height = 400px></img>
</div>

Buscar el archivo "ProyectoFinal.sln" dentro de la carpeta descomprimida y dar clic en el bot贸n de "Abrir".

<div align = "center">
<img src=img/captura3.png></img>
</div>

Antes de ejecutar el programa, es importante comprobar que todas las bibliotecas y configuraciones est茅n cargadas correctamente. Para hacer esto, se debe dirigir al explorador de soluciones, hacer clic derecho en el nombre del proyecto y seleccionar la opci贸n de propiedades.

<div align = "center">
<img src=img/captura4.png height = 500px></img>
</div>

En el apartado de "General" verificar que el Conjunto de herramientas de la plataforma sea uno que se tenga descargado, puede ser v142 o v143.

<div align = "center">
<img src=img/captura5.png></img>
</div>

Dentro de "C/C++ --> General" verificar que la palabra <b>include</b> se encuentra en "Directorios de inclusi贸n adicionales".

<div align = "center">
<img src=img/captura6.png></img>
</div>

En el "Vinculador --> General" verificar que la palabra <b>lib</b> se encuentra en "Directorios de bibliotecas adicionales".

<div align = "center">
<img src=img/captura7.png></img>
</div>

Finalmente, en "Vinculador --> Entrada" verificar que las dependencias <b>SDL2.lib;SDL2main.lib;assimp-vc141-mtd.lib;opengl32.lib;glfw3.lib;</b> est茅n incluidas en "Dependencias adicionales". De lo contrario, pegar el texto en negritas en dicho apartado, sin borrar las dependencias que ya se tengan.

<div align = "center">
<img src=img/captura8.png></img>
</div>

Para poner en ejecuci贸n el proyecto se debe seleccionar la opci贸n "x86" en a barra superior y verificar que est茅 seleccionada la opci贸n "Debug" como se muestra en la siguiente imagen.

<div align = "center">
<img src=img/captura9.png></img>
</div>

Ya puede ejecutarse el proyecto dando clic en el bot贸n "Depurador local de Windows", esto abrir谩 la ventana del programa.

<a name="item1"></a>
### ***Ejecuci贸n del archivo .exe*** 馃殌
Una vez que se ha clonado el proyecto o descomprimido el archivo .zip, se debe abrir la carpeta generada o ubicaci贸n del repositorio en el equipo y acceder a "ProyectoFinal\Release". Luego, se debe localizar el archivo "ProyectoFinal.exe" y hacer doble clic en 茅l para ejecutar el programa.

<div align = "center">
<img src=img/captura10.png></img>
</div>

## **Interacci贸n con el ambiente**馃彔
Una vez que la ventana est谩 abierta, se captura el mouse para que solo funcione dentro del espacio virtual. Como resultado, el cursor no es visible y el movimiento del mouse solo es posible dentro de la ventana. La interacci贸n se lleva a cabo a trav茅s del teclado y el mouse de la computadora.

<div align = "center">
<img src=img/captura11.png></img>
Fachada de la casa
</div>

<br>

<div align = "center">
<img src = img/captura12.png></img>
Sala de estar
</div>

<br>

<div align = "center">
<img src = img/captura13.png></img>
Cocina
</div>

<br>

<div align = "center">
<img src = img/captura14.png></img>
Cuarto 1
</div>

<br>

<div align = "center">
<img src = img/captura15.png></img>
Cuarto 2
</div>

<br>

<div align = "center">
<img src = img/captura16.png></img>
Cuarto 3
</div>

<br>

<div align = "center">
<img src = img/captura17.png></img>
Ba帽o en suite
</div>

<br>

<div align = "center">
<img src = img/captura18.png></img>
Ba帽o general
</div>

<br>

<div align = "center">
<img src = img/captura19.png></img>
Patio trasero con piscina
</div>

#### Funciones del Teclado
* "Esc" : para salir de la ventana / terminar el programa. 鉂?

* Simulaci贸n de las teclas de adelante 猬嗭笍, atr谩s 猬囷笍, izquierda 猬咃笍, derecha 鉃★笍 para movimiento como sucede en los videojuegos:
    * "W" : mover la c谩mara hacia enfrente 猬嗭笍. 
    * "S" : mover la c谩mara hacia atr谩s 猬囷笍. 
    * "A" : mover la c谩mara hacia la izquierda 猬咃笍.
    * "D" : mover la c谩mara hacia la derecha 鉃★笍.

* Movimientos del mouse:
    * El deslizamiento del mouse 馃攣 a la izquierda o derecha, arriba o abajo realiza el giro de la c谩mara 馃摲 en dicha direcci贸n de deslizado, el field of view 馃攳 se mueve como sucede con el cursor de la computadora.
    * Scroll del mouse reliza zoom + 馃攳 movi茅ndolo hacia enfrente y zoom - 馃攳 hacia atr谩s.
	
* Animaciones:
	* "SPACE": Activa la animaci贸n del veh铆culo 馃殫
		<div align = "center">
		<img src = img/captura20.png></img>
		</div>
		<br>

	* "R": Restablece la animaci贸n del veh铆culo 馃殫
		<div align = "center">
		<img src = img/captura21.png></img>
		Posici贸n inicial del veh铆culo.
		</div>
		<br>

	* "5": Activa la animaci贸n del helic贸ptero de juguete a control remoto 馃殎
		<div align = "center">
		<img src = img/captura22.png></img>
		</div>
		<br>

	* "P": Activa la animaci贸n por KeyFrames del ave 馃
		<div align = "center">
		<img src = img/captura23.png></img>
		</div>
		<br>

	* La animaci贸n del deportista no necesita una entrada del usuario 馃弮馃徑鈥嶁檪锔?
		<div align = "center">
		<img src = img/captura24.png></img>
		</div>
		<br>
	
En el siguiente video se pueden apreciar todas las animaciones ejecut谩ndose correctamente:

<div align = "center">
<a href = "https://youtu.be/0kX-gMDSoKM"><img src = img/captura25.png>Animaciones</a>
</div>
<br>

## **Recorrido Virtual por la casa**
En el caso de que el programa no pueda ejecutarse correctamente por motivos desconocidos, el siguiente video busca demostrar que el programa funciona de manera adecuada y sin errores. Adem谩s, el video tiene como prop贸sito hacer un recorrido por cada uno de los cuartos de la casa y mostrar los objetos que los componen.

<div align = "center">
<a href = "https://youtu.be/XWHkK6jfjIg"><img src = img/captura26.png>Recorrido Virtual</a>
</div>

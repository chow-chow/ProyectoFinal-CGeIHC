# **Manual de usuario** 📃

## **Proyecto Final CGeIHC** 💻
Proyecto Final para la materia de Computación Gráfica e Interacción Humano Computadora (Teoría).

## **Alumno:** 👦🏽
- Cruz Rangel Leonardo Said
- Número de cuenta: 316031062

### **Semestre 2023-1 | Grupo 05**

### **Requerimientos**
+ Para ejecución con Visual Studio 2022 con instalación de C++ o con el ejecutable .exe:
	+ Windows 7 (última actualización), Windows 8 (2919355), Windows 10 (versión 1703 o superior)
	+ Procesador: 1.8 GHz (recomendado 4 núcleos o más)
	+ 2.5 GB de memoria RAM (8 GB recomendado)
	+ 20 GB de espacio en disco (recomendado)
	+ Chip gráfico de mínimo 720p de resolución

### **Apertura y ejecución del proyecto**
Descargar el proyecto desde GitHub dando click al botón verde "Code" y seleccionando una de las opciones

<img src=img/captura1.png></img>

Si selecciona "Open with GitHub Desktop" deberá tener dicha aplicación instaada en su equipo y seguir los pasos para clonar el repositorio de manera local, una vez clonado saltar hasta ["Ejecución del archivo .exe"](#item1).

La selección "Download ZIP" descargará un archivo .zip del proyecto, habrá que descomprimirlo en su equipo, regresar a este manual y saltarse hasta ["Ejecución del archivo .exe"](#item1).

### ***Ejecución con Visual Studio*** 💻
Si se desea y se tiene instalado el IDE Visual Studio, se puede ejecutar la aplicación siguiendo los siguientes pasos: descargar el proyecto de GitHub y descomprimir la carpeta zip. Una vez hecho esto, abrir Visual Studio y seleccionar la opción "Abrir un proyecto o una solución".

<div align = "center">
<img src=img/captura2.png height = 400px></img>
</div>

Buscar el archivo "ProyectoFinal.sln" dentro de la carpeta descomprimida y dar clic en el botón de "Abrir".

<div align = "center">
<img src=img/captura3.png></img>
</div>

Antes de ejecutar el programa, es importante comprobar que todas las bibliotecas y configuraciones estén cargadas correctamente. Para hacer esto, se debe dirigir al explorador de soluciones, hacer clic derecho en el nombre del proyecto y seleccionar la opción de propiedades.

<div align = "center">
<img src=img/captura4.png height = 500px></img>
</div>

En el apartado de "General" verificar que el Conjunto de herramientas de la plataforma sea uno que se tenga descargado, puede ser v142 o v143.

<div align = "center">
<img src=img/captura5.png></img>
</div>

Dentro de "C/C++ --> General" verificar que la palabra <b>include</b> se encuentra en "Directorios de inclusión adicionales".

<div align = "center">
<img src=img/captura6.png></img>
</div>

En el "Vinculador --> General" verificar que la palabra <b>lib</b> se encuentra en "Directorios de bibliotecas adicionales".

<div align = "center">
<img src=img/captura7.png></img>
</div>

Finalmente, en "Vinculador --> Entrada" verificar que las dependencias <b>SDL2.lib;SDL2main.lib;assimp-vc141-mtd.lib;opengl32.lib;glfw3.lib;</b> estén incluidas en "Dependencias adicionales". De lo contrario, pegar el texto en negritas en dicho apartado, sin borrar las dependencias que ya se tengan.

<div align = "center">
<img src=img/captura8.png></img>
</div>

Para poner en ejecución el proyecto se debe seleccionar la opción "x86" en a barra superior y verificar que esté seleccionada la opción "Debug" como se muestra en la siguiente imagen.

<div align = "center">
<img src=img/captura9.png></img>
</div>

Ya puede ejecutarse el proyecto dando clic en el botón "Depurador local de Windows", esto abrirá la ventana del programa.

<a name="item1"></a>
### ***Ejecución del archivo .exe*** 🚀
Una vez que se ha clonado el proyecto o descomprimido el archivo .zip, se debe abrir la carpeta generada o ubicación del repositorio en el equipo y acceder a "ProyectoFinal\Release". Luego, se debe localizar el archivo "ProyectoFinal.exe" y hacer doble clic en él para ejecutar el programa.

<div align = "center">
<img src=img/captura10.png></img>
</div>

## **Interacción con el ambiente**🏠
Una vez que la ventana está abierta, se captura el mouse para que solo funcione dentro del espacio virtual. Como resultado, el cursor no es visible y el movimiento del mouse solo es posible dentro de la ventana. La interacción se lleva a cabo a través del teclado y el mouse de la computadora.

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
Baño en suite
</div>

<br>

<div align = "center">
<img src = img/captura18.png></img>
Baño general
</div>

<br>

<div align = "center">
<img src = img/captura19.png></img>
Patio trasero con piscina
</div>

#### Funciones del Teclado
* "Esc" : para salir de la ventana / terminar el programa. ❌

* Simulación de las teclas de adelante ⬆️, atrás ⬇️, izquierda ⬅️, derecha ➡️ para movimiento como sucede en los videojuegos:
    * "W" : mover la cámara hacia enfrente ⬆️. 
    * "S" : mover la cámara hacia atrás ⬇️. 
    * "A" : mover la cámara hacia la izquierda ⬅️.
    * "D" : mover la cámara hacia la derecha ➡️.

* Movimientos del mouse:
    * El deslizamiento del mouse 🔁 a la izquierda o derecha, arriba o abajo realiza el giro de la cámara 📷 en dicha dirección de deslizado, el field of view 🔍 se mueve como sucede con el cursor de la computadora.
    * Scroll del mouse reliza zoom + 🔍 moviéndolo hacia enfrente y zoom - 🔍 hacia atrás.
	
* Animaciones:
	* "SPACE": Activa la animación del vehículo 🚗
		<div align = "center">
		<img src = img/captura20.png></img>
		</div>
		<br>

	* "R": Restablece la animación del vehículo 🚗
		<div align = "center">
		<img src = img/captura21.png></img>
		Posición inicial del vehículo.
		</div>
		<br>

	* "5": Activa la animación del helicóptero de juguete a control remoto 🚁
		<div align = "center">
		<img src = img/captura22.png></img>
		</div>
		<br>

	* "P": Activa la animación por KeyFrames del ave 🦅
		<div align = "center">
		<img src = img/captura23.png></img>
		</div>
		<br>

	* La animación del deportista no necesita una entrada del usuario 🏃🏽‍♂️
		<div align = "center">
		<img src = img/captura24.png></img>
		</div>
		<br>
	
En el siguiente video se pueden apreciar todas las animaciones ejecutándose correctamente:

<div align = "center">
<a href = "https://youtu.be/0kX-gMDSoKM"><img src = img/captura25.png>Animaciones</a>
</div>
<br>

## **Recorrido Virtual por la casa**
En el caso de que el programa no pueda ejecutarse correctamente por motivos desconocidos, el siguiente video busca demostrar que el programa funciona de manera adecuada y sin errores. Además, el video tiene como propósito hacer un recorrido por cada uno de los cuartos de la casa y mostrar los objetos que los componen.

<div align = "center">
<a href = "https://youtu.be/XWHkK6jfjIg"><img src = img/captura26.png>Recorrido Virtual</a>
</div>

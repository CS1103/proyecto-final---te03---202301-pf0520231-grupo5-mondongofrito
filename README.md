# proyecto-final---te03---202301-pf0520231-grupo5-mondongofrito
proyecto-final---te03---202301-pf0520231-grupo5-mondongofrito created by GitHub Classroom
# Proyecto: Implementación del algoritmo Backpropagation para el reconocimiento de dígitos a mano

![image](https://github.com/CS1103/proyecto-final---te03---202301-pf0520231-grupo5-mondongofrito/assets/108534678/5d50c32b-4052-4bff-a024-01f764b46f5f)


En este proyecto, se implementará el algoritmo Backpropagation en C++ para reconocer dígitos manuscritos utilizando el conjunto de datos MNIST. El objetivo es diseñar e implementar una arquitectura de red neuronal, implementar los pases hacia adelante y hacia atrás, y optimizar la red utilizando el descenso de gradiente.

## Conjunto de datos MNIST

El conjunto de datos MNIST es una colección ampliamente utilizada de imágenes de dígitos escritos a mano. Consiste en 60,000 imágenes de entrenamiento y 10,000 imágenes de prueba, cada una de 28x28 píxeles en escala de grises. Cada imagen está etiquetada con el dígito correspondiente, que varía de 0 a 9.

## Arquitectura de red neuronal

Para este proyecto, se debe diseñar una arquitectura de red neuronal adecuada para el reconocimiento de dígitos. Una posible arquitectura puede incluir una capa de entrada con 784 neuronas (28x28 píxeles), una o varias capas ocultas y una capa de salida con 10 neuronas (correspondientes a los dígitos del 0 al 9).

## Implementación del algoritmo Backpropagation

El algoritmo Backpropagation consta de dos pasos principales: el pase hacia adelante (forward pass) y el pase hacia atrás (backward pass). Durante el pase hacia adelante, se propagan las entradas a través de la red neuronal, calculando las salidas de cada neurona utilizando una función de activación adecuada, como la función sigmoide. Durante el pase hacia atrás, se calcula el gradiente de la función de pérdida con respecto a los pesos y sesgos de la red, y se ajustan utilizando el descenso de gradiente.

## Optimización de la red utilizando descenso de gradiente

El descenso de gradiente es un algoritmo de optimización utilizado para ajustar los pesos y sesgos de la red neuronal con el fin de minimizar la función de pérdida. Se actualizan los pesos y sesgos en dirección opuesta al gradiente de la función de pérdida con respecto a ellos, multiplicados por una tasa de aprendizaje. Esto se repite en múltiples iteraciones (épocas) hasta que se logra convergencia y se obtiene una red neuronal entrenada.

## Implementación del proyecto

El proyecto se implementará en C++ y se proporciona una estructura básica de archivos para organizar el código:

- `neuron.h` y `neuron.cpp`: Contienen la definición y la implementación de la clase `Neuron`, que representa una neurona de la red neuronal.
- `network.h` y `network.cpp`: Contienen la definición y la implementación de la clase `Network`, que representa la red neuronal en su conjunto y contiene la lógica para el pase hacia adelante, el pase hacia atrás y la actualización de los pesos y sesgos.
- `main.cpp`: Contiene el código principal del proyecto, donde se crea la red neuronal, se realizan los pases hacia adelante y hacia atrás utilizando el conjunto de datos MNIST, y se evalúa el rendimiento de la red neuronal.

Se recomienda seguir las instrucciones en los comentarios del código para implementar y personalizar la red neuronal según tus necesidades y requisitos específicos.

¡Diviértete implementando el algoritmo Backpropagation para el reconocimiento de dígitos a mano!

# MondongoFrito - Digit Recognition

![Logo](/page/logo.png)


En este proyecto, se implementará el algoritmo Backpropagation en C++ para reconocer dígitos manuscritos utilizando el conjunto de datos MNIST. El objetivo es diseñar e implementar una arquitectura de red neuronal, implementar los forward y backward passes, y optimizar la red utilizando el descenso de gradiente.

## Conjunto de datos MNIST

El conjunto de datos MNIST es una amplia colección de imágenes de dígitos escritos a mano. Consiste de 60,000 imágenes de entrenamiento y 10,000 imágenes de prueba, cada una de 28x28 píxeles en escala de grises. Cada imagen está etiquetada con el dígito correspondiente, que varía de 0 a 9.

## Arquitectura de red neuronal

Para este proyecto, se debe diseñar una arquitectura de red neuronal adecuada para el reconocimiento de dígitos. Una posible arquitectura puede incluir una capa de entrada con 784 neuronas (28x28 píxeles), una o varias capas ocultas y una capa de salida con 10 neuronas (correspondientes a los dígitos del 0 al 9).

## Implementación del algoritmo Backpropagation

El algoritmo Backpropagation consta de dos pasos principales: el pase hacia adelante (forward pass) y el pase hacia atrás (backward pass). Durante el pase hacia adelante, se propagan las entradas a través de la red neuronal, calculando las salidas de cada neurona utilizando una función de activación adecuada, como la función sigmoide. Durante el pase hacia atrás, se calcula el gradiente de la función de pérdida con respecto a los pesos y sesgos de la red, y se ajustan utilizando el descenso de gradiente.

## Optimización de la red utilizando descenso de gradiente

El descenso de gradiente es un algoritmo de optimización utilizado para ajustar los pesos y sesgos de la red neuronal con el fin de minimizar la función de pérdida. Se actualizan los pesos y sesgos en dirección opuesta al gradiente de la función de pérdida con respecto a ellos, multiplicados por una tasa de aprendizaje. Esto se repite en múltiples iteraciones hasta que se logra convergencia y se obtiene una red neuronal entrenada.

## Requerimientos

Para compilar o ejecutar el programa, se requiere la versión 4.7.0 de OpenCV o una más reciente. Se está considerando incluir una instalación local con el ejecutable, aunque aún no se decide. Se recomienda, aunque no es completamente necesario, utilizar los compiladores especificados en la [guía de compilación](/COMPILINGSETUP.md).
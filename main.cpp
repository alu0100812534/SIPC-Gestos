#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/background_segm.hpp>

#include <stdio.h>
#include <string>
#include <iostream>

#include "MyBGSubtractorColor.hpp"
#include "HandGesture.hpp"

using namespace std;
using namespace cv;



int main(int argc, char** argv)
{

	Mat frame, bgmask, out_frame;



	//Abrimos la webcam

	VideoCapture cap;
	cap.open(1);
	if (!cap.isOpened())
	{
		printf("\nNo se puede abrir la c�mara\n");
		return -1;
	}
	int cont = 0;
	while (frame.empty()&& cont < 2000 ) {

<<<<<<< HEAD
                cap >> frame;
                ++cont;
        }
        if (cont >= 2000) {
                printf("No se ha podido leer un frame v�lido\n");
                exit(-1);
        }

	// Creamos las ventanas que vamos a usar en la aplicaci�n
=======
		cap >> frame;
		++cont;
	}
	if (cont >= 2000) {
		printf("No se ha podido leer un frame válido\n");
		exit(-1);
	}

	// Creamos las ventanas que vamos a usar en la aplicación
>>>>>>> 73e9a858d02deeb12299f215e260d626c83ac47b

	namedWindow("Reconocimiento");
	namedWindow("Fondo");
// creamos el objeto para la substracci�n de fondo
    MyBGSubtractorColor *mysub = new MyBGSubtractorColor(cap);
		mysub->LearnModel();

<<<<<<< HEAD
	// creamos el objeto para el reconocimiento de gestos

	// iniciamos el proceso de obtenci�n del modelo del fondo
=======
	// creamos el objeto para la substracción de fondo

	// creamos el objeto para el reconocimiento de gestos

	// iniciamos el proceso de obtención del modelo del fondo
>>>>>>> 73e9a858d02deeb12299f215e260d626c83ac47b


	for (;;)
	{
		cap >> frame;
		//flip(frame, frame, 1);
		if (frame.empty())
		{
			printf("Le�do frame vac�o\n");
			continue;
		}
		int c = cvWaitKey(40);
		if ((char)c == 'q') break;

		// obtenemos la m�scara del fondo con el frame actual

<<<<<<< HEAD
                // CODIGO 2.1
                // limpiar la m�scara del fondo de ruido
                //...
=======
		// CODIGO 2.1
		// limpiar la m�scara del fondo de ruido
		//...

>>>>>>> 73e9a858d02deeb12299f215e260d626c83ac47b

		// deteccion de las caracter�sticas de la mano

<<<<<<< HEAD
		// deteccion de las caracter�sticas de la mano

                // mostramos el resultado de la sobstracci�n de fondo

                // mostramos el resultado del reconocimento de gestos
=======
		// mostramos el resultado de la sobstracci�n de fondo

		// mostramos el resultado del reconocimento de gestos
>>>>>>> 73e9a858d02deeb12299f215e260d626c83ac47b

		imshow("Reconocimiento", frame);


	}

	destroyWindow("Reconocimiento");
	destroyWindow("Fondo");
	cap.release();
	return 0;
}
